#ifndef LEGORACEMAP_H
#define LEGORACEMAP_H

#include "legoraceactor.h"

class MxControlPresenter;
class MxStillPresenter;

// VTABLE: LEGO1 0x100d8858 LegoRaceActor
// VTABLE: LEGO1 0x100d8860 LegoAnimActor
// VTABLE: LEGO1 0x100d8870 LegoPathActor
// VTABLE: LEGO1 0x100d893c LegoRaceMap
// VTABLE: BETA10 0x101be4dc LegoRaceActor
// VTABLE: BETA10 0x101be4e0 LegoAnimActor
// VTABLE: BETA10 0x101be4f8 LegoPathActor
// VTABLE: BETA10 0x101be5e8 LegoRaceMap
// SIZE 0x1b4

/**
 * @brief [AI] Represents the world-space to screen-space mapping and rendering handler for the interactive race minimap. [AI]
 * 
 * LegoRaceMap is a specialized actor that manages the presentation, mapping, and events for the race map seen during gameplay.
 * It links race-world coordinates to their representation on the map image, manages map overlays and controls, responds to control events,
 * and coordinates the updating of the map indicator for the player or tracked entity. 
 * 
 * It is responsible for coordinating between world and map geometry, managing the mapping image (handled by MxStillPresenter), 
 * and integrating the in-map interactive controls (handled by MxControlPresenter). [AI]
 */
class LegoRaceMap : public virtual LegoRaceActor {
public:
	/**
	 * @brief [AI] Constructs a new, non-enabled LegoRaceMap and registers it with the ControlManager. [AI]
	 */
	LegoRaceMap();

	/**
	 * @brief [AI] Destroys the LegoRaceMap and unregisters it from the ControlManager. [AI]
	 */
	~LegoRaceMap() override;

	// LegoPathActor vtable

	/**
	 * @brief [AI] Handles notifications, especially for UI control interactions (e.g., clicking the map control to show/hide the minimap). [AI]
	 * 
	 * If a notification of type `c_notificationControl` is received for the map control button (m_Map_Ctl), and the notification indicates
	 * the map was toggled on, then the minimap's still presenter is enabled and the player indicator updated; if toggled off, disables the minimap image.
	 * 
	 * @param p_param [AI] Notification parameter providing notification type and control-specific data.
	 * @return [AI] Always returns 1 (notification handled).
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Parses action strings for map locator and geometry mapping and links control and map geometry to world/display mapping. [AI]
	 * 
	 * Recognizes "MAP_LOCATOR" and "MAP_GEOMETRY" keys in the string, setting up the still presenter for the map overlay,
	 * and the transforms that map between world-space and map-space for drawing/tracking purposes. Also binds the map
	 * control presenter for receiving control events.
	 * 
	 * @param p_extra [AI] Null-terminated string containing extra action data (map geometry/configuration).
	 */
	void ParseAction(char* p_extra) override; // vtable+0x20

	/**
	 * @brief [AI] Abstract interface for updating minimap animations according to world state/time. [AI]
	 * 
	 * To be implemented by concrete subclasses—responsible for animating the minimap overlay, e.g., moving the
	 * indicator based on player/world state.
	 * 
	 * @param p_time [AI] Time since last animation tick.
	 */
	void Animate(float p_time) override = 0;  // vtable+0x70

	// LegoRaceMap vtable

	/**
	 * @brief [AI] Updates the minimap overlay position and enables/disables the overlay image as needed. [AI]
	 * 
	 * Projects the tracked entity's position from world space to map geometry and updates the attached still presenter's screen coordinates.
	 * Only performed if minimap is enabled via m_unk0x08. [AI]
	 */
	virtual void FUN_1005d4b0(); // vtable+0x00

	// SYNTHETIC: LEGO1 0x10012c50
	// LegoRaceMap::`vbase destructor'

	// SYNTHETIC: LEGO1 0x1005d5d0
	// LegoRaceMap::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Flag indicating whether the minimap overlay is currently active/visible. [AI]
	 */
	MxBool m_unk0x08;                   // 0x08

	/**
	 * @brief [AI] Reference to the still presenter responsible for displaying the minimap overlay image; may be NULL if not configured yet. [AI]
	 */
	MxStillPresenter* m_stillPresenter; // 0x0c

	/**
	 * @brief [AI] Reference to the in-map control presenter ("Map_Ctl"), for responding to control events (user toggling the minimap). [AI]
	 */
	MxControlPresenter* m_Map_Ctl; // 0x10

	/**
	 * @brief [AI] X world-space offset of the map region being mapped—corresponds to origin for conversion. [AI]
	 */
	float m_unk0x14; // 0x14

	/**
	 * @brief [AI] Inverse scaling factor for X ("world units per map unit"); used to convert from world coordinates to normalized map region. [AI]
	 */
	float m_unk0x18; // 0x18

	/**
	 * @brief [AI] Y world-space offset of the map region ("bottom" coordinate). [AI]
	 */
	float m_unk0x1c; // 0x1c

	/**
	 * @brief [AI] Inverse scaling for Y ("world units per map unit"); as with m_unk0x18 but for vertical coordinate. [AI]
	 */
	float m_unk0x20; // 0x20

	/**
	 * @brief [AI] X scaling for the minimap image on screen (number of display/screen pixels mapped per map X unit). [AI]
	 */
	float m_unk0x24; // 0x24

	/**
	 * @brief [AI] Y scaling for the minimap image on screen (number of screen pixels mapped per map Y unit). [AI]
	 */
	float m_unk0x28; // 0x28

	/**
	 * @brief [AI] X screen-space offset of the minimap, i.e. the left position where the minimap image starts on the screen. [AI]
	 */
	float m_unk0x2c; // 0x2c

	/**
	 * @brief [AI] Y screen-space offset for the minimap, i.e. the top position on screen. [AI]
	 */
	float m_unk0x30; // 0x30
};

// GLOBAL: LEGO1 0x100d8848
// LegoRaceMap::`vbtable'

// GLOBAL: LEGO1 0x100d8840
// LegoRaceMap::`vbtable'{for `LegoAnimActor'}

// GLOBAL: LEGO1 0x100d8830
// LegoRaceMap::`vbtable'{for `LegoRaceActor'}

#endif // LEGORACEMAP_H
