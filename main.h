#include "nwpwin.h"
#include "nwpdlg.h"
class MainWindow : public Window {
public:
	COLORREF cl = RGB(150, 250, 150);
	int scn = 12;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
class NumDialog : public Dialog {
public:
	int i = 1;

protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};
