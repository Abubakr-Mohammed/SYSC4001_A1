/**
 *
 * @file interrupts.cpp
 * @author Abubakr Mohammed(101287262) Chikezilim Afulukwe(101279214)
 * 
 */

// interrupts.cpp
#include "interrupts.hpp"
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

int main(int argc, char* argv[]) {
    // Use parse_args (not parseargs)
    auto args_tuple = parse_args(argc, argv);
    std::vector<std::string> vectors = std::get<0>(args_tuple);
    std::vector<int> delays = std::get<1>(args_tuple);
    
    std::ifstream inputfile(argv[1]);
    std::string trace;
    std::string execution; 

    int current_time = 0;
    while (std::getline(inputfile, trace)) {
        // Use parse_trace (not parsetrace)
        auto [activity, duration_intr] = parse_trace(trace);

        if (activity == "CPU") {
            execution += std::to_string(current_time) + ", " +
                         std::to_string(duration_intr) +
                         ", CPU burst of " + std::to_string(duration_intr) + " ms\n";
            current_time += duration_intr;
        }
        else if (activity == "SYSCALL") {
            int devnum = duration_intr;
            // Step 1: switch to kernel mode (1 ms)
            execution += std::to_string(current_time) + ", 1, switch to kernel mode\n";
            current_time += 1;
            // Step 2: context saved (10 ms)
            execution += std::to_string(current_time) + ", 10, context saved\n";
            current_time += 10;
            // Step 3: find vector in memory (1 ms)
            char vectoraddr[10];
            snprintf(vectoraddr, sizeof(vectoraddr), "0x%04X", ADDR_BASE + devnum * VECTOR_SIZE);
            execution += std::to_string(current_time) + ", 1, find vector " +
                         std::to_string(devnum) +
                         " in memory position " + vectoraddr + "\n";
            current_time += 1;
            // Step 4: load address in PC (1 ms)
            execution += std::to_string(current_time) + ", 1, load address " +
                         vectors.at(devnum) + " into the PC\n";
            current_time += 1;
            // Step 5: execute ISR (40 ms)
            execution += std::to_string(current_time) + ", 40, execute ISR for device " +
                         std::to_string(devnum) + "\n";
            current_time += 40;
            // Step 6: IRET (1 ms)
            execution += std::to_string(current_time) + ", 1, IRET - end interrupt service\n";
            current_time += 1;
            // Step 7: start IO for device
            int io_time = delays.at(devnum);
            execution += std::to_string(current_time) + ", " +
                         std::to_string(io_time) +
                         ", start IO for device " + std::to_string(devnum) + "\n";
            current_time += io_time;
        }
        else if (activity == "ENDIO" || activity == "END_IO") {
            int devnum = duration_intr;
            // Step 1: Switch to kernel mode (1 ms)
            execution += std::to_string(current_time) + ", 1, switch to kernel mode\n";
            current_time += 1;
            // Step 2: Context saved (10 ms or as configured)
            execution += std::to_string(current_time) + ", 10, context saved\n";
            current_time += 10;
            // Step 3: Find vector in memory (1 ms)
            char vectoraddr[10];
            snprintf(vectoraddr, sizeof(vectoraddr), "0x%04X", ADDR_BASE + devnum * VECTOR_SIZE);
            execution += std::to_string(current_time) + ", 1, find vector " +
                        std::to_string(devnum) +
                        " in memory position " + vectoraddr + "\n";
            current_time += 1;
            // Step 4: Load address in PC (1 ms)
            execution += std::to_string(current_time) + ", 1, load address " +
                        vectors.at(devnum) + " into the PC\n";
            current_time += 1;
            // Step 5: Execute ISR for IO completion 
            execution += std::to_string(current_time) + ", 40, handle IO completion for device " +
                        std::to_string(devnum) + "\n";
            current_time += 40;
            // Step 6: IRET (1 ms)
            execution += std::to_string(current_time) + ", 1, IRET - end interrupt service\n";
            current_time += 1;
        }
    }
    inputfile.close()

    write_output(execution);

    return 0;
}

