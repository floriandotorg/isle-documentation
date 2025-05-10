// clang-format off

#ifndef MXSTL_H
#define MXSTL_H

#include <use_ansi.h>
#include <algorithm>
#include <deque>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>


#ifdef  _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,8)
#endif // _MSC_VER

/**
 * @class Deque
 * @brief [AI] Custom wrapper around std::deque providing consistent allocator usage and swap semantics.
 * @details [AI] Acts as a drop-in replacement for std::deque, using a specified allocator and providing an explicit swap function and friend overload for use throughout the LEGO Island codebase.
 */
template<class _TYPE>
class Deque : public deque<_TYPE, allocator<_TYPE> >
{
public:
  typedef Deque<_TYPE> _Myt; ///< [AI] Self type for use in member functions and templates. [AI]
  typedef allocator<_TYPE> _A; ///< [AI] Allocator type for contained elements. [AI]

  /**
   * @brief [AI] Constructs a Deque with an optional allocator.
   * @param _Al Allocator to use for storage. [AI]
   */
  explicit Deque(const _A& _Al = _A()) : deque<_TYPE, _A>(_Al)
  {}

  /**
   * @brief [AI] Constructs a Deque with a specified number of elements and initial value.
   * @param _N Number of elements. [AI]
   * @param _V Value to fill with. [AI]
   */
  explicit Deque(size_type _N, const _TYPE& _V = _TYPE()) : deque<_TYPE, _A>(_N, _V)
  {}

