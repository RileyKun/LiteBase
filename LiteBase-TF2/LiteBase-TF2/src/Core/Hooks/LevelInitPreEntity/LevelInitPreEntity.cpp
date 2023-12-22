#include "LevelInitPreEntity.h"

void __fastcall Hooks::LevelInitPreEntity::Func(void *ecx, void *edx, char const *pMapName)
{
	Hook.CallOriginal<fn>()(ecx, edx, pMapName);
}

void Hooks::LevelInitPreEntity::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::BaseClientDLL, 5));
	Hook.Create(FN, Func);
}