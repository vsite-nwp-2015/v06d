#include "main.h"
#include "rc.h"
#include <cmath>
#include <time.h>
#include <vector>
#include "Selector.hpp"

NumDialog::NumDialog(const uint32_t& diagNumber)
	: mCircleCount(diagNumber)
{
}

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, mCircleCount);
	return true;
}
const uint32_t& NumDialog::GetCount() const
{
	return mCircleCount;
}

bool NumDialog::OnOK()
{
	bool success = true;
	try
	{
		mCircleCount = GetInt(IDC_EDIT1);
		if (mCircleCount > sMaxCircleCount)
		{
			success = false;
		}
	}
	catch (const XCtrl& exc)
	{
		success = false;
	}
	return success;
}

MainWindow::MainWindow()
	: mColor(
	  RGB(
		static_cast<BYTE>(std::rand() % 255)
	  , static_cast<BYTE>(std::rand() % 255)
	  , static_cast<BYTE>(std::rand() % 255)))
	, mCircleNumber(std::rand() % 255)
	, mDrawable(std::make_unique<Elipse>())
{
}

void MainWindow::OnPaint(HDC hdc)
{
	RECT rect;
	GetClientRect(*this, &rect);
	const uint16_t radius = rect.bottom / 4;
	HBRUSH hBrush = ::CreateSolidBrush(mColor);
	DelSelObj hnd(hdc, hBrush);
	for(uint32_t i = 0; i != mCircleNumber; ++i)
	{
		mDrawable->GenerateDots(i, mCircleNumber, rect, radius);
		mDrawable->Draw(hdc);
	}
}

void MainWindow::OnCommand(int id){

	switch(id){
		case ID_COLOR:
			OnColor();
			break;
		case ID_NUMBER: 
			OnNumber();
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

void MainWindow::OnColor()
{
	std::vector<COLORREF> colors(16, RGB(0,0,0));
	CHOOSECOLOR chooseColor{ };
	::ZeroMemory(&chooseColor, sizeof(chooseColor));

	chooseColor.lpCustColors = colors.data();
	chooseColor.lStructSize  = sizeof(chooseColor);
	chooseColor.hwndOwner    = *this;
	chooseColor.rgbResult    = mColor;
	chooseColor.Flags		 = CC_RGBINIT | CC_FULLOPEN;

	if (ChooseColor(&chooseColor))
	{
		mColor = chooseColor.rgbResult;
		InvalidateRect(*this, nullptr, true);
	}
}

void MainWindow::OnNumber()
{
	NumDialog numberDialog { mCircleNumber };
	if (numberDialog.DoModal(0, *this))
	{
		mCircleNumber = numberDialog.GetCount();
		InvalidateRect(*this, nullptr, true);
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	std::srand(time(unsigned int(0)));
	Application app;
	MainWindow wnd;	
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}
