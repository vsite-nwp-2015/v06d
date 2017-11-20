#include "main.h"
#include <cmath>
#include "rc.h"
#include <list>
#define M_PI 3.14159265358979323846

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
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
	/*HRGN hrgn=NULL;
	HRGN hrgn2;
	for (float n = 0;n < 360;n += 360 / noOfDividingPoints)
	{
		int x = r*cos(n*M_PI / 180);
		int y = r*sin(n*M_PI / 180);
		hrgn2 = CreateEllipticRgn(x - r, y - r, x + r, y + r);
		CombineRgn(hrgn, hrgn, hrgn2, RGN_XOR);
	}*/

	std::list<int> x;
	std::list<int> y;
	int pointx = 0;
	int pointy = 0;
	
	double angle = 0;

	for (int i = 0;i < noOfDividingPoints;++i)
	{
		angle = i*(360 / noOfDividingPoints);
		x.push_back((int)x0 + r*cos(toRadians(angle)));
		y.push_back((int)y0 + r*sin(toRadians(angle)));
	}
	if (x.size() != 0 && y.size())
	{
		pointx = x.back(); x.pop_back();
		pointy = y.back(); y.pop_back();
	}
	HRGN hrgn = CreateEllipticRgn(pointx-r, pointy-r, pointx+r, pointy+r);
	HRGN hrgn2;
	while (!x.empty() && !y.empty())
	{
		pointx = x.back(); x.pop_back();
		pointy = y.back(); y.pop_back();
		hrgn2 = CreateEllipticRgn(pointx - r, pointy - r, pointx + r, pointy + r);
		CombineRgn(hrgn, hrgn, hrgn2, RGN_XOR);
	}
	return hrgn;
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
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	SetWindowExtEx(hdc, 1000, 1000, NULL);
	//SetViewportOrgEx(hdc, rc.right / 2, rc.bottom / 2, NULL);

	HBRUSH hbrush = CreateSolidBrush(myCol);
	
	HRGN hrgn = createRegion(500, 500, 250, numOfPoints);
	FillRgn(hdc, hrgn, hbrush);
	FrameRgn(hdc, hrgn, hbrush, 1, 1);
}

void MainWindow::OnCommand(int id){
	NumDialog dialog;
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

