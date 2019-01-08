#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
public:
	int num;
	NumDialog(int n): num(n){}
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	COLORREF myCol = RGB(100, 100, 100);
	int brojKrugova = 20;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
