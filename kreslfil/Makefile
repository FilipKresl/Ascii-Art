CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -std=c++17

all: kreslfil
# doc

compile: kreslfil

kreslfil: main.o CFormatBMP.o CFormatTGA.o CFormatManager.o CGallery.o CCommandLine.o
	$(CXX) $(CXXFLAGS) main.o CFormatBMP.o CFormatTGA.o CFormatManager.o CGallery.o CCommandLine.o -lncurses -o kreslfil 

main.o: src/main.cpp src/CGallery.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 

CFormatBMP.o: src/CFormatBMP.cpp src/CFormat.hpp src/CPixelMap.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatBMP.cpp -o CFormatBMP.o 

CFormatTGA.o: src/CFormatTGA.cpp src/CFormat.hpp src/CPixelMap.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatTGA.cpp -o CFormatTGA.o 

CFormatManager.o: src/CFormatManager.cpp src/CFormatManager.hpp src/CFormatBMP.hpp src/CFormatTGA.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatManager.cpp -o CFormatManager.o 

CGallery.o: src/CGallery.cpp src/CGallery.hpp src/CImage.hpp
	$(CXX) $(CXXFLAGS) -c src/CGallery.cpp -o CGallery.o

CCommandLine.o: src/CCommandLine.cpp src/CCommandLine.hpp src/CFlags.hpp
	$(CXX) $(CXXFLAGS) -c src/CCommandLine.cpp -o CCommandLine.o


clean:
	rm -f *.o kreslfil
	rm -rf doc

# deps:
# 	$(CXX) -MM *cpp > Makefile.d

run: kreslfil
	./kreslfil 

runJohnny: kreslfil
	./kreslfil assets/img/johnny.bmp

doc: 
	doxygen
	mv doc/html/* doc/
	rmdir doc/html

-include Makefile.d