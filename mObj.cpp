#include <cmath>
#include "mObj.h"

using namespace std;

double sphere::isHit(mRay& ray)
{
	double t = 0;
	mVector L = _center - ray.origin();
	double tca = L*ray.dir();
	if(tca < 0){
		t = -1;
		return t;
	}
	double D = pow(L.norm(),2) - pow(tca,2);
	double r = pow(_radius,2);
	if(D < r){
		double thc = sqrt(r - D);
		t = tca - thc;
		if(t <= 0)
			t = tca + thc;
	}
	else
		t = -1;
	return t;
}

mVector sphere::nVec(mVector& point)
{
	return (point - _center)/(point - _center).norm();
}