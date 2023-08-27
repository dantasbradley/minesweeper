#include <SFML/Graphics.hpp>
#include "Board.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>

void loadSettings(string filePath, vector<int>& settings){
    ifstream infile(filePath);
    string temp;
    int row;
    getline(infile, temp);
    row = stoi(temp);
    int column;
    getline(infile, temp);
    column = stoi(temp);
    int mines;
    getline(infile, temp);
    mines = stoi(temp);
    settings.push_back(row);
    settings.push_back(column);
    settings.push_back(mines);
}

int main()
{
    //make window and board
    vector<int> settings;
    loadSettings("boards/config.cfg", settings);
    int row = settings.at(0);
    int column = settings.at(1);
    int mines = settings.at(2);
    sf::RenderWindow window(sf::VideoMode(row*32, column*32 + 100), "Minesweeper");
    Board board(row, column, mines);

    //run program while window is open
    while (window.isOpen())
    {
        //check for all events in this window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f mousePosition (sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                //right click
                if (event.mouseButton.button == sf::Mouse::Left){
                    if (board.touchingBoard(mousePosition.x, mousePosition.y)){
                        if (!board.won() && !board.lost()){
                            //press a tile
                            board.tileAtP(mousePosition.x/32,mousePosition.y/32)->press();
                            board.checkCondition();
                        }
                    }
                    else if (board.touchingButton(mousePosition)){
                        //button touch
                    }
                    else{
                        
                    }
                }

                //left click
                else if (event.mouseButton.button == sf::Mouse::Right){
                    if (board.touchingBoard(mousePosition.x, mousePosition.y)){
                        if (!board.won() && !board.lost()){
                            //flag at tile location
                            board.tileAtP(mousePosition.x/32,mousePosition.y/32)->flagIt();
                            board.updateFlag();
                        }
                    }
                }


            }
        }
        //clear screen
        window.clear();
        //draw everything we want to see
        board.draw(window);
        //show the screen
        window.display();
    }

    TextureManager::Clear();
    return 0;
}
