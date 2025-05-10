#ifndef LEGOMETERPRESENTER_H
#define LEGOMETERPRESENTER_H

#include "mxgeometry.h"
#include "mxstillpresenter.h"
#include "mxstring.h"

// VTABLE: LEGO1 0x100d7ac8
// VTABLE: BETA10 0x101bca68
// SIZE 0x94

/**
 * @brief Presenter class for displaying and updating a graphical meter element, such as a progress bar or health bar, with support for different fill directions and variable-driven values. [AI]
 * @details Inherits from MxStillPresenter to provide additional drawing and update logic for meters, referencing a variable in the global variable table for its fill percentage, and supports customizable fill directions and filler color. [AI]
 */
class LegoMeterPresenter : public MxStillPresenter {
public:
	/**
	 * @brief Constructs a LegoMeterPresenter with default options (left to right fill, zero percent, no pixels allocated). [AI]
	 */
	LegoMeterPresenter();

	/**
	 * @brief Destructor for LegoMeterPresenter. Releases allocated meter pixel buffer. [AI]
	 */
	~LegoMeterPresenter() override;

	// MxStillPresenter's `::ClassName` and `::IsA` are used.

	/**
	 * @brief [AI] Performs initialization of the meter on first streaming update, copying original bitmap data and setting up dimensions.
	 * @details Called at the 'streaming' tickle phase; saves initial bitmap state and meter dimensions, and allocates buffer for meter rendering. [AI]
	 * @override
	 */
	void StreamingTickle() override; // vtable+0x20

	/**
	 * @brief [AI] Called every frame in the 'repeating' tickle phase, updates and redraws the meter based on current variable value.
	 * @details Invokes DrawMeter to update meter fill according to the relevant variable, then performs base class tickle logic. [AI]
	 * @override
	 */
	void RepeatingTickle() override; // vtable+0x24

	/**
	 * @brief [AI] Parses the "extra" data chunk attached to this presenter for dynamic meter configuration.
	 * @details Reads meter layout, fill color, and the variable to drive the meter from the configuration; ends the action if variable is missing. [AI]
	 * @override
	 */
	void ParseExtra() override;      // vtable+0x30

private:
	/**
	 * @brief [AI] Enumeration for meter fill direction/layout. Used to select visual growth direction of metric fill. [AI]
	 */
	enum MeterLayout {
		e_leftToRight = 0,  ///< [AI] Meter fills left to right.
		e_rightToLeft,      ///< [AI] Meter fills right to left.
		e_bottomToTop,      ///< [AI] Meter fills bottom to top.
		e_topToBottom       ///< [AI] Meter fills top to bottom.
	};

	/**
	 * @brief [AI] Fills and draws the meter pixels onto the display surface according to the currently set percentage and fill direction.
	 * @details Restores bitmap from original, then applies fill color for the filled portion determined by the variable-driven percent and chosen MeterLayout. Only left-to-right and bottom-to-top are currently implemented. [AI]
	 */
	void DrawMeter();

	MxU8* m_meterPixels;  ///< @brief [AI] Pixel data buffer holding the unfilled/original meter bitmap for restore/blitting.
	MxU16 m_fillColor;    ///< @brief [AI] Color palette index to use for the filled (active) area of the meter.
	MxString m_variable;  ///< @brief [AI] Name of the variable in the global variable table which indicates fill percentage (0..1 as string).
	MxFloat m_curPercent; ///< @brief [AI] Last known percentage filled (0..0.99). Used to avoid unnecessary redraws.
	MxRect16 m_meterRect; ///< @brief [AI] Rectangle area of the meter within the bitmap; used for filling algorithm.
	MxS16 m_layout;       ///< @brief [AI] Layout/fill direction for the meter, see MeterLayout.
};

// SYNTHETIC: LEGO1 0x10043760
// LegoMeterPresenter::`scalar deleting destructor'

#endif // LEGOMETERPRESENTER_H