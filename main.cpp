/*
 * Benito Sanchez
 * CS315
 * Dr. Rivoire
 *
 * Worm game, executable takes in 2 integer inputs, dictating the height and
 * width of the game screen. Uses the curses.h library to create the 'view'.
 */

#include <iostream>
#include <curses.h>
#include <string>
#include "ScreenBackend.hpp"
#include "Worm.hpp"
#include "cell.hpp"
#include "getChar.hpp"


void startup(void);

void terminate(void);

void reprintWorm(Worm w);

void reprintGrowingWorm(Worm &w);

void move(Worm &w, ScreenBackend &s, bool &lifeStatus, Cell tempCell, int width, int height);

void growingMove(Worm &w, ScreenBackend &s, bool &lifeStatus, Cell tempCell, int width, int height);

//check win and lose conditions
bool checkLife(Worm &worm, int h, int w, int tempCell);

void win(int s);


int main(int argc, char **argv) {

    int height = atoi(argv[1]);

    int width = atoi(argv[2]);

    //check screen size
    if (height < 9 || height > 25 || width < 9 || width > 80) {
        std::cerr << "invalid screen size" << std::endl;
        exit(9);
    }

    Worm worm(height, width);
    ScreenBackend screen(height, width);


    startup();

    move(0, 0);
    addstr("Worm");

    move(0, width - 4);
    addstr("Score: ");


    //make walls
    //there's an extra row added to height besides the top and bottom walls
    // this is to leave a space for the score and "worm" at the top of the
    // screen.
    for (int i = 1; i < height + 3; i++) {
        for (int j = 0; j < width + 2; j++) {
            move(i, j);
            if (screen.getValue(i, j) == -1) {
                addch('*');
            }
        }
    }
    refresh();

    //make worm
    // you need to use the cells to get half way though height and halfway through width
    Cell spawn((height / 2) + 2, (width / 2) - 3, 0);

    for (int i = 0; i < 7; i++) {
        Cell tempSpawn(spawn.row, spawn.column + i, -1);
        move(tempSpawn.row, tempSpawn.column);
        addch('o');
        worm.addHead(tempSpawn);
        screen.wormOccupy(tempSpawn, worm);
    }

    Cell tempSpawn(spawn.row, spawn.column + 7, -1);
    move(spawn.row, spawn.column + 7);

    worm.addHead(tempSpawn);
    screen.wormOccupy(tempSpawn, worm);
    addch('@');
    refresh();


    //GAMEPLAY LOOP STARTS HERE
    worm.setGrowing(false);
    bool dead = false;

    //FRUIT BUILD

    //this is the temporary random fruit number, since the fruit
    // has to update visibly on the map but not update the amount
    // that the player has to grow till after the player has eaten
    // the fruit.
    int rFN = 0;

    //gets random fruit number
    srand(time(NULL));
    int randomFruitNumber = rand() % 9 + 1;
    std::string tempRandNumber = std::to_string(randomFruitNumber);
    char const *randString = tempRandNumber.c_str();

    //puts fruit on map
    Cell fruit = screen.getRandomFreeCell();

    //this while loop is important because of the way the screen is built,
    // occasionally fruit may or may not spawn on the top wall so this is the
    // preventative measure.
    while (screen.getValue(fruit.row, fruit.column) == -1) {
        fruit = screen.getRandomFreeCell();
    }
    move(fruit.row, fruit.column);
    addch(*randString);
    int wormBodyCount = 0;

    //making score
    int score = 0;
    move(0, width + 2);
    std::string tempScore = std::to_string(score);
    char const *scoreString = tempScore.c_str();
    addstr(scoreString);


    refresh();
    height++;

    while (!dead) {
        //check win condition:
        if (!screen.full()) {
            char cc = get_char();
            if (cc != ' ') {
                if (cc == 'w') {
                    Cell temporaryCell(worm.head().row - 1, worm.head().column, 1);
                    if (!worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        move(worm, screen, dead, temporaryCell, width, height);

                    } else if (worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        growingMove(worm, screen, dead, temporaryCell, width, height);
                        wormBodyCount++;

                    }
                    if (wormBodyCount == randomFruitNumber) {
                        wormBodyCount = 0;
                        worm.setGrowing(false);
                        randomFruitNumber = rFN;

                    }

                } else if (cc == 'a') {
                    Cell temporaryCell(worm.head().row, worm.head().column - 1, 1);
                    if (!worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        move(worm, screen, dead, temporaryCell, width, height);


                    } else if (worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        growingMove(worm, screen, dead, temporaryCell, width, height);
                        wormBodyCount++;

                    }
                    if (wormBodyCount == randomFruitNumber) {
                        wormBodyCount = 0;
                        worm.setGrowing(false);
                        randomFruitNumber = rFN;

                    }

                } else if (cc == 's') {
                    Cell temporaryCell(worm.head().row + 1, worm.head().column, 1);
                    if (!worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        move(worm, screen, dead, temporaryCell, width, height);

                    } else if (worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        growingMove(worm, screen, dead, temporaryCell, width, height);
                        wormBodyCount++;

                    }
                    if (wormBodyCount == randomFruitNumber) {
                        wormBodyCount = 0;
                        worm.setGrowing(false);
                        randomFruitNumber = rFN;

                    }

                } else if (cc == 'd') {
                    Cell temporaryCell(worm.head().row, worm.head().column + 1, 1);
                    if (!worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        move(worm, screen, dead, temporaryCell, width, height);

                    } else if (worm.isGrowing()) {
                        if (screen.full()) {
                            win(score);
                        }
                        growingMove(worm, screen, dead, temporaryCell, width, height);
                        wormBodyCount++;

                    }
                    if (wormBodyCount == randomFruitNumber) {
                        wormBodyCount = 0;
                        worm.setGrowing(false);
                        randomFruitNumber = rFN;

                    }
                }

                //check if the fruit has been eaten
                if (worm.head().row == fruit.row && worm.head().column == fruit.column) {
                    //reset growing
                    wormBodyCount = 0;

                    //check win condition
                    if (screen.full()) {
                        win(score);
                    }

                    //increase score
                    score += randomFruitNumber;
                    move(0, width + 2);
                    tempScore = std::to_string(score);
                    char const *scoreString = tempScore.c_str();
                    addstr(scoreString);

                    //get fruit number
                    srand(time(NULL));
                    rFN = rand() % 9 + 1;
                    tempRandNumber = std::to_string(rFN);
                    char const *randString = tempRandNumber.c_str();

                    //puts fruit on map
                    fruit = screen.getRandomFreeCell();
                    while (screen.getValue(fruit.row, fruit.column) == -1) {
                        fruit = screen.getRandomFreeCell();

                    }
                    move(fruit.row, fruit.column);
                    addch(*randString);
                    worm.setGrowing(true);
                    refresh();
                }
                refresh();
            }
        } else {
            //win if wind condition is met
            win(score);
        }

    }
    //end game if dead == true
    terminate();
    std::cout << "YOU did not WIN!\n" << "Score: " << score << std::endl;
    exit(1);

}

