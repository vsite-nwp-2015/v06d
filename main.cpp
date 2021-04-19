#include "main.h"
#include <cmath>
#include "rc.h"
#include <windows.h>

int number_dialog::idd() const {
	return IDD_NUMBER;
}
bool number_dialog::on_init_dialog() {
	return true;
}
bool number_dialog::on_ok() {
	BOOL asd = true;
	try {
		this->glavni->BrojKrugova = dialog::get_int(IDC_EDIT1);
		InvalidateRect(*(this->glavni), NULL, true);
	}
	catch (std::runtime_error) {
		MessageBox(*this, _T("Unos mora biti broj"), 0, MB_OK);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc) {
	POINT sredina;
	RECT rect;
	GetClientRect(*this, &rect);
	sredina.x = rect.right / 2;
	sredina.y = rect.bottom / 2;
	int radijus = 100;
	HBRUSH h = CreateSolidBrush(this->color);
	SelectObject(hdc, h);
	SetROP2(hdc, R2_NOTXORPEN);
	for (int i = 0; i < this->BrojKrugova; ++i) {
		double a = this->pi * 2 * i / BrojKrugova;
		int centerX = sredina.x + radijus * sin(a);
		int centerY = sredina.y + radijus * cos(a);
		Ellipse(hdc, centerX - radijus, centerY - radijus, centerX + radijus, centerY + radijus);
	}
	DeleteObject(SelectObject(hdc, h));
}

void main_window::on_command(int id){
	number_dialog nd;
	nd.glavni = this;
	switch(id){
		case ID_COLOR: {
			CHOOSECOLOR ColorDialog;
			COLORREF acrCustClr[16] = { 0 };
			ZeroMemory(&ColorDialog, sizeof ColorDialog);
			ColorDialog.lStructSize = sizeof ColorDialog;
			ColorDialog.hwndOwner = *this;
			ColorDialog.lpCustColors = acrCustClr;
			ColorDialog.rgbResult = this->color;
			ColorDialog.Flags = CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&ColorDialog) == TRUE) {
				this->color = ColorDialog.rgbResult;
			}
			InvalidateRect(*this, NULL, true);
			break;
		}
		case ID_NUMBER:
			nd.do_modal(0, *this);
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
