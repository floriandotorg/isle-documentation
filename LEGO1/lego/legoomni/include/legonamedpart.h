#ifndef LEGONAMEDPART_H
#define LEGONAMEDPART_H

#include "legolodlist.h"
#include "mxstring.h"

// SIZE 0x14

/**
 * @class LegoNamedPart
 * @brief [AI] Encapsulates a named part within a LEGO object that contains a list of LODs (Levels of Detail).
 * 
 * This class provides an association between a part's name and its corresponding list of LOD geometries.
 * It serves as a component within the LOD system, allowing named access and lifecycle management 
 * of a group of LOD objects.
 * [AI]
 */
class LegoNamedPart {
public:
	/**
	 * @brief [AI] Constructs a LegoNamedPart with a given name and list of LODs.
	 * @param p_name The name of the part. [AI]
	 * @param p_list List of LOD (Level of Detail) objects associated with this part. [AI]
	 * @details [AI] The input p_name is copied to m_name, and p_list becomes the managed LOD list for this part.
	 */
	LegoNamedPart(const char* p_name, LegoLODList* p_list)
	{
		m_name = p_name;
		m_list = p_list;
	}

	/**
	 * @brief [AI] Destructor, cleans up all LOD objects and the LOD list.
	 * @details [AI] Iterates through the LOD list and deletes all owned LegoLOD objects, 
	 * detaching each one before deleting the LOD list itself to ensure proper resource management.
	 */
	~LegoNamedPart()
	{
		LegoLODListCursor cursor(m_list);
		LegoLOD* lod;

		while (cursor.First(lod)) {
			cursor.Detach();
			delete lod;
		}

		delete m_list;
	}

	/**
	 * @brief [AI] Gets the name of this named part.
	 * @return Pointer to the MxString holding the name of the part. [AI]
	 */
	const MxString* GetName() const { return &m_name; }

	/**
	 * @brief [AI] Accesses the list of LODs associated with this part.
	 * @return Pointer to the LegoLODList for this named part. [AI]
	 */
	LegoLODList* GetList() { return m_list; }

private:
	MxString m_name;     ///< @brief [AI] Name of this LEGO part, used for identification and lookup (offset 0x00). [AI]
	LegoLODList* m_list; ///< @brief [AI] Pointer to the list of LOD geometry objects for this part (offset 0x04). [AI]
};

#endif // LEGONAMEDPART_H
