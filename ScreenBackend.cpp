#include <algorithm>
#include <cstdlib>
#include <random>
#include <ctime>
#include "ScreenBackend.hpp"
#include "Worm.hpp"


//makes a 2d array to represent the screen data structure, and an array
//to represent the freePool.
ScreenBackend::ScreenBackend(int rows, int columns) {
    //make a 2d array
    ScreenBE.assign(rows + 4, std::vector<Cell>(columns + 2, Cell()));

    int inMatrixCount = 0;

    for (int j = 0; j < rows + 3; j++) {
        for (int i = 0; i < columns + 2; i++) {

            ScreenBE.at(j).at(i) = Cell(j, i, 0);

            //if the row is the row below the top make it -1 to leave space
            // for the score and "worm"
            if (j == 1 || j == rows + 2 || i == 0 || i == columns + 1) {

                ScreenBE.at(j).at(i).value = -1;

            } else if (j != 0) {
                ScreenBE.at(j).at(i).value = inMatrixCount;
                inMatrixCount++;
                freePool.push_back(ScreenBE.at(j).at(i));
            }
        }
    }
    lastIndex = freePool.size() - 1;
}

//makes a cell on freePool and screenBE free
void ScreenBackend::makeFree(Cell c) {
    ScreenBE[c.row][c.column].value = oldValue;
    freePool[oldValue].row = c.row;
    freePool[oldValue].column = c.column;
    ScreenBE[freePool[oldValue].row][freePool[oldValue].column].value = oldValue;

}

//occupy a space on by the worm on the screen, does different things if the
// worm is or is not growing.
void ScreenBackend::wormOccupy(Cell c, Worm worm) {
    // make c occupied by the worm
    if (worm.isGrowing()) {
        oldValue = ScreenBE[c.row][c.column].value;
        ScreenBE[c.row][c.column].value = -1;

        freePool[oldValue].row = freePool[lastIndex].row;
        freePool[oldValue].column = freePool[lastIndex].column;
        freePool[oldValue].value = oldValue;

        ScreenBE[freePool[oldValue].row][freePool[oldValue].column].value = oldValue;

        lastIndex--;

    } else if (!worm.isGrowing()) {
        oldValue = ScreenBE[c.row][c.column].value;
        ScreenBE[c.row][c.column].value = -1;
        makeFree(worm.tail());
    }
}

// return true if c is free, false if it’s occupied
bool ScreenBackend::isFree(Cell c) {
    if (ScreenBE.at(c.row).at(c.column).value == -1) {
        return false;
    }
    return true;
}

//returns true if the freePool is 'full'
bool ScreenBackend::full() {
    if (lastIndex == 1) {
        return true;
    }
    return false;
}

//returns a random cell from freePool
Cell ScreenBackend::getRandomFreeCell() {
    srand(time(NULL));
    int randomFruit = rand() % lastIndex;
    return freePool[randomFruit];
}