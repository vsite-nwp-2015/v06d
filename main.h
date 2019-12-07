#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
	int num;
public:
	NumDialog(int n) : num(n) {}
	int getNum() { return num; };
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	COLORREF selColor = RGB(0, 0, 0);
	int numCircle = 5;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	void NewColor();
	void NewNumber();
};
