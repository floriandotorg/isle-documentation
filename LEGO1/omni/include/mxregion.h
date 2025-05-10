#ifndef __MXREGION_H
#define __MXREGION_H

#include "decomp.h"
#include "mxcore.h"
#include "mxgeometry.h"
#include "mxlist.h"

// SIZE 0x08
/**
 * @brief [AI] Represents a 1D segment defined by a minimum and maximum integer value. This class is used in region and span decomposition to denote contiguous or adjacent ranges along one axis.
 */
class MxSegment {
protected:
	MxS32 m_min; ///< @brief [AI] Lower boundary of the segment (inclusive). [AI]
	MxS32 m_max; ///< @brief [AI] Upper boundary of the segment (exclusive). [AI]

public:
	/**
	 * @brief [AI] Constructs a new segment with the specified minimum and maximum boundaries.
	 * @param p_min Lower bound of the segment (inclusive). [AI]
	 * @param p_max Upper bound of the segment (exclusive). [AI]
	 */
	MxSegment(MxS32 p_min, MxS32 p_max)
	{
		m_min = p_min;
		m_max = p_max;
	}

	/**
	 * @brief [AI] Returns the lower boundary of the segment (inclusive).
	 * @return The minimum boundary value. [AI]
	 */
	MxS32 GetMin() { return m_min; }

	/**
	 * @brief [AI] Returns the upper boundary of the segment (exclusive).
	 * @return The maximum boundary value. [AI]
	 */
	MxS32 GetMax() { return m_max; }

	/**
	 * @brief [AI] Creates a copy of the current segment.
	 * @return A pointer to the newly created MxSegment instance. [AI]
	 */
	MxSegment* Clone() { return new MxSegment(m_min, m_max); }

	/**
	 * @brief [AI] Attempt to merge this segment with the specified segment, if they are adjacent or overlapping.
	 * @param p_seg Reference to a segment to attempt to merge. [AI]
	 * @return TRUE if segments were merged, FALSE otherwise. [AI]
	 */
	MxBool Combine(MxSegment& p_seg);

	/**
	 * @brief [AI] Checks if this segment is adjacent to another (i.e., ends where the other begins or vice versa).
	 * @param p_seg Reference to the segment to check adjacency with. [AI]
	 * @return TRUE if segments are adjacent, FALSE otherwise. [AI]
	 */
	MxBool Adjacent(MxSegment& p_seg) { return m_max == p_seg.m_min || m_min == p_seg.m_max; }

	/**
	 * @brief [AI] Determines if this segment horizontally intersects a given rectangle, interpreted as an interval comparison.
	 * @param p_rect Rectangle whose horizontal range is compared. [AI]
	 * @return TRUE if there is an overlap, FALSE otherwise. [AI]
	 */
	MxBool IntersectsH(MxRect32& p_rect) { return p_rect.GetRight() > m_min && p_rect.GetTop() < m_max; }

	/**
	 * @brief [AI] Equality operator: checks if this segment has identical boundaries to the specified segment.
	 * @param p_seg Reference to segment for the comparison. [AI]
	 * @return TRUE if the segments are equal, FALSE otherwise. [AI]
	 */
	MxBool operator==(MxSegment& p_seg) { return m_min == p_seg.m_min && m_max == p_seg.m_max; }

	/**
	 * @brief [AI] Inequality operator: checks if this segment differs from the specified segment by its boundaries.
	 * @param p_seg Reference to segment for the comparison. [AI]
	 * @return TRUE if the segments differ, FALSE otherwise. [AI]
	 */
	MxBool operator!=(MxSegment& p_seg) { return !operator==(p_seg); }
};

// VTABLE: LEGO1 0x100dcc40
// VTABLE: BETA10 0x101c2628
// class MxCollection<MxSegment *>

// VTABLE: LEGO1 0x100dcc58
// VTABLE: BETA10 0x101c2610
// class MxList<MxSegment *>

// VTABLE: LEGO1 0x100dcc70
// VTABLE: BETA10 0x101c25f8
// class MxPtrList<MxSegment>

