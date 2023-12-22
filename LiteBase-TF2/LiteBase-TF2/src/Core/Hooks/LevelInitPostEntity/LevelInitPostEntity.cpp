#include "LevelInitPostEntity.h"

void __fastcall Hooks::LevelInitPostEntity::Func(void *ecx, void *edx)
{
	Hook.CallOriginal<fn>()(ecx, edx);
}

void Hooks::LevelInitPostEntity::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::BaseClientDLL, 6));
	Hook.Create(FN, Func);
}