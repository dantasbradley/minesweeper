#include "Tile.h"
#include "TextureManager.h"


Tile::Tile(float x, float y) {
    xPos = x;
    yPos = y;
    tileHidden.setTexture(TextureManager::GetTexture("tile_hidden"));
    tileHidden.setPosition(xPos,yPos);
    tileRevealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    tileRevealed.setPosition(xPos,yPos);
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));
}

void Tile::display(sf::RenderWindow &window) {
    if (pressed){
        window.draw(tileRevealed);
        if (num > 0){
            number.setPosition(xPos,yPos);
            window.draw(number);
        }
    }
    else{
        window.draw(tileHidden);
    }

    if (flagged){
        flag.setPosition(xPos,yPos);
        window.draw(flag);
    }
    if (mined&&mineShow){
        mine.setPosition(xPos,yPos);
        window.draw(mine);
    }

}

void Tile::press() {
    if (mined){
        pressedMine = true;
        pressed = true;
    }
    if ((pressed == false)&(mined == false)&(flagged == false)){
        pressed = true;
        if (num == 0){
            pressAdjacent();
        }
    }
}

void Tile::pressAdjacent() {
    if (adjacentTiles.size()!=0){
        for (int i = 0; i < adjacentTiles.size(); ++i) {
            adjacentTiles.at(i)->press();
        }
    }
}

void Tile::addMine() {
    mined = true;
}

void Tile::mineChange() {
    if (mineShow==true){
        mineShow = false;
    }
    else{
        mineShow = true;
    }
}

void Tile::flagIt() {
    if (!pressed){
        if (flagged){
            flagged = false;
        }
        else{
            flagged = true;
        }
    }
}

void Tile::norm() {
    flagged = false;
    mined = false;
    mineShow = false;
    pressed = false;
    pressedMine = false;
    num = 0;
}

void Tile::addAdjacent(Tile* adjacent) {
    adjacentTiles.push_back(adjacent);
}

int Tile::getGridx() {
    int gridx = xPos/32;
    return gridx;
}

int Tile::getGridy() {
    int gridy = yPos/32;
    return gridy;
}

void Tile::updateNum() {
    if (num > 0){
        string numString = to_string(num);
        string name = "number_"+numString;
        number.setTexture(TextureManager::GetTexture(name));
    }
}

void Tile::addNum() {
    if (!mined){
        num += 1;
        updateNum();
    }
}

bool Tile::hasNumber() {
    if (num > 0){
        return true;
    }
    else{
        return false;
    }
}

bool Tile::hasMine() {
    return mined;
}

bool Tile::hasFlag() {
    return flagged;
}

bool Tile::hasPressed() {
    return pressed;
}

bool Tile::hasPressedMine() {
    return pressedMine;
}

void Tile::showMine() {
    mineShow = true;
}

void Tile::hideMine() {
    mineShow = false;
}

