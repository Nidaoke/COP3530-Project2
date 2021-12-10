#pragma once

class wallToBuild{
public:

    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;
    int f = 0;
    /*
    facing:
        0 = right
        1 = left
        2 = up
        3 = down
        4 = front
        5 = back
    */

    wallToBuild(int xs, int ys, int zs, int ws, int fs){
        x = xs;
        y = ys;
        z = zs;
        w = ws;
        f = fs;
    }
};