// VTABLE: LEGO1 0x100dcc88
// VTABLE: BETA10 0x101c25e0
// SIZE 0x18
/**
 * @brief [AI] List container for segments; stores pointers to MxSegment objects and may take ownership depending on construction.
 */
class MxSegmentList : public MxPtrList<MxSegment> {
public:
	/**
	 * @brief [AI] Constructs a segment list that takes ownership and deletes segments on destruction/removal.
	 */
	MxSegmentList() : MxPtrList<MxSegment>(TRUE) {}

	// SYNTHETIC: LEGO1 0x100c4e90
	// SYNTHETIC: BETA10 0x1014c1a0
	// MxSegmentList::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dcbf8
// VTABLE: BETA10 0x101c25b0
// class MxPtrListCursor<MxSegment>

// VTABLE: LEGO1 0x100dcc28
// VTABLE: BETA10 0x101c25c8
// class MxListCursor<MxSegment *>

// VTABLE: LEGO1 0x100dcc10
// VTABLE: BETA10 0x101c2598
/**
 * @brief [AI] Cursor for traversing an MxSegmentList; allows sequential access through the segments.
 */
class MxSegmentListCursor : public MxPtrListCursor<MxSegment> {
public:
	/**
	 * @brief [AI] Constructs a cursor to navigate the given segment list.
	 * @param p_list Pointer to MxSegmentList to iterate over. [AI]
	 */
	MxSegmentListCursor(MxSegmentList* p_list) : MxPtrListCursor<MxSegment>(p_list) {}
};

// SIZE 0x0c
/**
 * @brief [AI] Represents a vertical span—a 1D range plus a set of contained horizontal segments, used as a row (span) of contiguous horizontal regions.
 * This is foundational for complex region (polygon) representation by decomposing 2D space into vertical strips, each with 1D segment lists.
 */
class MxSpan {
protected:
	MxS32 m_min;              ///< @brief [AI] Lower vertical boundary (usually 'top'). [AI]
	MxS32 m_max;              ///< @brief [AI] Upper vertical boundary (usually 'bottom'). [AI]
	MxSegmentList* m_segList; ///< @brief [AI] List of horizontal segments covered by this vertical span. [AI]

public:
	/**
	 * @brief [AI] Constructs a span along the vertical axis with specified bounds.
	 * @param p_min Lower vertical boundary. [AI]
	 * @param p_max Upper vertical boundary. [AI]
	 */
	MxSpan(MxS32 p_min, MxS32 p_max);

	/**
	 * @brief [AI] Constructs a span from a rectangle, vertically from top to bottom of the rectangle, containing one segment equal to the rectangle's horizontal span. [AI]
	 * @param p_rect Rectangle whose top/bottom form the span and whose left/right constitute its initial segment. [AI]
	 */
	MxSpan(MxRect32& p_rect);

	/**
	 * @brief [AI] Destructor; releases the segment list and owned segments inside this span.
	 */
	~MxSpan() { delete m_segList; }

	/**
	 * @brief [AI] Returns the vertical lower boundary of the span.
	 */
	MxS32 GetMin() { return m_min; }

	/**
	 * @brief [AI] Sets the vertical lower boundary of the span.
	 * @param p_min New lower boundary value. [AI]
	 */
	void SetMin(MxS32 p_min) { m_min = p_min; }

	/**
	 * @brief [AI] Returns the vertical upper boundary of the span.
	 */
	MxS32 GetMax() { return m_max; }

	/**
	 * @brief [AI] Sets the vertical upper boundary of the span.
	 * @param p_max New upper boundary value. [AI]
	 */
	void SetMax(MxS32 p_max) { m_max = p_max; }

	/**
	 * @brief [AI] Deep copies this span, including all its attached segments.
	 * @return Pointer to the cloned span. [AI]
	 */
	MxSpan* Clone();

	/**
	 * @brief [AI] Compact this span, potentially merging adjacent or overlapping segments for optimal storage. [AI]
	 */
	void Compact();

