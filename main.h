#include "nwpwin.h"
#include "nwpdlg.h"



class main_window : public vsite::nwp::window {
public:
	const double pi = 3.14159265359;
	int BrojKrugova = 8;
	COLORREF color = RGB(255, 255, 255);
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
};

class number_dialog : public vsite::nwp::dialog {
public:
	main_window* glavni = NULL;
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};
