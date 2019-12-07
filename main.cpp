#include "main.h"
#include <cmath>
#include "rc.h"
class myPen {
	HDC hdc;
	HPEN pen;
public:
	myPen(HDC hdc, int r, int g, int b, int style, int thickness) {
		this->hdc = hdc;
		this->pen = CreatePen(style, thickness, RGB(r, g, b));
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
	myBrush(HDC hdc, int r, int g, int b) {
		this->hdc = hdc;
		this->brush = CreateSolidBrush(RGB(r,g,b));
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
	return true;
}

bool NumDialog::OnOK(){
	return true;
}

void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	myPen pen(hdc, 255, 0, 255, PS_SOLID, 5);
	
	myBrush brush(hdc, 0, 255, 255);
	SetBkMode(hdc, OPAQUE);
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
void MainWindow::OnCommand(int id){
	static COLORREF myCol = RGB(255, 128, 0);
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
			if (ChooseColor(&cc))
				myCol = cc.rgbResult;
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

