#ifndef LEGOTRANINFO_H
#define LEGOTRANINFO_H

#include "decomp.h"
#include "mxgeometry/mxmatrix.h"
#include "mxtypes.h"

struct AnimInfo;
class LegoAnimMMPresenter;
class LegoROI;
class MxPresenter;

/// @struct LegoTranInfo
/// @brief [AI] Holds transformation and animation information for a LEGO object/ROI, especially in the context of animation presentation. 
/// @details [AI] This structure aggregates references to animation data, transformation matrices, location indices, object IDs, presenter references, state flags, and transformation status. It is used for managing the transformation state and animation progress for individual LEGO objects in the render/animation system.
/// Many members are not self-descriptive, so see source for their initialization and update logic. [AI]
struct LegoTranInfo {
	/// @brief [AI] Bitwise flags for transformation states or conditions. Usage defined internally.
	enum {
		c_bit1 = 0x01, ///< [AI] Unknown flag (likely used for specialized transformation states). [AI]
		c_bit2 = 0x02  ///< [AI] Unknown flag (likely used for specialized transformation states). [AI]
	};

	/// @brief [AI] Initialize LegoTranInfo to default/neutral state.
	/// @details [AI] Sets object references to nullptr and initializes state/flags and transforms to safe defaults (identity, etc.). Used before animation and transformation operations are performed.
	LegoTranInfo()
	{
		m_index = 0;
		m_unk0x08 = NULL;
		m_unk0x0c = NULL;
		m_unk0x10 = 0;
		m_location = -1;
		m_unk0x14 = FALSE;
		m_unk0x1c = NULL;
		m_unk0x20 = NULL;
		m_presenter = NULL;
		m_unk0x15 = TRUE;
		m_unk0x28 = TRUE;
		m_unk0x29 = TRUE;
		m_flags = 0;
		m_unk0x2c.SetIdentity();
	}

	/// @brief [AI] Destructor releases owned transformation matrix pointer if allocated.
	/// @details [AI] Only m_unk0x0c is deleted, others are not owned by this struct.
	~LegoTranInfo() { delete m_unk0x0c; }

	AnimInfo* m_animInfo;             ///< [AI] Pointer to animation state information associated with this transformation instance (likely contains frame/cycle state, playback data, etc). [AI]
	MxU32 m_index;                    ///< [AI] Index for this transform instance; often used to correlate to a list or animation track. [AI]
	LegoROI* m_unk0x08;               ///< [AI] [AI_SUGGESTED_NAME: targetROI] Pointer to the LEGO ROI (object in world) this transformation applies to.
	MxMatrix* m_unk0x0c;              ///< [AI] [AI_SUGGESTED_NAME: overrideMatrix] Optional pointer to a dynamically allocated matrix for custom or temporary transformations. Null unless used for per-object overrides.
	MxU8 m_unk0x10;                   ///< [AI] Unknown; likely used for frame counters, step markers, or status flags in animation/transformation updates. [AI]
	MxS16 m_location;                 ///< [AI] Location index within a parent object, animation group, or part-based system. -1 means unset. [AI]
	MxBool m_unk0x14;                 ///< [AI] Boolean flag for an unknown state, frequently used in transformation validity or activation gating. [AI]
	MxBool m_unk0x15;                 ///< [AI] Boolean flag set TRUE on construction, usage context required. Could indicate active/valid status. [AI]
	MxU32 m_objectId;                 ///< [AI] Unique identifier for this object/transform pair; used for lookup or dispatch. [AI]
	MxPresenter** m_unk0x1c;          ///< [AI] [AI_SUGGESTED_NAME: presenterList] Pointer to an array of presenter objects. Allows for chained/parallel presentation or animation of this transform. [AI]
	MxLong* m_unk0x20;                ///< [AI] [AI_SUGGESTED_NAME: animationFramePtr] Pointer to a long integer, possibly for tracking current animation frame, timestamp, or similar value. [AI]
	LegoAnimMMPresenter* m_presenter; ///< [AI] Pointer to a specific animation presenter managing this transform's animation (controls playback, state, etc). [AI]
	MxBool m_unk0x28;                 ///< [AI] Another Boolean flag; TRUE by default. Likely used as part of a multi-flag state or for controlling per-frame transformation operations. [AI]
	MxBool m_unk0x29;                 ///< [AI] Another Boolean flag; TRUE by default. Possibly for progression or sequencing within animation handling. [AI]
	MxMatrix m_unk0x2c;               ///< [AI] Current transformation matrix for this entry; reset to identity at construction and modified by animation or external logic. [AI]
	MxU32 m_flags;                    ///< [AI] Miscellaneous flag word. Used for c_bit1, c_bit2, or internal mechanics related to transformation lifecycle. [AI]
};

#endif // LEGOTRANINFO_H
