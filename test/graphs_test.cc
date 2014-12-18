#include <gtest/gtest.h>

#include <deque>
#include <functional>
#include <map>
#include <queue>

#include <camshaft/graphs.hh>

using namespace std;

TEST(GraphsTest, basics)
{
  map<int,vector<int>> incidenceList {
    {1, {2, 3}},
    {2, {3}},
    {3, {1, 4}},
    {4, {2}}
  };

  vector<pair<string,int>> path = findPath<int,string>(1, 4, [&](const int from)
  {
    const vector<int>& v = incidenceList.find(from)->second;

    queue<pair<string,int>> result;

    for (auto const& to : v)
    {
      stringstream str;
      str << from << "->" << to;
      result.emplace(str.str(), to);
    }

    return result;
  });

  // NOTE even though a shorter path exists, it finds the longer one due to the ordering of edges provided by the callback
  ASSERT_EQ(3, path.size());
  EXPECT_EQ(make_pair(string("1->2"), 2), path[0]);
  EXPECT_EQ(make_pair(string("2->3"), 3), path[1]);
  EXPECT_EQ(make_pair(string("3->4"), 4), path[2]);
}
