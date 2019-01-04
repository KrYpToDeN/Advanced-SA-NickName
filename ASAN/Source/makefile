OUTFILE = "ASAN.so"
 
COMPILE_FLAGS= -std=c++11 -m32 -c -O3 -w -DLINUX -I./SDK/amx/

all:
	gcc $(COMPILE_FLAGS) SDK/amx/*.c
	g++ $(COMPILE_FLAGS) SDK/*.cpp
	g++ $(COMPILE_FLAGS) INI/*.cpp
	g++ $(COMPILE_FLAGS) *.cpp
	g++ -m32 -O -pthread -unistd -fshort-wchar -shared -o $(OUTFILE) *.o
	rm *.o
