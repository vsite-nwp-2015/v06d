#define _USE_MATH_DEFINES
#include "main.h"
#include <cmath>
#include "rc.h"

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
void MainWindow::colorWheel() {
	int h = 255;
	int l = 0;
	switch (abs(colorscroll)%8)
	{
	case 0:
		myCol=RGB(l, l, l);
		break;
	case 1:
		myCol = RGB(l, l, h);
		break;
	case 2:
		myCol = RGB(l, h, l);
		break;
	case 3:
		myCol = RGB(l, h, h);
		break;
	case 4:
		myCol = RGB(h, l, l);
		break;
	case 5:
		myCol = RGB(h, l, h);
		break;
	case 6:
		myCol = RGB(h, h, l);
		break;
	case 7:
		myCol = RGB(h, h, h);
		break;
	default:
		break;
	}
}

void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	myPen pen(hdc, RGB(0, 0, 0), PS_NULL, 1);
	myBrush brush(hdc, myCol);
	SetROP2(hdc, R2_NOTXORPEN);
	int r = rect.bottom / 4;
	double c = 2 * M_PI / numCircles;

	for (int i = 0; i < numCircles; i++) {
		double x_add = 2*r + cos(c*i) * r;
		double y_add = 2*r + sin(c*i) * r;
		switch (shapescroll) {
		case 0:
			Ellipse(hdc, x_add - r, y_add - r, x_add + r, y_add + r);
			break;
		case 1:
			Rectangle(hdc, x_add - r, y_add - r, x_add + r, y_add + r);
			break;
		case 2:
			RoundRect(hdc, x_add - r, y_add - r, x_add + r, y_add + r, 20, 20);
			break;
		}
	}
}
void MainWindow::OnKeyDown(int key) {
	switch (key) {
		case VK_LEFT:
			numCircles--;
			break;
		case VK_RIGHT:
			numCircles++;
			break;
		case VK_UP:
			colorscroll++;
			colorWheel();
			break;
		case VK_DOWN:
			colorscroll--;
			colorWheel();
			break;
		case 0x41:
			shapescroll = 0;
			break;
		case 0x53:
			shapescroll = 1;
			break;
		case 0x44:
			shapescroll = 2;
			break;
	}
	InvalidateRect(*this, 0, true);
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

