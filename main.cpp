#include "main.h"
#include "rc.h"
#include <cmath>
#include <time.h>
#include <vector>
#include "DrawElipse.hpp"
#include "Selector.hpp"

NumDialog::NumDialog(uint32_t diagNumber)
	: mCircleCount(std::move(diagNumber)){}

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, mCircleCount);
	//TODO: how to check is dialog created successfully?
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
	, mCircleNumber(std::rand()% 255)
	, mLogFile(std::make_shared<Log>(mCircleNumber))
{
}

MainWindow::MainWindow(COLORREF defaultColor, uint32_t circleNumber)
	: mColor(std::move(defaultColor))
	, mCircleNumber(std::move(circleNumber))
{
}

void MainWindow::OnPaint(HDC hdc)
{
	RECT rect;
	GetClientRect(*this, &rect);
	const uint16_t radius = rect.bottom / 4;

	HBRUSH hBrush = ::CreateSolidBrush(mColor);
	Selector hnd(hdc, hBrush);
	for(uint32_t i = 0; i != mCircleNumber; ++i)
	{
		DrawEclipse cfe(i, mCircleNumber, rect, radius, hdc);
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
		mColor = std::move(chooseColor.rgbResult);
		InvalidateRect(*this, nullptr, true);
	}
}

void MainWindow::OnNumber()
{
	NumDialog numberDialog { mCircleNumber };
	if (numberDialog.DoModal(0, *this))
	{
		mLogFile->ToFile(std::string("Before change"));
		mCircleNumber = numberDialog.GetCount();
		InvalidateRect(*this, nullptr, true);
		mLogFile->ToFile(std::string("AfterChange"));
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
