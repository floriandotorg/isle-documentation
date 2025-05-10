#if !defined(AFX_CONFIGCOMMANDLINEINFO_H)
#define AFX_CONFIGCOMMANDLINEINFO_H

#include "StdAfx.h"
#include "compat.h"
#include "config.h"
#include "decomp.h"

// VTABLE: CONFIG 0x004060e8
// SIZE 0x24

/**
 * @brief [AI] Specialized command line parser for the configuration application.
 * 
 * This class extends CCommandLineInfo to provide custom parsing logic for
 * command line parameters relevant to the configuration dialog of the LEGO Island
 * configuration utility. In particular, it supports a 'config' switch, which triggers
 * the configuration dialog to be shown.
 * 
 * When the 'config' flag is present in the command line arguments, the internal
 * configuration state (currentConfigApp->m_run_config_dialog) is updated to show
 * the configuration dialog at startup. [AI]
 */
class CConfigCommandLineInfo : public CCommandLineInfo {
public:
	/**
	 * @brief [AI] Constructor. Initializes the command line info object and ensures
	 * that the configuration dialog is not requested by default.
	 * 
	 * The m_run_config_dialog member in the global configuration application singleton
	 * is set to FALSE.
	 * [AI]
	 */
	CConfigCommandLineInfo();

	/**
	 * @brief [AI] Overridden command line parameter parser.
	 * 
	 * For each parameter, this checks if it is the 'config' flag (case-insensitive).
	 * If so, it sets the run_config_dialog member on the global config app to TRUE,
	 * so that the configuration dialog will be invoked on application start.
	 * 
	 * @param pszParam The command line parameter. [AI]
	 * @param bFlag TRUE if the parameter is a switch/flag (starts with '-' or '/'), FALSE otherwise. [AI]
	 * @param bLast TRUE if this is the last parameter in the command line. [AI]
	 * [AI]
	 */
	void ParseParam(LPCSTR pszParam, BOOL bFlag, BOOL bLast) override;
};

// SYNTHETIC: CONFIG 0x00403b80
// CConfigCommandLineInfo::`scalar deleting destructor'

#endif // !defined(AFX_CONFIGCOMMANDLINEINFO_H)