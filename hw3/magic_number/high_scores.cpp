#include "high_scores.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "types.h"

void load_high_scores(const std::string filename, std::vector<attemp_game>& vec) {
    std::ifstream in_file{ filename };
    std::string line;
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << filename << "!" << std::endl;
        return;
    }

    attemp_game item;

    while (true) {
        in_file >> item.user_name;
        in_file.ignore();
        in_file >> item.rank;
        in_file.ignore();
        in_file >> item.attempts_count;
        in_file.ignore();
        in_file >> item.max_value;
        in_file.ignore();
        in_file >> item.str_date_time;

        if (in_file.fail()) {
            break;
        }

        vec.push_back(item);
    }
    return;
}

// Write new high score to the records table
void save_high_scores(const std::string filename, std::vector<attemp_game>& vec) {
    // open the output file
    std::ofstream out_file{ filename, std::ios_base::trunc };
    if (!out_file.is_open()) {
        std::cout << "Failed to open file for write: " << filename << "!" << std::endl;
        return;
    }

    // save vector to file
    for (const auto& item : vec) {
        out_file << item.user_name << ' ';
        out_file << item.rank << ' ';
        out_file << item.attempts_count << ' ';
        out_file << item.max_value << ' ';
        out_file << item.str_date_time;
        out_file << std::endl;
    }

    return;
}

void update_high_scores(std::vector<attemp_game>& vec, attemp_game& item, const std::string filename) {

    auto it = std::find_if(vec.begin(), vec.end(),
        [item](const attemp_game& s) { return s.user_name == item.user_name; });

    if (it != vec.end()) {
        if (item.max_value == it->max_value) { // we store the results at different levels of difficulty
            if (item.rank > it->rank) { // we store the best result for the level
                vec.erase(it);
                vec.push_back(item);

                save_high_scores(filename, vec);  // save high scores to file 
            }
            else
                std::cout << "You can do better!!!" << std::endl;
        }
    }
    else {
        vec.push_back(item);
    }

    return;
}


void print_result(const attemp_game& item) {
    std::cout << item.user_name << '\t' << " [ rank: ";
    std::cout << std::fixed << std::setw(5) << std::setprecision(2) << item.rank << " | ";
    std::cout << std::setw(2) << item.attempts_count << " steps | ";
    std::cout << std::setw(3) << item.max_value << " max value ] ";
    std::cout << item.str_date_time;
    std::cout << std::endl;
    return;
}


static bool is_better(const attemp_game& x, const attemp_game& y) { return x.rank > y.rank; }

// Read the high score file and print all results
void print_table_high_scores(std::vector<attemp_game>& vec) {
    // SORT
    std::sort(vec.begin(), vec.end(), is_better);

    // PRINT
    std::cout << "High scores table:" << std::endl;
    for (const auto& item : vec) {
        print_result(item);
    }

    return;
}



