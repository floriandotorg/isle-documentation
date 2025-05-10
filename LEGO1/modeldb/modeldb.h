#ifndef MODELDB_H
#define MODELDB_H

#include "decomp.h"
#include "mxlist.h"
#include "mxstring.h"
#include "mxtypes.h"

#include <stdio.h>

// SIZE 0x18
/**
 * @struct ModelDbPart
 * @brief [AI] Represents a single part within a 3D model database entry, including its name and data offsets in a file.
 * @details [AI] Each ModelDbPart links to data in resource files using part offsets/lengths and is identified by a name (ROI name).
 */
struct ModelDbPart {
	/**
	 * @brief [AI] Reads a ModelDbPart object from a binary file.
	 * @details [AI] Reads the ROI name, data length and data offset for the part from the file pointer. Used during model database loading.
	 * @param p_file File pointer from which the part data will be read. [AI]
	 * @return Returns SUCCESS on success, FAILURE otherwise. [AI]
	 */
	MxResult Read(FILE* p_file);

	MxString m_roiName;          ///< @brief [AI] Name of the part/ROI this entry represents. [AI]
	undefined4 m_partDataLength; ///< @brief [AI] Length of binary part data in the file (in bytes). [AI]
	undefined4 m_partDataOffset; ///< @brief [AI] Offset within the file to the part's data. [AI]
};

// VTABLE: LEGO1 0x100d6888
// class MxCollection<ModelDbPart *>

// VTABLE: LEGO1 0x100d68a0
// class MxList<ModelDbPart *>

// VTABLE: LEGO1 0x100d68b8
// SIZE 0x1c
/**
 * @class ModelDbPartList
 * @brief [AI] Collection class representing a list of ModelDbPart pointers with custom comparison logic. Used for model part organization.
 * @details [AI] Stores all parts associated with a particular world/model. Inherits from MxList<ModelDbPart*> and defines a custom Compare method based on ROI name.
 */
class ModelDbPartList : public MxList<ModelDbPart*> {
public:
	/**
	 * @brief [AI] Constructs the ModelDbPartList and initializes the unknown member.
	 */
	ModelDbPartList() { m_unk0x18 = 1; }

	/**
	 * @brief [AI] Compares two ModelDbPart objects by their ROI names (case-insensitive).
	 * @details [AI] If names match, syncs the part's data length and offset from p_a to p_b. This provides comparison and merging for part loading.
	 * @param p_a First ModelDbPart* to compare. [AI]
	 * @param p_b Second ModelDbPart* to compare. If names match, its metadata is updated from p_a. [AI]
	 * @return Comparison result: <0, 0 (=equal), or >0. [AI]
	 */
	MxS8 Compare(ModelDbPart* p_a, ModelDbPart* p_b) override
	{
		MxS32 compare = strcmpi(p_a->m_roiName.GetData(), p_b->m_roiName.GetData());

		if (compare == 0) {
			p_b->m_partDataLength = p_a->m_partDataLength;
			p_b->m_partDataOffset = p_a->m_partDataOffset;
		}

		return compare;
	} // vtable+0x14

	// SYNTHETIC: LEGO1 0x10027d70
	// ModelDbPartList::`scalar deleting destructor'

private:
	undefined m_unk0x18; ///< @brief [AI] Unknown field; always initialized to 1. Purpose currently unknown. [AI]
};

// VTABLE: LEGO1 0x100d68d0
// class MxListCursor<ModelDbPart *>

// VTABLE: LEGO1 0x100d68e8
// SIZE 0x10
/**
 * @class ModelDbPartListCursor
 * @brief [AI] Iterator for traversing ModelDbPartList contents (ModelDbPart pointers).
 * @details [AI] Used for iterating over parts in a model/world safely.
 */
class ModelDbPartListCursor : public MxListCursor<ModelDbPart*> {
public:
	/**
	 * @brief [AI] Constructs a cursor for the given part list, enabling iteration.
	 * @param p_list Part list to iterate over. [AI]
	 */
	ModelDbPartListCursor(ModelDbPartList* p_list) : MxListCursor<ModelDbPart*>(p_list) {}
};

// TEMPLATE: LEGO1 0x10027c70
// MxCollection<ModelDbPart *>::Compare

// TEMPLATE: LEGO1 0x10027c80
// MxCollection<ModelDbPart *>::~MxCollection<ModelDbPart *>

// TEMPLATE: LEGO1 0x10027cd0
// MxCollection<ModelDbPart *>::Destroy

