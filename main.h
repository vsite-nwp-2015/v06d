#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	int numberOfPoints;
};

class MainWindow : public Window {
protected:
	int numOfPoints=4;
	COLORREF myCol = RGB(0, 0, 0);
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
