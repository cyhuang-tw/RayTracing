rts:main.o rtMgr.o mObj.o
	g++ -o rts -std=c++11 -O3 main.o rtMgr.o mObj.o
	rm *.o *.gch
main.o:main.cpp mVector.o rtMgr.o mObj.o
	g++ -c -std=c++11 -O3 main.cpp
rtMgr.o:rtMgr.cpp mObj.o mVector.o mLight.h.gch pixel.h.gch
	g++ -c -std=c++11 -O3 rtMgr.cpp
mObj.o:mObj.cpp pixel.h.gch mVector.o
	g++ -c -std=c++11 -O3 mObj.cpp
mLight.h.gch:mLight.h mVector.o pixel.h.gch
	g++ -c -std=c++11 -O3 mLight.h
pixel.h.gch:pixel.h
	g++ -c -std=c++11 -O3 pixel.h
mVector.o:mVector.cpp
	g++ -c -std=c++11 -O3 mVector.cpp
clean:
	rm -f *.o *.gch rts

