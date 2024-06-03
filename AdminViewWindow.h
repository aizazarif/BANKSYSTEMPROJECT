#ifndef ADMINVIEWWINDOW_H
#define ADMINVIEWWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h"

using namespace std;
using namespace sf;

class AdminViewWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    Font font;
    Picture background;
    Picture freezeIcon;
    Text instructionText;
    Text amountText;
    Text amountPlaceholder;
    RectangleShape amountBox;
    Button freezeButton;
    Button backButton; // Added back button
    std::string amount;
    bool amountActive;

public:
    AdminViewWindow(RenderWindow& win, BankSystem& bs, User* usr)
        : window(win), bankSystem(bs), user(usr),
        background("Accounting.jpg"),
        freezeIcon("lock.jpg"),
        freezeButton("Freeze Account", { 160, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        backButton("Back", { 160, 50 }, 20, sf::Color(38, 43, 145), sf::Color::White) {

        // Load the font
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font\n";
            throw runtime_error("Failed to load font.");
        }

        // Set up the background
        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });

        // Set up the freeze icon
        freezeIcon.setScale({ 64, 64 });
        freezeIcon.setPosition({ 368, 50 });

        // Set up the instruction text
        instructionText.setFont(font);
        instructionText.setString("Enter the account you want the detail of:");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 150);

        //amount box
        amountBox.setSize(Vector2f(300, 50));
        amountBox.setFillColor(Color(255, 255, 255, 128));
        amountBox.setPosition(400 - amountBox.getSize().x / 2, 200);

        //amount text
        amountText.setFont(font);
        amountText.setCharacterSize(20);
        amountText.setFillColor(Color::Black);
        amountText.setPosition(400 - amountBox.getSize().x / 2 + 10, 210);

        //placeholders
        amountPlaceholder.setFont(font);
        amountPlaceholder.setString("Enter amount");
        amountPlaceholder.setCharacterSize(20);
        amountPlaceholder.setFillColor(Color(128, 128, 128));
        amountPlaceholder.setPosition(400 - amountBox.getSize().x / 2 + 10, 210);

        // Set up the freeze button
        freezeButton.setFont(font);
        freezeButton.setPosition({ 300, 300 }); // Adjusted position for both buttons

        // Set up the back button
        backButton.setFont(font);
        backButton.setPosition({ 500, 300 }); // Adjusted position for both buttons
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (freezeButton.buttonClicked(window)) {
                        cout << "Freeze Account button clicked\n";
                        // Call the bank system method to freeze the account
                        bankSystem.freezeAccount(user->getUsername());
                        cout << "Account frozen\n";
                        // Close the window or perform other actions
                    }
                    else if (backButton.buttonClicked(window)) {
                        // Handle back button click
                        cout << "Back button clicked\n";
                        // Close the window or perform other actions
                        return;
                    }
                }
            }

            window.clear();
            background.drawTo(window);
            freezeIcon.drawTo(window);
            window.draw(instructionText);
            window.draw(amountBox);
            if (amount.empty() && !amountActive) {
                window.draw(amountPlaceholder);
            }
            else {
                window.draw(amountText);
            }
            freezeButton.drawTo(window);
            backButton.drawTo(window); // Draw the back button
            window.display();
        }
    }
};

#endif // ADMINVIEWWINDOW_H
