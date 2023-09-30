#include <iostream>
#include <oqs/oqs.h>
#include <chrono>
#include <vector>

#include "util.h"

#define MESSAGE_LEN 2500

int sign_and_verify() {

	OQS_STATUS rc;

	uint8_t public_key[OQS_SIG_falcon_512_length_public_key];
	uint8_t secret_key[OQS_SIG_falcon_512_length_secret_key];
	uint8_t message[MESSAGE_LEN];
	uint8_t signature[OQS_SIG_falcon_512_length_signature];
	size_t message_len = MESSAGE_LEN;
	size_t signature_len;

	OQS_randombytes(message, message_len);

        rc = OQS_SIG_falcon_512_keypair(public_key, secret_key);
        if (rc != OQS_SUCCESS) {
       		exit(EXIT_FAILURE);
       	}

	auto start = std::chrono::high_resolution_clock::now();

	rc = OQS_SIG_falcon_512_sign(signature, &signature_len, message, message_len, secret_key);

	auto stop = std::chrono::high_resolution_clock::now();
 	sign_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());

	start = std::chrono::high_resolution_clock::now();

	rc = OQS_SIG_falcon_512_verify(message, message_len, signature, signature_len, public_key);

	if (rc == OQS_SUCCESS) {
		std::cout << "Success." << std::endl;
		stop = std::chrono::high_resolution_clock::now();
		verify_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
		return 0;
	}
	else {
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
		   "falcon_results.txt");

	sign_times.clear();
	verify_times.clear();

	return 0;
}
