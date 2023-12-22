#pragma once

class CAttributeManager;
class CAttributeContainer;
class CBaseEntity;
class CAttributeList;

class IHasAttributes
{
public:
	virtual CAttributeManager *GetAttributeManager(void) = 0;
	virtual CAttributeContainer *GetAttributeContainer(void) = 0;
	virtual CBaseEntity *GetAttributeOwner(void) = 0;
	virtual CAttributeList *GetAttributeList(void) = 0;
	virtual void ReapplyProvision(void) = 0;
};