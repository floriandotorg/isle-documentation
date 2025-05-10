#ifndef _tglVector_h
#define _tglVector_h

#include "math.h" // sin() in RotateAroundY()

#include <stddef.h> // offsetof()

namespace Tgl
{

/**
 * @namespace Constant
 * @brief [AI] Contains mathematical constants used throughout the Tgl namespace. 
 * @details [AI] The constants defined in this namespace are intended for geometric and trigonometric operations, e.g. conversion between degrees and radians.
 */
namespace Constant
{
/**
 * @var Pi
 * @brief [AI] Mathematical constant representing π (pi), the ratio of a circle's circumference to its diameter.
 * @details [AI] This is expressed as a double precision value and is commonly used for angle conversions and trigonometric calculations.
 */
const double Pi = 3.14159265358979323846;
};

/**
 * @brief [AI] Converts an angle from degrees to radians.
 * @param degrees Angle in degrees. [AI]
 * @return [AI] Angle converted to radians.
 * @details [AI] Uses the mathematical formula: radians = degrees × (π / 180).
 */
inline double DegreesToRadians(double degrees)
{
	return Constant::Pi * (degrees / 180.0);
}

/**
 * @brief [AI] Converts an angle from radians to degrees.
 * @param radians Angle in radians. [AI]
 * @return [AI] Angle converted to degrees.
 * @details [AI] Uses the mathematical formula: degrees = radians × (180 / π).
 */
inline double RadiansToDegrees(double radians)
{
	return (radians / Constant::Pi) * 180.0;
}

/**
 * @typedef FloatMatrix4
 * @brief [AI] Represents a 4x4 matrix of single-precision floating point values.
 * @details [AI] Commonly used for 3D geometric transformations and coordinate operations (such as translation, rotation, or scaling).
 */
typedef float FloatMatrix4[4][4];

} // namespace Tgl

#endif /* _tglVector_h */
