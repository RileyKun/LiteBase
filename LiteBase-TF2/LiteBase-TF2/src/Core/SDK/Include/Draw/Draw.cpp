#include "Draw.h"

void CDraw::ReloadFonts()
{
	g_Fonts[EFonts::DEBUG] = { "Verdana", 16, FONTFLAG_OUTLINE };

	for (auto &v : g_Fonts)
		I::Surface->SetFontGlyphSet(v.second.m_dwFont = I::Surface->CreateFont(), v.second.m_szName, v.second.m_nTall, 0, 0, 0, v.second.m_nFlags);
}

void CDraw::UpdateScreenSize()
{
	m_nScreenW = I::BaseClientDLL->GetScreenWidth();
	m_nScreenH = I::BaseClientDLL->GetScreenHeight();
}

void CDraw::UpdateW2SMatrix()
{
	CViewSetup ViewSetup = {};

	if (I::BaseClientDLL->GetPlayerView(ViewSetup)) {
		static VMatrix WorldToView = {}, ViewToProjection = {}, WorldToPixels = {};
		I::RenderView->GetMatricesForView(ViewSetup, &WorldToView, &ViewToProjection, &g_Draw.m_WorldToProjection, &WorldToPixels);
	}
}

void CDraw::String(const DWORD &font, int x, int y, Color_t clr, short align, const char *str, ...)
{
	if (str == 0)
		return;

	va_list va_alist;
	char cbuffer[1024] = { '\0' };
	wchar_t wstr[1024] = { '\0' };

	va_start(va_alist, str);
	vsprintf_s(cbuffer, str, va_alist);
	va_end(va_alist);

	wsprintfW(wstr, L"%hs", cbuffer);

	if (align)
	{
		int w = 0, h = 0;
		I::Surface->GetTextSize(font, wstr, w, h);

		if (align & TXT_LEFT)
			x -= w;

		if (align & TXT_TOP)
			y -= h;

		if (align & TXT_CENTERX)
			x -= (w / 2);

		if (align & TXT_CENTERY)
			y -= (h / 2);
	}

	I::Surface->DrawSetTextPos(x, y);
	I::Surface->DrawSetTextFont(font);
	I::Surface->DrawSetTextColor(clr.r, clr.g, clr.b, clr.a);
	I::Surface->DrawPrintText(wstr, wcslen(wstr));
}

void CDraw::String(const DWORD &font, int x, int y, Color_t clr, short align, const wchar_t *str, ...)
{
	if (str == 0)
		return;

	va_list va_alist;
	wchar_t wstr[1024] = { '\0' };

	va_start(va_alist, str);
	vswprintf_s(wstr, str, va_alist);
	va_end(va_alist);

	if (align)
	{
		int w = 0, h = 0;
		I::Surface->GetTextSize(font, wstr, w, h);

		if (align & TXT_LEFT)
			x -= w;

		if (align & TXT_TOP)
			y -= h;

		if (align & TXT_CENTERX)
			x -= (w / 2);

		if (align & TXT_CENTERY)
			y -= (h / 2);
	}

	I::Surface->DrawSetTextPos(x, y);
	I::Surface->DrawSetTextFont(font);
	I::Surface->DrawSetTextColor(clr.r, clr.g, clr.b, clr.a);
	I::Surface->DrawPrintText(wstr, wcslen(wstr));
}

void CDraw::Line(int x, int y, int x1, int y1, Color_t clr)
{
	I::Surface->DrawSetColor(clr.r, clr.g, clr.b, clr.a);
	I::Surface->DrawLine(x, y, x1, y1);
}

void CDraw::Rect(int x, int y, int w, int h, Color_t clr)
{
	I::Surface->DrawSetColor(clr.r, clr.g, clr.b, clr.a);
	I::Surface->DrawFilledRect(x, y, x + w, y + h);
}

void CDraw::OutlinedRect(int x, int y, int w, int h, Color_t clr)
{
	I::Surface->DrawSetColor(clr.r, clr.g, clr.b, clr.a);
	I::Surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void CDraw::GradientRect(int x, int y, int x1, int y1, Color_t top_clr, Color_t bottom_clr, bool horizontal)
{
	I::Surface->DrawSetColor(top_clr.r, top_clr.g, top_clr.b, top_clr.a);
	I::Surface->DrawFilledRectFade(x, y, x1, y1, 255, 255, horizontal);

	I::Surface->DrawSetColor(bottom_clr.r, bottom_clr.g, bottom_clr.b, bottom_clr.a);
	I::Surface->DrawFilledRectFade(x, y, x1, y1, 0, 255, horizontal);
}