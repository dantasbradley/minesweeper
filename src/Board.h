#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Counter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#pragma once
using namespace std;

class Board{
    int row;
    int column;
    int mines;
    int initialMines;
    int flagAmount = 0;
    vector<Tile> tiles;
    vector<int> mineLoc;
    vector<int> blankLoc;
    Counter counter;

    sf::Sprite face;
    sf::Sprite debug;
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    bool win = false;
    bool lose = false;

public:
    Board(int _row, int _column, int _mines);
    Tile* tileAtP(int gridx, int gridy);
    bool touchingBoard(float x, float y);
    bool touchingButton(sf::Vector2f mouseLoc);
    void draw(sf::RenderWindow &window);
    void loadTest(string filePath);
    void reset();
    void debugMode();
    void newGame();
    void updateFlag();
    void updateNumbers();
    void updateAdjacents();
    void updateMines();
    void shuffleMines();
    void buttonSetup();
    bool won();
    bool lost();
    void checkCondition();

};