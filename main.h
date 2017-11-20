#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
public:
	int broj=1;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();	
};

class MainWindow : public Window {
public:
	int mojBroj = 4;
	COLORREF mojaBoja = RGB(0,150,150);
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
