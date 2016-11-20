#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	COLORREF boja;
public:
	MainWindow() : boja(RGB(0, 0, 0)) {}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
