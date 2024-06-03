#pragma once
#ifndef USERVIEWBALANCEWINDOW_H
#define USERVIEWBALANCEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h" // Including the Picture class header

using namespace std;
using namespace sf;

class UserViewBalanceWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    Font font;
    Picture background;
    Picture lockIcon;
    Text balanceText;
    Button backButton;
    Button back;

public:
    UserViewBalanceWindow(RenderWindow& win, BankSystem& bs, User* usr)
        : window(win), bankSystem(bs), user(usr),
        background("Accounting.jpg"),
        lockIcon("lock.jpg"),
        backButton("Back", { 100, 50 }, 20, sf::Color(255, 0, 0), sf::Color::White) {

        // Load the font
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font\n";
            throw runtime_error("Failed to load font.");
        }

        // Set up the background
        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });

        // Set up the lock icon
        lockIcon.setScale({ 64, 64 });
        lockIcon.setPosition({ 368, 50 });

        // Set up the balance text
        balanceText.setFont(font);
        balanceText.setCharacterSize(24);
        balanceText.setFillColor(Color::White);
        balanceText.setPosition(400, 300);

        // Set up the back button
        backButton.setFont(font);
        backButton.setPosition({ 50, 50 });
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (backButton.buttonClicked(window)) {
                        cout << "Back button clicked\n";
                        // Go back to the previous window or close the window
                        // Add your logic here
                        return;
                    }
                }
            }

            // Update balance text by calling checkBalance function
            try {
                double balance = bankSystem.checkBalance(user->getUsername());
                balanceText.setString("Balance: $" + to_string(balance));
            }
            catch (const std::exception& e) {
                cerr << "Error: " << e.what() << endl;
                balanceText.setString("Error: Unable to retrieve balance");
            }

            window.clear();
            background.drawTo(window);
            lockIcon.drawTo(window);
            window.draw(balanceText);
            backButton.drawTo(window);
            window.display();
        }
    }
};
#endif // USERVIEWBALANCEWINDOW_H
