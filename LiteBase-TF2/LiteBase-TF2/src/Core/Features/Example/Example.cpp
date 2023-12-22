#include "Example.h"

void CExample::Run()
{
	if (I::EngineVGui->IsGameUIVisible())
		return;

	if (auto pLocal = g_EntityCache.GetLocal())
	{
		if (pLocal->deadflag())
			return;

		//ThirdPerson Toggle
		{
			static bool bToggle = false;
			static float flLastHit = I::GlobalVars->curtime;

			if (GetAsyncKeyState('R') & 0x8000)
			{
				if ((I::GlobalVars->curtime - flLastHit) > 0.25f) {
					pLocal->m_nForceTauntCam() = static_cast<int>(bToggle = !bToggle);
					flLastHit = I::GlobalVars->curtime;
				}
			}
		}

		g_Draw.String(
			g_Fonts[EFonts::DEBUG].m_dwFont,
			200, 200,
			{ 255, 255, 255, 255 }, TXT_CENTERXY,
			L"PLAYERS_ALL -> %d", g_EntityCache.GetGroup(EEntGroup::PLAYERS_ALL).size()
		);

		g_Draw.String(
			g_Fonts[EFonts::DEBUG].m_dwFont,
			200, 220,
			{ 255, 255, 255, 255 }, TXT_CENTERXY,
			L"PLAYERS_ENEMIES -> %d", g_EntityCache.GetGroup(EEntGroup::PLAYERS_ENEMIES).size()
		);

		g_Draw.String(
			g_Fonts[EFonts::DEBUG].m_dwFont,
			200, 240,
			{ 255, 255, 255, 255 }, TXT_CENTERXY,
			L"PLAYERS_TEAMMATES -> %d", g_EntityCache.GetGroup(EEntGroup::PLAYERS_TEAMMATES).size()
		);
		
		for (auto pEntity : g_EntityCache.GetGroup(EEntGroup::PLAYERS_ALL))
		{
			auto pPlayer = pEntity->As<CTFPlayer>();

			if (pPlayer->deadflag())
				continue;

			Vec3 vBody = {};

			if (!Utils::W2S(pPlayer->GetHitboxPos(HITBOX_PELVIS), vBody))
				continue;

			bool bIsLocal = pPlayer == pLocal;

			Color_t DrawColor = G::GetEntityColor(pPlayer);

			if (!bIsLocal)
			{
				Vec3 vOrigin = {};

				if (Utils::W2S(pPlayer->GetAbsOrigin(), vOrigin))
				{
					g_Draw.Line(
						g_Draw.m_nScreenW / 2, g_Draw.m_nScreenH,
						static_cast<int>(vOrigin.x), static_cast<int>(vOrigin.y),
						DrawColor
					);
				}
			}

			int nTextOffset = 0;

			player_info_t pi = {};

			if (!I::EngineClient->GetPlayerInfo(pPlayer->entindex(), &pi))
				continue;

			g_Draw.String(
				g_Fonts[EFonts::DEBUG].m_dwFont,
				static_cast<int>(vBody.x), static_cast<int>(vBody.y) + nTextOffset,
				DrawColor, TXT_CENTERXY,
				Utils::ConvertUtf8ToWide(pi.m_sName).c_str()
			);

			nTextOffset += g_Fonts[EFonts::DEBUG].m_nTall;

			g_Draw.String(
				g_Fonts[EFonts::DEBUG].m_dwFont,
				static_cast<int>(vBody.x), static_cast<int>(vBody.y) + nTextOffset,
				DrawColor, TXT_CENTERXY,
				L"%d / %d", pPlayer->m_iHealth(), pPlayer->GetMaxHealth()
			);

			nTextOffset += g_Fonts[EFonts::DEBUG].m_nTall;

			if (pPlayer->InCond(TF_COND_ZOOMED))
			{
				g_Draw.String(
					g_Fonts[EFonts::DEBUG].m_dwFont,
					static_cast<int>(vBody.x), static_cast<int>(vBody.y) + nTextOffset,
					{ 255, 255, 0, 255 }, TXT_CENTERXY,
					L"ZOOM"
				);
			}
		}
	}
}