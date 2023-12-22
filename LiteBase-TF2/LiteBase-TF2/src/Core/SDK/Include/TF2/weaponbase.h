#pragma once
#include "basecombatweapon.h"
#include "GameEventListener.h"
#include "ihasowner.h"
#include "globalvars_base.h"
#include "tf_player.h"

class CTFWeaponBase : public CBaseCombatWeapon, public IHasOwner, public CGameEventListener
{
public:
	NETVAR(m_bLowered, bool, "CTFWeaponBase", "m_bLowered");
	NETVAR(m_iReloadMode, int, "CTFWeaponBase", "m_iReloadMode");
	NETVAR(m_bResetParity, bool, "CTFWeaponBase", "m_bResetParity");
	NETVAR(m_bReloadedThroughAnimEvent, bool, "CTFWeaponBase", "m_bReloadedThroughAnimEvent");
	NETVAR(m_bDisguiseWeapon, bool, "CTFWeaponBase", "m_bDisguiseWeapon");
	NETVAR(m_flLastCritCheckTime, float, "CTFWeaponBase", "m_flLastCritCheckTime");
	NETVAR(m_flReloadPriorNextFire, float, "CTFWeaponBase", "m_flReloadPriorNextFire");
	NETVAR(m_flLastFireTime, float, "CTFWeaponBase", "m_flLastFireTime");
	NETVAR(m_flEffectBarRegenTime, float, "CTFWeaponBase", "m_flEffectBarRegenTime");
	NETVAR(m_flObservedCritChance, float, "CTFWeaponBase", "m_flObservedCritChance");
	NETVAR(m_flEnergy, float, "CTFWeaponBase", "m_flEnergy");
	NETVAR(m_hExtraWearable, int, "CTFWeaponBase", "m_hExtraWearable");
	NETVAR(m_hExtraWearableViewModel, int, "CTFWeaponBase", "m_hExtraWearableViewModel");
	NETVAR(m_bBeingRepurposedForTaunt, bool, "CTFWeaponBase", "m_bBeingRepurposedForTaunt");
	NETVAR(m_nKillComboClass, int, "CTFWeaponBase", "m_nKillComboClass");
	NETVAR(m_nKillComboCount, int, "CTFWeaponBase", "m_nKillComboCount");
	NETVAR(m_flInspectAnimEndTime, float, "CTFWeaponBase", "m_flInspectAnimEndTime");
	NETVAR(m_nInspectStage, int, "CTFWeaponBase", "m_nInspectStage");
	NETVAR(m_iConsecutiveShots, int, "CTFWeaponBase", "m_iConsecutiveShots");

	//doesn't belong here!
	NETVAR(m_iItemDefinitionIndex, int, "CEconEntity", "m_iItemDefinitionIndex");

	inline int GetSlot() {
		using fn = int(__thiscall *)(void *);
		fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(this, 327));
		return FN(this);
	}

	inline int GetWeaponID() {
		using fn = int(__thiscall *)(void *);
		fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(this, 377));
		return FN(this);
	}

	inline int GetDamageType() {
		using fn = int(__thiscall *)(void *);
		fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(this, 378));
		return FN(this);
	}

	inline bool CanFireCriticalShot(CTFPlayer *pOwner, bool bIsHeadshot = false)
	{
		bool bOut = false;

		//the fov shit might be only needed for when checking bIsHeadshot but whatever
		if (pOwner)
		{
			using fn = bool(__thiscall *)(void *, bool, void *);
			fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(this, 421));
			int &iFOV = pOwner->m_iFOV(), nFovBackup = iFOV;

			iFOV = 70;
			bOut = FN(this, bIsHeadshot, nullptr);
			iFOV = nFovBackup;
		}
	
		return bOut;
	}

	inline bool CanHeadShot(CTFPlayer *pOwner)
	{
		bool bOut = false;

		if (pOwner)
			bOut = (GetDamageType() & DMG_USE_HITLOCATIONS) && CanFireCriticalShot(pOwner, true);

		return bOut;
	}

	inline bool CanPrimaryAttack(CTFPlayer *pOwner)
	{
		bool bOut = false;
		
		if (pOwner)
			bOut = m_flNextPrimaryAttack() < (static_cast<float>(pOwner->m_nTickBase()) * I::GlobalVars->interval_per_tick);

		return bOut;
	}

	inline bool CanSecondaryAttack(CTFPlayer *pOwner)
	{
		bool bOut = false;

		if (pOwner)
			bOut = m_flNextSecondaryAttack() < (static_cast<float>(pOwner->m_nTickBase()) * I::GlobalVars->interval_per_tick);

		return bOut;
	}
};

class CTFKnife : public CTFWeaponBase
{
public:
	NETVAR(m_bReadyToBackstab, bool, "CTFKnife", "m_bReadyToBackstab");
	NETVAR(m_bKnifeExists, bool, "CTFKnife", "m_bKnifeExists");
	NETVAR(m_flKnifeRegenerateDuration, float, "CTFKnife", "m_flKnifeRegenerateDuration");
	NETVAR(m_flKnifeMeltTimestamp, float, "CTFKnife", "m_flKnifeMeltTimestamp");
};

class CTFMinigun : public CTFWeaponBase
{
public:
	NETVAR(m_iWeaponState, int, "CTFMinigun", "m_iWeaponState");
	NETVAR(m_bCritShot, bool, "CTFMinigun", "m_bCritShot");
};

class CWeaponMedigun : public CTFWeaponBase
{
public:
	NETVAR(m_hHealingTarget, int, "CWeaponMedigun", "m_hHealingTarget");
	NETVAR(m_bHealing, bool, "CWeaponMedigun", "m_bHealing");
	NETVAR(m_bAttacking, bool, "CWeaponMedigun", "m_bAttacking");
	NETVAR(m_bChargeRelease, bool, "CWeaponMedigun", "m_bChargeRelease");
	NETVAR(m_bHolstered, bool, "CWeaponMedigun", "m_bHolstered");
	NETVAR(m_nChargeResistType, int, "CWeaponMedigun", "m_nChargeResistType");
	NETVAR(m_hLastHealingTarget, int, "CWeaponMedigun", "m_hLastHealingTarget");
	NETVAR(m_flChargeLevel, float, "CWeaponMedigun", "m_flChargeLevel");
};

class CTFPipebombLauncher : public CTFWeaponBase
{
public:
	NETVAR(m_iPipebombCount, int, "CTFPipebombLauncher", "m_iPipebombCount");
	NETVAR(m_flChargeBeginTime, float, "CTFPipebombLauncher", "m_flChargeBeginTime");
};

class CTFSniperRifle : public CTFWeaponBase
{
public:
	NETVAR(m_flChargedDamage, float, "CTFSniperRifle", "m_flChargedDamage");
};