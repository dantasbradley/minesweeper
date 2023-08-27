#include "Board.h"
#include "Random.h"
#include "TextureManager.h"

Board::Board(int _row, int _column, int _mines) {
    row = _row;
    column = _column;
    initialMines = _mines;
    mines = _mines;
    mineLoc.clear();
    blankLoc.clear();
    for (int c = 0; c < column; ++c) {
        for (int r = 0; r < row; ++r) {
            tiles.push_back(Tile(r*32,c*32));
        }
    }
    buttonSetup();

    //shuffle mines at random loc
    shuffleMines();
    //get numbers for tiles near mines
    updateNumbers();
    //get adjacent for all blank tiles
    updateAdjacents();
}

void Board::buttonSetup() {
    counter = Counter(column*32);
    face.setTexture(TextureManager::GetTexture("face_happy"));
    debug.setTexture(TextureManager::GetTexture("debug"));
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test3.setTexture(TextureManager::GetTexture("test_3"));
    int rightmostX = row * 32;
    int bottomY = column * 32;
    face.setPosition(rightmostX - 12 * 32, bottomY);
    debug.setPosition(rightmostX - 8 * 32, bottomY);
    test1.setPosition(rightmostX - 6 * 32, bottomY);
    test2.setPosition(rightmostX - 4 * 32, bottomY);
    test3.setPosition(rightmostX - 2 * 32, bottomY);
}

void Board::shuffleMines() {
    int j = 0;
    bool repeat;
    while (j < mines){
        repeat = false;
        int mineIndex = Random::Int(0,tiles.size()-1);
        for (int i = 0; i < mineLoc.size(); i++){
            if(mineLoc.at(i) == mineIndex){
                repeat = true;
            }
        }
        if (repeat == false){
            mineLoc.push_back(mineIndex);
            j++;
        }
    }
    updateMines();
}

void Board::updateMines() {
    for (int i = 0; i < mineLoc.size(); ++i) {
        tiles.at(mineLoc.at(i)).addMine();
    }
}

void Board::draw(sf::RenderWindow &window) {
    for (int i = 0; i < tiles.size(); ++i) {
        tiles.at(i).display(window);
    }
    counter.setCounter(mines - flagAmount);
    counter.display(window);
    window.draw(face);
    window.draw(debug);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);

}

Tile* Board::tileAtP(int gridx, int gridy) {
    int index = gridy * row + gridx;
    return &tiles.at(index);
}

void Board::newGame() {
    reset();
    mines = initialMines;
    shuffleMines();
    updateNumbers();
    updateAdjacents();
}

bool Board::touchingBoard(float x, float y) {
    if ((x <= row*32) &(y <= column*32)){
        return true;
    }
    else{
        return false;
    }
}

bool Board::touchingButton(sf::Vector2f mouseLoc) {
    if (face.getGlobalBounds().contains(mouseLoc)){
        newGame();
        return true;
    }
    else if (debug.getGlobalBounds().contains(mouseLoc) && !lose && !win){
        debugMode();
        return true;
    }
    else if (test1.getGlobalBounds().contains(mouseLoc)){
        loadTest("boards/testboard1.brd");
        return true;
    }
    else if (test2.getGlobalBounds().contains(mouseLoc)){
        loadTest("boards/testboard2.brd");
        return true;
    }
    else if (test3.getGlobalBounds().contains(mouseLoc)){
        loadTest("boards/testboard3.brd");
        return true;
    }
    else {
        return false;
    }
}

void Board::reset() {
    face.setTexture(TextureManager::GetTexture("face_happy"));
    lose = false;
    win = false;
    for (int i = 0; i < tiles.size(); ++i) {
        tiles.at(i).norm();
    }
    flagAmount = 0;
    mineLoc.clear();
    blankLoc.clear();
}

void Board::debugMode() {
    for (int i = 0; i < mineLoc.size(); ++i) {
        tiles.at(mineLoc.at(i)).mineChange();
    }
}

void Board::loadTest(string filePath) {
    reset();
    ifstream infile(filePath);
    string line;
    vector<int> indexes;
    int rowNum = 0;
    while(getline(infile, line)){
        istringstream stream(line);
        string numbers;
        getline(stream, numbers);
        string initialNums = numbers;
        int index = 0;
        int loc = 0;
        if (numbers.find("1") != string::npos){//if string found
            while (numbers.find_first_of("1") != numbers.find_last_of("1")){
                loc = numbers.find("1");
                index += loc;
                indexes.push_back(index);
                string temp = numbers.substr(loc+1, numbers.size());
                numbers = temp;
                index ++;
            }
            //one more time for last "1"
            loc = numbers.find("1");
            index += loc;
            indexes.push_back(index);
        }
        for (int i = 0; i < indexes.size(); ++i) {
            mineLoc.push_back(indexes.at(i)+rowNum*row);
        }
        rowNum++;
        indexes.clear();
    }
    mines= mineLoc.size();
    updateMines();
    updateNumbers();
    updateAdjacents();
}

