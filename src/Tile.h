#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once
using namespace std;

class Tile{
    float xPos;
    float yPos;
    sf::Sprite tileHidden;
    sf::Sprite tileRevealed;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite number;
    vector<Tile*> adjacentTiles;
    bool flagged = false;
    bool mined = false;
    bool mineShow = false;
    bool pressed = false;
    bool pressedMine = false;
    int num = 0;


public:
    Tile(float x, float y);
    void display(sf::RenderWindow &window);
    void press();
    void pressAdjacent();
    void flagIt();
    void addMine();
    void mineChange();
    void norm();
    void addAdjacent(Tile* adjacent);
    void addNum();
    void updateNum();
    int getGridx();
    int getGridy();
    bool hasNumber();
    bool hasMine();
    bool hasFlag();
    bool hasPressedMine();
    bool hasPressed();
    void showMine();
    void hideMine();

};