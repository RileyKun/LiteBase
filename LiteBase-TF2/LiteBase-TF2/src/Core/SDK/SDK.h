#pragma once
#include "Include/Include.h"

#pragma warning (push)
#pragma warning (disable : 6385)

namespace Utils
{
	inline bool W2S(const Vec3 &vOrigin, Vec3 &vScreen)
	{
		const matrix3x4_t &w2s = g_Draw.m_WorldToProjection.As3x4();

		float w = w2s[3][0] * vOrigin[0] + w2s[3][1] * vOrigin[1] + w2s[3][2] * vOrigin[2] + w2s[3][3];

		if (w > 0.001f) {
			float flsw = static_cast<float>(g_Draw.m_nScreenW);
			float flsh = static_cast<float>(g_Draw.m_nScreenH);
			float fl1dbw = 1.0f / w;
			vScreen.x = (flsw / 2.0f) + (0.5f * ((w2s[0][0] * vOrigin[0] + w2s[0][1] * vOrigin[1] + w2s[0][2] * vOrigin[2] + w2s[0][3]) * fl1dbw) * flsw + 0.5f);
			vScreen.y = (flsh / 2.0f) - (0.5f * ((w2s[1][0] * vOrigin[0] + w2s[1][1] * vOrigin[1] + w2s[1][2] * vOrigin[2] + w2s[1][3]) * fl1dbw) * flsh + 0.5f);
			return true;
		}
		
		return false;
	}

	inline void Trace(const Vec3 &start, const Vec3 &end, unsigned int mask, CTraceFilter *filter, trace_t *trace)
	{
		Ray_t ray = {};
		ray.Init(start, end);
		I::EngineTrace->TraceRay(ray, mask, filter, trace);
	}

	inline bool VisPos(const Vec3 &from, const Vec3 &to)
	{
		trace_t trace = {};
		CTraceFilterWorldAndPropsOnly filter = {};
		Trace(from, to, MASK_SOLID, &filter, &trace);
		return trace.fraction > 0.99f;
	}
}

#pragma warning (pop)

namespace G
{
	inline std::map<CTFPlayer *, bool> mapFriends;

	inline bool IsFriend(CTFPlayer *pPlayer)
	{
		if (mapFriends.find(pPlayer) != mapFriends.end())
			return mapFriends[pPlayer];

		return false;
	}

	inline Color_t GetEntityColor(CBaseEntity *pEntity)
	{
		if (pEntity->entindex() == LOCAL_IDX || G::IsFriend(pEntity->As<CTFPlayer>()))
			return { 50, 255, 60, 255 };

		switch (pEntity->m_iTeamNum()) {
			case 2: return { 255, 107, 107, 255 };
			case 3: return { 72, 219, 251, 255 };
			default: return { 255, 255, 255, 255 };
		}
	}
}