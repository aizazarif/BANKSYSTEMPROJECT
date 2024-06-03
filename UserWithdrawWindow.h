#pragma once
#ifndef USERWITHDRAWWINDOW_H
#define USERWITHDRAWWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h" // Including the Picture class header

using namespace std;
using namespace sf;

class UserWithdrawWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    Font font;
    Picture background;
    Picture lockIcon;
    Text instructionText;
    Text amountText;
    Text amountPlaceholder;
    RectangleShape amountBox;
    Button withdrawButton;
    std::string amount;
    bool amountActive;
    Button backButton;

public:
    UserWithdrawWindow(RenderWindow& win, BankSystem& bs, User* usr)
        : window(win), bankSystem(bs), user(usr),
        background("Accounting.jpg"),
        lockIcon("lock.jpg"),
        withdrawButton("Withdraw", { 100, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        backButton("Back", { 100, 50 }, 20, sf::Color(255, 0, 0), sf::Color::White),
        amount(""), amountActive(false) {

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

        // Set up the instruction text
        instructionText.setFont(font);
        instructionText.setString("Enter the amount you want to withdraw");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 150);

        // Set up the amount box
        amountBox.setSize(Vector2f(300, 50));
        amountBox.setFillColor(Color(255, 255, 255, 128));
        amountBox.setPosition(400 - amountBox.getSize().x / 2, 200);

        // Set up the amount text
        amountText.setFont(font);
        amountText.setCharacterSize(20);
        amountText.setFillColor(Color::Black);
        amountText.setPosition(400 - amountBox.getSize().x / 2 + 10, 210);

        // Set up the amount placeholder
        amountPlaceholder.setFont(font);
        amountPlaceholder.setString("Enter amount");
        amountPlaceholder.setCharacterSize(20);
        amountPlaceholder.setFillColor(Color(128, 128, 128));
        amountPlaceholder.setPosition(400 - amountBox.getSize().x / 2 + 10, 210);

        // Set up the withdraw button
        withdrawButton.setFont(font);
        withdrawButton.setPosition({ 400 - withdrawButton.getSize().x / 2, 300 });
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (withdrawButton.buttonClicked(window)) {
                        cout << "Withdraw button clicked\n";
                        cout << "Amount: " << amount << "\n";

                        // Add logic to handle the withdrawal
                        float withdrawAmount;
                        stringstream ss(amount);
                        if (ss >> withdrawAmount && withdrawAmount > 0) {
                            // Perform withdrawal from user's account
                            if (user->withdraw(withdrawAmount)) {
                                cout << "Withdrawal successful\n";
                            }
                            else {
                                cout << "Insufficient balance\n";
                            }
                        }
                        else {
                            cout << "Invalid amount entered\n";
                        }
                    }
                    else if (backButton.buttonClicked(window)) {
                        // Handle back button click
                        cout << "Back button clicked\n";
                        // Close the window or perform other actions
                        return;

                    }

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (amountBox.getGlobalBounds().contains(mousePos)) {
                        amountActive = true;
                    }
                    else {
                        amountActive = false;
                    }
                }

                if (event.type == Event::TextEntered) {
                    if (amountActive) {
                        if (event.text.unicode == '\b' && !amount.empty()) {
                            amount.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && amountText.getLocalBounds().width < amountBox.getSize().x - 20) {
                            amount += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }

            amountText.setString(amount);

            window.clear();
            background.drawTo(window);
            lockIcon.drawTo(window);
            window.draw(instructionText);
            window.draw(amountBox);
            if (amount.empty() && !amountActive) {
                window.draw(amountPlaceholder);
            }
            else {
                window.draw(amountText);
            }
            withdrawButton.drawTo(window);
            backButton.drawTo(window);
            window.display();
        }
    }
};

#endif // USERDEPOSITWINDOW_H
