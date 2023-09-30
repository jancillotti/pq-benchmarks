all: arm x86

x86:
	g++ -o xmss-x86 xmss.cpp util.cpp -I$(HOME)/botan-intel/include/botan-3/ -I$(HOME)/botan-intel/include/botan-3/botan $(HOME)/botan-x86/libbotan-3.a --std=c++20 -static
	g++ -o ecdsa-x86 ecdsa.cpp util.cpp -I$(HOME)/botan-intel/include/botan-3/ -I$(HOME)/user/botan-intel/include/botan-3/botan/ $(HOME)/botan-x86/libbotan-3.a --std=c++20 -static
	g++ -o dilithium-x86 dilithium.cpp util.cpp -I$(HOME)/botan-intel/include/botan-3/ -I$(HOME)/user/botan-intel/include/botan-3/botan/ $(HOME)/botan-x86/libbotan-3.a --std=c++20 -static
	g++ -o falcon-x86 falcon.cpp util.cpp -static -I$(HOME)/liboqs-x86/include $(HOME)/liboqs-x86/lib/liboqs.a
	g++ -o sphincs-x86 sphincs.cpp util.cpp -static -I$(HOME)/liboqs-x86/include $(HOME)/liboqs-x86/lib/liboqs.a

arm:
	aarch64-linux-gnu-g++ -o xmss-arm xmss.cpp util.cpp -I$(HOME)/botan-aarch64/include/botan-3/ $(HOME)/botan-arm/libbotan-3.a --std=c++20 -static
	aarch64-linux-gnu-g++ -o ecdsa-arm ecdsa.cpp util.cpp -I$(HOME)/botan-aarch64/include/botan-3/ -I$(HOME)botan-aarch64/include/botan-3/botan $(HOME)/botan-arm/libbotan-3.a --std=c++20 -static
	aarch64-linux-gnu-g++ -o dilithium-arm dilithium.cpp util.cpp -I$(HOME)/botan-aarch64/include/botan-3/ -I$(HOME)botan-aarch64/include/botan-3/botan $(HOME)/botan-arm/libbotan-3.a --std=c++20 -static
	aarch64-linux-gnu-g++ -o falcon-arm falcon.cpp util.cpp -static -I$(HOME)/liboqs-aarch64/include $(HOME)/liboqs-aarch64/lib/liboqs.a
	aarch64-linux-gnu-g++ -o sphincs-arm sphincs.cpp util.cpp -static -I$(HOME)/liboqs-aarch64/include $(HOME)/liboqs-aarch64/lib/liboqs.a
clean:
	@$(RM) xmss-arm
	@$(RM)  xmss-x86
	@$(RM)  ecdsa-arm
	@$(RM)  ecdsa-x86
	@$(RM) falcon-arm
	@$(RM) falcon-x86