	/**
	 * @brief [AI] Tries to merge this span with another, if possible (must be adjacent and have matching segments). [AI]
	 * @param p_span Span to merge. [AI]
	 * @return TRUE if merged, FALSE otherwise. [AI]
	 */
	MxBool Combine(MxSpan& p_span);

	/**
	 * @brief [AI] Checks if this span is vertically adjacent to another (end-to-end).
	 * @param p_span Span to check adjacency against. [AI]
	 * @return TRUE if adjacent, FALSE otherwise. [AI]
	 */
	MxBool Adjacent(MxSpan& p_span) { return m_max == p_span.m_min || m_min == p_span.m_max; }

	/**
	 * @brief [AI] Checks for pointwise segment equivalence between two spans. [AI]
	 * @param p_span Span to compare with. [AI]
	 * @return TRUE if the segment lists are identical, FALSE otherwise. [AI]
	 */
	MxBool HasSameSegments(MxSpan& p_span);

	/**
	 * @brief [AI] Check if this span vertically intersects a rectangle (vertical ranges overlap).
	 * @param p_rect Rectangle to check against. [AI]
	 * @return TRUE if vertical overlap exists, FALSE otherwise. [AI]
	 */
	MxBool IntersectsV(MxRect32& p_rect) { return p_rect.GetBottom() > m_min && p_rect.GetTop() < m_max; }

	/**
	 * @brief [AI] Checks if any segment in this span horizontally overlaps with the given rectangle. [AI]
	 * @param p_rect Rectangle to test horizontal overlap. [AI]
	 * @return TRUE if overlap exists, FALSE otherwise. [AI]
	 */
	MxBool IntersectsH(MxRect32& p_rect);

	/**
	 * @brief [AI] Adds a horizontal segment to this span, merging with adjacent segments if required to maintain compactness.
	 * @param p_min Leftmost coordinate of the new segment. [AI]
	 * @param p_max Rightmost coordinate of the new segment. [AI]
	 */
	void AddSegment(MxS32 p_min, MxS32 p_max);

	/**
	 * @brief [AI] Tests for equality (vertical bounds and segments) with another span.
	 * @param p_span Span to test equality against. [AI]
	 * @return TRUE if equal, FALSE otherwise. [AI]
	 */
	MxBool operator==(MxSpan& p_span)
	{
		return m_min == p_span.m_min && m_max == p_span.m_max && HasSameSegments(p_span);
	}

	/**
	 * @brief [AI] Tests for inequality with another span.
	 * @param p_span Span to compare. [AI]
	 * @return TRUE if not equal, FALSE otherwise. [AI]
	 */
	MxBool operator!=(MxSpan& p_span) { return !operator==(p_span); }

	friend class MxRegionCursor;

	// SYNTHETIC: BETA10 0x1014b0b0
	// MxSpan::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dcb10
// VTABLE: BETA10 0x101c24f8
// class MxCollection<MxSpan *>

// VTABLE: LEGO1 0x100dcb28
// VTABLE: BETA10 0x101c24e0
// class MxList<MxSpan *>

// VTABLE: LEGO1 0x100dcb40
// VTABLE: BETA10 0x101c24c8
// class MxPtrList<MxSpan>

// VTABLE: LEGO1 0x100dcb58
// VTABLE: BETA10 0x101c24b0
// SIZE 0x18
/**
 * @brief [AI] List container for spans; holds MxSpan pointers and may automatically destroy them.
 */
class MxSpanList : public MxPtrList<MxSpan> {
public:
	/**
	 * @brief [AI] Constructs a new span list which owns its entries.
	 */
	MxSpanList() : MxPtrList<MxSpan>(TRUE) {}

