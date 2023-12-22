#pragma once

class IClientEntity;
class IClientNetworkable;
class IClientUnknown;
using CBaseHandle = unsigned int;

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &handle) = 0;
	virtual const CBaseHandle &GetRefEHandle() const = 0;
};

class IClientEntityList
{
public:
	virtual IClientNetworkable *GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable *GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown *GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientEntity *GetClientEntity(int entnum) = 0;
	virtual IClientEntity *GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int GetHighestEntityIndex(void) = 0;
	virtual void SetMaxEntities(int maxents) = 0;
	virtual int GetMaxEntities() = 0;
};

namespace I { inline IClientEntityList *ClientEntityList; }

#define LOCAL_IDX I::EngineClient->GetLocalPlayer()
#define GET_ENT_I(index) I::ClientEntityList->GetClientEntity(index)
#define GET_ENT_H(handle) I::ClientEntityList->GetClientEntityFromHandle(handle)