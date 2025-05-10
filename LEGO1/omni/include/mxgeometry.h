#ifndef MXGEOMETRY_H
#define MXGEOMETRY_H

#include "mxlist.h"
#include "mxutilities.h"

/**
 * @brief [AI] 2D point class templated on its coordinate type.
 * @details [AI] Represents a point in 2D space, supporting basic arithmetic and access/modification of its coordinates.
 * @tparam T [AI] Underlying type for coordinates (e.g., int, float, etc.)
 */
template <class T>
class MxPoint {
protected:
	T m_x; /**< @brief [AI] X coordinate. */
	T m_y; /**< @brief [AI] Y coordinate. */

public:
	/**
	 * @brief [AI] Default constructor, does not initialize coordinates.
	 */
	MxPoint() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_p [AI] The point to copy.
	 */
	MxPoint(const MxPoint& p_p)
	{
		m_x = p_p.m_x;
		m_y = p_p.m_y;
	}

	/**
	 * @brief [AI] Constructor with explicit coordinates.
	 * @param p_x [AI] X coordinate.
	 * @param p_y [AI] Y coordinate.
	 */
	MxPoint(T p_x, T p_y)
	{
		m_x = p_x;
		m_y = p_y;
	}

	/**
	 * @brief [AI] Get X coordinate.
	 */
	T GetX() const { return m_x; }

	/**
	 * @brief [AI] Get Y coordinate.
	 */
	T GetY() const { return m_y; }

	/**
	 * @brief [AI] Set X coordinate.
	 * @param p_x [AI] The new X coordinate.
	 */
	void SetX(T p_x) { m_x = p_x; }

	/**
	 * @brief [AI] Set Y coordinate.
	 * @param p_y [AI] The new Y coordinate.
	 */
	void SetY(T p_y) { m_y = p_y; }

	/**
	 * @brief [AI] Add another point's coordinates to this point.
	 * @param p_p [AI] The point to add.
	 */
	void operator+=(const MxPoint& p_p)
	{
		m_x += p_p.m_x;
		m_y += p_p.m_y;
	}

	/**
	 * @brief [AI] Subtract another point's coordinates from this point.
	 * @param p_p [AI] The point to subtract.
	 */
	void operator-=(const MxPoint& p_p)
	{
		m_x -= p_p.m_x;
		m_y -= p_p.m_y;
	}

	/**
	 * @brief [AI] Add another point, returning the result.
	 * @param p_p [AI] The point to add.
	 */
	MxPoint operator+(const MxPoint& p_p) const { return MxPoint(m_x + p_p.m_x, m_y + p_p.m_y); }

	/**
	 * @brief [AI] Subtract another point, returning the result.
	 * @param p_p [AI] The point to subtract.
	 */
	MxPoint operator-(const MxPoint& p_p) const { return MxPoint(m_x - p_p.m_x, m_y - p_p.m_y); }
};

/**
 * @brief [AI] 2D size class templated on its value type.
 * @details [AI] Represents the width and height of a 2D object or region.
 * @tparam T [AI] Underlying type for width/height (e.g., int, float, etc.)
 */
template <class T>
class MxSize {
protected:
	T m_width;  /**< @brief [AI] Width. */
	T m_height; /**< @brief [AI] Height. */

public:
	/**
	 * @brief [AI] Default constructor, does not initialize size.
	 */
	MxSize() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_s [AI] The size to copy.
	 */
	MxSize(const MxSize& p_s)
	{
		m_width = p_s.m_width;
		m_height = p_s.m_height;
	}
	/**
	 * @brief [AI] Constructor with explicit width and height.
	 * @param p_width [AI] Width value.
	 * @param p_height [AI] Height value.
	 */
	MxSize(T p_width, T p_height)
	{
		m_width = p_width;
		m_height = p_height;
	}
	/**
	 * @brief [AI] Get the width.
	 */
	T GetWidth() const { return m_width; }

	/**
	 * @brief [AI] Get the height.
	 */
	T GetHeight() const { return m_height; }

	/**
	 * @brief [AI] Set the width.
	 * @param p_width [AI] New width.
	 */
	void SetWidth(T p_width) { m_width = p_width; }

