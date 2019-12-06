
#define _USE_MATH_DEFINES
#include "main.h"
#include <cmath>
#include "rc.h"

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, br);
	return true;
}
int nKrugova(HWND parent, int brKrugova) {
	NumDialog nm;
	nm.br = brKrugova;
	if (nm.DoModal(NULL, parent) == IDOK)
		brKrugova = nm.br;
	return brKrugova;
}
COLORREF GColor(HWND parent, COLORREF cursor){
	COLORREF cc[16] = { 0 };
	CHOOSECOLOR color;
	ZeroMemory(&cc, sizeof color);
	color.lStructSize = sizeof color;
	color.Flags = CC_FULLOPEN | CC_RGBINIT;
	color.hwndOwner = parent;
	color.lpCustColors = cc;
	color.rgbResult = cursor;
	if (ChooseColor(&color))
		cursor = color.rgbResult;
	return cursor;
}

bool NumDialog::OnOK() {
	try {
		br = GetInt(IDC_EDIT1);
		return true;
	}
	catch (XCtrl)
	{
		return false;
	}
}
	


void MainWindow::OnPaint(HDC hdc){
	RECT pravok;
	HBRUSH brush = CreateSolidBrush(boja);
	HGDIOBJ holder = SelectObject(hdc, brush);
	GetClientRect(*this, &pravok);
	int donji = pravok.bottom / 4;
	SelectObject(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	for (int i = 0; i < brKrugova; ++i) {
		double z = 2 * M_PI * i / brKrugova;
		int zb = pravok.right / 2 + donji * cos(z);
		int zc = pravok.bottom / 2 + donji * sin(z);
		Ellipse(hdc, zb - donji, zc - donji, zb + donji, zc + donji);

	}
	
	DeleteObject(SelectObject(hdc, holder));
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR: 
			boja = GColor(*this, boja);
			InvalidateRect(*this, NULL, true);
			break;
		case ID_NUMBER: 
			brKrugova = nKrugova(*this, brKrugova);
			InvalidateRect(*this, NULL, true);
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;

	}
	InvalidateRect(*this, NULL, TRUE);
}

void MainWindow::OnDestroy(){
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

