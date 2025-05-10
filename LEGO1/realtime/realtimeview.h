#ifndef REALTIMEVIEW_H
#define REALTIMEVIEW_H

/**
 * @brief [AI] Global variable storing the calculated LOD "power" value for the user, derived from base and max LOD. Used for fast LOD calculations during rendering.
 */
extern float g_userMaxLodPower;

/**
 * @class RealtimeView
 * @brief [AI] Handles global view and level-of-detail (LOD) settings for real-time rendering. 
 * @details [AI] This class encapsulates and manages various thresholds and powers related to LOD selection and performance tuning in the LEGO Island rendering engine. All members are static, meaning all state is global. Provides update and getter/setter functions for LOD parameters and part count thresholds for real-time scenes.
 */
class RealtimeView {
public:
	/**
	 * @brief [AI] Constructor, ensures the maximum LOD "power" is recalculated at initialization.
	 */
	RealtimeView();

	/**
	 * @brief [AI] Destructor. Does nothing (present for completeness).
	 */
	~RealtimeView();

	/**
	 * @brief [AI] Returns the global threshold for the number of scene parts above which LOD switching is triggered.
	 * @return [AI] The value of parts threshold currently set for LOD adjustment.
	 */
	static float GetPartsThreshold();

	/**
	 * @brief [AI] Returns the user-specified maximum LOD value. 
	 * @details [AI] This controls the maximum LOD allowed in rendered models for a user's settings.
	 * @return [AI] The user max LOD value.
	 */
	static float GetUserMaxLOD();

	/**
	 * @brief [AI] Sets the global threshold for the number of parts before LOD reduction.
	 * @param p_threshold [AI] Number of scene parts above which reduced LODs are enforced.
	 */
	static void SetPartsThreshold(float p_threshold);

	/**
	 * @brief [AI] Updates the global LOD power value based on current base and max user LOD.
	 * @details [AI] This recalculates g_userMaxLodPower as pow(base, -maxLOD), which is used for LOD computation. Intended to be called internally any time LOD settings change.
	 */
	static void UpdateMaxLOD();

	/**
	 * @brief [AI] Sets the maximum LOD allowed for the user and updates global LOD power.
	 * @param p_lod [AI] New maximum LOD setting from the user.
	 */
	static void SetUserMaxLOD(float p_lod);

	/**
	 * @brief [AI] Returns the cached LOD power, used for faster LOD checks in rendering.
	 * @details [AI] This is recalculated via UpdateMaxLOD() whenever SetUserMaxLOD or related settings are called.
	 * @return [AI] The current user max LOD power value (g_userMaxLodPower).
	 */
	static float GetUserMaxLodPower() { return g_userMaxLodPower; }
};

#endif // REALTIMEVIEW_H
