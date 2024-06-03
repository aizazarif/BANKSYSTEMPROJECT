#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
using namespace std;
using namespace sf;

class Button {
private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Font font;

public:
    // Default constructor
    Button() {
        // Set a default size for the button
        button.setSize({ 100, 50 });
        button.setFillColor(sf::Color::Blue); // Default background color

        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font" << endl;
            // Handle error
        }

        text.setFont(font);
        text.setString("Button"); // Default text
        text.setFillColor(sf::Color::White); // Default text color
        text.setCharacterSize(20); // Default character size

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
    }

    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
        button.setSize(size);
        button.setFillColor(bgColor);

        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
        }

        text.setFont(font);
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
    }

    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos);
        text.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
    }
    void setFont(sf::Font& font) {
        text.setFont(font);
    }
    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }
    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonRect = button.getGlobalBounds();

        if (buttonRect.contains((float)mousePos.x, (float)mousePos.y)) {
            return true;
        }
        return false;
    }

    Vector2f getPosition() const {
        return button.getPosition();
    }
    Vector2f getSize() const {
        return button.getSize();
    }
    bool buttonClicked(sf::RenderWindow& window) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (button.getPosition().x <= mousePos.x && mousePos.x <= button.getPosition().x + button.getSize().x && button.getPosition().y <= mousePos.y && mousePos.y <= button.getPosition().y + button.getSize().y) {
            return 1;
        }
        else
            return 0;
    }
    void leftalign(sf::Vector2f pos, float textOffset)
    {
        button.setPosition(pos);

        float xPos = pos.x + textOffset; // Set the x-position with the offset
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }
};

#endif // BUTTON_H
