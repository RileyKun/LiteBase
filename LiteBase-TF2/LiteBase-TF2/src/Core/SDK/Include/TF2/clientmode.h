#pragma once
#include "iclientmode.h"

class CBaseViewport;
class CReplayReminderPanel;
class CBaseHudChat;
class CBaseHudWeaponSelection;

class CClientModeShared : public IClientMode, public CGameEventListener
{
public:
	virtual ~CClientModeShared();
	virtual void Init();
	virtual void InitViewport();
	virtual void VGui_Shutdown();
	virtual void Shutdown();
	virtual void LevelInit(const char *newmap);
	virtual void LevelShutdown(void);
	virtual void Enable();
	virtual void Disable();
	virtual void Layout();
	virtual void ReloadScheme(bool flushLowLevel);
	virtual void OverrideView(CViewSetup *pSetup);
	virtual bool ShouldDrawDetailObjects();
	virtual bool ShouldDrawEntity(CBaseEntity *pEnt);
	virtual bool ShouldDrawLocalPlayer(CBasePlayer *pPlayer);
	virtual bool ShouldDrawViewModel();
	virtual bool ShouldDrawParticles();
	virtual bool ShouldDrawCrosshair(void);
	virtual bool ShouldBlackoutAroundHUD() = 0;
	virtual HeadtrackMovementMode_t ShouldOverrideHeadtrackControl() = 0;
	virtual void AdjustEngineViewport(int &x, int &y, int &width, int &height);
	virtual void PreRender(CViewSetup *pSetup);
	virtual void PostRender();
	virtual void PostRenderVGui();
	virtual void ProcessInput(bool bActive);
	virtual bool CreateMove(float flInputSampleTime, CUserCmd *cmd);
	virtual void Update();
	virtual int KeyInput(int down, ButtonCode_t keynum, const char *pszCurrentBinding);
	virtual int HudElementKeyInput(int down, ButtonCode_t keynum, const char *pszCurrentBinding);
	virtual void OverrideMouseInput(float *x, float *y);
	virtual void StartMessageMode(int iMessageModeType);
	virtual unsigned int *GetMessagePanel();
	virtual void ActivateInGameVGuiContext(unsigned int *pPanel);
	virtual void DeactivateInGameVGuiContext();
	virtual bool ShouldDrawFog(void);
	virtual float GetViewModelFOV(void);
	virtual unsigned int *GetViewport() = 0;
	virtual void *GetViewportAnimationController() = 0;
	virtual void FireGameEvent(IGameEvent *event);
	virtual bool CanRecordDemo(char *errorMsg, int length) const { return true; }
	virtual int HandleSpectatorKeyInput(int down, ButtonCode_t keynum, const char *pszCurrentBinding);
	virtual void ComputeVguiResConditions(KeyValues *pkvConditions) = 0;
	virtual wchar_t *GetServerName() { return NULL; }
	virtual void SetServerName(wchar_t *name) {}
	virtual wchar_t *GetMapName() { return NULL; }
	virtual void SetMapName(wchar_t *name) {}
	virtual bool DoPostScreenSpaceEffects(const CViewSetup *pSetup);
	virtual void DisplayReplayMessage(const char *pLocalizeName, float flDuration, bool bUrgent, const char *pSound, bool bDlg);
	virtual bool IsInfoPanelAllowed() = 0;
	virtual void InfoPanelDisplayed() = 0;
	virtual bool IsHTMLInfoPanelAllowed() = 0;
	virtual void OnDemoRecordStart(char const *pDemoBaseName) = 0;
	virtual void OnDemoRecordStop() = 0;

	CBaseViewport *m_pViewport;
	virtual void UpdateReplayMessages() = 0;
	float m_flReplayStartRecordTime;
	float m_flReplayStopRecordTime;
	CReplayReminderPanel *m_pReplayReminderPanel;
	CBaseHudChat *m_pChatElement;
	unsigned long m_CursorNone;
	CBaseHudWeaponSelection *m_pWeaponSelection;
	int m_nRootSize[2];
};

namespace I { inline CClientModeShared *ClientModeShared; }