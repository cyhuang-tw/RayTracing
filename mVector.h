#ifndef MVECTOR_H_
#define MVECTOR_H_

#include <iostream>
#include <cmath>

using namespace std;

class mVector;
class mRay;

class mVector
{
public:
	mVector(): _x(0.0), _y(0.0), _z(0.0) {}
	mVector(double p1,double p2,double p3): _x(p1), _y(p2), _z(p3) {}
	double operator[](unsigned idx) { if(idx == 0) return _x; if(idx == 1) return _y; return _z; }
	mVector operator+(mVector v) { return mVector(_x + v._x, _y + v._y, _z + v._z); }
	mVector operator-(mVector v) { return mVector(_x - v._x, _y - v._y, _z - v._z); }
	mVector operator*(double c) { return mVector(c*_x,c*_y,c*_z); }
	double operator*(mVector v) { return (_x * v._x + _y * v._y + _z * v._z); }
	mVector operator/(double c) { return mVector(_x/c, _y/c, _z/c); }
	mVector operator%(mVector v) { return mVector(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x); }
	double norm() { return sqrt(_x * _x + _y * _y + _z * _z); }
	friend ostream& operator<<(ostream& os, const mVector& v)
	{
		os << "(" << v._x << "," << v._y << "," << v._z << ")";
		return os;
	}

private:
	double _x,_y,_z;

};

class mRay
{
public:
	mRay(mVector o,mVector d): _ori(o), _dir(d) {}
	mVector& origin() { return _ori; }
	mVector& dir() { return _dir; }
private:
	mVector _dir,_ori;
};

#endif