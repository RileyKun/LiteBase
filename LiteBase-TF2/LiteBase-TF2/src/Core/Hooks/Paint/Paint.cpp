#include "Paint.h"
#include "../../Features/Example/Example.h"

void __fastcall Hooks::Paint::Func(void *ecx, void *edx, int mode)
{
	Hook.CallOriginal<fn>()(ecx, edx, mode);

	if (mode & PAINT_UIPANELS)
	{
		if (!g_Draw.m_nScreenW || !g_Draw.m_nScreenH)
			g_Draw.UpdateScreenSize();

		g_Draw.UpdateW2SMatrix();

		I::Surface->StartDrawing();
		{
			g_Example.Run();
		}
		I::Surface->FinishDrawing();
	}
}

void Hooks::Paint::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::EngineVGui, 13));
	Hook.Create(FN, Func);
}