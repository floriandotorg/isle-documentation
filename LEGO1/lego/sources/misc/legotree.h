#ifndef __LEGOTREE_H
#define __LEGOTREE_H

#ifdef _DEBUG
#include <stdio.h>
#endif
#include "legotypes.h"

class LegoStorage;

/// \class LegoTreeNodeData
/// \brief [AI] Abstract base class for storing data payloads inside nodes of a tree structure, forming the data content of each tree node.
/// \details [AI] Provides an interface for reading and writing data payloads to and from a generic \ref LegoStorage. Intended to be subclassed by users to store arbitrary, serializable data in a tree node.
/// Size: 0x4 bytes (empty, only for polymorphic interface) [AI]
class LegoTreeNodeData {
public:
	/// \brief [AI] Default constructor.
	LegoTreeNodeData() {}

	/// \brief [AI] Virtual destructor for safe polymorphic deletion of derived classes.
	// FUNCTION: LEGO1 0x1009a0e0
	virtual ~LegoTreeNodeData() {}

	/// \brief [AI] Virtual function for deserializing node data from a generic LegoStorage device.
	/// \param p_storage Storage object to read binary data from. [AI]
	/// \details [AI] Returns SUCCESS by default. Override in subclasses to read node-specific data.
	// FUNCTION: LEGO1 0x10099fe0
	virtual LegoResult Read(LegoStorage* p_storage) { return SUCCESS; } // vtable+0x04

	/// \brief [AI] Virtual function for serializing node data to a generic LegoStorage device.
	/// \param p_storage Storage object to write binary data to. [AI]
	/// \details [AI] Returns SUCCESS by default. Override in subclasses to write node-specific data.
	// FUNCTION: LEGO1 0x10099ff0
	virtual LegoResult Write(LegoStorage* p_storage) { return SUCCESS; } // vtable+0x08

	// SYNTHETIC: LEGO1 0x1009a000
	// LegoTreeNodeData::`scalar deleting destructor'
};

/// \class LegoTreeNode
/// \brief [AI] Represents a node within a general, N-ary tree structure. [AI]
/// \details [AI] Each node holds a pointer to a data object, a list of child nodes, and tracks the number of children. Intended for constructing arbitrarily nested tree data structures, loaded/saved recursively. [AI]
/// Size: 0x10 bytes [AI]
class LegoTreeNode {
public:
	/// \brief [AI] Constructs an empty tree node with no children or data. [AI]
	LegoTreeNode();

	/// \brief [AI] Destructor cleans up node data and children recursively. [AI]
	virtual ~LegoTreeNode();

	/// \brief [AI] Returns the data payload stored at this node (may be nullptr). [AI]
	// FUNCTION: BETA10 0x100595a0
	LegoTreeNodeData* GetData() { return m_data; }

	/// \brief [AI] Associates a data payload with this node. [AI]
	/// \param p_data Pointer to heap-allocated payload data, takes ownership. [AI]
	// FUNCTION: BETA10 0x100736f0
	void SetData(LegoTreeNodeData* p_data) { m_data = p_data; }

	/// \brief [AI] Returns the number of direct children of this node. [AI]
	// FUNCTION: BETA10 0x10012150
	LegoU32 GetNumChildren() { return m_numChildren; }

	/// \brief [AI] Sets the number of children for this node (does not resize pointer array). [AI]
	/// \param p_numChildren New number of children. [AI]
	// FUNCTION: BETA10 0x10073370
	void SetNumChildren(LegoU32 p_numChildren) { m_numChildren = p_numChildren; }

	/// \brief [AI] Gets the child node at the specified index (no bounds checking). [AI]
	/// \param p_i Child index. [AI]
	LegoTreeNode* GetChild(LegoU32 p_i) { return m_children[p_i]; }

	/// \brief [AI] Assigns a child node pointer at the specified index in this node's children array. [AI]
	/// \param p_i Array index to set. [AI]
	/// \param p_child Pointer to child tree node. [AI]
	void SetChild(LegoU32 p_i, LegoTreeNode* p_child) { m_children[p_i] = p_child; }

	/// \brief [AI] Returns the pointer to the children array. [AI]
	// FUNCTION: BETA10 0x100733a0
	LegoTreeNode** GetChildren() { return m_children; }

