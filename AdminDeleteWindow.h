#pragma once
#ifndef ADMINDELETEWINDOW_H
#define ADMINDELETEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h"
#include "AdminDashboardWindow.h"  // Ensure this includes the correct header

using namespace std;
using namespace sf;

class AdminDeleteWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    AdminDashboardWindow* dashboardWindow;
    Font font;
    Picture background;
    RectangleShape usernameBox;
    RectangleShape passwordBox;
    Text usernameText;
    Text passwordText;
    Text usernamePlaceholder;
    Text passwordPlaceholder;
    Button deleteButton;
    Button backButton;
    std::string username;
    std::string password;
    bool usernameActive;
    bool passwordActive;

public:
    AdminDeleteWindow(RenderWindow& win, BankSystem& bs, User* usr, AdminDashboardWindow* dashWin)
        : window(win), bankSystem(bs), user(usr), dashboardWindow(dashWin),
        background("Accounting.jpg"),
        deleteButton("Delete Account", { 160, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        backButton("Back", { 100, 50 }, 20, sf::Color(0, 0, 255), sf::Color::White),
        usernameActive(false), passwordActive(false) {

        // Load the font
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font\n";
            throw runtime_error("Failed to load font.");
        }

        // Set up the background
        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });

        // Set up the username box
        usernameBox.setSize(Vector2f(300, 50));
        usernameBox.setFillColor(Color(255, 255, 255, 128));
        usernameBox.setPosition(400 - usernameBox.getSize().x / 2, 150);

        // Set up the password box
        passwordBox.setSize(Vector2f(300, 50));
        passwordBox.setFillColor(Color(255, 255, 255, 128));
        passwordBox.setPosition(400 - passwordBox.getSize().x / 2, 250);

        // Set up the username text
        usernameText.setFont(font);
        usernameText.setCharacterSize(20);
        usernameText.setFillColor(Color::Black);
        usernameText.setPosition(400 - usernameBox.getSize().x / 2 + 10, 160);

        // Set up the password text
        passwordText.setFont(font);
        passwordText.setCharacterSize(20);
        passwordText.setFillColor(Color::Black);
        passwordText.setPosition(400 - passwordBox.getSize().x / 2 + 10, 260);

        // Set up the username placeholder
        usernamePlaceholder.setFont(font);
        usernamePlaceholder.setString("Enter username:");
        usernamePlaceholder.setCharacterSize(20);
        usernamePlaceholder.setFillColor(Color(128, 128, 128));
        usernamePlaceholder.setPosition(400 - usernameBox.getSize().x / 2 + 10, 160);

        // Set up the password placeholder
        passwordPlaceholder.setFont(font);
        passwordPlaceholder.setString("Enter password:");
        passwordPlaceholder.setCharacterSize(20);
        passwordPlaceholder.setFillColor(Color(128, 128, 128));
        passwordPlaceholder.setPosition(400 - passwordBox.getSize().x / 2 + 10, 260);

        // Set up the delete button
        deleteButton.setFont(font);
        deleteButton.setPosition({ 400 - deleteButton.getSize().x / 2, 350 });

        // Set up the back button
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
                    if (deleteButton.buttonClicked(window)) {
                        cout << "Delete Account button clicked\n";
                        if (bankSystem.deleteAccount(username, password)) {
                            cout << "Account deleted\n";
                        }
                        else {
                            cout << "Account not found or password incorrect\n";
                        }
                    }

                    if (usernameBox.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        usernameActive = true;
                        passwordActive = false;
                    }
                    else if (passwordBox.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        usernameActive = false;
                        passwordActive = true;
                    }
                    else {
                        usernameActive = false;
                        passwordActive = false;
                    }

                    if (backButton.buttonClicked(window)) {
                        cout << "Back button clicked\n";
                        return;
                    }
                }

                if (usernameActive && event.type == Event::TextEntered) {
                    if (event.text.unicode == 8) { // Handle backspace
                        if (!username.empty()) {
                            username.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13) { // Handle ASCII input except enter
                        username += static_cast<char>(event.text.unicode);
                    }
                }

                if (passwordActive && event.type == Event::TextEntered) {
                    if (event.text.unicode == 8) { // Handle backspace
                        if (!password.empty()) {
                            password.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13) { // Handle ASCII input except enter
                        password += static_cast<char>(event.text.unicode);
                    }
                }
            }

            usernameText.setString(username);
            passwordText.setString(password);

            window.clear();
            background.drawTo(window);
            window.draw(usernameBox);
            window.draw(passwordBox);

            if (username.empty() && !usernameActive) {
                window.draw(usernamePlaceholder);
            }
            else {
                window.draw(usernameText);
            }

            if (password.empty() && !passwordActive) {
                window.draw(passwordPlaceholder);
            }
            else {
                window.draw(passwordText);
            }

            deleteButton.drawTo(window);
            backButton.drawTo(window);
            window.display();
        }
    }
};

#endif // ADMINDELETEWINDOW_H
