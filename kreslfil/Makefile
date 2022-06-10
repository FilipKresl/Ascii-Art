CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -std=c++17

all: kreslfil
# doc

compile: kreslfil

kreslfil: main.o CFormatBMP.o CFormatManager.o
	$(CXX) $(CXXFLAGS) main.o CFormatBMP.o CFormatManager.o -lncurses -o kreslfil 

main.o: src/main.cpp src/CGallery.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 

CFormatBMP.o: src/CFormatBMP.cpp src/CFormat.hpp src/CPixelMap.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatBMP.cpp -o CFormatBMP.o 

CFormatManager.o: src/CFormatManager.cpp src/CFormatManager.hpp src/CFormatBMP.hpp src/CFormatTGA.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatManager.cpp -o CFormatManager.o 

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