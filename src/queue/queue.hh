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
#include <utility>
#include <cassert>

#include "traits/iter_traits.hh"

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
  enum { DEFAULT_SIZE = 8, SIZE_MULT = 1 };

public:
  /**
   * Aliases
   */
  using value_type = T;
  using allocator_type = Alloc;
  using reference = typename Alloc::reference;
  using const_reference = typename Alloc::const_reference;
  using pointer = typename Alloc::pointer;
  using const_pointer = typename Alloc::const_pointer;
  using iterator = PriorityQueueIter<value_type>;
  // TODO: determine how to write const iterator version
  //using const_iterator = const PriorityQueueIter<value_type>;
  //using difference_type = typename std::iterator_traits<iterator>::difference_type;
  using size_type = size_t;
  using compare_type = Compare;
  // TODO: create alias for reverse iterator

  /**
   * Initialize
   */
  explicit PriorityQueue();
  explicit PriorityQueue(const size_t size);
  explicit PriorityQueue(const allocator_type& alloc);
  explicit PriorityQueue(const compare_type& comp);
#if 0
  explicit PriorityQueue
    (const size_t size = DEFAULT_SIZE,
     const compare_type& comp = compare_type(),
     const allocator_type& alloc = allocator_type());
#endif
  template
  <
    typename InputIterator,
    typename = typename std::enable_if<is_input_iter<InputIterator>::value>::type
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
  size_t capacity() const noexcept;

  /**
   * object functionality
   */
  std::string toString() const;
  template<typename Hash = std::hash<T>>
  size_type hashCode(const Hash& hsh = Hash()) const noexcept;

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
  void bubbleDown(int index = 0) noexcept;
  void bubbleUp(int index) noexcept;
  int familyMin(const T& val, int index) const noexcept;


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
  template<typename U, typename CompareU, typename AllocU>
  friend std::ostream&
  operator<<(std::ostream&, const PriorityQueue<U, CompareU, AllocU>&);

  template<typename U, typename CompareU, typename AllocU>
  friend bool operator==
    (const PriorityQueue<U, CompareU, AllocU>&,
     const PriorityQueue<U, CompareU, AllocU>&) noexcept;

  template<typename U> friend class PriorityQueueIter;
};

////////////////////////////////////////////////////////////////////////////////
// Class Definition
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Default ctor.
 * @details The priority queue is initialized with an array of size 8, but none of
 * the elements in the dynamic array are constructed.
 * @throw May throw memory allocatoin failure.
 */
template<typename T, typename Compare, typename  Alloc>
PriorityQueue<T, Compare, Alloc>::
PriorityQueue()
  : mPtr(nullptr),
    mAlloc(),
    mCompare(),
    mSize(DEFAULT_SIZE),
    mCount()
{
  mPtr = mAlloc.allocate(mSize);
}

/**
 * @brief Constructor with one parameter.
 * @param size The starting capacity of the heap.
 * @throw May throw memory allocatoin failure.
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
  mPtr = mAlloc.allocate(mSize);
}

/**
 * @brief Constructor with one parameter.
 * @param alloc The allocator for the heap.
 * @throw May throw memory allocatoin failure.
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
  mPtr = mAlloc.allocate(mSize);
}

/**
 * @brief Constructor with one parameter.
 * @param comp The object used to compare items.
 * @throw May throw memory allocatoin failure.
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
  mPtr = mAlloc.allocate(mSize);
}

#if 0
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
  mPtr = mAlloc.allocate(mSize);
}
#endif

/**
 * @brief Iterator range constructor.
 * @param first The iterator to the beginning of the range.
 * @param last One past the last iterator.
 * @throw May throw memory allocatoin failure.
 */
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
    emplace(*first);
    ++first;
  }
}

/**
 * @brief Destructor.
 */