	// SYNTHETIC: LEGO1 0x100c3410
	// SYNTHETIC: BETA10 0x1014af90
	// MxSpanList::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dcb70
// VTABLE: BETA10 0x101c2528
// class MxPtrListCursor<MxSpan>

// VTABLE: LEGO1 0x100dcba0
// VTABLE: BETA10 0x101c2540
// class MxListCursor<MxSpan *>

// TODO: The initialize list param type should be MxSpanList, but doing that
// drastically reduced the match percentage for MxRegion::AddRect.
// (developer provided MxRegion.h file also uses MxSpanList*.)
// It also works with MxPtrList, so we'll do that until we figure this out.

// VTABLE: LEGO1 0x100dcb88
// VTABLE: BETA10 0x101c2510
/**
 * @brief [AI] Cursor for traversing an MxSpanList, to sequentially access all spans in the list.
 */
class MxSpanListCursor : public MxPtrListCursor<MxSpan> {
public:
	/**
	 * @brief [AI] Cursor for any list of span pointers.
	 * @param p_list Span pointer list to traverse. [AI]
	 */
	MxSpanListCursor(MxPtrList<MxSpan>* p_list) : MxPtrListCursor<MxSpan>(p_list) {}
};

// VTABLE: LEGO1 0x100dcae8
// SIZE 0x1c
/**
 * @brief [AI] Represents a 2D region as a set of vertical spans each containing one or more horizontal segments. Used to describe complex areas for rasterization or clipping.
 * Internally implemented as a list of spans, each containing their horizontal segments, forming an efficient structure for union, intersection, and decomposition.
 */
class MxRegion : public MxCore {
protected:
	MxSpanList* m_spanList;  ///< @brief [AI] List of vertical spans for the region. [AI]
	MxRect32 m_boundingRect; ///< @brief [AI] Cached bounding rectangle for the whole region. [AI]

public:
	/**
	 * @brief [AI] Constructs an (initially empty) region. [AI]
	 */
	MxRegion();
	
	/**
	 * @brief [AI] Destructor; destroys all spans and contained segments.
	 */
	~MxRegion() override;

	/**
	 * @brief [AI] Returns a reference to the current bounding rectangle for the region. [AI]
	 */
	MxRect32& GetBoundingRect() { return m_boundingRect; }

	/**
	 * @brief [AI] Removes all spans and resets the bounding rectangle to an empty state. [AI]
	 */
	virtual void Reset();                        // vtable+0x14

	/**
	 * @brief [AI] Adds a rectangle to this region, merging or splitting spans and segments as necessary. [AI]
	 * @param p_rect Rectangle to be added. [AI]
	 */
	virtual void AddRect(MxRect32& p_rect);      // vtable+0x18

	/**
	 * @brief [AI] Checks if this region intersects with a given rectangle (any overlap between the region's covered area and p_rect).
	 * @param p_rect Rectangle to check overlap against. [AI]
	 * @return TRUE if any overlap exists, FALSE otherwise. [AI]
	 */
	virtual MxBool Intersects(MxRect32& p_rect); // vtable+0x1c

	/**
	 * @brief [AI] Returns TRUE if the region contains zero spans (i.e., is empty).
	 */
	virtual MxBool IsEmpty() { return m_spanList->GetNumElements() == 0; } // vtable+0x20

	/**
	 * @brief [AI] Compacts the region's internal structure, merging adjacent/overlapping spans and segments when possible.
	 */
	void Compact();

	friend class MxRegionCursor;

	// SYNTHETIC: LEGO1 0x100c3670
	// SYNTHETIC: BETA10 0x1014b230
	// MxRegion::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dcbb8
// SIZE 0x18
/**
 * @brief [AI] Cursor object suitable for traversing all rectangles covered by an MxRegion. Supports both sequential and filtered (clipped) traversal.
 * Can return rectangles in scanline order.
 */
class MxRegionCursor : public MxCore {
protected:
	MxRegion* m_region;                   ///< @brief [AI] The region being traversed. [AI]
	MxRect32* m_rect;                     ///< @brief [AI] Current rectangle being referenced. [AI]
	MxSpanListCursor* m_spanListCursor;   ///< @brief [AI] Cursor for moving through the span list. [AI]
	MxSegmentListCursor* m_segListCursor; ///< @brief [AI] Cursor for the current segment list. [AI]

