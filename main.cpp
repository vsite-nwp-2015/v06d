#define _USE_MATH_DEFINES
#include "main.h"
#include <cmath>
#include "rc.h"
int cCalc(HWND parent, int scn) {
	NumDialog d;
	d.i = scn;
	if (IDOK != d.DoModal(NULL, parent))
	{
		return scn;
	}
	scn = d.i;
}
bool NumDialog::OnInitDialog() {
	SetInt(IDC_EDIT1, i);
	return true;
}
int NumDialog::IDD() {
	return IDD_NUMBER;
}

COLORREF ClCh(HWND parent, COLORREF cursor) {
	COLORREF c[16] = { 0 };
	CHOOSECOLOR clr;
	ZeroMemory(&c, sizeof clr);
	clr.lStructSize = sizeof clr;
	clr.Flags = CC_FULLOPEN | CC_RGBINIT;
	clr.hwndOwner = parent;
	clr.lpCustColors = c;
	clr.rgbResult = cursor;
	if (!ChooseColor(&clr)) {
		return cursor;
	}
	cursor = clr.rgbResult;
}

void MainWindow::OnPaint(HDC hdc) {
	RECT rt;
	HBRUSH brh = CreateSolidBrush(cl);
	HGDIOBJ hlr = SelectObject(hdc, brh);
	GetClientRect(*this, &rt);
	SelectObject(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	for (int i = 0; i < scn; ++i) {
		Ellipse(hdc, (rt.right / 2 + (rt.bottom / 4) * cos((double)(2 * M_PI * i / scn))) - (rt.bottom / 4), (rt.bottom / 2 + (rt.bottom / 4) * sin((double)(2 * M_PI * i / scn))) - (rt.bottom / 4), (rt.right / 2 + (rt.bottom / 4) * cos((double)(2 * M_PI * i / scn))) + (rt.bottom / 4), (rt.bottom / 2 + (rt.bottom / 4) * sin((double)(2 * M_PI * i / scn))) + (rt.bottom / 4));
				}

	DeleteObject(SelectObject(hdc, hlr));
}
bool NumDialog::OnOK() {
	try {
		i = GetInt(IDC_EDIT1);
		return true;
	}
	catch (XCtrl)
	{
		return false;
	}
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	case ID_COLOR:
		cl = ClCh(*this, cl);
		InvalidateRect(*this, NULL, true);
		break;
	case ID_NUMBER:
		scn = cCalc(*this, scn);
		InvalidateRect(*this, NULL, true);
		break;
		}
	InvalidateRect(*this, NULL, TRUE);
}

void MainWindow::OnDestroy() {
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP",
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.Run();
}