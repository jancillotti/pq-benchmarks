#include <botan/auto_rng.h>
#include <botan/ec_group.h>
#include <botan/ecdsa.h>
#include <botan/hex.h>
#include <botan/pubkey.h>

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

   Botan::AutoSeeded_RNG rng;
   // Generate ECDSA keypair
   Botan::ECDSA_PrivateKey key(rng, Botan::EC_Group("secp521r1"));

   const std::string message("This is a tasty burger!");

   // sign data
   Botan::PK_Signer signer(key, rng, "SHA-256");

   auto start = std::chrono::high_resolution_clock::now();
   signer.update(message);
   
   
   std::vector<uint8_t> signature = signer.signature(rng);
   //std::cout << "Signature:" << std::endl << Botan::hex_encode(signature);
   
   auto stop = std::chrono::high_resolution_clock::now();
   sign_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());

   //******************************VERIFY**********************************
   Botan::PK_Verifier verifier(key, "SHA-256");
   
   
   start = std::chrono::high_resolution_clock::now();
   verifier.update(message);
   stop = std::chrono::high_resolution_clock::now();
   std::cout << "is " << (verifier.check_signature(signature) ? "valid" : "invalid") << std::endl;
   verify_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
   return 0;
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
	
	std::cout << "Average sign time (ns):\t\t" << average_sign_time << std::endl;
	std::cout << "Std. sign time (ns):\t\t" << stddev_sign_time << std::endl << std::endl;
	
	std::cout << "Average verify time (ns):\t" << average_verify_time << std::endl;
	std::cout << "Std. verify time (ns):\t\t" << stddev_verify_time << std::endl;

	
	std::ofstream outfile;
	outfile.open("ecdsa_results.txt");
	outfile << "Average sign time (ns):\t\t" << average_sign_time << std::endl;
	outfile << "Std. sign time (ns):\t\t" << stddev_sign_time << std::endl << std::endl;
	
	outfile << "Average verify time (ns):\t" << average_verify_time << std::endl;
	outfile << "Std. verify time (ns):\t\t" << stddev_verify_time << std::endl;
	outfile.close();

	sign_times.clear();
	verify_times.clear();
	
	return 0;
}
