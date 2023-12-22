#pragma once
#include "../TF2/cdll_int.h"

inline int GetOffset(RecvTable *pTable, const char *szNetVar)
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		RecvProp Prop = pTable->m_pProps[i];

		if (std::string_view(Prop.m_pVarName).compare(szNetVar) == 0)
			return Prop.GetOffset();

		if (auto DataTable = Prop.GetDataTable())
		{
			if (auto nOffset = GetOffset(DataTable, szNetVar))
				return nOffset + Prop.GetOffset();
		}
	}

	return 0;
}

inline int GetNetVar(const char *szClass, const char *szNetVar)
{
	ClientClass *pClasses = I::BaseClientDLL->GetAllClasses();

	for (auto pCurrNode = pClasses; pCurrNode; pCurrNode = pCurrNode->m_pNext)
	{
		if (std::string_view(szClass).compare(pCurrNode->m_pNetworkName) == 0)
			return GetOffset(pCurrNode->m_pRecvTable, szNetVar);
	}

	return 0;
}

#define NETVAR(_name, type, table, name) inline type &_name() \
{ \
	static int offset = GetNetVar(table, name); \
	return *reinterpret_cast<type *>(reinterpret_cast<DWORD>(this) + offset); \
}