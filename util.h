//
// Created by geoff on 7/31/23.
//

#ifndef PQ_BENCHMARKS_UTIL_H
#define PQ_BENCHMARKS_UTIL_H

#include <vector>
#include <cstdint>

std::vector<int64_t> sign_times;
std::vector<int64_t> verify_times;

void get_average_sign_time(unsigned long long &average_sign_time, std::vector<int64_t> &sign_times);
void get_average_verify_time(unsigned long long &average_verify_time, std::vector<int64_t> &verify_times);

#endif //PQ_BENCHMARKS_UTIL_H
