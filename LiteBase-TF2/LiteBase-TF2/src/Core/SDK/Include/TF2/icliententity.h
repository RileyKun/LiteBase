#pragma once
#include "iclientrenderable.h"
#include "iclientnetworkable.h"
#include "iclientthinkable.h"
#include "const_light.h"
#include "../NetVar/NetVar.h"

struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void Release(void) = 0;
	virtual const Vector &GetAbsOrigin(void) const = 0;
	virtual const QAngle &GetAbsAngles(void) const = 0;
	virtual CMouthInfo *GetMouth(void) = 0;
	virtual bool GetSoundSpatialization(SpatializationInfo_t &info) = 0;
	template <typename T> inline T *As() { return reinterpret_cast<T *>(this); }
};