CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic

all: main.o CCommandLine.o CGallery.o CImage.o COutput.o

compile: kreslfil

# kreslfil: main.o CCommandLine.o CGallery.o COutput.o
# 	$(CXX) $(CXXFLAGS) main.o CCommandLine.o CGallery.o COutput.o -lncurses -o kreslfil 

# main.o: src/main.cpp src/CCommandLine.hpp src/CGallery.hpp src/COutput.hpp
# 	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 

# CCommandLine.o: src/CCommandLine.hpp
# 	$(CXX) $(CXXFLAGS) -c src/CCommandLine.hpp -o CCommandLine.o 

# CGallery.o: src/CGallery.hpp src/CImage.hpp
# 	$(CXX) $(CXXFLAGS) -c src/CGallery.hpp -o CGallery.o 

# CImage.o: src/CImage.hpp 
# 	$(CXX) $(CXXFLAGS) -c src/CImage.hpp -o CImage.o 

# COutput.o: src/COutput.hpp 
# 	$(CXX) $(CXXFLAGS) -c src/COutput.hpp -o COutput.o 

kreslfil: main.o 
	$(CXX) $(CXXFLAGS) main.o -lncurses -o kreslfil 

main.o: src/main.cpp src/CCommandLine.hpp src/CGallery.hpp src/COutput.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 

clean:
	rm -f *.o kreslfil Makefile.d

deps:
	$(CXX) -MM *cpp > Makefile.d

run: kreslfil
	./kreslfil 

runJohnny: kreslfil
	./kreslfil assets/img/johnny.bmp

doc: 
	cd .

-include Makefile.d