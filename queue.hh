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

/**
 * forward declaration
 */
template<typename T> class PriorityQueueIter;

////////////////////////////////////////////////////////////////////////////////
// Class Declaration
////////////////////////////////////////////////////////////////////////////////

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
  void pop() noexcept(std::is_nothrow_destructible<T>::value);

  /**
   * object functionality
   */
  std::string toString() const;
  template<typename Hash = std::hash<T>>
  size_type hashCode() const noexcept;

private:

  /**
   * indexing functions
   */
  int parent(int index) const noexcept;
  int leftChild(int index) const noexcept;
  int rightChild(int index) const noexcept;

  /**
   * movement functions
   */
  void bubbleDown(int index) noexcept;
  void bubbleUp(int index) noexcept;

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
  int mCount;

  /**
   * friends
   */
  friend std::ostream& operator<<(std::ostream&, const PriorityQueue&);
  friend bool operator==(const PriorityQueue&, const PriorityQueue&) noexcept;
  friend template<typename T> class PriorityQueueIter;
};

////////////////////////////////////////////////////////////////////////////////
// Class Definition
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructor with one parameter.
 * @param size The starting size of the heap.
 */
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

/**
 * @brief Constructor with one parameter.
 * @param alloc The allocator for the heap.
 */
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

/**
 * @brief Constructor with one parameter.
 * @param comp The object used to compare items.
 */
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

template<typename T, typename Compare, typename Alloc>
inline bool PriorityQueue<T, Compare, Alloc>::
empty() const noexcept
{
  return mCount == 0;
}

template<typename T, typename Compare, typename Alloc>
inline size_t PriorityQueue<T, Compare, Alloc>::
size() const noexcept
{
  return static_cast<size_t>(mSize);
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline T PriorityQueue<T, Compare, Alloc>::
top() const noexcept
{
  return mPtr[0];
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
push(const value_type& value)
{
  return;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
push(value_type&& value)
{
  return;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
  template<typename Args...>
inline void PriorityQueue<T, Compare, Alloc>::
emplace(Args&&... args)
{
  return;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
pop() noexcept(std::is_nothrow_destructible<T>::value)
{
  return;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
pop() noexcept(std::is_nothrow_destructible<T>::value)
{
  return;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline std::string PriorityQueue<T, Compare, Alloc>::
toString() const
{
  return std::string();
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
  template<typename Hash>>
inline size_t PriorityQueue<T, Compare, Alloc>::
hashCode(const Hash& hsh)) const noexcept
{
  return 0;
}

/**
 * @brief Get parent of the node at the given index.
 * @param index The index of the child node.
 * @return The index of the left child.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
parent(int index) const noexcept
{
  assert(index >= 0 && index < mCount);
  return (index - 1) >> 2;
}

/**
 * @brief Get the left child of the node at the given index.
 * @param index The index of the parent node.
 * @return The index of the left child.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
leftChild(int index) const noexcept
{
  assert(index >= 0 && index < mCount);
  return (index << 2) + 1;
}

/**
 * @brief Get the right child of the node at the given index.
 * @param index The index of the parent node.
 * @return The index of the right child.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
rightChild(int index) const noexcept
{
  assert(index >= 0 && index < mCount);
  return (index << 2) + 2;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
bubbleDown(int index) const noexcept
{
  return;
}

// TODO: implement
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
bubbleUp(int index) const noexcept
{
  return;
}

} // namespace ospp

#endif /* _QUEUE_H */
