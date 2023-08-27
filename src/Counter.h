#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#pragma once
class Counter{
    int bottomY;
    int width = 21;
    int height = 32;
    bool negative = false;
    vector<sf::Sprite> numbers;
    vector<int> nums;
    sf::Sprite counter;
    sf::Sprite counter1;
    sf::Sprite counter2;
    sf::Sprite counter3;
    sf::Sprite counter4;
    sf::Sprite counter5;
    sf::Sprite counter6;
    sf::Sprite counter7;
    sf::Sprite counter8;
    sf::Sprite counter9;
    sf::Sprite counterN;

public:
    Counter();
    Counter(int _bottomY);
    void setCounter(int num);
    void display(sf::RenderWindow &window);
};
