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
void get_stddev_sign(unsigned long long &stddev_sign_time, std::vector<int64_t> &sign_times);
void get_stddev_verify(unsigned long long &stddev_verify_time, std::vector<int64_t> &verify_times);
void record_results(unsigned long long average_sign_time,
                    unsigned long long average_verify_time,
                    unsigned long long stddev_sign_time,
                    unsigned long long stddev_verify_time,
                    std::string output_file_name);

#endif //PQ_BENCHMARKS_UTIL_H
