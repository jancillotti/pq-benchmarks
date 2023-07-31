#include <botan/auto_rng.h>
#include <botan/pubkey.h>
#include <botan/secmem.h>
#include <botan/xmss.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

#define ITERATIONS 1000

std::vector<int64_t> sign_times;
std::vector<int64_t> verify_times;

void get_average_sign_time(unsigned long long &average_sign_time) {

	uint64_t total = 0;

	for(int64_t i : sign_times)
		total += i;

	average_sign_time = total / sign_times.size();

}

void get_average_verify_time(unsigned long long &average_verify_time) {

	uint64_t total = 0;

	for(int64_t i : verify_times)
		total += i;

	average_verify_time = total / verify_times.size();

}

void get_stddev_sign(unsigned long long &stddev_sign_time) {
	double sum = std::accumulate(sign_times.begin(), sign_times.end(), 0.0);
	double mean = sum / sign_times.size();
	double squared_sum = std::inner_product(sign_times.begin(), sign_times.end(), sign_times.begin(), 0.0);
	stddev_sign_time = std::sqrt(squared_sum / sign_times.size() - mean * mean);
}

void get_stddev_verify(unsigned long long &stddev_verify_time) {
	double sum = std::accumulate(verify_times.begin(), verify_times.end(), 0.0);
	double mean = sum / verify_times.size();
	double squared_sum = std::inner_product(verify_times.begin(), verify_times.end(), verify_times.begin(), 0.0);
	stddev_verify_time = std::sqrt(squared_sum / verify_times.size() - mean * mean);
}

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
   sign_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

   // create Public Key Verifier using the public key
   Botan::PK_Verifier verifier(public_key, "");

   start = std::chrono::high_resolution_clock::now();
   // verify the signature for the previously generated message.
   verifier.update(msg.data(), msg.size());
   if(verifier.check_signature(sig.data(), sig.size())) {
      std::cout << "Success." << std::endl;
      stop = std::chrono::high_resolution_clock::now();
      verify_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
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
	get_average_sign_time(average_sign_time);
	get_average_verify_time(average_verify_time);
	get_stddev_sign(stddev_sign_time);
	get_stddev_verify(stddev_verify_time);
	
	std::cout << "Average sign time (us):\t\t" << average_sign_time << std::endl;
	std::cout << "Std. sign time (us):\t\t" << stddev_sign_time << std::endl << std::endl;
	
	std::cout << "Average verify time (us):\t" << average_verify_time << std::endl;
	std::cout << "Std. verify time (us):\t\t" << stddev_verify_time << std::endl;

	
	std::ofstream outfile;
	outfile.open("xmss_results.txt");
	outfile << "Average sign time (us):\t\t" << average_sign_time << std::endl;
	outfile << "Std. sign time (us):\t\t" << stddev_sign_time << std::endl << std::endl;
	
	outfile << "Average verify time (us):\t" << average_verify_time << std::endl;
	outfile << "Std. verify time (us):\t\t" << stddev_verify_time << std::endl;
	outfile.close();

	sign_times.clear();
	verify_times.clear();
	
	return 0;
}
