CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -std=c++17

all: kreslfil deps doc

compile: kreslfil

kreslfil: main.o CPixelMap.o CFormat.o CFormatBMP.o CFormatTGA.o CFormatManager.o CImage.o CGallery.o CCommandLine.o CMessages.o CEffectManager.o COutput.o
	$(CXX) $(CXXFLAGS) main.o CPixelMap.o CFormat.o CFormatBMP.o CFormatTGA.o CFormatManager.o CImage.o CGallery.o CCommandLine.o CMessages.o CEffectManager.o COutput.o -lncurses -o kreslfil 

main.o: src/main.cpp src/CGallery.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 

CPixelMap.o: src/CPixelMap.cpp src/CPixelMap.hpp src/rgba.hpp
	$(CXX) $(CXXFLAGS) -c src/CPixelMap.cpp -o CPixelMap.o 

CFormat.o: src/CFormat.cpp src/CFormat.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormat.cpp -o CFormat.o 

CFormatBMP.o: src/CFormatBMP.cpp src/CFormat.hpp src/CPixelMap.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatBMP.cpp -o CFormatBMP.o 

CFormatTGA.o: src/CFormatTGA.cpp src/CFormat.hpp src/CPixelMap.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatTGA.cpp -o CFormatTGA.o 

CFormatManager.o: src/CFormatManager.cpp src/CFormatManager.hpp src/CFormatBMP.hpp src/CFormatTGA.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatManager.cpp -o CFormatManager.o 

CImage.o: src/CImage.cpp src/CImage.hpp 
	$(CXX) $(CXXFLAGS) -c src/CImage.cpp -o CImage.o

CGallery.o: src/CGallery.cpp src/CGallery.hpp src/CImage.hpp
	$(CXX) $(CXXFLAGS) -c src/CGallery.cpp -o CGallery.o

CCommandLine.o: src/CCommandLine.cpp src/CCommandLine.hpp src/CFlags.hpp
	$(CXX) $(CXXFLAGS) -c src/CCommandLine.cpp -o CCommandLine.o

CMessages.o: src/CMessages.cpp src/CMessages.hpp 
	$(CXX) $(CXXFLAGS) -c src/CMessages.cpp -o CMessages.o

CEffectManager.o: src/CEffectManager.cpp src/CEffectManager.hpp 
	$(CXX) $(CXXFLAGS) -c src/CEffectManager.cpp -o CEffectManager.o

COutput.o: src/COutput.cpp src/COutput.hpp 
	$(CXX) $(CXXFLAGS) -c src/COutput.cpp -o COutput.o





clean:
	rm -f *.o kreslfil Makefile.d
	rm -rf doc

deps:
	$(CXX) -MM src/*cpp > Makefile.d

run: kreslfil
	./kreslfil 

runJohnny: kreslfil
	./kreslfil assets/img/johnny.bmp

doc: 
	doxygen
	mv doc/html/* doc/
	rmdir doc/html

-include Makefile.d