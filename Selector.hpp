#pragma once
#include <Windows.h>

class Selector
{
public:
	Selector(HDC hdc, HGDIOBJ hObj) : mHdc(hdc), mHoldBursh(::SelectObject(hdc, hObj))
	{
		SetROP2(hdc, R2_NOTXORPEN);
	}
	~Selector() {
		DeleteObject(SelectObject(mHdc, mHoldBursh));
	}
private:
	HDC mHdc;
	HGDIOBJ mHoldBursh;
};

