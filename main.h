#include "nwpwin.h"
#include "nwpdlg.h"

class NumDialog : public Dialog {
public:
	int br;
	NumDialog() : br(0) {}
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};


class MainWindow : public Window {

public:
	COLORREF col;
	int br;
	
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
