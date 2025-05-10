#ifndef __LEGOCOLOR_H
#define __LEGOCOLOR_H

#include "misc/legotypes.h"

class LegoStorage;

/// @brief LEGO color representation with 8-bit RGB channels. [AI]
/// @details This class encapsulates a 24-bit RGB color using three 8-bit unsigned integers for red, green, and blue components, as used for LEGO elements and rendering. It provides accessors, mutators, and reading from serialized storage. [AI]
class LegoColor {
public:
	/// @brief Default constructor. [AI]
	/// @details Initializes all RGB channels to zero (black color). [AI]
	LegoColor() { m_red = m_green = m_blue = 0; }

	/// @brief Get the red channel value. [AI]
	/// @return The red component (0-255). [AI]
	LegoU8 GetRed() { return m_red; }

	/// @brief Set the red channel value. [AI]
	/// @param p_red New value for the red component (0-255). [AI]
	void SetRed(LegoU8 p_red) { m_red = p_red; }

	/// @brief Get the green channel value. [AI]
	/// @return The green component (0-255). [AI]
	LegoU8 GetGreen() { return m_green; }

	/// @brief Set the green channel value. [AI]
	/// @param p_green New value for the green component (0-255). [AI]
	void SetGreen(LegoU8 p_green) { m_green = p_green; }

	/// @brief Get the blue channel value. [AI]
	/// @return The blue component (0-255). [AI]
	LegoU8 GetBlue() { return m_blue; }

	/// @brief Set the blue channel value. [AI]
	/// @param p_blue New value for the blue component (0-255). [AI]
	void SetBlue(LegoU8 p_blue) { m_blue = p_blue; }

	/// @brief Read the color from a storage object in the order red, green, blue (each as a byte). [AI]
	/// @details Reads three bytes from the provided LegoStorage: red, green, and blue, setting this color's components accordingly. Returns the result status of the storage read operation. [AI]
	/// @param p_storage Storage instance to read color data from. [AI]
	/// @return Result of the read operation (e.g., SUCCESS or error code). [AI]
	LegoResult Read(LegoStorage* p_storage);

protected:
	LegoU8 m_red;   ///< Red color component (0x00 offset). [AI]
	LegoU8 m_green; ///< Green color component (0x01 offset). [AI]
	LegoU8 m_blue;  ///< Blue color component (0x02 offset). [AI]
};

#endif // __LEGOCOLOR_H
