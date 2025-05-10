#if !defined(AFX_MAINDLG_H)
#define AFX_MAINDLG_H

#include "StdAfx.h"
#include "compat.h"
#include "decomp.h"
#include "res/resource.h"

// VTABLE: CONFIG 0x004063e0
// SIZE 0x70

/**
 * @brief The main dialog window for the LEGO Island configuration program (config.exe). [AI]
 * 
 * CMainDialog is the primary UI dialog for configuring graphics, sound, input and other options,
 * representing the main property sheet of the configuration tool. Inherits from MFC's CDialog. [AI]
 */
class CMainDialog : public CDialog {
public:
	/**
	 * @brief Construct a new CMainDialog object. [AI]
	 * 
	 * @param pParent Parent window pointer for dialog initialization. [AI]
	 */
	CMainDialog(CWnd* pParent);

	enum {
		IDD = IDD_MAIN ///< Dialog ID/resource identifier for the main dialog. [AI]
	};

protected:
	/**
	 * @brief DDX (Dialog Data Exchange) for MFC controls. [AI]
	 * @details Called by MFC to transfer data between UI controls and member variables. [AI]
	 * @param pDX Data exchange context for controls. [AI]
	 */
	void DoDataExchange(CDataExchange* pDX) override;

	/**
	 * @brief Refreshes the dialog interface according to current configuration settings. [AI]
	 * @details Updates checkboxes, radio buttons and enables/disables controls depending on current state. [AI]
	 */
	void UpdateInterface();

	/**
	 * @brief Switches UI layout between basic and advanced configuration. [AI]
	 * @param p_advanced If TRUE, shows advanced options; otherwise shows basic view. [AI]
	 */
	void SwitchToAdvanced(BOOL p_advanced);

	/// Internal/unknown member. Purpose unclear, contains 4 bytes of undefined data. [AI] [AI_SUGGESTED_NAME: m_paddingOrUnknown]
	undefined m_unk0x60[4]; // 0x60

	/// Handle to the dialog's icon (used for window/taskbar and drag). [AI]
	HCURSOR m_icon;         // 0x64

	/// Whether any configuration setting has been modified and needs to be saved. [AI]
	BOOL m_modified;        // 0x68

	/// Whether the dialog is in advanced mode. [AI]
	BOOL m_advanced;        // 0x6c

	// Implementation

protected:
	/**
	 * @brief Initialize dialog upon creation. [AI]
	 * @return TRUE if initialization successful. [AI]
	 */
	BOOL OnInitDialog() override;

	/**
	 * @brief MFC handler for system commands (such as About box invocation). [AI]
	 * @param nID Command identifier. [AI]
	 * @param lParam Command parameter. [AI]
	 */
	void OnSysCommand(UINT nID, LPARAM lParam);

	/**
	 * @brief Handles dialog paint (redraw). Shows icon if minimized. [AI]
	 */
	void OnPaint();

	/**
	 * @brief Returns handle to drag icon when dragging minimized window. [AI]
	 * @return HCURSOR Icon handle for drag. [AI]
	 */
	HCURSOR OnQueryDragIcon();

	/**
	 * @brief Handles selection changes in the list of 3D devices. [AI]
	 * @details Updates currently selected 3D device and enables/disables relevant controls. [AI]
	 */
	void OnList3DevicesSelectionChanged();

	/**
	 * @brief Handles dialog cancellation and executes clean-up (if needed). [AI]
	 */
	void OnCancel();

	/**
	 * @brief Handles destruction/closing of the dialog window (WM_DESTROY handler). [AI]
	 */
	void OnDestroy();

	/**
	 * @brief Processes 'Cancel' button press (IDABORT), optionally writes settings before exit. [AI]
	 */
	void OnButtonCancel();

	/**
	 * @brief Handler for '3D sound' checkbox toggle. Enables/disables 3D sound. [AI]
	 */
	void OnCheckbox3DSound();

	/**
	 * @brief Handler for '3D video memory' checkbox toggle. Enables/disables 3D acceleration in VRAM. [AI]
	 */
	void OnCheckbox3DVideoMemory();

	/**
	 * @brief Handler for '16-bit palette' radio button. Selects 16-bit display mode. [AI]
	 */
	void OnRadiobuttonPalette16bit();

	/**
	 * @brief Handler for '256-color palette' radio button. Selects 256-color (8-bit) display mode. [AI]
	 */
	void OnRadiobuttonPalette256();

	/**
	 * @brief Handler for 'Flip video memory pages' checkbox. Enables page flipping in VRAM. [AI]
	 */
	void OnCheckboxFlipVideoMemPages();

	/**
	 * @brief Handler for 'Low quality model' radio button. Selects low polygon/LOD model mode. [AI]
	 */
	void OnRadiobuttonModelLowQuality();

	/**
	 * @brief Handler for 'High quality model' radio button. Selects high polygon/LOD model mode. [AI]
	 */
	void OnRadiobuttonModelHighQuality();

	/**
	 * @brief Handler for 'Low quality texture' radio button. Selects reduced quality textures. [AI]
	 */
	void OnRadiobuttonTextureLowQuality();

	/**
	 * @brief Handler for 'High quality texture' radio button. Selects highest quality textures. [AI]
	 */
	void OnRadiobuttonTextureHighQuality();

	/**
	 * @brief Handler for 'Joystick' checkbox toggle. Enables or disables joystick as input device. [AI]
	 */
	void OnCheckboxJoystick();

	/**
	 * @brief Handler for 'Advanced' button. Toggles the dialog between basic and advanced settings views. [AI]
	 */
	void OnButtonAdvanced();

	/**
	 * @brief Handler for 'Draw cursor' checkbox toggle. Enables/disables drawing hardware cursor. [AI]
	 */
	void OnCheckboxDrawCursor();

	/**
	 * @brief Handler for 'Music' checkbox toggle. Enables/disables in-game music. [AI]
	 */
	void OnCheckboxMusic();

	/// MFC message map declaration for this dialog class. [AI]
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: CONFIG 0x00403de0
// CMainDialog::`scalar deleting destructor'

// FUNCTION: CONFIG 0x00403e60
// CMainDialog::_GetBaseMessageMap

// FUNCTION: CONFIG 0x00403e70
// CMainDialog::GetMessageMap

// GLOBAL: CONFIG 0x00406120
// CMainDialog::messageMap

// GLOBAL: CONFIG 0x00406128
// CMainDialog::_messageEntries

#endif // !defined(AFX_MAINDLG_H)