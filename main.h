#include "nwpwin.h"
#include "nwpdlg.h"
#include "wingdi.h"
#include <memory>
#include "Drawable.hpp"

class NumDialog : public Dialog
{
public:
	NumDialog(uint32_t diagNumber);
	const uint32_t& GetCount() const;

protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
private:
	uint32_t mCircleCount;
	static constexpr uint16_t sMaxCircleCount = 10000;
};

class MainWindow : public Window {
public:
	MainWindow();
	MainWindow(COLORREF defaultColor, uint32_t circleNumber);
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	void OnColor();
	void OnNumber();
private:
	COLORREF mColor;
	uint16_t mCircleNumber;
	std::unique_ptr<Elipse> mDrawable;
};
