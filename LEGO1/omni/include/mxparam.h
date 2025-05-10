#ifndef MXPARAM_H
#define MXPARAM_H

/// @brief [AI] MxParam serves as a polymorphic base class for parameter passing in event and notification systems throughout the LEGO Island engine. [AI]
/// @details [AI] MxParam is a minimal virtual base type used for argument polymorphism when sending or receiving notifications or system events. Subclasses typically carry actual payload data relevant to a particular notification or event, but by using MxParam pointers the notification interface can remain generic. [AI]
/// @size 0x04 [AI]
class MxParam {
public:
	/// @brief [AI] Virtual destructor for safe polymorphic deletion of derived parameter objects. [AI]
	/// @details [AI] Ensures that destruction of derived classes through a MxParam pointer invokes the correct destructor chain. [AI]
	virtual ~MxParam() {}
};

// SYNTHETIC: BETA10 0x10013710
// MxParam::MxParam

// SYNTHETIC: ISLE 0x401540
// SYNTHETIC: LEGO1 0x10010370
// SYNTHETIC: BETA10 0x10013570
// MxParam::`scalar deleting destructor'

#endif // MXPARAM_H