#pragma once
#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class TextField {
public:
    TextField()
        : font(nullptr), placeholder(""), hideText(false), active(false) {
        // Set default values or leave members uninitialized, depending on your requirements
    }
    TextField(Vector2f size, Font& font, const string& placeholder, bool hideText = false)
        : font(&font), placeholder(placeholder), hideText(hideText), active(false) {

        textField.setSize(size);
        textField.setFillColor(Color(255, 255, 255, 10));
        textField.setOutlineColor(Color::Black);
        textField.setOutlineThickness(1);

        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);

        placeholderText.setFont(font);
        placeholderText.setString(placeholder);
        placeholderText.setCharacterSize(20);
        placeholderText.setFillColor(Color(169, 169, 169));
    }

    void setPosition(Vector2f pos) {
        textField.setPosition(pos);
        text.setPosition(pos.x + 5, pos.y + 5);
        placeholderText.setPosition(pos.x + 5, pos.y + 5);
    }

    void handleEvent(Event event) {
        if (!active) return;

        if (event.type == Event::TextEntered) {
            if (event.text.unicode == 8) { // Handle backspace
                if (!inputString.empty()) {
                    inputString.pop_back();
                }
            }
            else if (event.text.unicode < 128) { // Handle regular characters
                if (text.getLocalBounds().width < textField.getLocalBounds().width - 10) {
                    inputString += static_cast<char>(event.text.unicode);
                }
            }
            text.setString(hideText ? string(inputString.size(), '*') : inputString); // Set asterisks or actual text
        }
    }

    void drawTo(RenderWindow& window) {
        window.draw(textField);
        if (inputString.empty()) {
            window.draw(placeholderText);
        }
        else {
            window.draw(text);
        }
    }

    string getText() const {
        return inputString;
    }
    void setText(const string& str) {
        inputString = str;
        text.setString(hideText ? string(inputString.size(), '*') : inputString);
    }

    bool isMouseOver(RenderWindow& window) const {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        return textField.getGlobalBounds().contains(mousePos);
    }

    void setActive(bool active) {
        this->active = active;
        textField.setOutlineColor(active ? Color::Blue : Color::Black);
    }

private:
    RectangleShape textField;
    Text text;
    Text placeholderText;
    string inputString;
    Font* font;
    string placeholder;
    bool active;
    bool hideText; // Indicates whether text should be hidden
};

#endif // TEXTFIELD_H
