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

#include "iter_traits.hh"

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
  size_t mSize;

  /**
   * The number of items held by the priority queue.
   */
  size_t mCount;

  /**
   * friends
   */
  friend std::ostream& operator<<(std::ostream&, const PriorityQueue&);
  friend bool operator==(const PriorityQueue&, const PriorityQueue&) noexcept;
  friend template<typename T> class PriorityQueueIter;
};

// ctor
template<typename T, typename Compare, typename Alloc>
PriorityQueue<T, Compare, Alloc>::
PriorityQueue(const size_t size)
  : mPtr(nullptr),
    mAlloc(),
    mCompare(),
    mSize(size),
    mCount()
{
  assert(mSize > 0);
  mPtr = mAlloc.allocate(static_cast<size_t>(mSize));
}

// ctor
template<typename T, typename Compare, typename Alloc>
PriorityQueue<T, Compare, Alloc>::
PriorityQueue(const allocator_type& alloc)
  : mPtr(nullptr),
    mAlloc(alloc),
    mCompare(),
    mSize(DEFAULT_SIZE),
    mCount()
{
  mPtr = mAlloc.allocate(static_cast<size_t>(mSize));
}

// ctor
template<typename T, typename Compare, typename  Alloc>
PriorityQueue<T, Compare, Alloc>::
PriorityQueue(const compare_type& comp)
  : mPtr(nullptr),
    mAlloc(),
    mCompare(comp),
    mSize(DEFAULT_SIZE),
    mCount()
{
  mPtr = mAlloc.allocate(static_cast<size_t>(mSize));
}

// ctor
template<typename T, typename Compare, typename Alloc>
PriorityQueue<T, Compare, Alloc>::
PriorityQueue
  (const size_t size,
   const compare_type& comp,
   const allocator_type& alloc)
  : mPtr(nullptr),
    mAlloc(alloc),
    mCompare(comp),
    mSize(size),
    mCount()
{
  assert(size > 0);
  mPtr = mAlloc.allocate(static_cast<size_t>(mSize));
}

// ctor
template<typename T, typename Compare, typename Alloc>
  template<typename InputIterator, typename>
PriorityQueue<T, Compare, Alloc>::
PriorityQueue(InputIterator first, InputIterator last)
  : mPtr(nullptr),
    mAlloc(),
    mCompare(),
    mSize(DEFAULT_SIZE),
    mCount()
{
  mPtr = mAlloc.allocate(mSize);

  while (first != last)
  {
    if (mCount == mSize)
    {
      // increase the size
      mSize <<= SIZE_MULT;
      auto tmp = mAlloc.allocate(mSize);

      // copy items
      for (size_t i = 0; i < mCount; ++i)
        mAlloc.construct(tmp+i, mPtr[i]);

      // destroy copies of items
      for (size_t i = 0; i < mCount; ++i)
        mAlloc.destroy(mPtr+i);

      mAlloc.deallocate(mPtr);
      mPtr = tmp;
    }

    mAlloc.construct(mPtr+mCount, *first);
    ++mCount;
    ++first;
  }

  // TODO: heapify array
  heapify();
}

} // namespace ospp

#endif /* _QUEUE_H */
