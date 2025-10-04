/**
 *
 * @file interrupts.cpp
 * @author Abubakr Mohammed(101287262) Chikezilim Afulukwe(101279214)
 * 
 */

#include<interrupts.hpp>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

int main(int argc, char** argv) {

    auto args_tuple = parse_args(argc, argv);
    std::vector<std::string> vectors = std::get<0>(args_tuple);
    std::vector<int> delays = std::get<1>(args_tuple);
    
    std::ifstream inputfile(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output
    int current_time = 0;
    

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);
        /******************ADD YOUR SIMULATION CODE HERE*************************/
        auto event = parse_trace(trace);
        std::string activity = std::get<0>(event);
        int value = std::get<1>(event);

        if (activity == "CPU") {
            execution += std::to_string(current_time) + ", " +
                         std::to_string(value) +
                         ", CPU burst of " + std::to_string(value) + " ms\n";
            current_time += value;
        }



        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
