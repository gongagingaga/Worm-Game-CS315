#ifndef PROJECT2_WORM_HPP
#define PROJECT2_WORM_HPP

#include <iostream>
#include "cell.hpp"


//circle queue data structure class representing the in-game worm
class Worm {
public:
    //creates the worm which is a circle queue
    Worm(int height, int width);

    //adds a new head to the circle queue
    void addHead(Cell c);

    //removes the first element of the circle queue
    void removeTail();

    //returns the head of the worm/the last index of the circle queue
    Cell head();

    //returns the tail of the worm/the first index of the circle queue
    Cell tail();

    //returns the cell just before the head
    Cell justBeforeHead();

    //returns whether the worm is growing or not
    bool isGrowing();

    //sets the growing bool to 'set'
    void setGrowing(bool set) { growing = set; }

private:
    bool growing;
    int size;
    int tailIndex;
    int headIndex;
    Cell *wormQ;
    int MAX_QSIZE;

};

#endif