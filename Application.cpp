#include "Game.h"

int main(){

    Game game(
        "Worm Test",
        640, 480,
        4, 5,
        false);

    //MAIN LOOP
    while (!game.getWindowShouldClose()){
        //TODO UPDATE INPUT
        game.update();
        game.render();
    }

    return 0;
}