	/**
	 * @brief [AI] Set the height.
	 * @param p_height [AI] New height.
	 */
	void SetHeight(T p_height) { m_height = p_height; }
};

/**
 * @brief [AI] 2D rectangle class templated on its value type.
 * @details [AI] Represents a rectangular region using left/top/right/bottom coordinates.
 * @tparam T [AI] Underlying type for coordinates (e.g., int, float, etc.)
 */
template <class T>
class MxRect {
protected:
	T m_left;   /**< @brief [AI] Left edge (minimum x). */
	T m_top;    /**< @brief [AI] Top edge (minimum y). */
	T m_right;  /**< @brief [AI] Right edge (maximum x). */
	T m_bottom; /**< @brief [AI] Bottom edge (maximum y). */

public:
	/**
	 * @brief [AI] Default constructor, does not initialize rectangle.
	 */
	MxRect() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_r [AI] Rectangle to copy.
	 */
	MxRect(const MxRect& p_r)
	{
		m_left = p_r.m_left;
		m_top = p_r.m_top;
		m_right = p_r.m_right;
		m_bottom = p_r.m_bottom;
	}

	/**
	 * @brief [AI] Construct from coordinates.
	 * @param p_l [AI] Left.
	 * @param p_t [AI] Top.
	 * @param p_r [AI] Right.
	 * @param p_b [AI] Bottom.
	 */
	MxRect(T p_l, T p_t, T p_r, T p_b)
	{
		m_left = p_l;
		m_top = p_t;
		m_right = p_r;
		m_bottom = p_b;
	}

	/**
	 * @brief [AI] Construct from point and size.
	 * @param p_p [AI] Top-left point.
	 * @param p_s [AI] Size.
	 */
	MxRect(const MxPoint<T>& p_p, const MxSize<T>& p_s)
	{
		m_left = p_p.GetX();
		m_top = p_p.GetY();
		m_right = p_p.GetX() + p_s.GetWidth() - 1;
		m_bottom = p_p.GetY() + p_s.GetHeight() - 1;
	}

	/**
	 * @brief [AI] Get the left edge.
	 */
	T GetLeft() const { return m_left; }
	/**
	 * @brief [AI] Set the left edge.
	 * @param p_left [AI] Value to set.
	 */
	void SetLeft(T p_left) { m_left = p_left; }

	/**
	 * @brief [AI] Get the top edge.
	 */
	T GetTop() const { return m_top; }
	/**
	 * @brief [AI] Set the top edge.
	 * @param p_top [AI] Value to set.
	 */
	void SetTop(T p_top) { m_top = p_top; }

	/**
	 * @brief [AI] Get the right edge.
	 */
	T GetRight() const { return m_right; }
	/**
	 * @brief [AI] Set the right edge.
	 * @param p_right [AI] Value to set.
	 */
	void SetRight(T p_right) { m_right = p_right; }

	/**
	 * @brief [AI] Get the bottom edge.
	 */
	T GetBottom() const { return m_bottom; }
	/**
	 * @brief [AI] Set the bottom edge.
	 * @param p_bottom [AI] Value to set.
	 */
	void SetBottom(T p_bottom) { m_bottom = p_bottom; }

	/**
	 * @brief [AI] Get the rectangle's width.
	 * @details [AI] (right - left + 1)
	 */
	T GetWidth() const { return (m_right - m_left + 1); }

	/**
	 * @brief [AI] Get the rectangle's height.
	 * @details [AI] (bottom - top + 1)
	 */
	T GetHeight() const { return (m_bottom - m_top + 1); }

	/**
	 * @brief [AI] Get the top-left point of the rectangle.
	 */
	MxPoint<T> GetLT() const { return MxPoint<T>(m_left, m_top); }

	/**
	 * @brief [AI] Get the bottom-right point of the rectangle.
	 */
	MxPoint<T> GetRB() const { return MxPoint<T>(m_right, m_bottom); }

	/**
	 * @brief [AI] Returns whether the rectangle is empty or not.
	 * @details [AI] Returns true if left >= right or top >= bottom.
	 */
	MxBool Empty() const { return m_left >= m_right || m_top >= m_bottom; }

