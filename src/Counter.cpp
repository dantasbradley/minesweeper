#include "Counter.h"
Counter::Counter() {

}
Counter::Counter(int _bottomY) {
    bottomY = _bottomY;
    for (int i = 0; i <= 10; ++i) {
        sf::Sprite counter;
        counter.setTexture(TextureManager::GetTexture("digits"));
        //counter.setPosition(0, bottomY);
        counter.setTextureRect(sf::IntRect(width*i,0,width,height));
        numbers.push_back(counter);
    }
    //number 0-9
    //number 10 is Negative sign
}
void Counter::setCounter(int num) {
    nums.clear();
    negative = false;
    if (num < 0){
        num *= -1;
        negative = true;
    }
    int n = 1;
    int a;
    int temp = num;
    //134 / 10 = 13     %=4
    //13 / 10 = 1       %=3
    //1 / 10 = 0        %=1
    while (n != 0){
        n = temp / 10;
        a = temp % 10;
        temp = n;
        nums.push_back(a);
    }
    //nums are backwards

}
void Counter::display(sf::RenderWindow &window) {
    int l = 0;
    for (int i = nums.size()-1; i >= 0; --i) {
        sf::Sprite curr;
        curr = numbers.at(nums.at(i));
        curr.setPosition(width*l+width,bottomY);
        window.draw(curr);
        l++;
    }
    if (negative){
        sf::Sprite negative;
        negative = numbers.at(10);
        negative.setPosition(0, bottomY);
        window.draw(negative);
    }
}