void Board::updateNumbers() {
    blankLoc.clear();
    for (int i = 0; i < mineLoc.size(); ++i) {
        int currX = tiles.at(mineLoc.at(i)).getGridx();
        int currY = tiles.at(mineLoc.at(i)).getGridy();
        if (currY == 0){ //top 3 not possible
        }
        else{
            if (currX == 0){//topMiddle + topRight
                tileAtP(currX,currY-1)->addNum();
                tileAtP(currX+1,currY-1)->addNum();
            }
            else if (currX == row-1){//topLeft + topMiddle
                tileAtP(currX-1,currY-1)->addNum();
                tileAtP(currX,currY-1)->addNum();
            }
            else{//topLeft + topMiddle + topRight
                tileAtP(currX-1,currY-1)->addNum();
                tileAtP(currX,currY-1)->addNum();
                tileAtP(currX+1,currY-1)->addNum();
            }
        }
        if (currX == 0){//right
            tileAtP(currX+1,currY)->addNum();
        }
        else if (currX == row-1){//left
            tileAtP(currX-1,currY)->addNum();
        }
        else{//left + right
            tileAtP(currX+1,currY)->addNum();
            tileAtP(currX-1,currY)->addNum();
        }
        if (currY == column-1){ //bottom 3 not possible
        }
        else{
            if (currX == 0){//bottomMiddle + bottomRight
                tileAtP(currX,currY+1)->addNum();
                tileAtP(currX+1,currY+1)->addNum();

            }
            else if (currX == row-1){//bottomLeft + bottomMiddle
                tileAtP(currX,currY+1)->addNum();
                tileAtP(currX-1,currY+1)->addNum();
            }
            else{//bottomLeft + bottomMiddle + bottomRight
                tileAtP(currX,currY+1)->addNum();
                tileAtP(currX+1,currY+1)->addNum();
                tileAtP(currX-1,currY+1)->addNum();
            }
        }
        tiles.at(mineLoc.at(i)).updateNum();
    }
    for (int i = 0; i < tiles.size(); ++i) {
        if (!tiles.at(i).hasNumber() && !tiles.at(i).hasMine()){
            blankLoc.push_back(i);
        }
    }
}

void Board::updateAdjacents() {
    for (int i = 0; i < blankLoc.size(); ++i) {

        int currX = tiles.at(blankLoc.at(i)).getGridx();
        int currY = tiles.at(blankLoc.at(i)).getGridy();
            if (currY == 0){ //top 3 not possible
            }
            else{
                if (currX == 0){//topMiddle + topRight
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX,currY-1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX+1,currY-1));
                }
                else if (currX == row-1){//topLeft + topMiddle
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX-1,currY-1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX,currY-1));
                }
                else{//topLeft + topMiddle + topRight
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX-1,currY-1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX,currY-1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX+1,currY-1));
                }
            }
            if (currX == 0){//right
                tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX+1,currY));
            }
            else if (currX == row-1){//left
                tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX-1,currY));
            }
            else{//left + right
                tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX+1,currY));
                tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX-1,currY));
            }
            if (currY == column-1){ //bottom 3 not possible
            }
            else{
                if (currX == 0){//bottomMiddle + bottomRight
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX,currY+1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX+1,currY+1));

                }
                else if (currX == row-1){//bottomLeft + bottomMiddle
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX,currY+1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX-1,currY+1));
                }
                else{//bottomLeft + bottomMiddle + bottomRight
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX,currY+1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX+1,currY+1));
                    tiles.at(blankLoc.at(i)).addAdjacent(tileAtP(currX-1,currY+1));
                }
            }
    }
}

void Board::updateFlag() {
    flagAmount = 0;
    for (int i = 0; i < tiles.size(); ++i) {
        if(tiles.at(i).hasFlag()){
            flagAmount ++;
        }
    }
}

bool Board::won() {
    return win;
}

bool Board::lost() {
    return lose;
}

void Board::checkCondition() {
    bool allPressed = true;
    bool minePress = false;
    for (int i = 0; i < tiles.size(); ++i) {
        if (tiles.at(i).hasPressedMine()){
            minePress = true;
        }
        if (!tiles.at(i).hasMine() && !tiles.at(i).hasPressed()){
            allPressed = false;
        }
    }
    if (allPressed == true){ // win
        win = true;
        face.setTexture(TextureManager::GetTexture("face_win"));
        for (int i = 0; i < tiles.size(); ++i){
            if (tiles.at(i).hasMine()){
                //tiles.at(i).hideMine();
                tiles.at(i).flagIt();
                updateFlag();
                counter.setCounter(mines - flagAmount);
            }
        }
    }
    if (minePress){ // lose
        lose = true;
        face.setTexture(TextureManager::GetTexture("face_lose"));
        for (int i = 0; i < tiles.size(); ++i){
            if (tiles.at(i).hasMine()){
                tiles.at(i).showMine();
                tiles.at(i).press();
            }
        }

    }
}
