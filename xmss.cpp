#include <botan/auto_rng.h>
#include <botan/pubkey.h>
#include <botan/xmss.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "util.h"

int sign_and_verify() {
   // Create a random number generator used for key generation.
   Botan::AutoSeeded_RNG rng;

   // create a new public/private key pair using SHA2 256 as hash
   // function and a tree height of 10.
   Botan::XMSS_PrivateKey private_key(Botan::XMSS_Parameters::xmss_algorithm_t::XMSS_SHA2_10_256, rng);
   const Botan::XMSS_PublicKey& public_key(private_key);

   // create Public Key Signer using the private key.
   Botan::PK_Signer signer(private_key, rng, "");

   auto start = std::chrono::high_resolution_clock::now();
   // create and sign a message using the Public Key Signer.
   Botan::secure_vector<uint8_t> msg{0x01, 0x02, 0x03, 0x04};
   signer.update(msg.data(), msg.size());
   std::vector<uint8_t> sig = signer.signature(rng);
   
   auto stop = std::chrono::high_resolution_clock::now();
   sign_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());

   // create Public Key Verifier using the public key
   Botan::PK_Verifier verifier(public_key, "");

   start = std::chrono::high_resolution_clock::now();
   // verify the signature for the previously generated message.
   verifier.update(msg.data(), msg.size());
   if(verifier.check_signature(sig.data(), sig.size())) {
      std::cout << "Success." << std::endl;
      stop = std::chrono::high_resolution_clock::now();
      verify_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
      return 0;
   } else {
      std::cout << "Error." << std::endl;
      return 1;
   }
}

int main() {
	unsigned long long average_sign_time, average_verify_time, stddev_sign_time, stddev_verify_time;	

    for(int i = 0; i < ITERATIONS; i++) {
		std::cout << "i=" << i << "\t";
		sign_and_verify();
	}

	get_average_sign_time(average_sign_time, sign_times);
	get_average_verify_time(average_verify_time, verify_times);
	get_stddev_sign(stddev_sign_time, sign_times);
	get_stddev_verify(stddev_verify_time, verify_times);

    record_results(average_sign_time,
                   average_verify_time,
                   stddev_sign_time,
                   stddev_verify_time,
                   "xmss_results.txt");

	sign_times.clear();
	verify_times.clear();
	
	return 0;
}
