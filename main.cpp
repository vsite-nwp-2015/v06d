#define _USE_MATH_DEFINES
#include "main.h"
#include <cmath>
#include "rc.h"

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, number);
	return true;
}

bool NumDialog::OnOK(){
	try {
		number = GetInt(IDC_EDIT1);
		if (number<= 0 || number > 10000)
			return false;
	}
	catch (XCtrl&) {
		return false;
	}
	return true;
}

void MainWindow::NewColor() {
	COLORREF colors[16] = { 0 };
	CHOOSECOLOR choose;
	ZeroMemory(&choose, sizeof choose);
	choose.lStructSize = sizeof choose;
	choose.Flags = CC_FULLOPEN | CC_RGBINIT;
	choose.lpCustColors = colors;
	choose.hwndOwner = *this;
	choose.rgbResult = selColor;
	if (ChooseColor(&choose) == IDOK) {
		selColor = choose.rgbResult;
		InvalidateRect(*this, NULL, true);
	}
}

void MainWindow::NewNumber() {
	NumDialog numdialog(numCircle);

	if (numdialog.DoModal(0, *this) == IDOK) {
		numCircle = numdialog.getNumber();
		InvalidateRect(*this, NULL, true);
	}
}

void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	int r = rect.bottom / 4;
	HBRUSH hbrush = CreateSolidBrush(selColor);
	HGDIOBJ holdBrush = SelectObject(hdc, hbrush);
	SelectPen(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	double f = 2 * 3.14 / numCircle;
	for (int i = 0; i < numCircle; ++i) {
		double m = f * i;
		double a = rect.right / 2 + r * cos(m);
		double b = rect.bottom / 2 + r * sin(m);
		Ellipse(hdc, a + r, b + r, a - r, b- r);
	}
	DeleteObject(SelectObject(hdc, holdBrush));
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR:
			NewColor();
			break;
		case ID_NUMBER:
			NewNumber();
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
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

