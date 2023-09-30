#include <botan/auto_rng.h>
#include <botan/dilithium.h>
#include <botan/pubkey.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "util.h"

int sign_and_verify() {

    Botan::AutoSeeded_RNG rng;
    auto priv_key = Botan::Dilithium_PrivateKey(rng, Botan::DilithiumMode(Botan::DilithiumMode::Dilithium4x4));
    const auto pub_key = priv_key.public_key();

    auto signer = Botan::PK_Signer(priv_key, rng, "Randomized");

    Botan::secure_vector<uint8_t> msg{0x01, 0x02, 0x03, 0x04};

    auto start = std::chrono::high_resolution_clock::now();
    signer.update(msg.data(), msg.size());
    std::vector<uint8_t> sig = signer.signature(rng);
    auto stop = std::chrono::high_resolution_clock::now();

    sign_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());

    Botan::PK_Verifier verifier(*pub_key, "");

    start = std::chrono::high_resolution_clock::now();
    verifier.update(msg);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << "is " << (verifier.check_signature(sig) ? "valid" : "invalid") << std::endl;
    verify_times.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count());
    return 0;
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
                   "dilithium_results.txt");

    sign_times.clear();
    verify_times.clear();

    return 0;
}
