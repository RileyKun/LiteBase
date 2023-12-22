#include "CreateMove.h"

bool __fastcall Hooks::CreateMove::Func(void *ecx, void *edx, float flInputSampleTime, CUserCmd *pCmd)
{
	uintptr_t _bp; __asm mov _bp, ebp;
	bool *pSendPacket = (bool *)(***(uintptr_t ***)_bp - 0x1);

	if (!pCmd || !pCmd->command_number)
		return Hook.CallOriginal<fn>()(ecx, edx, flInputSampleTime, pCmd);

	return Hook.CallOriginal<fn>()(ecx, edx, flInputSampleTime, pCmd);
}

void Hooks::CreateMove::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::ClientModeShared, 21));
	Hook.Create(FN, Func);
}