// TEMPLATE: LEGO1 0x10027ce0
// MxList<ModelDbPart *>::~MxList<ModelDbPart *>

// SYNTHETIC: LEGO1 0x10027de0
// MxCollection<ModelDbPart *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10027e50
// MxList<ModelDbPart *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10027f00
// ModelDbPartListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x10027f70
// MxListCursor<ModelDbPart *>::~MxListCursor<ModelDbPart *>

// SYNTHETIC: LEGO1 0x10027fc0
// MxListCursor<ModelDbPart *>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x10028030
// ModelDbPartListCursor::~ModelDbPartListCursor

// SIZE 0x38
/**
 * @struct ModelDbModel
 * @brief [AI] Represents a 3D model entry in a model database, including metadata and spatial transform info.
 * @details [AI] Contains model name, presenter name, raw data info, and transformation (location, direction, up) for placement in the world.
 */
struct ModelDbModel {
	/**
	 * @brief [AI] Frees dynamically allocated memory in the model (model name and presenter name).
	 * @details [AI] Should be called before deleting or reusing this struct to avoid memory leaks.
	 */
	void Free();

	/**
	 * @brief [AI] Loads a ModelDbModel from the current file pointer.
	 * @details [AI] Reads string names, data offsets and lengths, and transformation vectors from the binary format.
	 * @param p_file File pointer from which to read the model entry. [AI]
	 * @return SUCCESS if load is successful, FAILURE otherwise. [AI]
	 */
	MxResult Read(FILE* p_file);

	char* m_modelName;       ///< @brief [AI] Name of the model, dynamically allocated. [AI]
	MxU32 m_modelDataLength; ///< @brief [AI] Length of the model's raw data in the file, in bytes. [AI]
	MxU32 m_modelDataOffset; ///< @brief [AI] File offset to the model's raw data. [AI]
	char* m_presenterName;   ///< @brief [AI] Name of the presenter/handler class used for this model, dynamically allocated. [AI]
	float m_location[3];     ///< @brief [AI] World-space position of the model origin (as a 3D vector). [AI]
	float m_direction[3];    ///< @brief [AI] World-space direction vector (indicates model "forward" direction). [AI]
	float m_up[3];           ///< @brief [AI] World-space up vector (indicates model "up" orientation). [AI]
	undefined m_unk0x34;     ///< @brief [AI] Unknown field, possibly additional flags or type (purpose currently unknown). [AI]
};

// SIZE 0x18
/**
 * @struct ModelDbWorld
 * @brief [AI] Represents a world/scene in the model database, containing its parts and models.
 * @details [AI] Bridges the gap between a named world and the constituent 3D models and their parts.
 */
struct ModelDbWorld {
	char* m_worldName;           ///< @brief [AI] Name of the world (scene); dynamically allocated on read. [AI]
	ModelDbPartList* m_partList; ///< @brief [AI] List of model parts belonging to this world. [AI]
	ModelDbModel* m_models;      ///< @brief [AI] Array of models within this world. [AI]
	MxS32 m_numModels;           ///< @brief [AI] Number of models in the array m_models. [AI]
	undefined m_unk0x10[0x08];   ///< @brief [AI] Unknown 8 bytes at offset 0x10; purpose and usage are currently unknown. [AI]
};

/**
 * @brief [AI] Reads the collection of worlds (ModelDbWorld) from a model database file.
 * @details [AI] Allocates and loads the specified number of worlds, each containing their names, part lists, and models.
 *              Populates p_worlds and p_numWorlds accordingly. The caller is responsible for freeing with FreeModelDbWorlds.
 * @param p_file The file pointer to read from. [AI]
 * @param p_worlds Reference to pointer where the array of worlds will be stored. [AI]
 * @param p_numWorlds Reference to int to store the number of worlds read. [AI]
 * @return SUCCESS on successful load, FAILURE on error. [AI]
 */
MxResult ReadModelDbWorlds(FILE* p_file, ModelDbWorld*& p_worlds, MxS32& p_numWorlds);

/**
 * @brief [AI] Frees all resources related to ModelDbWorlds previously allocated by ReadModelDbWorlds.
 * @details [AI] Deallocates all world names, part lists/parts, model presenter/model names, and the worlds array itself.
 * @param p_worlds Reference to worlds array pointer, which is set to NULL after deletion. [AI]
 * @param p_numWorlds Number of worlds in the array, needed for cleanup. [AI]
 */
void FreeModelDbWorlds(ModelDbWorld*& p_worlds, MxS32 p_numWorlds);

#endif // MODELDB_H
