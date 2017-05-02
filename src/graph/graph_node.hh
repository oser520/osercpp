#pragma once

#include <functional>
#include <list>
#include <set>


namespace ospp {


template<typename TData>
struct GraphNode {
  using GraphNodeRef = std::reference_wrapper<GraphNode>;
  TData data{};
  std::list<GraphNodeRef> neighbors;

  GraphNode() = default;
  GraphNode(const TData &data);
};


template<typename TData>
GraphNode<TData>::GraphNode(const TData &data)
  : data{data}, neighbors{}
{}


template<typename TData, typename TFringe>
bool
pathExists(GraphNode<TData> start, GraphNode<TData> goal)
{
  using NodeType = GraphNode<TData>;
  std::set<TData> visited;
  TFringe fringe;
  fringe.push(start);
  while (not fringe.empty()) {
    auto& node = fringe.next();
    if (node.data == goal.data)
      return true;
    visited.insert(node);
    for (NodeType& n : node.neighbors) {
      if (visited.find(n) == visited.end() and not fringe.contains(n))
        fringe.push(n);
    }
  }
  return false;
}


} // namespace ospp
