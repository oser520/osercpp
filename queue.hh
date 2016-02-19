/**
 * @file queue.hh
 * @author Omar A Serrano
 * @date 2016-01-15
 */

#ifndef _QUEUE_H
#define _QUEUE_H

namespace ospp {

// forward declaration
template<typename T> class PriorityQueueIter;

/**
 * PriorityQueue.
 */
template<typename T, typename Alloc = std::allocator<T>>
class PriorityQueue
{
  friend template<typename T> class PriorityQueueIter;
public:
  // aliases
  using value_type = T;
  using allocator_type = Alloc;
  using reference = Alloc::reference;
  using const_reference = Alloc::const_reference;
  using pointer = Alloc::pointer;
  using const_pointer = Alloc::const_pointer;
  using iterator = PriorityQueueIter<value_type>;
  using const_iterator = const PriorityQueueIter<value_type>;
  using difference_type = std::iterator_traits<iterator>::difference_type;
  using size_type = size_t;
  // TODO: create alias for reverse iterator
private:
};

} // namespace ospp

#endif /* _QUEUE_H */
