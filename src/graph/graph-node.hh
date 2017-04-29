#pragma once

#include <list>


namespace ospp {


template<typename TData>
struct GraphNode {
  TData data{};
  std::list<GraphNode> neighbors;

  GraphNode() = default;
  GraphNode(const TData &data);
};


template<typename TData>
GraphNode<TData>::GraphNode(const TData &data)
  : data{data}, neighbors{}
{}


} // namespace ospp
