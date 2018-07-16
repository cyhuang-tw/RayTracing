#ifndef RTMGR_H_
#define RTMGR_H_

#include <vector>
#include "mVector.h"
#include "mObj.h"
#include "mLight.h"
#include "pixel.h"

using namespace std;

class rtMgr;

class rtMgr
{
public:
	rtMgr() { init(); }
	~rtMgr() { reset(); }
	void setWnH(unsigned w,unsigned h);
	void setCenter(mVector& c) { _center = c; }
	void setEye(mVector& e) { _eye = e; }
	void addObj(mObj*& ptr) { _obj.push_back(ptr); }
	void addLight(mLight*& ptr) { _light.push_back(ptr); }
	void rayTrace();
	void print(string);
	void test();

private:
	void init();
	void reset();
	pixel rayTrace(mRay&,unsigned&);
	bool isBlocked(mRay&,mObj*&,double&);
	pixel phong_shading(mVector&,mVector&,mVector&,pixel&,mLight*&);
	unsigned _width,_height,_depth;
	mVector _center;
	mVector _eye;
	pixel** _window;
	vector<mObj*> _obj;
	vector<mLight*> _light;
};

#endif