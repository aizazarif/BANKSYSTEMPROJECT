#ifndef ADMINUNFREEZEWINDOW_H
#define ADMINUNFREEZEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h"

using namespace std;
using namespace sf;

class AdminUnFreezeWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    Font font;
    Picture background;
    Picture unfreezeIcon;
    Text instructionText;
    Text usernameLabel;
    Text usernameInput;
    Button unfreezeButton;
    Button backButton;
    string username;

public:
    AdminUnFreezeWindow(RenderWindow& win, BankSystem& bs)
        : window(win), bankSystem(bs),
        background("Accounting.jpg"),
        unfreezeIcon("unlock.jpg"),
        unfreezeButton("Unfreeze Account", { 160, 50 }, 20, sf::Color(38, 145, 51), sf::Color::White),
        backButton("Back", { 160, 50 }, 20, sf::Color(38, 43, 145), sf::Color::White) {

        // Load the font
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font\n";
            throw runtime_error("Failed to load font.");
        }

        // Set up the background
        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });

        // Set up the unfreeze icon
        unfreezeIcon.setScale({ 64, 64 });
        unfreezeIcon.setPosition({ 368, 50 });

        // Set up the instruction text
        instructionText.setFont(font);
        instructionText.setString("Enter the username to unfreeze the account:");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 150);

        // Set up the username label
        usernameLabel.setFont(font);
        usernameLabel.setString("Username:");
        usernameLabel.setCharacterSize(20);
        usernameLabel.setFillColor(Color::White);
        usernameLabel.setPosition(250, 250);

        // Set up the username input
        usernameInput.setFont(font);
        usernameInput.setCharacterSize(20);
        usernameInput.setFillColor(Color::White);
        usernameInput.setPosition(400, 250);

        // Set up the unfreeze button
        unfreezeButton.setFont(font);
        unfreezeButton.setPosition({ 300, 350 });

        // Set up the back button
        backButton.setFont(font);
        backButton.setPosition({ 500, 350 });
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::TextEntered) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!username.empty()) {
                            username.pop_back();
                            usernameInput.setString(username);
                        }
                    }
                    else if (event.text.unicode == '\r') { // Handle enter
                        if (!username.empty()) {
                            bankSystem.unfreezeAccount(username);
                        }
                    }
                    else {
                        username += event.text.unicode;
                        usernameInput.setString(username);
                    }
                }

                if (event.type == Event::MouseButtonPressed) {
                    if (unfreezeButton.buttonClicked(window)) {
                        cout << "Unfreeze Account button clicked\n";
                        if (!username.empty()) {
                            bankSystem.unfreezeAccount(username);
                            cout << "Account unfrozen\n";
                        }
                    }
                    else if (backButton.buttonClicked(window)) {
                        cout << "Back button clicked\n";
                        // Handle back button click (e.g., close window or switch to another view)
                        return;
                    }
                }
            }

            window.clear();
            background.drawTo(window);
            unfreezeIcon.drawTo(window);
            window.draw(instructionText);
            window.draw(usernameLabel);
            window.draw(usernameInput);
            unfreezeButton.drawTo(window);
            backButton.drawTo(window);
            window.display();
        }
    }
};

#endif // ADMINUNFREEZEWINDOW_H
