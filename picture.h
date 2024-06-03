#pragma once
#ifndef PICTURE_H
#define PICTURE_H

#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
using namespace std;
using namespace sf;
class Picture {
public:
    Picture(std::string filePath) {
        texture.loadFromFile(filePath);
        sprite.setTexture(texture);
    }

    void setScale(sf::Vector2f scale) {
        sf::Vector2f aspectRatio(scale.x / texture.getSize().x, scale.y / texture.getSize().y);
        sprite.setScale(aspectRatio);
    }

    void setPosition(sf::Vector2f position) {
        sprite.setPosition(position);
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif
