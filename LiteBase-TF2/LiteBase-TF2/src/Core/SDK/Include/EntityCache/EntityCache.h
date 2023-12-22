#pragma once
#include "../Draw/Draw.h"

enum class EEntGroup {
	PLAYERS_ALL, PLAYERS_ENEMIES, PLAYERS_TEAMMATES,
	BUILDINGS_ALL, BUILDINGS_ENEMIES, BUILDINGS_TEAMMATES
};

class CEntityCache
{
private:
	std::map<EEntGroup, std::vector<IClientEntity *>> m_Groups;
	CTFPlayer *m_pLocal = nullptr;
	CTFWeaponBase *m_pWeapon = nullptr;

public:
	void Fill();
	void Clear();

public:
	const std::vector<IClientEntity *> &GetGroup(EEntGroup Group);
	CTFPlayer *GetLocal();
	CTFWeaponBase *GetWeapon();
};

inline CEntityCache g_EntityCache;