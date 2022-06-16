CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -std=c++17

all: kreslfil deps doc

compile: kreslfil

kreslfil: main.o CPixelMap.o CFormat.o CFormatBMP.o CFormatTGA.o \
 CFormatManager.o CImage.o CGallery.o CCommandLine.o CMessages.o \
 CEffectManager.o COutput.o CTests.o
	$(CXX) $(CXXFLAGS) main.o CPixelMap.o CFormat.o CFormatBMP.o \
	CFormatTGA.o CFormatManager.o CImage.o CGallery.o CCommandLine.o \
	CMessages.o CEffectManager.o COutput.o CTests.o -lncurses -o kreslfil 

main.o: src/main.cpp src/CGallery.hpp src/CFormatManager.hpp \
 src/CFormatBMP.hpp src/CPixelMap.hpp src/rgba.hpp src/CFormat.hpp \
 src/CFlags.hpp src/CFormatTGA.hpp src/CImage.hpp src/CCommandLine.hpp \
 src/CMessages.hpp src/COutput.hpp src/COutputRound.hpp \
 src/COutputSharp.hpp src/CEffectManager.hpp src/CTests.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 

CPixelMap.o: src/CPixelMap.cpp src/CPixelMap.hpp src/rgba.hpp
	$(CXX) $(CXXFLAGS) -c src/CPixelMap.cpp -o CPixelMap.o 

CFormat.o: src/CFormat.cpp src/rgba.hpp src/CPixelMap.hpp src/CFlags.hpp \
 src/CFormat.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormat.cpp -o CFormat.o 

CFormatBMP.o: src/CFormatBMP.cpp src/CFormatBMP.hpp src/CPixelMap.hpp \
 src/rgba.hpp src/CFormat.hpp src/CFlags.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatBMP.cpp -o CFormatBMP.o 

CFormatTGA.o: src/CFormatTGA.cpp src/CFormatTGA.hpp src/CPixelMap.hpp \
 src/rgba.hpp src/CFormat.hpp src/CFlags.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatTGA.cpp -o CFormatTGA.o 

CFormatManager.o: src/CEffectManager.cpp src/CEffectManager.hpp \
 src/COutput.hpp src/CImage.hpp src/CPixelMap.hpp src/rgba.hpp \
 src/CFlags.hpp src/CGallery.hpp src/CFormatManager.hpp \
 src/CFormatBMP.hpp src/CFormat.hpp src/CFormatTGA.hpp
	$(CXX) $(CXXFLAGS) -c src/CFormatManager.cpp -o CFormatManager.o 

CImage.o: src/CImage.cpp src/CImage.hpp src/CPixelMap.hpp src/rgba.hpp
	$(CXX) $(CXXFLAGS) -c src/CImage.cpp -o CImage.o

CGallery.o: src/CGallery.cpp src/CGallery.hpp src/CFormatManager.hpp \
 src/CFormatBMP.hpp src/CPixelMap.hpp src/rgba.hpp src/CFormat.hpp \
 src/CFlags.hpp src/CFormatTGA.hpp src/CImage.hpp
	$(CXX) $(CXXFLAGS) -c src/CGallery.cpp -o CGallery.o

CCommandLine.o: src/CCommandLine.cpp src/CFlags.hpp src/CCommandLine.hpp
	$(CXX) $(CXXFLAGS) -c src/CCommandLine.cpp -o CCommandLine.o

CMessages.o: src/CMessages.cpp src/CMessages.hpp 
	$(CXX) $(CXXFLAGS) -c src/CMessages.cpp -o CMessages.o

CEffectManager.o: src/CFormatManager.cpp src/CFormatManager.hpp \
 src/CFormatBMP.hpp src/CPixelMap.hpp src/rgba.hpp src/CFormat.hpp \
 src/CFlags.hpp src/CFormatTGA.hpp
	$(CXX) $(CXXFLAGS) -c src/CEffectManager.cpp -o CEffectManager.o

COutput.o: src/COutput.cpp src/COutput.hpp src/CImage.hpp \
 src/CPixelMap.hpp src/rgba.hpp
	$(CXX) $(CXXFLAGS) -c src/COutput.cpp -o COutput.o

CTests.o: src/CTests.cpp src/CTests.hpp src/CGallery.hpp \
 src/CFormatManager.hpp src/CFormatBMP.hpp src/CPixelMap.hpp src/rgba.hpp \
 src/CFormat.hpp src/CFlags.hpp src/CFormatTGA.hpp src/CImage.hpp \
 src/CEffectManager.hpp src/COutput.hpp
	$(CXX) $(CXXFLAGS) -c src/CTests.cpp -o CTests.o

clean:
	rm -f *.o kreslfil Makefile.d
	rm -rf doc

deps:
	$(CXX) -MM src/*cpp > Makefile.d

run: kreslfil
	./kreslfil 

runExample01: kreslfil
	./kreslfil assets/img/johnny.bmp
runExample02: kreslfil
	./kreslfil assets/img/albert.tga
runExample03: kreslfil
	./kreslfil -l assets/palleteNumbers.txt assets/img/cat2.bmp assets/img/cat.bmp
runExample04: kreslfil
	./kreslfil -l assets/palletePerfect.txt assets/img/cat2.bmp assets/img/cat.bmp
runExample05: kreslfil
	./kreslfil -s -p assets/img/img*.bmp

doc: 
	doxygen
	mv doc/html/* doc/
	rmdir doc/html

# -include Makefile.d