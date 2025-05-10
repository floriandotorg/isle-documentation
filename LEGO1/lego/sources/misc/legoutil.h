#ifndef __LEGOUTIL_H
#define __LEGOUTIL_H

// Exclude from modern compilers due to clash with mxutilities.h
#ifndef COMPAT_MODE

/**
 * @brief [AI] Returns the minimum of two values.
 * @param p_t1 First value to compare. [AI]
 * @param p_t2 Second value to compare. [AI]
 * @return The smaller of p_t1 and p_t2. [AI]
 */
template <class T>
inline T Min(T p_t1, T p_t2)
{
	return p_t1 < p_t2 ? p_t1 : p_t2;
}

/**
 * @brief [AI] Returns the minimum of three values.
 * @param p_t1 First value to compare. [AI]
 * @param p_t2 Second value to compare. [AI]
 * @param p_t3 Third value to compare. [AI]
 * @return The smallest of the three values. [AI]
 */
template <class T>
inline T Min(T p_t1, T p_t2, T p_t3)
{
	return Min(p_t1, Min(p_t2, p_t3));
}

/**
 * @brief [AI] Returns the maximum of two values.
 * @param p_t1 First value to compare. [AI]
 * @param p_t2 Second value to compare. [AI]
 * @return The larger of p_t1 and p_t2. [AI]
 */
template <class T>
inline T Max(T p_t1, T p_t2)
{
	return p_t1 > p_t2 ? p_t1 : p_t2;
}

/**
 * @brief [AI] Returns the maximum of three values.
 * @param p_t1 First value to compare. [AI]
 * @param p_t2 Second value to compare. [AI]
 * @param p_t3 Third value to compare. [AI]
 * @return The largest of the three values. [AI]
 */
template <class T>
inline T Max(T p_t1, T p_t2, T p_t3)
{
	return Max(p_t1, Max(p_t2, p_t3));
}

/**
 * @brief [AI] Returns the absolute value.
 * @details [AI] This computes the absolute value of the provided value by negating it if it is negative.
 * @param p_t Input value. [AI]
 * @return The absolute value of p_t. [AI]
 */
template <class T>
inline T Abs(T p_t)
{
	return p_t < 0 ? -p_t : p_t;
}

#endif

/**
 * @brief [AI] Swaps the values of two variables of the same type.
 * @param p_t1 First variable to swap; value will be updated with the value of p_t2. [AI]
 * @param p_t2 Second variable to swap; value will be updated with the value of p_t1. [AI]
 */
template <class T>
inline void Swap(T& p_t1, T& p_t2)
{
	T t = p_t1;
	p_t1 = p_t2;
	p_t2 = t;
}

// TEMPLATE: BETA10 0x10073c20
// Swap

/**
 * @brief [AI] Converts degrees to radians.
 * @details [AI] Useful for trigonometric functions which use radians. [AI]
 * @param p_d Angle in degrees. [AI]
 * @return The angle in radians. [AI]
 */
template <class T>
inline T DToR(T p_d)
{
	return p_d * 3.1416F / 180.0F;
}

/**
 * @brief [AI] Converts radians to degrees.
 * @details [AI] Useful for conversion to a more human-friendly angle representation. [AI]
 * @param p_r Angle in radians. [AI]
 * @return The angle in degrees. [AI]
 */
template <class T>
inline T RToD(T p_r)
{
	return p_r * 180.0F / 3.1416F;
}

#endif // __LEGOUTIL_H
