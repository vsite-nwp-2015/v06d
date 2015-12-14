#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
public:
	int broj;
	NumDialog() :broj(1) {}
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
		COLORREF clr;
	int brj;
	MainWindow() : clr(RGB(0, 0, 0)), brj(3) {}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