	/**
	 * @brief [AI] Allocates a segment list cursor for the given segment list, replacing any previous segment cursor.
	 * @param p_segList Segment list to navigate. [AI]
	 */
	void CreateSegmentListCursor(MxSegmentList* p_segList);

	/**
	 * @brief [AI] Initializes or updates m_rect with the specified coordinates.
	 * @param p_left Left boundary. [AI]
	 * @param p_top Top boundary. [AI]
	 * @param p_right Right boundary. [AI]
	 * @param p_bottom Bottom boundary. [AI]
	 */
	void SetRect(MxS32 p_left, MxS32 p_top, MxS32 p_right, MxS32 p_bottom);

	/**
	 * @brief [AI] Step to the next span which overlaps p_rect (for filtered/region-clip traversal).
	 * @param p_rect Rectangle defining the filter window for the next span. [AI]
	 */
	void NextSpan(MxRect32& p_rect);

	/**
	 * @brief [AI] Step to the previous span (reverse traversal) intersecting p_rect.
	 * @param p_rect Rectangle used for calculating intersection. [AI]
	 */
	void PrevSpan(MxRect32& p_rect);

public:
	/**
	 * @brief [AI] Constructs a traversal cursor for the specified region.
	 * @param p_region The region to be traversed. [AI]
	 */
	MxRegionCursor(MxRegion* p_region);

	/**
	 * @brief [AI] Destructor; releases ownership of current rectangle and cursors.
	 */
	~MxRegionCursor() override;

	/**
	 * @brief [AI] Seeks to and returns the first (topmost, leftmost) rectangle covered by the region.
	 * @return Pointer to internal MxRect32 (do not delete). [AI]
	 */
	virtual MxRect32* Head();                 // vtable+0x18

	/**
	 * @brief [AI] Seeks to and returns the last (bottommost, rightmost) rectangle covered by the region.
	 * @return Pointer to internal MxRect32 (do not delete). [AI]
	 */
	virtual MxRect32* Tail();                 // vtable+0x20

	/**
	 * @brief [AI] Advances to and returns the next rectangle in region sequence.
	 * @return Pointer to internal MxRect32 (do not delete). [AI]
	 */
	virtual MxRect32* Next();                 // vtable+0x28

	/**
	 * @brief [AI] Steps backward to and returns the previous rectangle in region sequence.
	 * @return Pointer to internal MxRect32 (do not delete). [AI]
	 */
	virtual MxRect32* Prev();                 // vtable+0x30

	/**
	 * @brief [AI] Filtered: Places at the first rectangle overlapping p_rect and returns it.
	 * @param p_rect Rectangle defining the filter/clipping region. [AI]
	 * @return Pointer to intersection rectangle. [AI]
	 */
	virtual MxRect32* Head(MxRect32& p_rect); // vtable+0x14

	/**
	 * @brief [AI] Filtered: Steps to last rectangle intersecting p_rect.
	 * @param p_rect Rectangle to limit the search to. [AI]
	 * @return Pointer to intersection rectangle. [AI]
	 */
	virtual MxRect32* Tail(MxRect32& p_rect); // vtable+0x1c

	/**
	 * @brief [AI] Filtered: Advances to next rectangle intersecting p_rect.
	 * @param p_rect Filter/clipping rectangle. [AI]
	 * @return Pointer to intersection rectangle. [AI]
	 */
	virtual MxRect32* Next(MxRect32& p_rect); // vtable+0x24

	/**
	 * @brief [AI] Filtered: Steps to previous rectangle intersecting p_rect.
	 * @param p_rect Rectangle for filtering. [AI]
	 * @return Pointer to intersection rectangle. [AI]
	 */
	virtual MxRect32* Prev(MxRect32& p_rect); // vtable+0x2c

	/**
	 * @brief [AI] Returns a pointer to the currently referenced rectangle.
	 * @return Pointer to internal MxRect32 or nullptr if at end. [AI]
	 */
	virtual MxRect32* GetRect() { return m_rect; } // vtable+0x34

