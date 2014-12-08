#pragma once

struct ccolor
{
  struct fore
  {
    static const char* black;
    static const char* blue;
    static const char* red;
    static const char* magenta;
    static const char* green;
    static const char* cyan;
    static const char* yellow;
    static const char* white;
    static const char* console;

    static const char* lightblack;
    static const char* lightblue;
    static const char* lightred;
    static const char* lightmagenta;
    static const char* lightgreen;
    static const char* lightcyan;
    static const char* lightyellow;
    static const char* lightwhite;

  private:
    fore() = delete;
  };

  struct back
  {
    static const char* black;
    static const char* blue;
    static const char* red;
    static const char* magenta;
    static const char* green;
    static const char* cyan;
    static const char* yellow;
    static const char* white;
    static const char* console;

    static const char* lightblack;
    static const char* lightblue;
    static const char* lightred;
    static const char* lightmagenta;
    static const char* lightgreen;
    static const char* lightcyan;
    static const char* lightyellow;
    static const char* lightwhite;

  private:
    back() = delete;
  };

  static const char* error;
  static const char* warning;
  static const char* info;

  static char* color(int attr, int fg, int bg);

  static const char* reset;
  static const char* bold;
  static const char* underline;

private:
  ccolor() = delete;
};
