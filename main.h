#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	int num;
};

class MainWindow : public Window {
protected:
	COLORREF myCol;
	int numCircles=5;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