	/**
	 * @brief [AI] Test whether a point is inside the rectangle (inclusive).
	 * @param p_p [AI] Point to check.
	 */
	MxBool Contains(const MxPoint<T>& p_p) const
	{
		return p_p.GetX() >= m_left && p_p.GetX() <= m_right && p_p.GetY() >= m_top && p_p.GetY() <= m_bottom;
	}

	/**
	 * @brief [AI] Returns whether this rectangle intersects another.
	 * @param p_r [AI] Rectangle to test.
	 */
	MxBool Intersects(const MxRect& p_r) const
	{
		return p_r.m_right > m_left && p_r.m_left < m_right && p_r.m_bottom > m_top && p_r.m_top < m_bottom;
	}

	/**
	 * @brief [AI] Assignment operator.
	 * @param p_r [AI] Rectangle to copy.
	 */
	void operator=(const MxRect& p_r)
	{
		m_left = p_r.m_left;
		m_top = p_r.m_top;
		m_right = p_r.m_right;
		m_bottom = p_r.m_bottom;
	}

	/**
	 * @brief [AI] Equality operator.
	 * @param p_r [AI] Rectangle to compare.
	 */
	MxBool operator==(const MxRect& p_r) const
	{
		return m_left == p_r.m_left && m_top == p_r.m_top && m_right == p_r.m_right && m_bottom == p_r.m_bottom;
	}

	/**
	 * @brief [AI] Inequality operator.
	 * @param p_r [AI] Rectangle to compare.
	 */
	MxBool operator!=(const MxRect& p_r) const { return !operator==(p_r); }

	/**
	 * @brief [AI] Translate the rectangle by a point, in-place.
	 * @param p_p [AI] Point to add to corners.
	 */
	void operator+=(const MxPoint<T>& p_p)
	{
		m_left += p_p.GetX();
		m_top += p_p.GetY();
		m_right += p_p.GetX();
		m_bottom += p_p.GetY();
	}

	/**
	 * @brief [AI] Translate the rectangle by the negative of a point, in-place.
	 * @param p_p [AI] Point to subtract from corners.
	 */
	void operator-=(const MxPoint<T>& p_p)
	{
		m_left -= p_p.GetX();
		m_top -= p_p.GetY();
		m_right -= p_p.GetX();
		m_bottom -= p_p.GetY();
	}

	/**
	 * @brief [AI] Intersect rectangle in-place with another.
	 * @details [AI] Produces the intersection of this rectangle with another (the overlapping area).
	 * @param p_r [AI] Rectangle to intersect with.
	 */
	void operator&=(const MxRect& p_r)
	{
		m_left = Max(p_r.m_left, m_left);
		m_top = Max(p_r.m_top, m_top);
		m_right = Min(p_r.m_right, m_right);
		m_bottom = Min(p_r.m_bottom, m_bottom);
	}

	/**
	 * @brief [AI] Unites this rectangle with another in-place.
	 * @details [AI] Produces the bounding rectangle covering both.
	 * @param p_r [AI] Rectangle to unite with.
	 */
	void operator|=(const MxRect& p_r)
	{
		m_left = Min(p_r.m_left, m_left);
		m_top = Min(p_r.m_top, m_top);
		m_right = Max(p_r.m_right, m_right);
		m_bottom = Max(p_r.m_bottom, m_bottom);
	}

	/**
	 * @brief [AI] Returns a translated rectangle.
	 * @param p_p [AI] Amount to translate by.
	 */
	MxRect operator+(const MxPoint<T>& p_p) const
	{
		return MxRect(m_left + p_p.GetX(), m_top + p_p.GetY(), m_left + p_p.GetX(), m_bottom + p_p.GetY());
	}

	/**
	 * @brief [AI] Returns a translated rectangle (by negative).
	 * @param p_p [AI] Amount to translate by.
	 */
	MxRect operator-(const MxPoint<T>& p_p) const
	{
		return MxRect(m_left - p_p.GetX(), m_top - p_p.GetY(), m_left - p_p.GetX(), m_bottom - p_p.GetY());
	}

