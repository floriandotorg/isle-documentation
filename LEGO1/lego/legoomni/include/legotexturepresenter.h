#ifndef LEGOTEXTUREPRESENTER_H
#define LEGOTEXTUREPRESENTER_H

#include "legonamedtexturelist.h"
#include "mxmediapresenter.h"

// VTABLE: LEGO1 0x100d4d90
// SIZE 0x54

/**
 * @brief [AI] Manages the loading, storage, and management of named textures for the LEGO Island engine.
 * 
 * The LegoTexturePresenter class is responsible for reading texture data from MxDSChunk objects,
 * storing textures to the central texture container, and interfacing with the game's tickle manager
 * for periodic logic updates. It acts as a specialized media presenter focused on the game's streamable
 * texture resources. Instances of LegoTexturePresenter are automatically registered/unregistered with the VideoManager.
 * 
 * @details [AI] This presenter serves the purpose of deserializing and registering textures present in streamed
 * media files (such as those included in SI scene files) and exposing them to the in-game renderer's container and lookup tables. 
 * It supports Direct3D hardware mode selection for optimal rendering.
 */
class LegoTexturePresenter : public MxMediaPresenter {
public:
	/**
	 * @brief [AI] Constructs a LegoTexturePresenter and initializes its texture list pointer to NULL.
	 */
	LegoTexturePresenter() : m_textures(NULL) {}

	/**
	 * @brief [AI] Destructor: Unregisters the presenter from the VideoManager and cleans up owned texture data.
	 */
	~LegoTexturePresenter() override;

	/**
	 * @brief [AI] Returns the handler class name used for presenter name dispatching and type identification.
	 * @return [AI] "LegoTexturePresenter" (static string)
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0664
		return "LegoTexturePresenter";
	}

	/**
	 * @brief [AI] Returns the dynamic class name for runtime type identification.
	 * @return [AI] Same as HandlerClassName()
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Determines if the presenter is or inherits from a given class name.
	 * @param p_name Name of the class to check against. [AI]
	 * @return [AI] TRUE if the class matches this type or any base class type.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoTexturePresenter::ClassName()) || MxMediaPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Updates this presenter when the tickle state reaches "Done". Handles composite presenters or delegates to base class logic.
	 */
	void DoneTickle() override;       // vtable+0x2c

	/**
	 * @brief [AI] Registers this presenter with the VideoManager, making it available for video/texture updates and management.
	 * @details [AI] Called by the tickle/streaming infrastructure when the presenter is activated.
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] Loads texture data from the current data chunk, registers these textures with the global texture container, and manages memory.
	 * @details [AI] Invoked as a presentation step upon new chunk arrival. Frees textures after pushing them to the container.
	 */
	MxResult PutData() override;      // vtable+0x4c

	// SYNTHETIC: LEGO1 0x1000cf40
	// LegoTexturePresenter::`scalar deleting destructor'

	/**
	 * @brief [AI] Loads and parses one or more texture objects from a provided serialized data chunk.
	 * 
	 * @details [AI] Constructs a LegoNamedTextureList and fills it by reading and parsing
	 * each texture blob from the chunk, using the current Direct3D hardware mode and file context.
	 * On failure, any allocated resources are correctly cleaned up.
	 * 
	 * @param p_chunk The SI file chunk containing serialized texture data. [AI]
	 * @return [AI] SUCCESS if all textures are read and parsed, otherwise FAILURE.
	 */
	MxResult Read(MxDSChunk& p_chunk);

	/**
	 * @brief [AI] Transfers all loaded textures to the global texture container and initializes their info structure.
	 * 
	 * @details [AI] Each named texture is either created anew within TextureContainer or updates existing ones with new image data.
	 * All memory owned by m_textures is freed after successful storage.
	 * 
	 * @return [AI] Always returns SUCCESS.
	 */
	MxResult Store();

private:
	/**
	 * @brief [AI] Linked list of loaded named textures pending registration.
	 */
	LegoNamedTextureList* m_textures; // 0x50
};

#endif // LEGOTEXTUREPRESENTER_H
