//
// Created by geoff on 7/31/23.
//

#include <cstdint>
#include <vector>

void get_average_sign_time(unsigned long long &average_sign_time, std::vector<int64_t> &sign_times) {

    uint64_t total = 0;

    for(int64_t i : sign_times)
        total += i;

    average_sign_time = total / sign_times.size();

}

void get_average_verify_time(unsigned long long &average_verify_time, std::vector<int64_t> &verify_times) {

    uint64_t total = 0;

    for(int64_t i : verify_times)
        total += i;

    average_verify_time = total / verify_times.size();

}