	/**
	 * @brief [AI] Returns the intersection of this rectangle and another.
	 * @param p_r [AI] Rectangle to intersect.
	 */
	MxRect operator&(const MxRect& p_r) const
	{
		return MxRect(
			Max(p_r.m_left, m_left),
			Max(p_r.m_top, m_top),
			Min(p_r.m_right, m_right),
			Min(p_r.m_bottom, m_bottom)
		);
	}

	/**
	 * @brief [AI] Returns the bounding rectangle (union) of this and another.
	 * @param p_r [AI] Rectangle to unite.
	 */
	MxRect operator|(const MxRect& p_r) const
	{
		return MxRect(
			Min(p_r.m_left, m_left),
			Min(p_r.m_top, m_top),
			Max(p_r.m_right, m_right),
			Max(p_r.m_bottom, m_bottom)
		);
	}
};

/******************************* MxPoint16 **********************************/

/**
 * @brief [AI] 2D point with 16-bit signed integer coordinates.
 * @details [AI] Used for pixel or grid coordinates with 16-bit precision.
 */
class MxPoint16 : public MxPoint<MxS16> {
public:
	/**
	 * @brief [AI] Default constructor.
	 */
	MxPoint16() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_p [AI] Point to copy.
	 */
	MxPoint16(const MxPoint16& p_p) : MxPoint<MxS16>(p_p) {}

	/**
	 * @brief [AI] Constructor with explicit coordinates.
	 * @param p_x [AI] X coordinate.
	 * @param p_y [AI] Y coordinate.
	 */
	MxPoint16(MxS16 p_x, MxS16 p_y) : MxPoint<MxS16>(p_x, p_y) {}
};

/**
 * @brief [AI] List class for pointers to MxPoint16.
 * @details [AI] Used to manage collections of 16-bit points with optional ownership.
 */
class MxPoint16List : public MxPtrList<MxPoint16> {
public:
	/**
	 * @brief [AI] Construct with ownership flag.
	 * @param p_ownership [AI] If true, destroys pointers on list destruction.
	 */
	MxPoint16List(MxBool p_ownership) : MxPtrList<MxPoint16>(p_ownership) {}
};

/**
 * @brief [AI] Cursor for iterating MxPoint16List.
 * @details [AI] Used to traverse a list of point pointers.
 */
class MxPoint16ListCursor : public MxPtrListCursor<MxPoint16> {
public:
	/**
	 * @brief [AI] Construct for a given list.
	 * @param p_list [AI] List to traverse.
	 */
	MxPoint16ListCursor(MxPoint16List* p_list) : MxPtrListCursor<MxPoint16>(p_list) {}
};

/******************************* MxPoint32 **********************************/

/**
 * @brief [AI] 2D point with 32-bit signed integer coordinates.
 * @details [AI] Used for large coordinate spaces with 32-bit precision.
 */
class MxPoint32 : public MxPoint<MxS32> {
public:
	/**
	 * @brief [AI] Default constructor.
	 */
	MxPoint32() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_p [AI] Point to copy.
	 */
	MxPoint32(const MxPoint32& p_p) : MxPoint<MxS32>(p_p) {}

	/**
	 * @brief [AI] Constructor with explicit coordinates.
	 * @param p_x [AI] X coordinate.
	 * @param p_y [AI] Y coordinate.
	 */
	MxPoint32(MxS32 p_x, MxS32 p_y) : MxPoint<MxS32>(p_x, p_y) {}
};

/**
 * @brief [AI] List class for pointers to MxPoint32.
 * @details [AI] Used to manage collections of 32-bit points.
 */
class MxPoint32List : public MxPtrList<MxPoint32> {
public:
	/**
	 * @brief [AI] Construct with ownership flag.
	 * @param p_ownership [AI] If true, owns and destroys contained pointers.
	 */
	MxPoint32List(MxBool p_ownership) : MxPtrList<MxPoint32>(p_ownership) {}
};

/**
 * @brief [AI] Cursor for iterating MxPoint32List.
 * @details [AI] Used to traverse a list of 32-bit point pointers.
 */
class MxPoint32ListCursor : public MxPtrListCursor<MxPoint32> {
public:
	/**
	 * @brief [AI] Construct for a given list.
	 * @param p_list [AI] List to traverse.
	 */
	MxPoint32ListCursor(MxPoint32List* p_list) : MxPtrListCursor<MxPoint32>(p_list) {}
};

