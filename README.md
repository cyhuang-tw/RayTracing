# Ray Tracing Simulator

A simple, fast and friendly program to experience the power of ray tracing.


## Introduction
There are 5 basic class in the program:
  - rtMgr: ray tracing manager, which manages objects and lights and provides functions relating to ray tracing.
  - mVector: Vectors and points in the space.
  - mObj: A base class about objects that can be inherited to create more complicate objects(e.g. ellipsoid).
  - mLight: Lights in the space. The position and color are adjustable.
  - pixel: Used to store RGB information with normalized value.(i.e. values are in the range of 0 ~ 1)


## Usage

Objects and lights should be created through pointer and be passed to rtMgr via addObj(mObj*) or addLight(mLight*).
```sh
mObj* obj = new sphere(mVector(100,200,300),250);
mLight* light = new mLight(mVector(-150,0,500),pixel(1,1,1));
mgr -> addObj(obj);
mgr -> addLight(light);
```
**Note: You HAVE TO free these pointers in main on your own.**

To develop your own object models, you can construct object classes inheriting the base class "mObj". In each class, there are two functions necessary to be defined:
  - double isHit(mRay&): Determine when the given ray hits the object. If there is no hitting, return -1.
  - mVector nVec(mVector&): Determine the normal vector at the given point. Assume the point is on the object surface.


## Known Constraints

  - The width and height must be odd numbers.
  - The window is vertical to x-y plane.
  - The x-coordinate of the window should be greater than that of the eyes. Otherwise, the y-coordinate may be opposite.


## Bug Reporting

If finding any bugs, please contact me via email: bennyhuang1997@gmail.com or Facebook, thanks.
