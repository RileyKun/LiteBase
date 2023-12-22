#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace FrameStageNotify
	{
		inline CHook Hook;
		using fn = void(__fastcall *)(void *, void *, ClientFrameStage_t);
		void __fastcall Func(void *ecx, void *edx, ClientFrameStage_t curStage);
		void Init();
	}
}