/******************************** MxSize16 **********************************/

/**
 * @brief [AI] Size with 16-bit signed integer width and height.
 * @details [AI] Used for storing 2D dimensions in a compact form.
 */
class MxSize16 : public MxSize<MxS16> {
public:
	/**
	 * @brief [AI] Default constructor.
	 */
	MxSize16() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_s [AI] Size to copy.
	 */
	MxSize16(const MxSize16& p_s) : MxSize<MxS16>(p_s) {}

	/**
	 * @brief [AI] Constructor with specified width and height.
	 * @param p_width [AI] Width value.
	 * @param p_height [AI] Height value.
	 */
	MxSize16(MxS16 p_width, MxS16 p_height) : MxSize<MxS16>(p_width, p_height) {}
};

/**
 * @brief [AI] List class for pointers to MxSize16.
 * @details [AI] Used to manage collections of compact sizes.
 */
class MxSize16List : public MxPtrList<MxSize16> {
public:
	/**
	 * @brief [AI] Construct with ownership flag.
	 * @param p_ownership [AI] If true, owns and destroys contained pointers.
	 */
	MxSize16List(MxBool p_ownership) : MxPtrList<MxSize16>(p_ownership) {}
};

/**
 * @brief [AI] Cursor for iterating MxSize16List.
 * @details [AI] Used for traversing MxSize16 pointers in a list.
 */
class MxSize16ListCursor : public MxPtrListCursor<MxSize16> {
public:
	/**
	 * @brief [AI] Construct for a given list.
	 * @param p_list [AI] List to traverse.
	 */
	MxSize16ListCursor(MxSize16List* p_list) : MxPtrListCursor<MxSize16>(p_list) {}
};

/******************************** MxSize32 **********************************/

/**
 * @brief [AI] Size with 32-bit signed integer width and height.
 * @details [AI] Represents a 2D size with large range.
 */
class MxSize32 : public MxSize<MxS32> {
public:
	/**
	 * @brief [AI] Default constructor.
	 */
	MxSize32() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_s [AI] Size to copy.
	 */
	MxSize32(const MxSize32& p_s) : MxSize<MxS32>(p_s) {}

	/**
	 * @brief [AI] Constructor with specified width and height.
	 * @param p_width [AI] Width value.
	 * @param p_height [AI] Height value.
	 */
	MxSize32(MxS32 p_width, MxS32 p_height) : MxSize<MxS32>(p_width, p_height) {}
};

/**
 * @brief [AI] List class for pointers to MxSize32.
 * @details [AI] Used for managing collections of sizes with 32-bit values.
 */
class MxSize32List : public MxPtrList<MxSize32> {
public:
	/**
	 * @brief [AI] Construct with ownership flag.
	 * @param p_ownership [AI] If true, owns and destroys contained pointers.
	 */
	MxSize32List(MxBool p_ownership) : MxPtrList<MxSize32>(p_ownership) {}
};

/**
 * @brief [AI] Cursor for iterating MxSize32List.
 * @details [AI] Used to traverse 32-bit size pointer lists.
 */
class MxSize32ListCursor : public MxPtrListCursor<MxSize32> {
public:
	/**
	 * @brief [AI] Construct for a given list.
	 * @param p_list [AI] List to traverse.
	 */
	MxSize32ListCursor(MxSize32List* p_list) : MxPtrListCursor<MxSize32>(p_list) {}
};

/******************************** MxRect16 **********************************/

/**
 * @brief [AI] Rectangle using 16-bit signed integer coordinates.
 * @details [AI] Represents a rectangle suitable for UI or grid spaces with 16-bit range.
 */
class MxRect16 : public MxRect<MxS16> {
public:
	/**
	 * @brief [AI] Default constructor.
	 */
	MxRect16() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_r [AI] Rectangle to copy.
	 */
	MxRect16(const MxRect16& p_r) : MxRect<MxS16>(p_r) {}

