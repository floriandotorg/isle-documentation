#ifndef LEGONAMEDTEXTURELIST_H
#define LEGONAMEDTEXTURELIST_H

#include "legonamedtexture.h"
#include "mxlist.h"

// VTABLE: LEGO1 0x100d8110
// class MxCollection<LegoNamedTexture *>

// VTABLE: LEGO1 0x100d8128
// class MxList<LegoNamedTexture *>

// VTABLE: LEGO1 0x100d8140
// class MxPtrList<LegoNamedTexture>

// VTABLE: LEGO1 0x100d8158
// SIZE 0x18
/**
 * @brief [AI] A list class that manages a collection of pointers to LegoNamedTexture objects. 
 * @details [AI] This class is specialized for use with LegoNamedTexture and provides storage and iteration functionality, allowing safe memory-managing containers (with object ownership) of textures by name within the rendering engine. 
 * By inheriting from MxPtrList<LegoNamedTexture>, it automatically supports list operations for managing named textures.
 */
class LegoNamedTextureList : public MxPtrList<LegoNamedTexture> {
public:
	/**
	 * @brief [AI] Constructs a new LegoNamedTextureList and enables object ownership semantics for contained pointers.
	 * @details [AI] The TRUE argument ensures the list is responsible for deleting held LegoNamedTexture objects.
	 */
	LegoNamedTextureList() : MxPtrList<LegoNamedTexture>(TRUE) {}

	// SYNTHETIC: LEGO1 0x1004f040
	// LegoNamedTextureList::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100d8170
// class MxListCursor<LegoNamedTexture *>

// VTABLE: LEGO1 0x100d8188
// class MxPtrListCursor<LegoNamedTexture>

// VTABLE: LEGO1 0x100d81a0
// SIZE 0x10
/**
 * @brief [AI] Cursor/iterator for traversing a LegoNamedTextureList.
 * @details [AI] This class allows iteration over the textures in a LegoNamedTextureList, supporting standard cursor operations through inheritance from MxPtrListCursor<LegoNamedTexture>.
 */
class LegoNamedTextureListCursor : public MxPtrListCursor<LegoNamedTexture> {
public:
	/**
	 * @brief [AI] Constructs a cursor for a specific LegoNamedTextureList.
	 * @param p_list Pointer to the list to iterate over. [AI]
	 */
	LegoNamedTextureListCursor(LegoNamedTextureList* p_list) : MxPtrListCursor<LegoNamedTexture>(p_list) {}
};

// SYNTHETIC: LEGO1 0x1004f500
// LegoNamedTextureListCursor::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1004f570
// MxPtrListCursor<LegoNamedTexture>::~MxPtrListCursor<LegoNamedTexture>

// SYNTHETIC: LEGO1 0x1004f5c0
// MxListCursor<LegoNamedTexture *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1004f630
// MxPtrListCursor<LegoNamedTexture>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1004f6a0
// MxListCursor<LegoNamedTexture *>::~MxListCursor<LegoNamedTexture *>

// FUNCTION: LEGO1 0x1004f6f0
// LegoNamedTextureListCursor::~LegoNamedTextureListCursor

// TEMPLATE: LEGO1 0x1004eec0
// MxCollection<LegoNamedTexture *>::Compare

// TEMPLATE: LEGO1 0x1004eed0
// MxCollection<LegoNamedTexture *>::~MxCollection<LegoNamedTexture *>

// TEMPLATE: LEGO1 0x1004ef20
// MxCollection<LegoNamedTexture *>::Destroy

// TEMPLATE: LEGO1 0x1004ef30
// MxList<LegoNamedTexture *>::~MxList<LegoNamedTexture *>

// TEMPLATE: LEGO1 0x1004efc0
// MxPtrList<LegoNamedTexture>::Destroy

// TEMPLATE: LEGO1 0x1004f0b0
// MxPtrList<LegoNamedTexture>::~MxPtrList<LegoNamedTexture>

// SYNTHETIC: LEGO1 0x1004f100
// MxCollection<LegoNamedTexture *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1004f170
// MxList<LegoNamedTexture *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1004f220
// MxPtrList<LegoNamedTexture>::`scalar deleting destructor'

#endif // LEGONAMEDTEXTURELIST_H
