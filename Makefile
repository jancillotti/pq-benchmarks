all:
	aarch64-linux-gnu-g++ -o xmss xmss.cpp util.cpp -I/usr/local/include/botan-3/ -I/usr/local/include/botan-3/botan /home/geoff/botan/libbotan-3.a --std=c++20 -static
	aarch64-linux-gnu-g++ -o ecdsa ecdsa.cpp util.cpp -I/usr/local/include/botan-3/ -I/usr/local/include/botan-3/botan /home/geoff/botan/libbotan-3.a --std=c++20 -static

clean:
	@rm xmss
	@rm ecdsa
