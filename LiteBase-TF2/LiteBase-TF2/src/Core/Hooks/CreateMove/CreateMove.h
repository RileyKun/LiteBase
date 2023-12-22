#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace CreateMove
	{
		inline CHook Hook;
		using fn = bool(__fastcall *)(void *, void *, float, CUserCmd *);
		bool __fastcall Func(void *ecx, void *edx, float flInputSampleTime, CUserCmd *pCmd);
		void Init();
	}
}