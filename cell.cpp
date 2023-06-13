#include "cell.hpp"


Cell::Cell() {
    row = 0;
    column = 0;
    value = 0;
}

//the cells hold a value as well as their coordinates, a bit of convenience
Cell::Cell(int r, int c, int v) {
    row = r;
    column = c;
    value = v;
}