#pragma once
#ifndef USERDEPOSITWINDOW_H
#define USERDEPOSITWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h" // Including the Picture class header

using namespace std;
using namespace sf;

class UserDepositWindow {
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
    Button depositButton;
    std::string amount;
    bool amountActive;
    Button backButton;

public:
    UserDepositWindow(RenderWindow& win, BankSystem& bs, User* usr)
        : window(win), bankSystem(bs), user(usr),
        background("Accounting.jpg"),
        lockIcon("lock.jpg"),
        depositButton("Deposit", { 100, 50 }, 20, sf::Color(0, 204, 0), sf::Color::White),
        backButton("Back", { 100, 50 }, 20, sf::Color(0, 0, 255), sf::Color::White),
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
        instructionText.setString("Enter the amount you want to deposit");
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

        // Set up the deposit button
        depositButton.setFont(font);
        depositButton.setPosition({ 400 - depositButton.getSize().x / 2, 300 });
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (depositButton.buttonClicked(window)) {
                        cout << "Deposit button clicked\n";
                        cout << "Amount: " << amount << "\n";

                        // Convert the amount string to a float
                        float depositAmount;
                        stringstream ss(amount);
                        ss >> depositAmount;

                        // Check if the amount is valid
                        if (depositAmount > 0) {
                            // Get the username of the current user
                            string username = user->getUsername();

                            // Perform deposit to user's account
                            if (bankSystem.deposit(username, depositAmount)) {
                                cout << "Deposit successful\n";

                                // Update the user interface or show a success message
                                // For example, you can clear the amount input field
                                amount = "";
                            }
                            else {
                                cout << "Failed to deposit amount\n";
                                // Handle the case where the deposit fails, e.g., show an error message
                            }
                        }
                        else {
                            cout << "Invalid amount entered\n";
                            // Handle the case where the entered amount is invalid, e.g., show an error message
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
            depositButton.drawTo(window);
            backButton.drawTo(window);
            window.display();
        }
    }
};

#endif // USERDEPOSITWINDOW_H
