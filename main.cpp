#include "main.h"
#include <cmath>
#include "rc.h"

#define M_PI   3.14159265358979323846264338327950288
class myPen {
	HDC hdc;
	HPEN pen;
public:
	myPen(HDC hdc, COLORREF color, int style, int thickness) {
		this->hdc = hdc;
		this->pen = CreatePen(style, thickness, color);
		SelectObject(hdc, pen);
	}

	~myPen() {
		DeleteObject(SelectObject(hdc, pen));
	}
};
class myBrush {
	HDC hdc;
	HBRUSH brush;
public:
	myBrush(HDC hdc,COLORREF color) {
		this->hdc = hdc;
		this->brush = CreateSolidBrush(color);
		SelectObject(hdc, brush);
	}
	~myBrush(){
		DeleteObject(SelectObject(hdc, brush));
	}
};

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, num);
	return true;
}

bool NumDialog::OnOK(){
	try {
		num = GetInt(IDC_EDIT1);
	}
	catch (XCtrl a) {
		return false;
	}
	return true;
}

void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	myPen pen(hdc, RGB(0, 0, 0), PS_NULL, 1);
	SetBkMode(hdc, OPAQUE);
	myBrush brush(hdc, myCol);
	SetROP2(hdc, R2_NOTXORPEN);
	int r = rect.bottom / 4;
	double c = 2 * M_PI / numCircles;
	for (int i = 0; i < numCircles; i++) {
		double x_add = 2*r + cos(c*i) * r;
		double y_add = rect.bottom / 2 + sin(c*i) * r;
		Ellipse(hdc, x_add - r, y_add - r, x_add + r, y_add + r);
	}
}
void MainWindow::OnCommand(int id){
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;

	switch(id){
		case ID_COLOR: 
			ZeroMemory(&cc, sizeof cc);
			cc.lStructSize = sizeof cc;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			cc.hwndOwner = *this;
			cc.lpCustColors = custCols;
			cc.rgbResult = myCol;
			if (ChooseColor(&cc)) {
				myCol = cc.rgbResult;
				InvalidateRect(*this,0,true);
			}
			/*Ne vidim nacin da pošaljem rezultat od ovdje do OnPainta
				-globaljuse ne dolaze u obzir
				-nemam hdc da pozovem myBrush
				-koliko znam ne smijemo mijenjati pozive funkcija OnCommand i OnPaint niti dodavati nove funkcije klasi mainwindow
				-znam da jos uvijek ne radi krugove kak treba, ali do toga cu doci nakon sto ovo porjesavam sa dijalozima
				-razmisljao sam i staviti 2 klase za getanje boje i broja ali ni to ne ide jer ih ne mogu proslijediti jer globaljuse
				-bih li smio izmjeniti main.h tj klasu mainwindow kako bi si proslijedio boje?
			*/

			break;
		case ID_NUMBER: 
		{
			NumDialog diag;
			diag.num = numCircles;
			if (diag.DoModal(0, *this) == IDOK) {
				numCircles = diag.num;
				InvalidateRect(*this,0,true);
			};
		}
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

