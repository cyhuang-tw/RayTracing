#include <cmath>
#include <climits>
#include <fstream>
#include "rtMgr.h"

void rtMgr::init()
{
	_width = _height = 667;
	_center = mVector(0,0,0);
	_eye = mVector(-500,0,0);
	_window = new pixel*[_width];
	for(unsigned i = 0; i < _width; ++i){
		_window[i] = new pixel[_height];
	}
	_depth = 1;
}

void rtMgr::reset()
{
	for(unsigned i = 0; i < _width; ++i){
		delete[] _window[i];
	}
	delete[] _window;
	_window = 0;
}

void rtMgr::setWnH(unsigned w,unsigned h)
{
	reset();
	_width = w;
	_height = h;

	_window = new pixel*[_width];
	for(unsigned i = 0; i < _width; ++i){
		_window[i] = new pixel[_height];
	}
}

void rtMgr::rayTrace()
{
	for(int i = 0; i < _width; ++i){
		for(int j = 0; j < _height; ++j){
			mVector cur_pix = _center + mVector(0,((float)(_width + 1))/2.0,((float)(_height + 1))/2.0) + mVector(0,-i,-j);
			mVector dir = cur_pix - _eye;
			dir = dir/dir.norm();
			mRay ray(cur_pix,dir);

			_window[i][j] = rayTrace(ray,_depth);

		}
	}
}

pixel rtMgr::rayTrace(mRay& ray,unsigned& depth)
{
	double amb = 0.2;
	double smoothness = 0;
	pixel ilumi(0,0,0);
	pixel reflect(0,0,0);
	pixel refract(0,0,0);
	mObj* ptr = 0;
	double t = INT_MAX;
	bool hit = isBlocked(ray,ptr,t);
	if(hit){
		mVector point = ray.origin() + ray.dir()*t;
		mVector nVec = ptr -> nVec(point);
		pixel color = ptr -> color();
		smoothness = ptr -> smoothness();
		mVector vec = (ray.origin() - point)/(ray.origin() - point).norm();
		for(unsigned i = 0; i < _light.size(); ++i){
			mVector lightDir = (_light[i] -> pos()) - point;
			mRay lightRay(point,lightDir/lightDir.norm());
			ptr = 0;
			double shadow_t = lightDir.norm();
			bool shadow_hit = isBlocked(lightRay,ptr,shadow_t);

			pixel ambient = (color*_light[i] -> color())*amb;
			ilumi = ilumi + ambient;
			if(!(shadow_hit && shadow_t < lightDir.norm())){
				lightDir = lightDir/lightDir.norm();
				ilumi = ilumi + phong_shading(nVec,lightDir,vec,color,_light[i]);
			}
		}
	}
	pixel pixColor = ilumi*(1.0 - smoothness) + (reflect + refract)*smoothness;
	pixColor.fix();

	return pixColor;
}

bool rtMgr::isBlocked(mRay& ray,mObj*& ptr,double& t)
{
	for(unsigned i = 0; i < _obj.size(); ++i){
		double t_tmp = _obj[i] -> isHit(ray);
		if(t_tmp != -1 && t_tmp < t){
			t = t_tmp;
			ptr = _obj[i];
		}
	}

	if(ptr)
		return true;
	else
		return false;
}

pixel rtMgr::phong_shading(mVector& nVec,mVector& lightDir,mVector& vec,pixel& color,mLight*& ptr)
{
	double diff = 0.6;
	double spec = 0.2;
	double alpha = 10;
	double L_cos = nVec*lightDir;
	double cosine = std::max(L_cos,0.0);
	pixel diffuse = (color*diff)*(ptr -> color())*cosine;

	mVector L_sin = lightDir - nVec*L_cos;
	mVector R = nVec*L_cos - L_sin;
	cosine = std::max(R*vec,0.0);
	pixel specular = (ptr -> color())*spec*pow(cosine,alpha);

	pixel ans = diffuse + specular;

	return ans;
}

void rtMgr::print(string name)
{
	const unsigned headerSize = 54;
	long size = _width * _height * 4 + 54;
	char header[headerSize];
	for(unsigned i = 0; i < headerSize; ++i)
		header[i] = 0;
	header[0] = 0x42;
	header[1] = 0x4d;
	header[2] = (unsigned char)(size & 0x000000ff);
	header[3] = (size >> 8) & 0x000000ff;
	header[4] = (size >> 16) & 0x000000ff;
	header[5] = (size >> 24) & 0x000000ff;
	header[10] = 54;
	header[14] = 40;
	header[18] = ((long)_width) & 0x000000ff;
	header[19] = (((long)_width) >> 8) & 0x000000ff;
	header[20] = (((long)_width) >> 16) & 0x000000ff;
	header[21] = (((long)_width) >> 24) & 0x000000ff;
	header[22] = ((long)_height) & 0x000000ff;
	header[23] = (((long)_height) >> 8) & 0x000000ff;
	header[24] = (((long)_height) >> 16) & 0x000000ff;
	header[25] = (((long)_height) >> 24) & 0x000000ff;
	header[26] = 1;
	header[28] = 32;

	fstream file;
	file.open(name.c_str(),ios::out | ios::binary);
	file.write(header,headerSize);
	for(int i = _height - 1; i >= 0; --i){
		for(int j = 0; j < _width; ++j){
			file.put(char(_window[j][i][2])).put(char(_window[j][i][1])).put(char(_window[j][i][0])).put(0);
		}
	}
	file.close();
}