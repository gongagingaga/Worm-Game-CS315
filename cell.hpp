#ifndef PROJECT2_CELL_HPP
#define PROJECT2_CELL_HPP

#include <iostream>


//this is used to make the coordinates in the screen and worm data structures
struct Cell {
    int row, column, value;

    Cell();

    Cell(int r, int c, int v);
};

#endif //PROJECT2_CELL_HPP
