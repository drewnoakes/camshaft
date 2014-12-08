#pragma once

// adapted from boost::any

#include <algorithm>

class any
{
public:
  any() noexcept
    : content(0)
  {}

  template<typename ValueType>
  any(const ValueType& value)
    : content(new holder<typename std::remove_cv<typename std::decay<const ValueType>::type>::type>(value))
  {}

  any(const any& other)
    : content(other.content ? other.content->clone() : nullptr)
  {}

  // Move constructor
  any(any&& other) noexcept
    : content(other.content)
  {
    other.content = 0;
  }

  // Perfect forwarding of ValueType
  template<typename ValueType>
  any(ValueType&& value,
      typename std::enable_if<!std::is_same<any&,ValueType>::type>::type* = 0, // disable if value has type `any&`
      typename std::enable_if<!std::is_const<ValueType>::type>::type* = 0) // disable if value has type `const ValueType&&`
  : content(new holder<typename std::decay<ValueType>::type>(static_cast<ValueType&&>(value)))
  {}

  ~any() noexcept
  {
    delete content;
  }

  any& swap(any& rhs) noexcept
  {
    std::swap(content, rhs.content);
    return *this;
  }

  any& operator =(const any& rhs)
  {
    any(rhs).swap(*this);
    return *this;
  }

  // move assignment
  any& operator =(any&& rhs) noexcept
  {
    rhs.swap(*this);
    any().swap(rhs);
    return *this;
  }

  // Perfect forwarding of ValueType
  template<class ValueType>
  any& operator =(ValueType&& rhs)
  {
    any(static_cast<ValueType&&>(rhs)).swap(*this);
    return *this;
  }

  bool empty() const noexcept
  {
    return !content;
  }

  template<typename T>
  bool is() const noexcept
  {
    return content && content->type() == typeid(T);
  }

  void clear() noexcept
  {
    any().swap(*this);
  }

  const std::type_info& type() const noexcept
  {
    return content ? content->type() : typeid(void);
  }

  class placeholder
  {
  public:
    virtual ~placeholder() = default;
    virtual const std::type_info& type() const noexcept = 0;
    virtual placeholder* clone() const = 0;
  };

  template<typename ValueType>
  class holder : public placeholder
  {
  public:
    holder(const ValueType& value)
      : held(value)
    {}

    holder(ValueType&& value)
      : held(static_cast<ValueType&&>(value))
    {}

    const std::type_info& type() const noexcept override
    {
      return typeid(ValueType);
    }

    placeholder* clone() const override
    {
      return new holder(held);
    }

    ValueType held;

  private:
    holder& operator=(const holder&) = delete;
  };

private:
  template<typename ValueType>
  friend ValueType* any_cast(any*) noexcept;

  template<typename ValueType>
  friend ValueType* unsafe_any_cast(any*) noexcept;

  placeholder* content;
};

inline void swap(any& lhs, any& rhs) noexcept
{
  lhs.swap(rhs);
}

class bad_any_cast : public std::bad_cast
{
public:
  const char* what() const noexcept override
  {
    return "bad_any_cast: failed conversion using any_cast";
  }
};

template<typename ValueType>
ValueType* any_cast(any* operand) noexcept
{
  return operand && (operand->type() == typeid(ValueType) || operand->type() == typeid(typename std::remove_cv<ValueType>::type))
    ? &static_cast<typename any::holder<typename std::remove_cv<ValueType>::type>*>(operand->content)->held
    : nullptr;
}

template<typename ValueType>
inline const ValueType* any_cast(const any* operand) noexcept
{
  return any_cast<ValueType>(const_cast<any*>(operand));
}

template<typename ValueType>
ValueType any_cast(any& operand)
{
  typedef typename std::remove_reference<ValueType>::type nonref;

  nonref* result = any_cast<nonref>(&operand);
  if (!result)
    throw bad_any_cast();

  // Attempt to avoid construction of a temporary object in cases when
  // `ValueType` is not a reference. Example:
  // `static_cast<std::string>(*result);`
  // which is equal to `std::string(*result);`
  typedef typename std::add_lvalue_reference<ValueType>::type ref_type;

  return static_cast<ref_type>(*result);
}

template<typename ValueType>
inline ValueType any_cast(const any& operand)
{
  typedef typename std::remove_reference<ValueType>::type nonref;
  return any_cast<const nonref&>(const_cast<any&>(operand));
}

template<typename ValueType>
inline ValueType any_cast(any&& operand)
{
  static_assert(
    std::is_rvalue_reference<ValueType&&>::value /*true if ValueType is rvalue or just a value*/
      || std::is_const<typename std::remove_reference<ValueType>::type>::value,
    "any_cast shall not be used for getting nonconst references to temporary objects"
  );
  return any_cast<ValueType>(operand);
}

// Note: The "unsafe" versions of any_cast are not part of the
// public interface and may be removed at any time. They are
// required where we know what type is stored in the any and can't
// use typeid() comparison, e.g., when our types may travel across
// different shared libraries.
template<typename ValueType>
inline ValueType* unsafe_any_cast(any* operand) noexcept
{
  return &static_cast<any::holder <ValueType>*>(operand->content)->held;
}

template<typename ValueType>
inline const ValueType* unsafe_any_cast(const any* operand) noexcept
{
  return unsafe_any_cast<ValueType>(const_cast<any*>(operand));
}
