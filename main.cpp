#include "main.h"
#include <cmath>
#include "rc.h"
#include <list>
#define M_PI 3.14159265358979323846

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, numberOfPoints);
	return true;
}

bool NumDialog::OnOK(){
	numberOfPoints = GetInt(IDC_EDIT1);
	return true;
}

double toRadians(double angle)
{
	return angle*M_PI / 180;
}

HRGN createRegion(int x0, int y0, int r, int noOfDividingPoints)
{
	HRGN hrgn= CreateEllipticRgn(0, 0, 0, 0);;
	HRGN hrgn2;
	for (float n = 0;n < 360;n += 360. / noOfDividingPoints)
	{
		int x = r*cos(n*M_PI / 180);
		int y = r*sin(n*M_PI / 180);
		hrgn2 = CreateEllipticRgn(x - r, y - r, x + r, y + r);
		CombineRgn(hrgn, hrgn, hrgn2, RGN_XOR);
	}

	
	return hrgn;
}

void createElipses(HDC hdc, int r, int noOfDividingPoints)
{
	SetROP2(hdc, R2_NOTXORPEN);
	for (float n = 0;n < 360;n += 360. / noOfDividingPoints)
	{
		int x = r*cos(n*M_PI / 180);
		int y = r*sin(n*M_PI / 180);
		::Ellipse(hdc, x - r, y - r, x + r, y + r);
	}
}

COLORREF boja(HWND hwnd, COLORREF myCol)
{
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.hwndOwner = hwnd;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.lpCustColors = custCols;
	cc.rgbResult = myCol;
	if (ChooseColor(&cc))
		myCol = cc.rgbResult;
	return myCol;
}

void MainWindow::OnPaint(HDC hdc){
	RECT rc; GetClientRect(*this, &rc);
	int ypix = 1000, xpix = 1000;
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	SetViewportOrgEx(hdc, rc.right / 2, rc.bottom / 2, NULL);
	SetWindowExtEx(hdc, ypix, xpix, NULL);

	HBRUSH hbrush = CreateSolidBrush(myCol);
	//NOTE TO SELF: crtanje brze od regija
	//HRGN hrgn = createRegion(0, 0, xpix/4, numOfPoints);
	//FillRgn(hdc, hrgn, hbrush);
	SelectBrush(hdc, hbrush);
	createElipses(hdc, xpix / 4, numOfPoints);
	DeleteObject(hbrush);
}

void MainWindow::OnCommand(int id){
	NumDialog dialog;
	dialog.numberOfPoints = numOfPoints;
	switch(id){
		case ID_COLOR:
			myCol = boja(*this, myCol);
			InvalidateRect(*this, 0, true);
			break;
		case ID_NUMBER:
			dialog.DoModal(NULL, *this);
			numOfPoints = dialog.numberOfPoints;
			InvalidateRect(*this, 0, true);
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

