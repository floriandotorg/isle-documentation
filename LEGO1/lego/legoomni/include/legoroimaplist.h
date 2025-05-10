#ifndef LEGOROIMAPLIST_H
#define LEGOROIMAPLIST_H

#include "mxlist.h"
#include "mxtypes.h"

class LegoROI;

/**
 * @class LegoROIMapList
 * @brief [AI] Specialized pointer list that manages collections of LegoROI pointers, for ROI map management in the LEGO Island engine.
 * @details [AI] Inherits from MxPtrList<LegoROI*>, providing automatic deletion of list elements (TRUE is passed to the base constructor). Primarily used to maintain lists of world object instances (ROI) mappings that require custom memory and object management. [AI]
 * @note [AI] This class does not introduce additional methods or members beyond its base, but enforces automatic element destruction semantics specific to the game logic. [AI]
 */
class LegoROIMapList : public MxPtrList<LegoROI*> {
public:
	/**
	 * @brief [AI] Constructs an empty list of LegoROI pointers with automatic element destruction enabled.
	 */
	LegoROIMapList() : MxPtrList<LegoROI*>(TRUE) {}

	// SYNTHETIC: LEGO1 0x1006d360
	// LegoROIMapList::`scalar deleting destructor'
};

// TEMPLATE: LEGO1 0x1006d250
// MxCollection<LegoROI * *>::Compare

// TEMPLATE: LEGO1 0x1006d260
// MxCollection<LegoROI * *>::~MxCollection<LegoROI * *>

// TEMPLATE: LEGO1 0x1006d2b0
// MxCollection<LegoROI * *>::Destroy

// TEMPLATE: LEGO1 0x1006d2c0
// MxList<LegoROI * *>::~MxList<LegoROI * *>

// TEMPLATE: LEGO1 0x1006d3d0
// MxPtrList<LegoROI *>::~MxPtrList<LegoROI *>

// TEMPLATE: LEGO1 0x1006d350
// MxPtrList<LegoROI *>::Destroy

// SYNTHETIC: LEGO1 0x1006d420
// MxCollection<LegoROI * *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1006d490
// MxList<LegoROI * *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1006d540
// MxPtrList<LegoROI *>::`scalar deleting destructor'

#endif // LEGOROIMAPLIST_H
