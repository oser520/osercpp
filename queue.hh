/**
 * @file queue.hh
 * @author Omar A Serrano
 * @date 2016-01-15
 */
#ifndef _QUEUE_H
#define _QUEUE_H

#include <memory>
#include <functional>
#include <string>
#include <iterator>
#include <type_traits>

namespace ospp {

// forward declaration
template<typename T> class PriorityQueueIter;

/**
 * PriorityQueue.
 */
template
<
  typename T,
  typename Compare = std::less<T>,
  typename Alloc = std::allocator<T>
>
class PriorityQueue
{
  /**
   * Default size for priority queue and size multiplier when items don't fit
   * in priority queue
   */
  enum { DEFAULT_SIZE = 8, SIZE_MULT = 2 };

public:
  /**
   * Aliases
   */
  using value_type = T;
  using allocator_type = Alloc;
  using reference = Alloc::reference;
  using const_reference = Alloc::const_reference;
  using pointer = Alloc::pointer;
  using const_pointer = Alloc::const_pointer;
  using iterator = PriorityQueueIter<value_type>;
  // TODO: determine how to write const iterator version
  //using const_iterator = const PriorityQueueIter<value_type>;
  using difference_type = std::iterator_traits<iterator>::difference_type;
  using size_type = size_t;
  using compare_type = Compare;
  // TODO: create alias for reverse iterator

  /**
   * Initialize
   */
  explicit PriorityQueue(const size_t size);
  explicit PriorityQueue(const allocator_type& alloc);
  explicit PriorityQueue(const compare_type& comp);
  explicit PriorityQueue
    (const size_t size = DEFAULT_SIZE,
     const compare_type& comp = compare_type(),
     const allocator_type& alloc = allocator_type());
  template
  <
    typename InputIterator,
    typename = std::enable_if<is_input_iter<InputIterator>::value>::type
  >
  PriorityQueue(InputIterator first, InputIterator last);

  /**
   * Copy Construct
   */
  PriorityQueue(const PriorityQueue& cont);
  PriorityQueue(PriorityQueue&& cont);


  /**
   * Assignment
   */
  PriorityQueue& operator=(const PriorityQueue& cont);
  PriorityQueue& operator=(PriorityQueue&& cont);

  /**
   * Destructor
   */
  ~PriorityQueue() noexcept;

  /**
   * priority queue functionality
   */
  bool empty() const noexcept;
  size_type size() const noexcept;
  value_type top() const noexcept;
  void push(const value_type& value);
  void push(value_type&& value);
  template<typename... Args>
  void emplace(Args&&... args);
  void pop();

  /**
   * object functionality
   */
  std::string toString() const;
  size_type hashCode() const noexcept;

private:
  /**
   * Pointer to the array of values in the priority queue.
   */
  pointer mPtr;

  /**
   * The allocator.
   */
  allocator_type mAlloc;

  /**
   * The comparator.
   */
  compare_type mCompare;

  /**
   * The maximum number of elements that may be held.
   */
  int mSize;

  /**
   * The number of items held by the priority queue.
   */
  int mItems;

  /**
   * friends
   */
  friend std::ostream& operator<<(std::ostream&, const PriorityQueue&);
  friend bool operator==(const PriorityQueue&, const PriorityQueue&) noexcept;
  friend template<typename T> class PriorityQueueIter;
};

} // namespace ospp

#endif /* _QUEUE_H */
