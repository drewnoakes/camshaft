#pragma once

#include <deque>
#include <functional>
#include <map>
#include <queue>

template<typename Vertex, typename Edge>
std::vector<std::pair<Edge,Vertex>> findPath(
  const Vertex from,
  const Vertex to,
  std::function<std::queue<std::pair<Edge,Vertex>>(const Vertex)> adj)
{
  std::deque<std::queue<std::pair<Edge,Vertex>>> path; // stack containing current path
  std::set<Vertex> expanded {from};                    // set of visited (and completed) vertices

  path.push_back(adj(from));

  while (!path.empty())
  {
    auto& headQueue = path.back();

    if (headQueue.empty())
    {
      // We have followed all outbound paths from this vertex. Pop and drop back a level.
      path.pop_back();
      continue;
    }

    auto& headEdge = headQueue.front();

    if (headEdge.second == to)
    {
      // We found our solution
      break;
    }

    if (expanded.find(headEdge.second) != expanded.end())
    {
      // We have already visited this edge's target vertex
      headQueue.pop();
      continue;
    }

    // Follow this vertex's outbound edges
    path.push_back(adj(headEdge.second));

    expanded.insert(headEdge.second);
  }

  // Build result path by picking the front element at each level in the path
  std::vector<std::pair<Edge,Vertex>> result;
  for (const auto& pathLevel : path)
    result.push_back(pathLevel.front());
  return result;
}