	/// \brief [AI] Assigns the entire children pointer array. [AI]
	/// \param p_children Pointer to an array of LegoTreeNode* (must be heap-allocated). [AI]
	// FUNCTION: BETA10 0x10073720
	void SetChildren(LegoTreeNode** p_children) { m_children = p_children; }

	// SYNTHETIC: LEGO1 0x10099d80
	// SYNTHETIC: BETA10 0x10188cb0
	// LegoTreeNode::`scalar deleting destructor'

protected:
	LegoTreeNodeData* m_data;  ///< [AI] Pointer to node data payload, owned by node. nullptr indicates no data present. [AI]
	LegoU32 m_numChildren;     ///< [AI] Number of valid child pointers in m_children. [AI]
	LegoTreeNode** m_children; ///< [AI] Pointer to array of tree node children (size = m_numChildren). nullptr if no children allocated. [AI]
};

/// \class LegoTree
/// \brief [AI] Represents an N-ary tree of LegoTreeNode objects, with support for recursive reading and writing of tree structures. [AI]
/// \details [AI] This class owns its root node and manages serialization/deserialization of the entire tree to a \ref LegoStorage stream via virtual node data creation. [AI]
/// Size: 0x08 bytes [AI]
class LegoTree {
public:
	/// \brief [AI] Constructs an empty tree (root not allocated). [AI]
	LegoTree();

	/// \brief [AI] Recursively destroys all tree nodes and their payloads. [AI]
	virtual ~LegoTree();

	/// \brief [AI] Returns a pointer to the root node of the tree. [AI]
	// FUNCTION: BETA10 0x100121b0
	LegoTreeNode* GetRoot() { return m_root; }

	/// \brief [AI] Assigns the root node pointer for the tree (takes ownership). [AI]
	/// \param p_root Pointer to a LegoTreeNode heap object. [AI]
	// FUNCTION: BETA10 0x10073750
	void SetRoot(LegoTreeNode* p_root) { m_root = p_root; }

	/// \brief [AI] Loads the tree structure recursively from the given storage. [AI]
	/// \param p_storage Storage stream to read from. [AI]
	/// \details [AI] Recursively constructs tree structure and node payloads using CreateData() and each node's Read(). [AI]
	virtual LegoResult Read(LegoStorage* p_storage);  // vtable+0x04

	/// \brief [AI] Serializes the tree structure recursively to the given storage. [AI]
	/// \param p_storage Storage stream to write to. [AI]
	/// \details [AI] Recursively traverses all nodes and their children, writing data and structure. [AI]
	virtual LegoResult Write(LegoStorage* p_storage); // vtable+0x08

	// SYNTHETIC: LEGO1 0x10099de0
	// LegoTree::`scalar deleting destructor'

protected:
	/// \brief [AI] Reads a subtree recursively from storage, creating a new node and reading its data/children. [AI]
	/// \param p_storage Reading source. [AI]
	/// \param p_node Reference to pointer which will be assigned to the created node. [AI]
	/// \details [AI] Called internally for recursive loading; constructs nodes and their payloads and child pointers. [AI]
	LegoResult Read(LegoStorage* p_storage, LegoTreeNode*& p_node);

	/// \brief [AI] Writes a subtree recursively to storage from the given node. [AI]
	/// \param p_storage Target for writing. [AI]
	/// \param p_node Node from which to begin recursive writing. [AI]
	LegoResult Write(LegoStorage* p_storage, LegoTreeNode* p_node);

	/// \brief [AI] Recursively deletes an entire subtree starting at the given node. [AI]
	/// \param p_node Node at which to begin deletion (includes all children). [AI]
	void Delete(LegoTreeNode* p_node);

	/// \brief [AI] Virtual function to instantiate node payload objects for the tree structure. [AI]
	/// \details [AI] Intended for overriding in derived tree classes to allocate node data of specific subclass types; default returns new LegoTreeNodeData().
	// FUNCTION: LEGO1 0x10099f70
	virtual LegoTreeNodeData* CreateData() { return new LegoTreeNodeData(); } // vtable+0x0c

	LegoTreeNode* m_root; ///< [AI] Root node of the tree. nullptr if tree is empty. Owned by the tree instance. [AI]
};

#endif // __LEGOTREE_H