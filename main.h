#include "nwpwin.h"
#include "nwpdlg.h"


class NumDialog : public Dialog {
public:
	int br = 1;
	
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	COLORREF boja = RGB(125, 125, 125);
	int brKrugova = 6;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
