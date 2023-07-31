//
// Created by geoff on 7/31/23.
//

#include <cstdint>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>
#include <iostream>


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

void get_stddev_sign(unsigned long long &stddev_sign_time, std::vector<int64_t> &sign_times) {
    double sum = std::accumulate(sign_times.begin(), sign_times.end(), 0.0);
    double mean = sum / sign_times.size();
    double squared_sum = std::inner_product(sign_times.begin(), sign_times.end(), sign_times.begin(), 0.0);
    stddev_sign_time = std::sqrt(squared_sum / sign_times.size() - mean * mean);
}

void get_stddev_verify(unsigned long long &stddev_verify_time, std::vector<int64_t> &verify_times) {
    double sum = std::accumulate(verify_times.begin(), verify_times.end(), 0.0);
    double mean = sum / verify_times.size();
    double squared_sum = std::inner_product(verify_times.begin(), verify_times.end(), verify_times.begin(), 0.0);
    stddev_verify_time = std::sqrt(squared_sum / verify_times.size() - mean * mean);
}

void record_results(unsigned long long average_sign_time,
                    unsigned long long average_verify_time,
                    unsigned long long stddev_sign_time,
                    unsigned long long stddev_verify_time,
                    std::string output_file_name) {

    std::cout << "Average sign time (ns):\t\t" << average_sign_time << std::endl;
    std::cout << "Std. sign time (ns):\t\t" << stddev_sign_time << std::endl << std::endl;

    std::cout << "Average verify time (ns):\t" << average_verify_time << std::endl;
    std::cout << "Std. verify time (ns):\t\t" << stddev_verify_time << std::endl;


    std::ofstream outfile;
    outfile.open(output_file_name);
    outfile << "Average sign time (ns):\t\t" << average_sign_time << std::endl;
    outfile << "Std. sign time (ns):\t\t" << stddev_sign_time << std::endl << std::endl;

    outfile << "Average verify time (ns):\t" << average_verify_time << std::endl;
    outfile << "Std. verify time (ns):\t\t" << stddev_verify_time << std::endl;
    outfile.close();
}