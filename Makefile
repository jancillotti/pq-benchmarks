all:
	aarch64-linux-gnu-g++ timing.cpp -o timing -static -I/home/geoff/liboqs/build/include /home/geoff/liboqs/build/lib/liboqs.a

clean: 
	rm timing
