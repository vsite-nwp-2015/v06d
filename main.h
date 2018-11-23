#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
	int num=5;
public: int getNum() { return num; };
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	COLORREF myCol = RGB(0, 0, 0);
	int brojKrugova;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	void NewColor();
	void NewNumber();
};
