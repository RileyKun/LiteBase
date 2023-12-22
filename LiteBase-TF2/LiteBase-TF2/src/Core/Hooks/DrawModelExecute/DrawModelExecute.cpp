#include "DrawModelExecute.h"

void __fastcall Hooks::DrawModelExecute::Func(void *ecx, void *edx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	static IMaterial *pMat = nullptr;

	if (!pMat)
	{
		KeyValues *pKeyVals = new KeyValues("VertexLitGeneric");
		pKeyVals->SetString("$basetexture", "vgui/white_additive");
		pKeyVals->SetString("$bumpmap", "vgui/white_additive");
		pKeyVals->SetString("$selfillum", "1");
		pKeyVals->SetString("$selfillumfresnel", "1");
		pKeyVals->SetString("$selfillumfresnelminmaxexp", "[0.1 1 2]");
		pMat = I::MaterialSystem->CreateMaterial("ChamMaterial", pKeyVals);
	}

	if (auto pEntity = GET_ENT_I(pInfo.entity_index))
	{
		if (pEntity->GetClassId() == EClassIds::CTFPlayer)
		{
			I::RenderView->SetColorModulation(G::GetEntityColor(pEntity->As<CBaseEntity>()));
			I::ModelRender->ForcedMaterialOverride(pMat);
			Hook.CallOriginal<fn>()(ecx, edx, state, pInfo, pCustomBoneToWorld);
			I::ModelRender->ForcedMaterialOverride(nullptr);
			I::RenderView->SetColorModulation(1.0f, 1.0f, 1.0f);
			return;
		}
	}

	Hook.CallOriginal<fn>()(ecx, edx, state, pInfo, pCustomBoneToWorld);
}

void Hooks::DrawModelExecute::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::ModelRender, 19));
	Hook.Create(FN, Func);
}