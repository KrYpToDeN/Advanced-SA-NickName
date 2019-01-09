OUTFILE = "ASAN/bin/plugins/ASAN.so"
 
COMPILE_FLAGS=-m32 -c -O3 -w -idirafter "lib"
LINK_FLAGS=-m32 -shared -O3 -static-libstdc++

all:
	gcc $(COMPILE_FLAGS) ASAN/src/lib/SDK/amx/*.h
	g++ $(COMPILE_FLAGS) -std=c++11 ASAN/src/lib/SDK/*.cpp		
	g++ $(COMPILE_FLAGS) -std=c++11 ASAN/src/lib/INI/*.cpp	
	g++ $(COMPILE_FLAGS) -std=c++11 ASAN/src/*.cpp
	g++ $(LINK_FLAGS) -o $(OUTFILE) *.o
	rm ASAN/src/lib/SDK/amx/*.h.gch
	rm *.o
	strip -s $(OUTFILE)