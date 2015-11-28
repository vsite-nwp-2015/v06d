#include "main.h"
#include <cmath>
#include "rc.h"



COLORREF GetColor(HWND parent, COLORREF col)
{
	
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = custCols;
	cc.rgbResult = col;
	if (ChooseColor(&cc))
		col = cc.rgbResult;
	return col;
	
}
int GetNumber(HWND parent, int br)
{
	
	NumDialog numDial;
	if (numDial.DoModal(NULL, parent) == IDOK)
	{
		br = numDial.br;		
	}
	return br;
}

int NumDialog::IDD()
{
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog()
{
	
	SetInt(IDC_EDIT1,br);
	return true;
}

bool NumDialog::OnOK()
{
	try 
	{
		NumDialog::br = GetInt(IDC_EDIT1);
		return true;
	}
	catch (XCtrl )
	{
		MessageBox(*this, "Krivi unos", "Greška", MB_OK | MB_ICONERROR);
		return false;
	}
}

void MainWindow::OnPaint(HDC hdc)
{
	double y, x;
	int r =200;
	RECT rc;
	GetClientRect(*this, &rc);

	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, 1000, 1000, NULL);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	
	
	HBRUSH brush = CreateSolidBrush(back);
	SelectBrush(hdc, brush);
	SelectPen(hdc,GetStockPen(NULL_PEN ));
	SetROP2(hdc, R2_NOTXORPEN);

	for (int k = 0; k < br; k++)
	{
		y = (int)(r*(sin(k*(2 * atan(1) * 4 / br)))); //atan(1)*4  = pi
		x = (int)(r*(cos(k*(2 * atan(1) * 4 / br))));
		
		Ellipse(hdc, x - r + 500, y - r + 500, x + r + 500, y + r + 500);
	}
	

	DeleteObject(brush);

	
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR: 
			back = GetColor(*this, back);			
			break;
		case ID_NUMBER: 
			br = GetNumber(*this, br);
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
	InvalidateRect(*this, NULL, true);
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

