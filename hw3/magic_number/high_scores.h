#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "types.h"

void load_high_scores(const std::string filename, std::vector<attemp_game>& vec);
void save_high_scores(const std::string filename, std::vector<attemp_game>& vec);
void update_high_scores(std::vector<attemp_game>& vec, attemp_game& item, const std::string filename);
void print_result(const attemp_game& item);
void print_table_high_scores(std::vector<attemp_game>& vec);

