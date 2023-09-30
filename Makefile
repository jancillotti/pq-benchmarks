all: arm x86

x86:
	g++ -o xmss-x86 xmss.cpp util.cpp -I$(HOME)/botan-intel/include/botan-3/ -I$(HOME)/botan-intel/include/botan-3/botan $(HOME)/botan-x86/libbotan-3.a --std=c++20 -static
	g++ -o ecdsa-x86 ecdsa.cpp util.cpp -I$(HOME)/botan-intel/include/botan-3/ -I$(HOME)/user/botan-intel/include/botan-3/botan/ $(HOME)/botan-x86/libbotan-3.a --std=c++20 -static
arm:
	aarch64-linux-gnu-g++ -o xmss-arm xmss.cpp util.cpp -I$(HOME)/botan-aarch64/include/botan-3/ $(HOME)/botan-arm/libbotan-3.a --std=c++20 -static
	aarch64-linux-gnu-g++ -o ecdsa-arm ecdsa.cpp util.cpp -I$(HOME)/botan-aarch64/include/botan-3/ -I$(HOME)botan-aarch64/include/botan-3/botan $(HOME)/botan-arm/libbotan-3.a --std=c++20 -static

clean:
	@rm xmss-arm
	@rm ecdsa-arm
	@rm xmss-x86
	@rm ecdsa-x86
