#include "nwpwin.h"
#include "nwpdlg.h"

class number_dialog : public vsite::nwp::dialog {
private:
	int broj = 0;

public:
	number_dialog(int n) : broj(n) {};
	int get_int() { return broj; };

protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
	int k = 3; // broj krugova (default)
	COLORREF set_color = RGB(255, 128, 0);
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

	int new_number();
	void new_color();
};