	/**
	 * @brief [AI] Checks if the cursor is currently referencing a valid rectangle (not at end).
	 * @return TRUE if valid, FALSE if past end of region. [AI]
	 */
	virtual MxBool Valid() { return m_rect != NULL; } // vtable+0x38

	/**
	 * @brief [AI] Resets the cursor(s) to the initial (uninitialized) state. All internal cursors are reset, and no rectangle is selected.
	 */
	virtual void Reset(); // vtable+0x3c

	// SYNTHETIC: LEGO1 0x100c4090
	// MxRegionCursor::`scalar deleting destructor'
};

#ifdef REGION_SANITY_CHECK

/**
 * @brief [AI] Used for integrity checking: records the intersection of an MxRect32 with the region and number of source rectangles contributing.
 */
class MxRectIntersection {
protected:
	MxRect32 m_rect; ///< @brief [AI] Rectangle corresponding to a found intersection. [AI]
	MxS32 m_numRects; ///< @brief [AI] Number of rectangles intersecting at this region. [AI]

public:
	/**
	 * @brief [AI] Retrieve the intersection rectangle.
	 * @return Reference to intersection rectangle. [AI]
	 */
	MxRect32& GetRect() { return m_rect; }

	/**
	 * @brief [AI] Store a rectangle as the intersection result.
	 * @param p_rect Rectangle to set. [AI]
	 */
	void SetRect(MxRect32& p_rect) { m_rect = p_rect; }

	/**
	 * @brief [AI] Number of overlaps at this intersection.
	 * @return Rectangle count. [AI]
	 */
	MxS32 GetNumRects() { return m_numRects; }

	/**
	 * @brief [AI] Sets the count of rectangles that contributed to this intersection.
	 * @param p_numRects Count value. [AI]
	 */
	void SetNumRects(MxS32 p_numRects) { m_numRects = p_numRects; }
};

/**
 * @brief [AI] List of MxRectIntersection objects for region sanity checking.
 */
class MxRectIntersectionList : public MxPtrList<MxRectIntersection> {
public:
	/**
	 * @brief [AI] Constructs a list of rect intersections which destroys its entries upon disposal.
	 */
	MxRectIntersectionList() : MxPtrList<MxRectIntersection>(TRUE) {}
};

/**
 * @brief [AI] Cursor for iterating over an MxRectIntersectionList.
 */
class MxRectIntersectionListCursor : public MxPtrListCursor<MxRectIntersection> {
public:
	/**
	 * @brief [AI] Constructs a cursor for the given rect intersection list.
	 * @param p_list List to provide traversal for. [AI]
	 */
	MxRectIntersectionListCursor(MxRectIntersectionList* p_list) : MxPtrListCursor<MxRectIntersection>(p_list) {}
};

/**
 * @brief [AI] Utility for validating correctness of region management; tracks intersections, adds rectangles, calculates overlap area, and can reset state.
 */
class MxRegionSanityCheck {
protected:
	MxRectIntersectionList* m_rectIntersectionList; ///< @brief [AI] List of intersection regions for tracking. [AI]

public:
	/**
	 * @brief [AI] Constructs a region sanity checker instance.
	 */
	MxRegionSanityCheck();

	/**
	 * @brief [AI] Destructor; destroys intersection results.
	 */
	~MxRegionSanityCheck();

	/**
	 * @brief [AI] Erases all intersection records and resets to initial state.
	 */
	void Reset() { m_rectIntersectionList->Delete(); }

	/**
	 * @brief [AI] Adds a rectangle to the set to be tracked and checked for overlaps in the region.
	 * @param p_rect Rectangle to record. [AI]
	 */
	void AddRect(MxRect32& p_rect);

	/**
	 * @brief [AI] Computes the area covered by one or more rectangles in the tracked list (possibly accounting for overlaps).
	 * @return Total covered area. [AI]
	 */
	MxS32 CalculateArea();
};

#endif

#endif // __MXREGION_H
