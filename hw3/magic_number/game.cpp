#include "game.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "high_scores.h"


void clrscr()
{
    std::cout << "\033[2J";     // clr scr
    std::cout << "\033[0;0f";   // ret cursor
}

void set_date_time_win(attemp_game& item) {
    // get date time
    std::time_t now = std::time(0);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d_%H:%M:%S", std::localtime(&now));
    std::string dateTimeString = timeStr;

    item.str_date_time = dateTimeString;
}



void game_init(config_game& config) {
    load_high_scores(config.high_scores_filename, config.v_high_scores);
    return;
}

void game_over(config_game& config) {
    print_table_high_scores(config.v_high_scores);
    return;
}

static int getValue()//std::string query)
{
    int value;
    //std::cout << query.c_str();
    while (!(std::cin >> value))
    {
        if (std::cin.eof())
        {
            throw "eof";
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Try again: ";
    }
    return value;
}

void game_play(config_game& config) {
    //==================================================
    // INIT
    std::string flag_again = "next"; // A new player
    do {
        clrscr();

        std::srand(static_cast<unsigned int>(std::time(nullptr))); // use current time as seed for random generator
        const int random_value = std::rand() % config.max_value;
        //std::cout << random_value << std::endl; // debug

        std::cout << "===========================" << std::endl;

        if (flag_again == "next") {
            // Ask about name
            std::cout << "Hi! Enter your name, please:" << std::endl;
            //std::string user_name;
            std::cin >> config.attemp.user_name;// user_name;
        }

        config.attemp.max_value = config.max_value;
        config.attemp.attempts_count = 0;

        bool not_win = true;
        int current_value = 0;
        int max_range = config.max_value;
        int min_range = 0;

        // PLAY
        std::cout << "Enter your guess, range [0.." << config.max_value << ") :" << std::endl;
        do {
            try
            {
                current_value = getValue();
            }
            catch (char const* ex)
            {
                std::cout << ex << std::endl;
            }
            
            //std::cin >> current_value;
            config.attemp.attempts_count++;

            if (current_value < random_value) {
                std::cout << "less than " << current_value;
                if (min_range < current_value) min_range = current_value;
            }
            else if (current_value > random_value) {
                std::cout << "greater than " << current_value;
                if (max_range > current_value) max_range = current_value;
            }
            else {
                std::cout << "you win!" << std::endl;
                set_date_time_win(config.attemp);
                config.attemp.rank = static_cast<float>(config.attemp.max_value) / static_cast<float>(config.attemp.attempts_count);
                std::cout << "\033[31m";
                print_result(config.attemp);
                std::cout << "\033[0m";
                break;
            }
            std::cout << ", range (" << min_range << ".." << max_range << ")" << std::endl;

        } while (true);
        // END PLAY
        //==================================================

        std::cout << "===========================" << std::endl;

        // UPDATE HIGH SCORES
        update_high_scores(config.v_high_scores, config.attemp, config.high_scores_filename);

        // PRINT TABLE
        print_table_high_scores(config.v_high_scores);

        // AGAIN ???
        std::cout << std::endl << "Do you want to play again ? [yes / no / next] ";
        std::cin >> flag_again;

    } while (flag_again == "yes" || flag_again == "next");

    return;
}
