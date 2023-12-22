#include "FrameStageNotify.h"

void __fastcall Hooks::FrameStageNotify::Func(void *ecx, void *edx, ClientFrameStage_t curStage)
{
	Hook.CallOriginal<fn>()(ecx, edx, curStage);

	switch (curStage)
	{
		case ClientFrameStage_t::FRAME_NET_UPDATE_START: {
			g_EntityCache.Clear();
			break;
		}

		case ClientFrameStage_t::FRAME_NET_UPDATE_END: {
			g_EntityCache.Fill();
			break;
		}
	}
}

void Hooks::FrameStageNotify::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::BaseClientDLL, 35));
	Hook.Create(FN, Func);
}