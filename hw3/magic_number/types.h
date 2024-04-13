#pragma once

#include <iostream>
#include <string>
#include <vector>

struct attemp_game {
    std::string user_name;
    float rank = 0.0;
    int attempts_count = 0;
    int max_value = 0;
    std::string str_date_time;
};

struct config_game {
    int parameter_level = 0;
    int max_value = 50;
    attemp_game attemp;
    std::vector<attemp_game> v_high_scores;
    const std::string high_scores_filename = "high_scores.txt";
};

