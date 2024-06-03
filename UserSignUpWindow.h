#pragma once
#ifndef USERSIGNUPWINDOW_H
#define USERSIGNUPWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Button.h"
#include "bank_system.h"
#include "picture.h"

using namespace std;
using namespace sf;

class UserSignUpWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    Font font;
    Picture background;
    Picture lockIcon;
    Text instructionText;
    Text usernameText;
    Text usernamePlaceholder;
    RectangleShape usernameBox;
    Text passwordText;
    Text passwordPlaceholder;
    RectangleShape passwordBox;
    Text companyNameText;
    Text companyNamePlaceholder;
    RectangleShape companyNameBox;
    Text firstNameText;
    Text firstNamePlaceholder;
    RectangleShape firstNameBox;
    Text lastNameText;
    Text lastNamePlaceholder;
    RectangleShape lastNameBox;
    Text emailText;
    Text emailPlaceholder;
    RectangleShape emailBox;
    Button signUpButton;
    std::string username;
    std::string password;
    std::string companyName;
    std::string firstName;
    std::string lastName;
    std::string email;
    bool usernameActive;
    bool passwordActive;
    bool companyNameActive;
    bool firstNameActive;
    bool lastNameActive;
    bool emailActive;
    Button backButton;
    double defaultBalance = 0.0; // or set a specific balance value
    double defaultLoan = 0.0;