//starts curses
void startup(void) {
    initscr();     /* activate the curses */
    curs_set(0);   /* do not display the cursor */
    clear();       /* clear the screen that curses provides */
    noecho();      /* prevent the input chars to be echoed to the screen */
    cbreak();      /* change the stty so that characters are delivered to the
                program as they are typed--no need to hit the return key!*/
}

//ends curses
void terminate(void) {
    mvcur(0, COLS - 1, LINES - 1, 0);
    clear();
    refresh();
    endwin();
}

//reprint the worm if the worm is not growing, the difference between this
// and reprintGrowing worm is that it does empty the tail, both visually and
// in the data structure.
void reprintWorm(Worm w) {
    move(w.tail().row, w.tail().column);
    addch(' ');
    w.removeTail();

    move(w.justBeforeHead().row, w.justBeforeHead().column);
    addch('o');

    move(w.head().row, w.head().column);
    addch('@');
    refresh();

}

//reprints the worm if it's growing.
void reprintGrowingWorm(Worm &w) {
    move(w.justBeforeHead().row, w.justBeforeHead().column);
    addch('o');

    Cell tail1(w.tail().row, w.tail().column, -1);
    move(tail1.row, tail1.column);
    addch('o');

    move(w.head().row, w.head().column);
    addch('@');
    refresh();

}

//checks if the worm is dead and returns true or false.
bool checkLife(Worm &worm, int height, int width, int tempCell) {
    if (worm.head().row == 1 || worm.head().row == height + 1 || worm.head().column == 0 ||
        worm.head().column == width + 1 || tempCell == -1) {
        return true;
    }
    return false;
}

//moves the worm in the data structure if the worm isn't growing.
void move(Worm &w, ScreenBackend &s, bool &lifeStatus, Cell tempCell, int width, int height) {
    lifeStatus = checkLife(w, height, width, s.getValue(tempCell.row, tempCell.column));
    if (lifeStatus) {
        return;
    }
    w.addHead(tempCell);
    s.wormOccupy(tempCell, w);

    reprintWorm(w);
    w.removeTail();

    refresh();

}

//moves the worm if the worm is growing.
void growingMove(Worm &w, ScreenBackend &s, bool &lifeStatus, Cell tempCell, int width, int height) {
    lifeStatus = checkLife(w, height, width, s.getValue(tempCell.row, tempCell.column));
    if (lifeStatus) {
        return;
    }
    w.addHead(tempCell);
    s.wormOccupy(tempCell, w);

    reprintGrowingWorm(w);

    refresh();
}

//applies the win if win condition is true.
void win(int score) {
    terminate();
    std::cout << "YOU WON!\n" << "Score: " << score << std::endl;
    exit(1);
}
