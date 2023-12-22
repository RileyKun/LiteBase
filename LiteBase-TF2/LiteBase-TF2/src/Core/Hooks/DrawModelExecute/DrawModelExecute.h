#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace DrawModelExecute
	{
		inline CHook Hook;
		using fn = void(__fastcall *)(void *, void *, const DrawModelState_t &, const ModelRenderInfo_t &, matrix3x4_t *);
		void __fastcall Func(void *ecx, void *edx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
		void Init();
	}
}