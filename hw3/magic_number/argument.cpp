#include "argument.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "types.h"

static int set_max_value_from_level(int parameter_level) {
    int res = 50;
    switch (parameter_level)
    {
        case 1: res = 10; break;
        case 2: res = 50; break;
        case 3: res = 100; break;
        default: res = parameter_level; break;
    }

    std::cout << "You have chosen " << parameter_level << "lavel. Max value = " << res << std::endl;
    return res; // max_value
}

int get_argument_cmd(int argc, char** argv, config_game& config) {
    if (argc == 1) {
        // Ask level
        std::cout << "Please choose the difficulty level (1/2/3 or the maximum value):" << std::endl;
        std::cin >> config.parameter_level;
        config.max_value = set_max_value_from_level(config.parameter_level);
        return 1;
    }

    // check if the argc >= 2
    if (argc >= 2) {
        std::string arg1_value{ argv[1] };
        // LEVEL
        if (arg1_value == "-level") {
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
                return -1;
            }
            config.parameter_level = std::stoi(argv[2]);
            config.max_value = set_max_value_from_level(config.parameter_level);
            return 1;
        }

        // MAX VALUE
        if (arg1_value == "-max") {
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
                return -1;
            }

            config.max_value = std::stoi(argv[2]);
            std::cout << "You have chosen max value = " << config.max_value << std::endl;
            return 1;
        }

        // PRINT HIGH SCORES TABLE
        if (arg1_value == "-table") {
            return 0; // END GAME
        }
    }

    std::cout << "Unknown error..." << std::endl;
    return -1;
}
