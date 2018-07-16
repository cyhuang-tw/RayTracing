#include <iostream>
#include "rtMgr.h"

rtMgr* mgr;

using namespace std;

int main()
{
	mgr = new rtMgr;

	mObj* sph = new sphere(mVector(500,200,300),200);
	sph -> setColor(pixel(1,0,0));
	sph -> setSmooth(0.0);
	mgr -> addObj(sph);
	
	mLight* light = new mLight(mVector(-10000,2500,5000),pixel(1,1,1));
	mgr -> addLight(light);

	mgr -> rayTrace();
	mgr -> print("test.bmp");

	delete light;
	delete sph;
	delete mgr;
	return 0;
}