#ifndef MLIGHT_H_
#define MLIGHT_H_

#include "mVector.h"
#include "pixel.h"

class mLight;

class mLight
{
public:
	mLight(): _pos(mVector(0,0,0)), _color(pixel(1,1,1)) {}
	mLight(mVector p, pixel c): _pos(p), _color(c) {}
	void setPos(mVector p) { _pos = p; }
	void setRGB(pixel c) { _color = c; }
	mVector& pos() { return _pos; }
	pixel& color() { return _color; }
private:
	mVector _pos;
	pixel _color;

};

#endif