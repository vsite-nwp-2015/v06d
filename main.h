#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
public:
	int broj;
	NumDialog() :broj(1) {};
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	COLORREF boja;
	int brojKrugova;
	public:
		MainWindow() : boja(RGB(0, 0, 0)), brojKrugova(4) {}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
