#pragma once
#include <Windows.h>

class DelSelObj
{
public:
	DelSelObj(HDC hdc, HGDIOBJ hObj) : mHdc(hdc), mHoldBursh(::SelectObject(hdc, hObj))
	{
		SelectPen(hdc, GetStockObject(NULL_PEN));
		SetROP2(hdc, R2_NOTXORPEN);
	}
	~DelSelObj() {
		DeleteObject(SelectObject(mHdc, mHoldBursh));
	}
private:
	HDC mHdc;
	HGDIOBJ mHoldBursh;
};

