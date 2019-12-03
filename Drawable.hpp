#pragma once

class IDrawable
{
public:
	IDrawable() = default;
	virtual ~IDrawable() = default;
	virtual void Draw(HDC hdc)  = 0;
};

class Elipse : IDrawable
{
public:
	Elipse() = default;

	void GenerateDots(const uint8_t& iteration, const uint16_t& circleNumber, const RECT& rect, const int& radius)
	{
		const double a = 2 * PI * iteration / circleNumber;
		const double b = rect.right / 2 + radius * std::cos(a);
		const double c = rect.bottom / 2 + radius * std::sin(a);

		mLeft   = b + radius;
		mTop    = c + radius;
		mRight  = b - radius;
		mBottom = c - radius;
	}

	void Draw(HDC hdc) override
	{
		::Ellipse(hdc, mLeft, mTop, mRight, mBottom);
	}
private:
	double mLeft, mTop, mRight, mBottom;
	const double PI = std::atan(1) * 4;
};
