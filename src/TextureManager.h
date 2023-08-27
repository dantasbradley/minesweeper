#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
using namespace std;

class TextureManager{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string fileName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear(); //call this once, at the end of main()
};