  /**
   * @brief [AI] Swaps the contents of this Deque with another.
   * @param _X Reference to the other Deque. [AI]
   */
  void swap(_Myt& _X)
  {
    deque<_TYPE, _A>::swap((deque<_TYPE, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap function for ADL-enabled efficient swapping.
   * @param _X First Deque. [AI]
   * @param _Y Second Deque. [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class List
 * @brief [AI] Custom wrapper around std::list providing consistent allocator usage and swap semantics.
 * @details [AI] Used for game-specific collections requiring linked list behavior.
 */
template<class _TYPE>
class List : public list<_TYPE, allocator<_TYPE> >
{
public:
  typedef List<_TYPE> _Myt; ///< [AI] Self type for member use. [AI]
  typedef allocator<_TYPE> _A; ///< [AI] Allocator type. [AI]

  /**
   * @brief [AI] Constructs an empty List.
   */
  explicit List() : list<_TYPE, _A>()
  {}

  /**
   * @brief [AI] Constructs a List with a specified number of elements and initial value.
   * @param _N Number of elements. [AI]
   * @param _V Value to fill with. [AI]
   */
  explicit List(size_type _N, const _TYPE& _V = _TYPE()) : list<_TYPE, _A>(_N, _V)
  {}

  /**
   * @brief [AI] Swaps the contents of this List with another.
   * @param _X Reference to the other List. [AI]
   */
  void swap(_Myt& _X)
  {
    list<_TYPE, _A>::swap((list<_TYPE, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap for efficient List swapping.
   * @param _X First List. [AI]
   * @param _Y Second List. [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class Map
 * @brief [AI] Custom wrapper for std::map with consistent allocator and customizable comparator.
 * @details [AI] Used as an associative container where fast ordered lookup is required in the game engine.
 */
template<class _K, class _TYPE, class _Pr>
class Map : public map<_K, _TYPE, _Pr, allocator<_TYPE> >
{
public:
  typedef Map<_K, _TYPE, _Pr> _Myt; ///< [AI] Self type [AI]
  typedef allocator<_TYPE> _A; ///< [AI] Allocator type [AI]

  /**
   * @brief [AI] Constructs an empty Map with an optional predicate.
   * @param _Pred Key comparator predicate [AI]
   */
  explicit Map(const _Pr& _Pred = _Pr())
    : map<_K, _TYPE, _Pr, _A>(_Pred)
  {}

  /**
   * @brief [AI] Swaps with another Map.
   * @param _X Reference to another Map of the same type [AI]
   */
  void swap(_Myt& _X)
  {
    map<_K, _TYPE, _Pr, _A>::swap((map<_K, _TYPE, _Pr, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap for Map.
   * @param _X First Map [AI]
   * @param _Y Second Map [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class Multimap
 * @brief [AI] Custom multimap supporting multiple values per key with custom allocator and comparator.
 * @details [AI] Used where duplicate keys are needed within the engine's associative containers.
 */
template<class _K, class _TYPE, class _Pr>
class Multimap : public multimap<_K, _TYPE, _Pr, allocator<_TYPE> >
{
public:
  typedef Multimap<_K, _TYPE, _Pr> _Myt; ///< [AI] Self type [AI]
  typedef allocator<_TYPE> _A; ///< [AI] Allocator type [AI]

  /**
   * @brief [AI] Constructs an empty Multimap with optional predicate.
   * @param _Pred Key comparator predicate [AI]
   */
  explicit Multimap(const _Pr& _Pred = _Pr()) : multimap<_K, _TYPE, _Pr, _A>(_Pred)
  {}

  /**
   * @brief [AI] Swaps with another Multimap.
   * @param _X Reference to another Multimap [AI]
   */
  void swap(_Myt& _X)
  {
    multimap<_K, _TYPE, _Pr, _A>::swap((multimap<_K, _TYPE, _Pr, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap for Multimap.
   * @param _X First Multimap [AI]
   * @param _Y Second Multimap [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class Set
 * @brief [AI] Set wrapper utilizing a custom allocator and comparator.
 * @details [AI] Used for storing unique, ordered keys—commonly used for sets of IDs or other unique game elements.
 */
template<class _K, class _Pr>
class Set : public set<_K, _Pr, allocator<_K> >
{
public:
  typedef Set<_K, _Pr> _Myt; ///< [AI] Self type [AI]
  typedef allocator<_K> _A; ///< [AI] Allocator type [AI]

  /**
   * @brief [AI] Constructs an empty Set with an optional predicate.
   * @param _Pred Comparator predicate for ordering [AI]
   */
  explicit Set(const _Pr& _Pred = _Pr()) : set<_K, _Pr, _A>(_Pred)
  {}

  /**
   * @brief [AI] Swaps with another Set.
   * @param _X Reference to another Set [AI]
   */
  void swap(_Myt& _X)
  {
    set<_K, _Pr, _A>::swap((set<_K, _Pr, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap for Set.
   * @param _X First Set [AI]
   * @param _Y Second Set [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class Multiset
 * @brief [AI] Multiset wrapper for storing ordered collections of non-unique elements with a custom allocator.
 * @details [AI] Used for grouped elements where duplicates are permitted, such as a collection of repeated resource tokens.
 */
template<class _K, class _Pr>
class Multiset : public multiset<_K, _Pr, allocator<_K> >
{
public:
  typedef Multiset<_K, _Pr> _Myt; ///< [AI] Self type [AI]
  typedef allocator<_K> _A; ///< [AI] Allocator type [AI]

  /**
   * @brief [AI] Constructs an empty Multiset with an optional predicate.
   * @param _Pred Comparator predicate [AI]
   */
  explicit Multiset(const _Pr& _Pred = _Pr())
    : multiset<_K, _Pr, _A>(_Pred)
  {}

  /**
   * @brief [AI] Swaps with another Multiset.
   * @param _X Reference to another Multiset [AI]
   */
  void swap(_Myt& _X)
  {
    multiset<_K, _Pr, _A>::swap((multiset<_K, _Pr, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap for Multiset.
   * @param _X First Multiset [AI]
   * @param _Y Second Multiset [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class Vector
 * @brief [AI] Custom vector supporting allocator and custom swap semantics.
 * @details [AI] Used for contiguous storage of objects, as a standard replacement of std::vector, with explicit allocator management to support the LEGO Island memory model.
 */
template<class _TYPE>
class Vector : public vector<_TYPE, allocator<_TYPE> >
{
public:
  typedef Vector<_TYPE> _Myt; ///< [AI] Self type [AI]
  typedef allocator<_TYPE> _A; ///< [AI] Allocator type [AI]

  /**
   * @brief [AI] Constructs an empty Vector with an optional allocator.
   * @param _Al Allocator to use [AI]
   */
  explicit Vector(const _A& _Al = _A()) : vector<_TYPE, _A>(_Al)
  {}

  /**
   * @brief [AI] Swaps the content with another Vector.
   * @param _X Reference to another Vector [AI]
   */
  void swap(_Myt& _X)
  {
    vector<_TYPE, _A>::swap((vector<_TYPE, _A>&)_X);
  }

  /**
   * @brief [AI] Friend swap for Vector.
   * @param _X First Vector [AI]
   * @param _Y Second Vector [AI]
   */
  friend void swap(_Myt& _X, _Myt& _Y)
  {
    _X.swap(_Y);
  }
};

/**
 * @class Priority_queue
 * @brief [AI] Customized priority queue for use with game-specific containers and allocators.
 * @details [AI] Useful for game systems where prioritized event or action dispatching is needed.
 */
template<class _C, class _Pr>
class Priority_queue : public priority_queue<_C::value_type, _C, _Pr, _C::allocator_type>
{
public:
  typedef _C::value_type _TYPE; ///< [AI] Element type [AI]
  typedef _C::allocator_type _A; ///< [AI] Allocator type [AI]
  typedef _C::allocator_type allocator_type; ///< [AI] Allocator type (synonym) [AI]

  /**
   * @brief [AI] Constructs an empty Priority_queue with optional comparator and allocator.
   * @param _X Comparator for priority [AI]
   * @param _Al Allocator to use [AI]
   */
  explicit Priority_queue(const _Pr& _X = _Pr(), const _C::allocator_type& _Al = _C::allocator_type()) : priority_queue<_C::value_type, _C, _Pr, _C::allocator_type>(_X, _Al)
  {}
};

/**
 * @class Queue
 * @brief [AI] Customized queue for compatibility with the engine's allocator requirements.
 * @details [AI] Used for FIFO processing of game events and action queues.
 */
template<class _C>
class Queue : public queue<_C::value_type, _C, _C::allocator_type>
{};

/**
 * @class Stack
 * @brief [AI] Customized stack for compatibility with the engine's allocator and usage patterns.
 * @details [AI] Used for LIFO storage, e.g. undo/redo or recursive world/event simulation stacks.
 */
template<class _C>
class Stack : public stack<_C::value_type, _C, _C::allocator_type>
{};

/**
 * @def deque
 * @brief [AI] Macro alias for Deque<T>, replacing std::deque<T>.
 */

/**
 * @def list
 * @brief [AI] Macro alias for List<T>, replacing std::list<T>.
 */

/**
 * @def map
 * @brief [AI] Macro alias for Map<K, T, Pr>, replacing std::map<T>.
 */

/**
 * @def multimap
 * @brief [AI] Macro alias for Multimap<K, T, Pr>, replacing std::multimap<T>.
 */

/**
 * @def set
 * @brief [AI] Macro alias for Set<K, Pr>, replacing std::set<K>.
 */

/**
 * @def multiset
 * @brief [AI] Macro alias for Multiset<K, Pr>, replacing std::multiset<K>.
 */

/**
 * @def vector
 * @brief [AI] Macro alias for Vector<T>, replacing std::vector<T>.
 */

/**
 * @def priority_queue
 * @brief [AI] Macro alias for Priority_queue<C, Pr>, replacing std::priority_queue.
 */

/**
 * @def queue
 * @brief [AI] Macro alias for Queue<C>, replacing std::queue.
 */

/**
 * @def stack
 * @brief [AI] Macro alias for Stack<C>, replacing std::stack.
 */
#define deque Deque
#define list List
#define map Map
#define multimap Multimap
#define set Set
#define multiset Multiset
#define vector Vector
#define priority_queue Priority_queue
#define queue Queue
#define stack Stack

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif // MXSTL_H

// clang-format on
