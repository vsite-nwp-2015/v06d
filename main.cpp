#include "main.h"
#include <cmath>
#include "rc.h"

COLORREF GetcColor(HWND parent, COLORREF cur) {
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
int brojKrugova(HWND parent, int broj) {
	NumDialog n;
	if (n.DoModal(NULL, parent) == IDOK)
		broj = n.broj;

	return broj;
}

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, broj);
	return true;
}

bool NumDialog::OnOK(){
	try {
		NumDialog::broj = GetInt(IDC_EDIT1);
		return true;

	}
	catch (XCtrl) {
		MessageBox(*this, "Greska","Unesi Broj", MB_OK | MB_ICONERROR);
		return false;

	}
	}
	
	


void MainWindow::OnPaint(HDC hdc){
	RECT rc; GetClientRect(*this, &rc);
	HBRUSH brus = CreateSolidBrush(clr);
	SelectBrush(hdc, brus);
	SelectPen(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	
	SetViewportOrgEx(hdc, rc.right / 2, rc.bottom / 2, NULL);
	for (int i = 0;i < brj;i++){
		double a = i*2*3.14 / brj;
		double xcor = 100*sin(a);
		double ycor = 100 * cos(a);
		::Ellipse(hdc, xcor - 100, ycor - 100, xcor + 100, ycor + 100);
	}
	DeleteObject(brus);

}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR: 
			clr = GetcColor(*this, clr);
			break;
		case ID_NUMBER: 
			brj = brojKrugova(*this, brj);
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

