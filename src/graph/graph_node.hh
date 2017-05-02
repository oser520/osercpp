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


} // namespace ospp
