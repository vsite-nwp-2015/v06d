#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>
#include "rc.h"

int number_dialog::idd() const {
	return IDD_NUMBER;
}
bool number_dialog::on_init_dialog() {
	set_int(IDC_EDIT1,broj);
	return true;
}
bool number_dialog::on_ok() {
	try {
		broj = dialog::get_int(IDC_EDIT1);
	}
	catch (std::runtime_error e) {
		MessageBox(*this, _T("not a number"), _T("watcha doin"), MB_ICONWARNING | MB_OK);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc) {

	RECT rect;
	GetClientRect(*this, &rect);
	HBRUSH brush = CreateSolidBrush(set_color);
	HGDIOBJ holdBrush = SelectObject(hdc, brush);

	SelectPen(hdc, GetStockObject(NULL_PEN));

	// centering circle
	// specifies which device point maps to the window origin. default (0, 0).
	SetViewportOrgEx(hdc, rect.right / 2 , rect.bottom / 2, NULL);
	SetROP2(hdc, R2_NOTXORPEN);
	
	int radius = rect.bottom / 4;
	
	// https://math.stackexchange.com/a/206662
	// polarne koordinate
	for (int n = 0; n < k; ++n) {
		double a = 2 * n * M_PI / k;

		// pretvorba u kartezijev koordinatni
		double x = radius * cos(a);
		double y = radius * sin(a);
		
		// left top right bottom
		::Ellipse(hdc, x + radius, y + radius, x - radius, y - radius);
	}
	DeleteObject(SelectObject(hdc, holdBrush));
}

void main_window::new_color() {

	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = *this;
	cc.lpCustColors = custCols;
	cc.rgbResult = set_color;
	if (ChooseColor(&cc))
		set_color = cc.rgbResult;
}

void main_window::new_number() {

	number_dialog nd(k);
		if (nd.do_modal(0, *this) == IDOK) {
			k = nd.get_int();
	}
}

void main_window::on_command(int id){
	switch(id){
		case ID_COLOR: 
			new_color();
			InvalidateRect(*this, NULL, TRUE);
			break;
		case ID_NUMBER: 
			new_number();
			InvalidateRect(*this, NULL, TRUE);
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
