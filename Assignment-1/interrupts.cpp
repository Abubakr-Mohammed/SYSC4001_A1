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

        if (activity == "CPU") {
            execution += std::to_string(current_time) + ", " +
                         std::to_string(duration_intr) +
                         ", CPU burst of " + std::to_string(duration_intr) + " ms\n";
            current_time += duration_intr;
        }
        else if (activity == "SYSCALL"){
            int devnum = duration_intr;
            // Interrupt boilerplate steps using macros ADDR_BASE and VECTOR_SIZE
            // Step 1: switch to kernel mode (1 ms)
            execution += std::to_string(current_time) + ", 1, switch to kernel mode\n";
            current_time += 1;
            // Step 2: context saved (10 ms)
            execution += std::to_string(current_time) + ", 10, context saved\n";
            current_time += 10;
            // Step 3: find vector in memory (1 ms)
            char vectoraddr[10];
            snprintf(vectoraddr, sizeof(vectoraddr), "0x%04X", ADDR_BASE + devnum * VECTOR_SIZE);
        }



        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
