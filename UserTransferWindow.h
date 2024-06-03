#pragma once
#ifndef USERTRANSFERWINDOW_H
#define USERTRANSFERWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h" // Including the Picture class header

using namespace std;
using namespace sf;

class UserTransferWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    Font font;
    Picture background;
    Picture lockIcon;
    Text instructionText;
    Text recipientText;
    Text recipientPlaceholder;
    RectangleShape recipientBox;
    Text amountText;
    Text amountPlaceholder;
    RectangleShape amountBox;
    Button transferButton;
    std::string recipient;
    Button backButton;
    std::string amount;
    bool recipientActive;
    bool amountActive;

public:
    UserTransferWindow(RenderWindow& win, BankSystem& bs, User* usr)
        : window(win), bankSystem(bs), user(usr),
        background("Accounting.jpg"),
        lockIcon("lock.jpg"),
        transferButton("Transfer", { 100, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        backButton("Back", { 100, 50 }, 20, sf::Color(0, 0, 255), sf::Color::White),
        recipient(""), amount(""), recipientActive(false), amountActive(false) {

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
        instructionText.setString("Enter the recipient's username and the amount to transfer");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 150);

        // Set up the recipient box
        recipientBox.setSize(Vector2f(300, 50));
        recipientBox.setFillColor(Color(255, 255, 255, 128));
        recipientBox.setPosition(400 - recipientBox.getSize().x / 2, 200);

        // Set up the recipient text
        recipientText.setFont(font);
        recipientText.setCharacterSize(20);
        recipientText.setFillColor(Color::Black);
        recipientText.setPosition(400 - recipientBox.getSize().x / 2 + 10, 210);

        // Set up the recipient placeholder
        recipientPlaceholder.setFont(font);
        recipientPlaceholder.setString("Enter recipient username");
        recipientPlaceholder.setCharacterSize(20);
        recipientPlaceholder.setFillColor(Color(128, 128, 128));
        recipientPlaceholder.setPosition(400 - recipientBox.getSize().x / 2 + 10, 210);

        // Set up the amount box
        amountBox.setSize(Vector2f(300, 50));
        amountBox.setFillColor(Color(255, 255, 255, 128));
        amountBox.setPosition(400 - amountBox.getSize().x / 2, 280);

        // Set up the amount text
        amountText.setFont(font);
        amountText.setCharacterSize(20);
        amountText.setFillColor(Color::Black);
        amountText.setPosition(400 - amountBox.getSize().x / 2 + 10, 290);

        // Set up the amount placeholder
        amountPlaceholder.setFont(font);
        amountPlaceholder.setString("Enter amount");
        amountPlaceholder.setCharacterSize(20);
        amountPlaceholder.setFillColor(Color(128, 128, 128));
        amountPlaceholder.setPosition(400 - amountBox.getSize().x / 2 + 10, 290);

        // Set up the transfer button
        transferButton.setFont(font);
        transferButton.setPosition({ 400 - transferButton.getSize().x / 2, 360 });

        backButton.setFont(font);
        backButton.setPosition({ 10, 10 });
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (transferButton.buttonClicked(window)) {
                        cout << "Transfer button clicked\n";
                        cout << "Recipient: " << recipient << "\n";
                        cout << "Amount: " << amount << "\n";

                        // Add logic to handle the transfer
                        float transferAmount;
                        stringstream ss(amount);
                        if (ss >> transferAmount && transferAmount > 0) {
                            // Perform transfer to recipient's account
                            User* recipientUser = bankSystem.getUserByUsername(recipient);
                            if (recipientUser) {
                                user->transfer(transferAmount, *recipientUser);
                                cout << "Transfer successful\n";
                            }
                            else {
                                cout << "Recipient not found\n";
                            }
                        }
                        else {
                            cout << "Invalid amount entered\n";
                        }
                    }

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (recipientBox.getGlobalBounds().contains(mousePos)) {
                        recipientActive = true;
                        amountActive = false;
                    }
                    else if (amountBox.getGlobalBounds().contains(mousePos)) {
                        amountActive = true;
                        recipientActive = false;
                    }
                    else {
                        recipientActive = false;
                        amountActive = false;
                    }
                }

                if (event.type == Event::TextEntered) {
                    if (recipientActive) {
                        if (event.text.unicode == '\b' && !recipient.empty()) {
                            recipient.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && recipientText.getLocalBounds().width < recipientBox.getSize().x - 20) {
                            recipient += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (amountActive) {
                        if (event.text.unicode == '\b' && !amount.empty()) {
                            amount.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && amountText.getLocalBounds().width < amountBox.getSize().x - 20) {
                            amount += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }

            recipientText.setString(recipient);
            amountText.setString(amount);

            window.clear();
            background.drawTo(window);
            background.drawTo(window);
            lockIcon.drawTo(window);
            window.draw(instructionText);
            window.draw(recipientBox);
            if (recipient.empty() && !recipientActive) {
                window.draw(recipientPlaceholder);
            }
            else {
                window.draw(recipientText);
            }
            window.draw(amountBox);
            if (amount.empty() && !amountActive) {
                window.draw(amountPlaceholder);
            }
            else {
                window.draw(amountText);
            }
            transferButton.drawTo(window);
            window.display();
        }
    }
};

#endif // USERTRANSFERWINDOW_H