	/**
	 * @brief [AI] Constructor from coordinates.
	 * @param p_l [AI] Left coordinate.
	 * @param p_t [AI] Top coordinate.
	 * @param p_r [AI] Right coordinate.
	 * @param p_b [AI] Bottom coordinate.
	 */
	MxRect16(MxS16 p_l, MxS16 p_t, MxS16 p_r, MxS16 p_b) : MxRect<MxS16>(p_l, p_t, p_r, p_b) {}

	/**
	 * @brief [AI] Construct a rectangle from point and size.
	 * @param p_p [AI] Point (top-left).
	 * @param p_s [AI] Size.
	 */
	MxRect16(MxPoint16& p_p, MxSize16& p_s) : MxRect<MxS16>(p_p, p_s) {}
};

/**
 * @brief [AI] List for pointers to MxRect16 rectangles.
 */
class MxRect16List : public MxPtrList<MxRect16> {
public:
	/**
	 * @brief [AI] Construct with ownership flag.
	 * @param p_ownership [AI] If true, destroys elements on deletion.
	 */
	MxRect16List(MxBool p_ownership) : MxPtrList<MxRect16>(p_ownership) {}
};

/**
 * @brief [AI] Cursor for iterating lists of MxRect16 pointers.
 */
class MxRect16ListCursor : public MxPtrListCursor<MxRect16> {
public:
	/**
	 * @brief [AI] Construct for a given list.
	 * @param p_list [AI] List to traverse.
	 */
	MxRect16ListCursor(MxRect16List* p_list) : MxPtrListCursor<MxRect16>(p_list) {}
};

/******************************** MxRect32 **********************************/

/**
 * @brief [AI] Rectangle using 32-bit signed integer coordinates.
 * @details [AI] Used for describing large regions of space or layers in the engine.
 */
class MxRect32 : public MxRect<MxS32> {
public:
	/**
	 * @brief [AI] Default constructor.
	 */
	MxRect32() {}

	/**
	 * @brief [AI] Copy constructor.
	 * @param p_r [AI] Rectangle to copy.
	 */
	MxRect32(const MxRect32& p_r) : MxRect<MxS32>(p_r) {}

	/**
	 * @brief [AI] Construct from explicit coordinates.
	 * @param p_l [AI] Left coordinate.
	 * @param p_t [AI] Top coordinate.
	 * @param p_r [AI] Right coordinate.
	 * @param p_b [AI] Bottom coordinate.
	 */
	MxRect32(MxS32 p_l, MxS32 p_t, MxS32 p_r, MxS32 p_b) : MxRect<MxS32>(p_l, p_t, p_r, p_b) {}

#ifndef COMPAT_MODE
	/**
	 * @brief [AI] Construct using MxPoint32 and MxSize32.
	 * @param p_p [AI] Top-left point.
	 * @param p_s [AI] Size.
	 */
	MxRect32(MxPoint32& p_p, MxSize32& p_s) : MxRect<MxS32>(p_p, p_s) {}
#else
	/**
	 * @brief [AI] Construct using MxPoint32 and MxSize32 (const overload).
	 * @param p_p [AI] Top-left point.
	 * @param p_s [AI] Size.
	 */
	MxRect32(const MxPoint32& p_p, const MxSize32& p_s) : MxRect<MxS32>(p_p, p_s) {}
#endif
};

/**
 * @brief [AI] List for pointers to MxRect32 rectangles.
 * @details [AI] Enables collections of 32-bit rectangle region descriptions.
 */
class MxRect32List : public MxPtrList<MxRect32> {
public:
	/**
	 * @brief [AI] Construct with ownership.
	 * @param p_ownership [AI] If true, will destroy contained objects.
	 */
	MxRect32List(MxBool p_ownership) : MxPtrList<MxRect32>(p_ownership) {}
};

/**
 * @brief [AI] Cursor for iterating lists of MxRect32 pointers.
 */
class MxRect32ListCursor : public MxPtrListCursor<MxRect32> {
public:
	/**
	 * @brief [AI] Construct for a given list.
	 * @param p_list [AI] List to traverse.
	 */
	MxRect32ListCursor(MxRect32List* p_list) : MxPtrListCursor<MxRect32>(p_list) {}
};

#endif // MXGEOMETRY_H
