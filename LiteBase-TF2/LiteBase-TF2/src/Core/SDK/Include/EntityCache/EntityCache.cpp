#include "EntityCache.h"

void CEntityCache::Fill()
{
	if (m_pLocal = GET_ENT_I(LOCAL_IDX)->As<CTFPlayer>())
	{
		int nLocalTeam = m_pLocal->m_iTeamNum();

		if (nLocalTeam != TEAM_RED && nLocalTeam != TEAM_BLU) {
			m_pLocal = nullptr;
			return;
		}

		m_pWeapon = GET_ENT_H(m_pLocal->m_hActiveWeapon())->As<CTFWeaponBase>();

		for (int n = 1; n < I::ClientEntityList->GetHighestEntityIndex(); n++)
		{
			IClientEntity *pEntity = GET_ENT_I(n);

			if (!pEntity || pEntity->IsDormant())
				continue;

			switch (pEntity->GetClassId())
			{
				case EClassIds::CTFPlayer:
				{
					int nPlayerTeam = pEntity->As<CTFPlayer>()->m_iTeamNum();

					if (nPlayerTeam != TEAM_RED && nPlayerTeam != TEAM_BLU)
						continue;

					m_Groups[EEntGroup::PLAYERS_ALL].push_back(pEntity);
					m_Groups[nLocalTeam != nPlayerTeam ? EEntGroup::PLAYERS_ENEMIES : EEntGroup::PLAYERS_TEAMMATES].push_back(pEntity);

					break;
				}

				case EClassIds::CObjectSentrygun:
				case EClassIds::CObjectDispenser:
				case EClassIds::CObjectTeleporter:
				{
					int nObjectTeam = pEntity->As<CBaseObject>()->m_iTeamNum();

					m_Groups[EEntGroup::BUILDINGS_ALL].push_back(pEntity);
					m_Groups[nLocalTeam != nObjectTeam ? EEntGroup::BUILDINGS_ENEMIES : EEntGroup::BUILDINGS_TEAMMATES].push_back(pEntity);

					break;
				}

				default: break;
			}
		}
	}
}

void CEntityCache::Clear()
{
	for (auto &Group : m_Groups)
		Group.second.clear();

	m_pLocal = nullptr;
	m_pWeapon = nullptr;
}

const std::vector<IClientEntity *> &CEntityCache::GetGroup(EEntGroup Group) {
	return m_Groups[Group];
}

CTFPlayer *CEntityCache::GetLocal() {
	return m_pLocal;
}

CTFWeaponBase *CEntityCache::GetWeapon() {
	return m_pWeapon;
}