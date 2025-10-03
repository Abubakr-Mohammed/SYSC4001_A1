/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
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

    /******************ADD YOUR VARIABLES HERE*************************/



    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/



        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
