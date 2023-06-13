#ifndef PROJECT2_SCREEN_HPP
#define PROJECT2_SCREEN_HPP

#include <vector>
#include "Worm.hpp"
#include "cell.hpp"


//2d array and array representing the in-game screen and their spaces.
class ScreenBackend {
public:
    //constructor
    ScreenBackend(int row, int column);

    // make c a free (empty) cell
    void makeFree(Cell c);

    // make c occupied by the worm
    void wormOccupy(Cell c, Worm);

    // return true if c is free, false if it’s occupied
    bool isFree(Cell c);

    //returns true if freePool is pretty low on supplies, hence win.
    bool full();

    // randomly select and return a free cell to place the snack in
    Cell getRandomFreeCell();

    //returns the value on screen at the coordinates (x,y)
    int getValue(int x, int y) { return ScreenBE.at(x).at(y).value; }

private:
    std::vector<std::vector<Cell>> ScreenBE;
    std::vector<Cell> freePool;
    int lastIndex;
    Cell food;
    int oldValue;
};

#endif //PROJECT2_SCREEN_HPP
