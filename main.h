#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
	int number;
public:
	NumDialog(int n) : number(n) {}
	int getNumber() { return number; }


protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
protected:
	COLORREF selColor = RGB(0, 0, 0);
	int numCircle = 5;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	void NewColor();
	void NewNumber();
};