template<typename T, typename Compare, typename Alloc>
PriorityQueue<T, Compare, Alloc>::
~PriorityQueue() noexcept
{
  for (auto i = mCount - 1; i >= 0; --i)
    mAlloc.destroy(mPtr+i);

  mAlloc.deallocate(mPtr, mSize);
}

/**
 * @brief Determine if the queue is empty.
 * @return True if the queue is empty, false otherwise.
 */
template<typename T, typename Compare, typename Alloc>
inline bool PriorityQueue<T, Compare, Alloc>::
empty() const noexcept
{
  return mCount == 0;
}

/**
 * @brief Get the size of the queue.
 * @return The size of the queue.
 */
template<typename T, typename Compare, typename Alloc>
inline size_t PriorityQueue<T, Compare, Alloc>::
size() const noexcept
{
  return static_cast<size_t>(mCount);
}

/**
 * @brief Get the top value.
 * @return A copy of the top value in the queue.
 */
template<typename T, typename Compare, typename Alloc>
inline T PriorityQueue<T, Compare, Alloc>::
top() const noexcept
{
  return mPtr[0];
}

/**
 * @brief Push an item into the queue by copying the value.
 * @param value The value copied and pushed into the queue.
 */
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
push(const value_type& value)
{
  emplace(value);
}

/**
 * @brief Push an item into the queue by moving it.
 * @param value The value moved into the queue.
 */
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
push(value_type&& value)
{
  emplace(std::move(value));
}

/**
 * @brief Push an item into the queue by constructing it in place.
 * @param args The arguments used to construct the object.
 */
template<typename T, typename Compare, typename Alloc>
  template<typename... Args>
inline void PriorityQueue<T, Compare, Alloc>::
emplace(Args&&... args)
{
  if (mCount < mSize) {
    mAlloc.construct(mPtr+mCount, std::forward<Args>(args)...);
    ++mCount;
    bubbleUp(mCount-1);
    return;
  }

  auto oldSize = mSize;
  mSize <<= SIZE_MULT;
  auto tmp = mAlloc.allocate(mSize);

  // copy items
  // TODO: catch any exceptions that may arise during construction
  for (int i = 0; i < mCount; ++i)
    mAlloc.construct(tmp+i, mPtr[i]);

  // destroy copies of items
  for (int i = 0; i < mCount; ++i)
    mAlloc.destroy(mPtr+i);

  // swap and release resources
  mAlloc.deallocate(mPtr, oldSize);
  mPtr = tmp;

  // emplace args
  mAlloc.construct(mPtr+mCount, std::forward<Args>(args)...);
  ++mCount;
  bubbleUp(mCount-1);
}

/**
 * @brief Remove the top value from the heap.
 * @throw Does not throw if the destructor for <em>T</em> does not throw.
 */
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
pop() noexcept(std::is_nothrow_destructible<T>::value)
{
  if (mCount == 0)
    return;

  auto last = mCount - 1;

  // No need to shuffle items if the last value is being popped
  if (!last) {
    mAlloc.destroy(mPtr+last);
    --mCount;
    return;
  }

  mPtr[0] = mPtr[last];
  mAlloc.destroy(mPtr+last);
  --mCount;
  bubbleDown();
}

