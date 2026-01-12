#ifndef MXDSSTREAMINGACTION_H
#define MXDSSTREAMINGACTION_H

#include "mxdsaction.h"

class MxDSBuffer;

// VTABLE: LEGO1 0x100dd088
// VTABLE: BETA10 0x101c2850
// SIZE 0xb4
class MxDSStreamingAction : public MxDSAction {
public:
	MxDSStreamingAction(MxDSAction& p_dsAction, MxU32 p_offset);
	MxDSStreamingAction(MxDSStreamingAction& p_dsStreamingAction);
	~MxDSStreamingAction() override;

	MxDSStreamingAction* CopyFrom(MxDSStreamingAction& p_dsStreamingAction);

	MxBool HasId(MxU32 p_objectId) override; // vtable+0x34

	void Init();
	void SetInternalAction(MxDSAction* p_dsAction);
	void AdvanceLoop();

	// FUNCTION: BETA10 0x10156530
	MxU32 GetUnknown94() { return m_unk0x94; }

	// FUNCTION: BETA10 0x10156380
	MxS32 GetUnknown9c() { return m_unk0x9c; }

	// FUNCTION: BETA10 0x10156630
	MxDSBuffer* GetBuffer1() { return m_unkBuffer1; }

	// FUNCTION: BETA10 0x101563d0
	MxDSBuffer* GetUnkBuffer2() { return m_unkBuffer2; }

	// FUNCTION: BETA10 0x10159190
	MxLong GetElapsedTime() { return m_elapsedTime; }

	MxDSAction* GetInternalAction() { return m_internalAction; }

	// FUNCTION: BETA10 0x10156580
	MxU32 GetBufferOffset() { return m_bufferOffset; }

	// FUNCTION: BETA10 0x10156550
	void SetUnknown94(MxU32 p_unk0x94) { m_unk0x94 = p_unk0x94; }

	// FUNCTION: BETA10 0x101563a0
	void SetUnknown9c(MxS32 p_unk0x9c) { m_unk0x9c = p_unk0x9c; }

	// FUNCTION: BETA10 0x10156470
	void SetUnkBuffer1(MxDSBuffer* p_unk0xa0) { m_unkBuffer1 = p_unk0xa0; }

	// FUNCTION: BETA10 0x101563f0
	void SetUnkBuffer2(MxDSBuffer* p_unk0xa4) { m_unkBuffer2 = p_unk0xa4; }

	// FUNCTION: BETA10 0x10151150
	void SetBufferOffset(MxU32 p_bufferOffset) { m_bufferOffset = p_bufferOffset; }

	// FUNCTION: BETA10 0x10156650
	void ClearBuffer1() { m_unkBuffer1 = NULL; }

	// SYNTHETIC: LEGO1 0x100cd0b0
	// SYNTHETIC: BETA10 0x101565f0
	// MxDSStreamingAction::`scalar deleting destructor'

private:
	MxU32 m_unk0x94;              // 0x94
	MxU32 m_bufferOffset;         // 0x98
	MxS32 m_unk0x9c;              // 0x9c
	MxDSBuffer* m_unkBuffer1;     // 0xa0
	MxDSBuffer* m_unkBuffer2;     // 0xa4
	MxLong m_elapsedTime;         // 0xa8
	undefined2 m_unk0xac;         // 0xac
	MxDSAction* m_internalAction; // 0xb0
};

#endif // MXDSSTREAMINGACTION_H
