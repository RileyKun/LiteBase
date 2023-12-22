#pragma once
#include "../TF2/TF2.h"

#define TXT_DEFAULT		(1 << 0)
#define TXT_LEFT		(1 << 1)
#define TXT_TOP			(1 << 2)
#define TXT_CENTERX		(1 << 3)
#define TXT_CENTERY		(1 << 4)
#define TXT_CENTERXY	TXT_CENTERX | TXT_CENTERY

class CFont
{
public:
	const char *m_szName;
	int m_nTall, m_nFlags;
	DWORD m_dwFont;
};

enum class EFonts {
	DEBUG
};

inline std::map<EFonts, CFont> g_Fonts;

class CDraw
{
public:
	void ReloadFonts();
	void UpdateScreenSize();
	void UpdateW2SMatrix();

public:
	int m_nScreenW = 0, m_nScreenH = 0;
	VMatrix m_WorldToProjection;

public:
	void String(const DWORD &font, int x, int y, Color_t clr, short align, const char *str, ...);
	void String(const DWORD &font, int x, int y, Color_t clr, short align, const wchar_t *str, ...);
	void Line(int x, int y, int x1, int y1, Color_t clr);
	void Rect(int x, int y, int w, int h, Color_t clr);
	void OutlinedRect(int x, int y, int w, int h, Color_t clr);
	void GradientRect(int x, int y, int x1, int y1, Color_t top_clr, Color_t bottom_clr, bool horizontal);
};

inline CDraw g_Draw;