public:
    UserSignUpWindow(RenderWindow& win, BankSystem& bs)
        : window(win), bankSystem(bs),
        background("Accounting.jpg"),
        lockIcon("Lock Symbol For Interface free icons designed by Freepik.jpg"),
        signUpButton("Sign Up", { 100, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        username(""), password(""), companyName(""), firstName(""), lastName(""), email(""),
        usernameActive(false), passwordActive(false), companyNameActive(false), firstNameActive(false),
        backButton("Back", { 100, 50 }, 20, sf::Color(255, 0, 0), sf::Color::White),
        lastNameActive(false), emailActive(false) {

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
        instructionText.setString("Enter your details to sign up");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 100);

        // Set up the username box
        usernameBox.setSize(Vector2f(300, 50));
        usernameBox.setFillColor(Color(255, 255, 255, 128));
        usernameBox.setPosition(400 - usernameBox.getSize().x / 2, 150);

        // Set up the username text
        usernameText.setFont(font);
        usernameText.setCharacterSize(20);
        usernameText.setFillColor(Color::Black);
        usernameText.setPosition(400 - usernameBox.getSize().x / 2 + 10, 160);

        // Set up the username placeholder
        usernamePlaceholder.setFont(font);
        usernamePlaceholder.setString("Enter username");
        usernamePlaceholder.setCharacterSize(20);
        usernamePlaceholder.setFillColor(Color(128, 128, 128));
        usernamePlaceholder.setPosition(400 - usernameBox.getSize().x / 2 + 10, 160);

        // Set up the password box
        passwordBox.setSize(Vector2f(300, 50));
        passwordBox.setFillColor(Color(255, 255, 255, 128));
        passwordBox.setPosition(400 - passwordBox.getSize().x / 2, 220);

        // Set up the password text
        passwordText.setFont(font);
        passwordText.setCharacterSize(20);
        passwordText.setFillColor(Color::Black);
        passwordText.setPosition(400 - passwordBox.getSize().x / 2 + 10, 230);

        // Set up the password placeholder
        passwordPlaceholder.setFont(font);
        passwordPlaceholder.setString("Enter password");
        passwordPlaceholder.setCharacterSize(20);
        passwordPlaceholder.setFillColor(Color(128, 128, 128));
        passwordPlaceholder.setPosition(400 - passwordBox.getSize().x / 2 + 10, 230);

        // Set up the company name box
        companyNameBox.setSize(Vector2f(300, 50));
        companyNameBox.setFillColor(Color(255, 255, 255, 128));
        companyNameBox.setPosition(400 - companyNameBox.getSize().x / 2, 290);

        // Set up the company name text
        companyNameText.setFont(font);
        companyNameText.setCharacterSize(20);
        companyNameText.setFillColor(Color::Black);
        companyNameText.setPosition(400 - companyNameBox.getSize().x / 2 + 10, 300);

        // Set up the company name placeholder
        companyNamePlaceholder.setFont(font);
        companyNamePlaceholder.setString("Enter company name");
        companyNamePlaceholder.setCharacterSize(20);
        companyNamePlaceholder.setFillColor(Color(128, 128, 128));
        companyNamePlaceholder.setPosition(400 - companyNameBox.getSize().x / 2 + 10, 300);

        // Set up the first name box
        firstNameBox.setSize(Vector2f(300, 50));
        firstNameBox.setFillColor(Color(255, 255, 255, 128));
        firstNameBox.setPosition(400 - firstNameBox.getSize().x / 2, 360);

        // Set up the first name text
        firstNameText.setFont(font);
        firstNameText.setCharacterSize(20);
        firstNameText.setFillColor(Color::Black);
        firstNameText.setPosition(400 - firstNameBox.getSize().x / 2 + 10, 370);

        // Set up the first name placeholder
        firstNamePlaceholder.setFont(font);
        firstNamePlaceholder.setString("Enter first name");
        firstNamePlaceholder.setCharacterSize(20);
        firstNamePlaceholder.setFillColor(Color(128, 128, 128));
        firstNamePlaceholder.setPosition(400 - firstNameBox.getSize().x / 2 + 10, 370);

        // Set up the last name box
        lastNameBox.setSize(Vector2f(300, 50));
        lastNameBox.setFillColor(Color(255, 255, 255, 128));
        lastNameBox.setPosition(400 - lastNameBox.getSize().x / 2, 430);

        // Set up the last name text
        lastNameText.setFont(font);
        lastNameText.setCharacterSize(20);
        lastNameText.setFillColor(Color::Black);
        lastNameText.setPosition(400 - lastNameBox.getSize().x / 2 + 10, 440);

        // Set up the last name placeholder
        lastNamePlaceholder.setFont(font);
        lastNamePlaceholder.setString("Enter last name");
        lastNamePlaceholder.setCharacterSize(20);
        lastNamePlaceholder.setFillColor(Color(128, 128, 128));
        lastNamePlaceholder.setPosition(400 - lastNameBox.getSize().x / 2 + 10, 440);

        // Set up the email box
        emailBox.setSize(Vector2f(300, 50));
        emailBox.setFillColor(Color(255, 255, 255, 128));
        emailBox.setPosition(400 - emailBox.getSize().x / 2, 500);

        // Set up the email text
        emailText.setFont(font);
        emailText.setCharacterSize(20);
        emailText.setFillColor(Color::Black);
        emailText.setPosition(400 - emailBox.getSize().x / 2 + 10, 510);

        // Set up the email placeholder
        emailPlaceholder.setFont(font);
        emailPlaceholder.setString("Enter email");
        emailPlaceholder.setCharacterSize(20);
        emailPlaceholder.setFillColor(Color(128, 128, 128));
        emailPlaceholder.setPosition(400 - emailBox.getSize().x / 2 + 10, 510);

        // Set up the sign-up button
        signUpButton.setFont(font);
        signUpButton.setPosition({ 400 - signUpButton.getSize().x / 2, 570 });
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (signUpButton.buttonClicked(window)) {
                        cout << "Sign-Up button clicked\n";
                        cout << "Username: " << username << "\n";
                        cout << "Password: " << password << "\n";
                        cout << "Company Name: " << companyName << "\n";
                        cout << "First Name: " << firstName << "\n";
                        cout << "Last Name: " << lastName << "\n";
                        cout << "Email: " << email << "\n";

                        if (bankSystem.addUser(username, password, companyName, firstName, lastName, email, defaultBalance, defaultLoan)) {
                            cout << "Sign-Up successful\n";
                        }
                        else {
                            cout << "Username Already Exist\n";
                        }

                    }
                    else if (backButton.buttonClicked(window)) {
                        // Handle back button click
                        cout << "Back button clicked\n";
                        // Close the window or perform other actions
                        return;

                    }

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (usernameBox.getGlobalBounds().contains(mousePos)) {
                        usernameActive = true;
                        passwordActive = false;
                        companyNameActive = false;
                        firstNameActive = false;
                        lastNameActive = false;
                        emailActive = false;
                    }
                    else if (passwordBox.getGlobalBounds().contains(mousePos)) {
                        passwordActive = true;
                        usernameActive = false;
                        companyNameActive = false;
                        firstNameActive = false;
                        lastNameActive = false;
                        emailActive = false;
                    }
                    else if (companyNameBox.getGlobalBounds().contains(mousePos)) {
                        companyNameActive = true;
                        usernameActive = false;
                        passwordActive = false;
                        firstNameActive = false;
                        lastNameActive = false;
                        emailActive = false;
                    }
                    else if (firstNameBox.getGlobalBounds().contains(mousePos)) {
                        firstNameActive = true;
                        usernameActive = false;
                        passwordActive = false;
                        companyNameActive = false;
                        lastNameActive = false;
                        emailActive = false;
                    }
                    else if (lastNameBox.getGlobalBounds().contains(mousePos)) {
                        lastNameActive = true;
                        usernameActive = false;
                        passwordActive = false;
                        companyNameActive = false;
                        firstNameActive = false;
                        emailActive = false;
                    }
                    else if (emailBox.getGlobalBounds().contains(mousePos)) {
                        emailActive = true;
                        usernameActive = false;
                        passwordActive = false;
                        companyNameActive = false;
                        firstNameActive = false;
                        lastNameActive = false;
                    }
                    else {
                        usernameActive = false;
                        passwordActive = false;
                        companyNameActive = false;
                        firstNameActive = false;
                        lastNameActive = false;
                        emailActive = false;
                    }
                }

                if (event.type == Event::TextEntered) {
                    if (usernameActive) {
                        if (event.text.unicode == '\b' && !username.empty()) {
                            username.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && usernameText.getLocalBounds().width < usernameBox.getSize().x - 20) {
                            username += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (passwordActive) {
                        if (event.text.unicode == '\b' && !password.empty()) {
                            password.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && passwordText.getLocalBounds().width < passwordBox.getSize().x - 20) {
                            password += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (companyNameActive) {
                        if (event.text.unicode == '\b' && !companyName.empty()) {
                            companyName.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && companyNameText.getLocalBounds().width < companyNameBox.getSize().x - 20) {
                            companyName += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (firstNameActive) {
                        if (event.text.unicode == '\b' && !firstName.empty()) {
                            firstName.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && firstNameText.getLocalBounds().width < firstNameBox.getSize().x - 20) {
                            firstName += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (lastNameActive) {
                        if (event.text.unicode == '\b' && !lastName.empty()) {
                            lastName.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && lastNameText.getLocalBounds().width < lastNameBox.getSize().x - 20) {
                            lastName += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (emailActive) {
                        if (event.text.unicode == '\b' && !email.empty()) {
                            email.pop_back();
                        }
                        else if (event.text.unicode < 128 && event.text.unicode != '\b' && emailText.getLocalBounds().width < emailBox.getSize().x - 20) {
                            email += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }

            usernameText.setString(username);
            passwordText.setString(password);
            companyNameText.setString(companyName);
            firstNameText.setString(firstName);
            lastNameText.setString(lastName);
            emailText.setString(email);

            window.clear();
            background.drawTo(window);
            lockIcon.drawTo(window);
            window.draw(instructionText);
            window.draw(usernameBox);
            if (username.empty() && !usernameActive) {
                window.draw(usernamePlaceholder);
            }
            else {
                window.draw(usernameText);
            }
            window.draw(passwordBox);
            if (password.empty() && !passwordActive) {
                window.draw(passwordPlaceholder);
            }
            else {
                window.draw(passwordText);
            }
            window.draw(companyNameBox);
            if (companyName.empty() && !companyNameActive) {
                window.draw(companyNamePlaceholder);
            }
            else {
                window.draw(companyNameText);
            }
            window.draw(firstNameBox);
            if (firstName.empty() && !firstNameActive) {
                window.draw(firstNamePlaceholder);
            }
            else {
                window.draw(firstNameText);
            }
            window.draw(lastNameBox);
            if (lastName.empty() && !lastNameActive) {
                window.draw(lastNamePlaceholder);
            }
            else {
                window.draw(lastNameText);
            }
            window.draw(emailBox);
            if (email.empty() && !emailActive) {
                window.draw(emailPlaceholder);
            }
            else {
                window.draw(emailText);
            }
            signUpButton.drawTo(window);
            backButton.drawTo(window);
            window.display();
        }
    }
};

#endif // SIGNUPWINDOW_H
