#ifndef MOBJ_H_
#define MOBJ_H_

#include "mVector.h"
#include "pixel.h"

class mObj;
class sphere;

class mObj
{
public:
	mObj() {}
	virtual double isHit(mRay&) = 0;
	virtual mVector nVec(mVector&) = 0;
	virtual pixel color() { return _color; }
	virtual double smoothness() { return _smoothness; }
	void setColor(pixel c) { _color = c; }
	void setSmooth(double s) { _smoothness = s; }
protected:
	pixel _color;
	double _smoothness;

private:

};

class sphere : public mObj
{
public:
	sphere(mVector c,double r): _center(c), _radius(r) {}
	double isHit(mRay&);
	mVector nVec(mVector&);


private:
	mVector _center;
	double _radius;

};

#endif