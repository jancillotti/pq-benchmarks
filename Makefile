x86:
	g++ -o xmss-x86 xmss.cpp util.cpp -I/home/user/botan-intel/include/botan-3/ -I/home/user/botan-intel/include/botan-3/botan /home/user/botan-x86/libbotan-3.a --std=c++20 -static
	g++ -o ecdsa-x86 ecdsa.cpp util.cpp -I/home/user/botan-intel/include/botan-3/ -I/home/user/botan-intel/include/botan-3/botan/ /home/user/botan-x86/libbotan-3.a --std=c++20 -static
arm:
	aarch64-linux-gnu-g++ -o ecdsa-arm ecdsa.cpp util.cpp -I/home/user/botan-aarch64/include/botan-3/ -I/home/user/botan-aarch64/include/botan-3/botan /home/user/botan-arm/libbotan-3.a --std=c++20 -static

clean:
	@rm xmss-arm
	@rm ecdsa-arm
	@rm xmss-x86
	@rm ecdsa-x86
