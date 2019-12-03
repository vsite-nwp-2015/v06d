#pragma once
#include <fstream>

struct DrawEclipse
{
public:
	static const double& PI()
	{
		static const double pi = std::atan(1) * 4;
		return pi;
	}

	DrawEclipse(const int& i, const uint32_t& circleNumber, const RECT& rect, const int& radius, HDC hdc)
	{
		const double a = 2 * PI() * i / circleNumber;
		const double b = rect.right / 2 + radius * std::cos(a);
		const double c = rect.bottom / 2 + radius * std::sin(a);

		left   = b + radius;
		top    = c + radius;
		right  = b - radius;
		bottom = c - radius;
		Ellipse(hdc, left, top, right, bottom);
	}

private:
	double left, top, right, bottom;
};

/**
 * Used ONLY FOR DEBUG.
 */
struct Log
{
public:
	explicit Log(uint16_t numberToRef) : refNum(numberToRef), fs("Log.txt")
	{
	}

	~Log()
	{
		if (fs.is_open())
		{
			fs.close();
		}
	}

	void ToFile(std::string& str)
	{
		fs << str << refNum << std::endl;
	}

private:
	const uint16_t& refNum;
	std::fstream fs;
};