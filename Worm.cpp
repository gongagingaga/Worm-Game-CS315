#include "Worm.hpp"
#include "cell.hpp"

//creates circle queue to represent the worm. Allocating the maximum size
// possible, so we don't have to resize.
Worm::Worm(int height, int width) {
    MAX_QSIZE = (height) * (width);
    wormQ = new Cell[MAX_QSIZE];

    tailIndex = 0;
    headIndex = -1;
    size = 0;
    growing = true;
}

//adding the head means moving the integer representing the location
// on the worm array and adding c to that location.
void Worm::addHead(Cell c) {
    headIndex++;
    if (headIndex == MAX_QSIZE) {
        headIndex = 0;
    }
    size++;
    wormQ[headIndex] = c;
}

//removing the tail just means we pretend that the array is smaller using
// the representation of the tailIndex
void Worm::removeTail() {
    if (size == 0) {
        std::cerr << "Can't do this operation on an empty queue\n";
        exit(1);
    }
    tailIndex++;
    if (tailIndex == MAX_QSIZE) {
        tailIndex = 0;
    }
    size--;
}

//returns the head of the worm located in wormQ at headIndex
Cell Worm::head() {
    return wormQ[headIndex];
}

//returns the index before the head
Cell Worm::justBeforeHead() {
    if (headIndex - 1 == -1) {
        return wormQ[MAX_QSIZE - 1];
    }
    return wormQ[headIndex - 1];
}

//returns the tail of the worm
Cell Worm::tail() {
    return wormQ[tailIndex];
}

//returns whether the worm is growing
bool Worm::isGrowing() {
    return growing;
}