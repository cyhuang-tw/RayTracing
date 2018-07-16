#ifndef PIXEL_H_
#define PIXEL_H_

#include <iostream>

using namespace std;

class pixel;

class pixel
{
public:
	pixel() { init(); }
	pixel(double r,double g,double b): _r(r), _g(g), _b(b) {}
	void fix() { if(_r > 1) _r = 1; if(_g > 1) _g = 1; if(_b > 1) _b = 1; }
	unsigned operator[](unsigned idx) { if(idx == 0) return 255*_r; if(idx == 1) return 255*_g; return 255*_b; }
	pixel operator*(double c) { return pixel(_r * c,_g * c,_b * c); }
	pixel operator*(pixel p) { return pixel(_r * p._r,_g * p._g,_b * p._b); }
	pixel operator+(pixel p) { return pixel(_r + p._r,_g + p._g,_b + p._b); }
	bool operator!=(pixel p) { if(_r == p._r && _g == p._g && _b == p._b) return false; return true; }
	friend ostream& operator<<(ostream& os, const pixel& p)
	{
		os << "(" << p._r << "," << p._g << "," << p._b << ")";
		return os;
	}
private:
	void init() { _r = _g = _b = 0; }
	double _r,_g,_b;

};

#endif