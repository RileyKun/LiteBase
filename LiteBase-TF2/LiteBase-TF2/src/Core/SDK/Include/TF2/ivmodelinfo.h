#pragma once
#include "IEngineTrace.h"

class IMaterial;
class KeyValues;
struct vcollide_t;
struct model_t;
struct cplane_t;
struct studiohdr_t;
struct virtualmodel_t;
typedef unsigned char byte;
struct virtualterrainparams_t;
class CPhysCollide;
typedef unsigned short MDLHandle_t;
class CUtlBuffer;

class IModelLoadCallback
{
public:
	virtual void OnModelLoadComplete(const model_t *pModel) = 0;
};

class IVModelInfo
{
public:
	virtual ~IVModelInfo(void) = 0;
	virtual const model_t *GetModel(int modelindex) = 0;
	virtual int GetModelIndex(const char *name) const = 0;
	virtual const char *GetModelName(const model_t *model) const = 0;
	virtual vcollide_t *GetVCollide(const model_t *model) = 0;
	virtual vcollide_t *GetVCollide(int modelindex) = 0;
	virtual void GetModelBounds(const model_t *model, Vector &mins, Vector &maxs) const = 0;
	virtual	void GetModelRenderBounds(const model_t *model, Vector &mins, Vector &maxs) const = 0;
	virtual int GetModelFrameCount(const model_t *model) const = 0;
	virtual int GetModelType(const model_t *model) const = 0;
	virtual void *GetModelExtraData(const model_t *model) = 0;
	virtual bool ModelHasMaterialProxy(const model_t *model) const = 0;
	virtual bool IsTranslucent(model_t const *model) const = 0;
	virtual bool IsTranslucentTwoPass(const model_t *model) const = 0;
	virtual void RecomputeTranslucency(const model_t *model, int nSkin, int nBody, void *pClientRenderable, float fInstanceAlphaModulate = 1.0f) = 0;
	virtual int GetModelMaterialCount(const model_t *model) const = 0;
	virtual void GetModelMaterials(const model_t *model, int count, IMaterial **ppMaterial) = 0;
	virtual bool IsModelVertexLit(const model_t *model) const = 0;
	virtual const char *GetModelKeyValueText(const model_t *model) = 0;
	virtual bool GetModelKeyValue(const model_t *model, CUtlBuffer &buf) = 0;
	virtual float GetModelRadius(const model_t *model) = 0;
	virtual const studiohdr_t *FindModel(const studiohdr_t *pStudioHdr, void **cache, const char *modelname) const = 0;
	virtual const studiohdr_t *FindModel(void *cache) const = 0;
	virtual	virtualmodel_t *GetVirtualModel(const studiohdr_t *pStudioHdr) const = 0;
	virtual byte *GetAnimBlock(const studiohdr_t *pStudioHdr, int iBlock) const = 0;
	virtual void GetModelMaterialColorAndLighting(const model_t *model, Vector const &origin, QAngle const &angles, trace_t *pTrace, Vector &lighting, Vector &matColor) = 0;
	virtual void GetIlluminationPoint(const model_t *model, IClientRenderable *pRenderable, Vector const &origin, QAngle const &angles, Vector *pLightingCenter) = 0;
	virtual int GetModelContents(int modelIndex) = 0;
	virtual studiohdr_t *GetStudiomodel(const model_t *mod) = 0;
	virtual int GetModelSpriteWidth(const model_t *model) const = 0;
	virtual int GetModelSpriteHeight(const model_t *model) const = 0;
	virtual void SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void GetLevelScreenFadeRange(float *pMinArea, float *pMaxArea) const = 0;
	virtual void SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual unsigned char ComputeLevelScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char ComputeViewScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual int GetAutoplayList(const studiohdr_t *pStudioHdr, unsigned short **pAutoplayList) const = 0;
	virtual CPhysCollide *GetCollideForVirtualTerrain(int index) = 0;
	virtual bool IsUsingFBTexture(const model_t *model, int nSkin, int nBody, void *pClientRenderable) const = 0;
	virtual const model_t *FindOrLoadModel(const char *name) = 0;
	virtual void InitDynamicModels() = 0;
	virtual void ShutdownDynamicModels() = 0;
	virtual void AddDynamicModel(const char *name, int nModelIndex = -1) = 0;
	virtual void ReferenceModel(int modelindex) = 0;
	virtual void UnreferenceModel(int modelindex) = 0;
	virtual void CleanupDynamicModels(bool bForce = false) = 0;
	virtual MDLHandle_t GetCacheHandle(const model_t *model) const = 0;
	virtual int GetBrushModelPlaneCount(const model_t *model) const = 0;
	virtual void GetBrushModelPlane(const model_t *model, int nIndex, cplane_t &plane, Vector *pOrigin) const = 0;
	virtual int GetSurfacepropsForVirtualTerrain(int index) = 0;
	virtual void OnLevelChange() = 0;
	virtual int GetModelClientSideIndex(const char *name) const = 0;
	virtual int RegisterDynamicModel(const char *name, bool bClientSide) = 0;
	virtual bool IsDynamicModelLoading(int modelIndex) = 0;
	virtual void AddRefDynamicModel(int modelIndex) = 0;
	virtual void ReleaseDynamicModel(int modelIndex) = 0;
	virtual bool RegisterModelLoadCallback(int modelindex, IModelLoadCallback *pCallback, bool bCallImmediatelyIfLoaded = true) = 0;
	virtual void UnregisterModelLoadCallback(int modelindex, IModelLoadCallback *pCallback) = 0;
};

namespace I { inline IVModelInfo *ModelInfo; }