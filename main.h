#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
public:
	int br;
	NumDialog() : br(1) {}
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};


class MainWindow : public Window {

public:
	COLORREF back;
	int br;
	MainWindow() : back(RGB(0, 0, 0)), br(1){}
	
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
