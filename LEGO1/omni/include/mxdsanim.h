#ifndef MXDSANIM_H
#define MXDSANIM_H

#include "mxdsmediaaction.h"

// VTABLE: LEGO1 0x100dcd88
// VTABLE: BETA10 0x101c2b20
// SIZE 0xb8

/**
 * @brief Derived class representing an animation action extracted from SI files. [AI]
 * @details [AI] MxDSAnim augments MxDSMediaAction to specialize in representing discrete animation media actions within the Lego Island resource and event system. It sets the type to e_anim on instantiation, keeping type-safe behavior for DS action handling. This class enables deep copying and polymorphic cloning to facilitate scripted or dynamic creation, duplication, and dispatch in the framework. [AI]
 */
class MxDSAnim : public MxDSMediaAction {
public:
	/**
	 * @brief Default constructor. Initializes type to animation. [AI]
	 */
	MxDSAnim();

	/**
	 * @brief Copy constructor. [AI]
	 * @param p_dsAnim The MxDSAnim object to copy from. [AI]
	 */
	MxDSAnim(MxDSAnim& p_dsAnim);

	/**
	 * @brief Virtual destructor. [AI]
	 */
	~MxDSAnim() override;

	/**
	 * @brief Copies all internal properties from another MxDSAnim instance. [AI]
	 * @param p_dsAnim The source MxDSAnim to copy from. [AI]
	 * @details [AI] This function ensures all settings (besides base class) are copied. [AI]
	 */
	void CopyFrom(MxDSAnim& p_dsAnim);

	/**
	 * @brief Assignment operator for deep copying from another MxDSAnim. [AI]
	 * @param p_dsAnim The source MxDSAnim for assignment. [AI]
	 * @return Reference to this object after assignment. [AI]
	 */
	MxDSAnim& operator=(MxDSAnim& p_dsAnim);

	/**
	 * @brief Returns the type name for this class for run-time type identification. [AI]
	 * @return Always returns "MxDSAnim". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101025d8
		return "MxDSAnim";
	}

	/**
	 * @brief Run-time type check. [AI]
	 * @param p_name The class name to check. [AI]
	 * @return True if p_name matches this class or any superclass. [AI]
	 * @details [AI] Enables safe downcasting and IsA checks in the scripting and object system. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSAnim::ClassName()) || MxDSMediaAction::IsA(p_name);
	}

	/**
	 * @brief Creates a new cloned copy of this MxDSAnim. [AI]
	 * @return A pointer to the duplicated MxDSAnim object (caller responsible for deletion). [AI]
	 * @details [AI] Supports the object system's ability to create copies at runtime for dynamic scenarios. [AI]
	 */
	MxDSAction* Clone() override; // vtable+0x2c

	// SYNTHETIC: LEGO1 0x100c9180
	// SYNTHETIC: BETA10 0x1015d910
	// MxDSAnim::`scalar deleting destructor'
};

#endif // MXDSANIM_H
