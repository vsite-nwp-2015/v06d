#include "main.h"
#include <cmath>
#include "rc.h"


int NumDialog::IDD(){
	return IDD_NUMBER; 
}


bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, broj);
	return true;
}
int getBrojKrugova(HWND parent, int brojKrugova)
{
	NumDialog nd;
	nd.broj = brojKrugova;
	if (nd.DoModal(NULL, parent) == IDOK)
		brojKrugova = nd.broj;
	return brojKrugova;
}

bool NumDialog::OnOK(){
	try {
		NumDialog::broj = GetInt(IDC_EDIT1);
		return true;
	}
	catch(XCtrl)
	{
		return false;
	}
}

void MainWindow::OnPaint(HDC hdc) {
	RECT rectangle;
	GetClientRect(*this, &rectangle);
	int size = rectangle.bottom/4;
	HBRUSH brush = CreateSolidBrush(boja);
	SelectBrush(hdc, brush);
	SelectPen(hdc, GetStockObject(NULL_PEN));
	SetViewportOrgEx(hdc, rectangle.right / 2, rectangle.bottom / 2, NULL);
	SetROP2(hdc, R2_NOTXORPEN);
	for (int r = 0; r != brojKrugova; r++)
	{
		double a = (2 * r * atan(1) * 4) / brojKrugova ;
		double x = size * cos(a);
		double y = size * sin(a);
		::Ellipse(hdc, x+size, y+size, x - size, y - size);
	}
	DeleteObject(brush);
}

COLORREF GetColor(HWND parent, COLORREF cur) {
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = custCols;
	cc.rgbResult = cur;
	if (ChooseColor(&cc))
		cur = cc.rgbResult;
	return cur;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR: 
			boja = GetColor(*this, boja);
			break;
		case ID_NUMBER: 
			brojKrugova = getBrojKrugova(*this, brojKrugova);
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			return;
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

