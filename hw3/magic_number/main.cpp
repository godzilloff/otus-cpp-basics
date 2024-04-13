#include "types.h"
#include "argument.h"
#include "game.h"

int main(int argc, char** argv) {
    // config GAME
    config_game config_g;

    // get the parameters from the CMD
    int ret = get_argument_cmd(argc, argv, config_g);

    if (ret > -1)
    {
        // load_high_scores
        game_init(config_g);

        // let's start
        if (ret == 0)
            game_over(config_g);
        else
            game_play(config_g);
    }
    else
        std::cout << "ERROR LOAD GAME!!!" << std::endl;

	return 0;
}