/**
 * @return The current capacity of the priority queue.
 * @details The capacity refers to the total number of items that can be added to
 * the queue before it needs to be reallocated to a different chunk of memory.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline size_t PriorityQueue<T, Compare, Alloc>::
capacity() const noexcept
{
  return static_cast<size_t>(mSize);
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
  template<typename Hash>
inline size_t PriorityQueue<T, Compare, Alloc>::
hashCode(const Hash& hsh) const noexcept
{
  return 0;
}

/**
 * @brief Get parent of the node at the given index.
 * @detail If negative, then index refers to root node.
 * @param index The index of the child node.
 * @return The index of the left child.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
parent(int index) const noexcept
{
  assert(index >= 0 && index < mCount);
  return (index - 1) >> 1;
}

/**
 * @brief Get the left child of the node at the given index.
 * @detail If greater then <em>mSize</em>, then index refers to left most child
 *  node.
 * @param index The index of the parent node.
 * @return The index of the left child.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
leftChild(int index) const noexcept
{
  assert(index >= 0 && index < mCount);
  return (index << 1) + 1;
}

/**
 * @brief Get the right child of the node at the given index.
 * @detail If greater then <em>mSize</em>, then index refers to right most child
 *  node.
 * @param index The index of the parent node.
 * @return The index of the right child.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
rightChild(int index) const noexcept
{
  assert(index >= 0 && index < mCount);
  return (index << 1) + 2;
}

/**
 * @brief Bubble down a node to its right place.
 * @param index The index of the current node.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
bubbleDown(int index) noexcept
{
  assert(index >= 0 && index < mCount);

  auto val = mPtr[index];
  auto i = familyMin(val, index);

  while (i != index)
  {
    mPtr[index] = mPtr[i];
    index = i;
    i = familyMin(val, index);
  }

  mPtr[index] = val;
}

/**
 * @brief Bubble up a node up the heap to its right place.
 * @param index The index of the node.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline void PriorityQueue<T, Compare, Alloc>::
bubbleUp(int index) noexcept
{
  assert(index >= 0 && index < mCount);

  auto val = mPtr[index];
  auto i = parent(index);

  while (i >= 0 && mCompare(val, mPtr[i]))
  {
    mPtr[index] = mPtr[i];
    index = i;
    i = parent(index);
  }  

  mPtr[index] = val;
}

/**
 * @brief Return the index of the node with the value that should be at the top
 *  between a parent and its two children.
 * @param index The index of the parent node.
 * @return The index of the node with the value that should at the top.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
inline int PriorityQueue<T, Compare, Alloc>::
familyMin(const T& val, int index) const noexcept
{
  assert(index >= 0 && index < mCount);

  auto lc = leftChild(index);
  auto rc = rightChild(index);

  if (lc < mCount && mCompare(mPtr[lc], val))
    return mCompare(mPtr[lc], mPtr[rc]) ? lc : rc;

  if (rc < mCount && mCompare(mPtr[rc], val))
    return rc;

  return index;
}

/**
 * @brief Output operator.
 * @detail Items are ordered like they are stored internally.
 * @param os The output stream.
 * @param pq The priority queue.
 * @return A reference to the output stream.
 */
template<typename T, typename Compare, typename Alloc>
std::ostream&
operator<<(std::ostream& os, const PriorityQueue<T, Compare, Alloc>& pq)
{
  os << "{";

  auto last = pq.mCount - 1;
  for (int i = 0; i < last; ++i)
    os << pq.mPtr[i] << ", ";

  os << pq.mPtr[last] << "}";

  return os;
}

/**
 * @brief Equality operator.
 * @param pq1 The first priority queue.
 * @param pq2 The second priority queue.
 * @return True if the queues are equal, false otherwise.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
bool operator==
  (const PriorityQueue<T, Compare, Alloc>& pq1,
   const PriorityQueue<T, Compare, Alloc>& pq2) noexcept
{
  if (pq1.mCount != pq2.mCount)
    return false;

  for (int i = 0; i < pq1.mCount; ++i)
  {
    if (pq1.mPtr[i] != pq2.mPtr[i])
      return false;
  }

  return true;
}

/**
 * @brief Non-equality operator.
 * @param pq1 The first priority queue.
 * @param pq2 The second priority queue.
 * @return True if the queues are not equal, false otherwise.
 * @throw Never throws.
 */
template<typename T, typename Compare, typename Alloc>
bool operator!=
  (const PriorityQueue<T, Compare, Alloc>& pq1,
   const PriorityQueue<T, Compare, Alloc>& pq2) noexcept
{
  return !(pq1 == pq2);
}

} // namespace ospp

#endif /* _QUEUE_H */
