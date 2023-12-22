#include "Core.h"

//std::ofstream File;
//const char *szClassName;
//
//void DumpTable(RecvTable *pTable, int nDepth)
//{
//	if (!pTable)
//		return;
//
//	const char *Types[7] = { "int", "float", "Vec3", "Vec2", "const char *", "Array", "void *" };
//
//	if (nDepth == 0)
//		File << "class " << szClassName << "\n{\npublic:\n";
//
//	for (int n = 0; n < pTable->m_nProps; n++)
//	{
//		RecvProp *pProp = pTable->GetPropW(n);
//
//		if (!pProp)
//			continue;
//
//		std::string_view sVarName(pProp->m_pVarName);
//
//		if (!sVarName.find("baseclass") || !sVarName.find("0") || !sVarName.find("1") || !sVarName.find("2"))
//			continue;
//
//		const char *szType = Types[pProp->GetType()];
//
//		if (sVarName.find("m_b") == 0 && pProp->GetType() == 0)
//			szType = "bool";
//
//		if (pProp->GetOffset())
//			File << "\tNETVAR(" << sVarName << ", " << szType << ", \"" << szClassName << "\", \"" << sVarName << "\");\n";
//
//		if (auto DataTable = pProp->GetDataTable())
//			DumpTable(DataTable, nDepth + 1);
//	}
//
//	if (nDepth == 0)
//		File << "};\n";
//}
//
//void DumpTables()
//{
//	File.open("NETVAR_DUMP_NEW.h");
//
//	for (ClientClass *pClass = I::BaseClientDLL->GetAllClasses(); pClass; pClass = pClass->m_pNext) {
//		szClassName = pClass->m_pNetworkName;
//		DumpTable(pClass->m_pRecvTable, 0);
//	}
//
//	File.close();
//}

void CCore::Load()
{
	while (!GetModuleHandleW(L"mss32.dll"))
		Sleep(2500); //we sleepin'

	//Interfaces
	{
		I::Surface = reinterpret_cast<ISurface *>(g_Interface.Get(L"vguimatsurface.dll", "VGUI_Surface030"));
		I::EngineClient = reinterpret_cast<IVEngineClient013 *>(g_Interface.Get(L"engine.dll", "VEngineClient013"));
		I::BaseClientDLL = reinterpret_cast<IBaseClientDLL *>(g_Interface.Get(L"client.dll", "VClient017"));
		I::ClientEntityList = reinterpret_cast<IClientEntityList *>(g_Interface.Get(L"client.dll", "VClientEntityList003"));
		I::ModelInfo = reinterpret_cast<IVModelInfo *>(g_Interface.Get(L"engine.dll", "VModelInfoClient006"));
		I::DebugOverlay = reinterpret_cast<IVDebugOverlay *>(g_Interface.Get(L"engine.dll", "VDebugOverlay003"));
		I::ClientModeShared = **reinterpret_cast<CClientModeShared ***>(g_Pattern.Find(L"client.dll", L"8B 0D ? ? ? ? 8B 02 D9 05") + 0x2);
		I::MaterialSystem = reinterpret_cast<IMaterialSystem *>(g_Interface.Get(L"materialsystem.dll", "VMaterialSystem081"));
		I::ModelRender = reinterpret_cast<IVModelRender *>(g_Interface.Get(L"engine.dll", "VEngineModel016"));
		I::EngineVGui = reinterpret_cast<IEngineVGui *>(g_Interface.Get(L"engine.dll", "VEngineVGui001"));
		I::RenderView = reinterpret_cast<IVRenderView *>(g_Interface.Get(L"engine.dll", "VEngineRenderView014"));
		I::PlayerInfoManager = reinterpret_cast<IPlayerInfoManager *>(g_Interface.Get(L"server.dll", "PlayerInfoManager002"));
		I::GlobalVars = *reinterpret_cast<CGlobalVarsBase **>(g_Pattern.Find(L"engine.dll", L"A1 ? ? ? ? 8B 11 68") + 0x8);
		I::EngineTrace = reinterpret_cast<IEngineTrace *>(g_Interface.Get(L"engine.dll", "EngineTraceClient003"));
		I::CVar = reinterpret_cast<ICvar *>(g_Interface.Get(L"vstdlib.dll", "VEngineCvar004"));
		I::Prediction = reinterpret_cast<CPrediction *>(g_Interface.Get(L"client.dll", "VClientPrediction001"));
		I::MoveHelper = **reinterpret_cast<IMoveHelper ***>(g_Pattern.Find(L"client.dll", L"8B 0D ? ? ? ? 8B 46 08 68 ? ? ? ? 05 ? ? ? ? 8B 11 50") + 0x2);
	}
	
	//Other
	{
		g_Draw.ReloadFonts();
	}

	//Hooks
	{
		MH_Initialize();
		{
			Hooks::WndProc::Init();
			Hooks::CreateMove::Init();
			Hooks::Paint::Init();
			Hooks::OnScreenSizeChanged::Init();
			Hooks::FrameStageNotify::Init();
			Hooks::LevelInitPreEntity::Init();
			Hooks::LevelInitPostEntity::Init();
			Hooks::LevelShutdown::Init();
			Hooks::DrawModelExecute::Init();
			Hooks::IsPlayerOnSteamFriendsList::Init();
		}
		MH_EnableHook(MH_ALL_HOOKS);
	}

	I::CVar->ConsoleColorPrintf({ 0, 148, 50, 255 }, "Hake Loaded!\n");
}

void CCore::Unload()
{
	MH_Uninitialize();
	SetWindowLongPtr(Hooks::WndProc::hwWindow, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc::Original);
	I::CVar->ConsoleColorPrintf({ 237, 76, 103, 255 }, "Hake Unloaded!\n");
}

bool CCore::ShouldUnload()
{
	return GetAsyncKeyState(VK_F11) & 0x8000;
}