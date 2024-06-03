#pragma once
#ifndef ADMINLOGINWINDOW_H
#define ADMINLOGINWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "TextField.h"
#include "UserSignUpWindow.h" // Ensure this header is included
#include "AdminDashboardWindow.h"
#include "Picture.h"

class AdminLoginWindow {
private:
    sf::RenderWindow& window;
    sf::Font font;
    BankSystem& bankSystem;
    Button loginButton;
    Button signupButton;
    Button resetButton;
    sf::Text accountLabel;
    sf::Text passwordLabel;
    TextField accountField;
    TextField passwordField;
    Picture background;
    Button backButton;

public:
    AdminLoginWindow(sf::RenderWindow& win, BankSystem& bs)
        : window(win), bankSystem(bs),
        loginButton("Login", { 160, 50 }, 20, sf::Color(38, 43, 145), sf::Color::White),
        signupButton("Sign Up", { 160, 50 }, 20, sf::Color(38, 43, 145), sf::Color::White),
        resetButton("Reset", { 160, 50 }, 20, sf::Color(38, 43, 145), sf::Color::White),
        accountField({ 410, 40 }, font, "e.g: 000-00000-000", false),
        passwordField({ 410, 40 }, font, "e.g: **********", true),
        backButton("Back", { 100, 50 }, 20, sf::Color(255, 0, 0), sf::Color::White),
        background("Accounting.jpg") {

        loginButton.setPosition({ 150, 300 });
        signupButton.setPosition({ 350, 300 });
        resetButton.setPosition({ 550, 300 });

        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        accountField.setPosition({ 290, 150 });
        passwordField.setPosition({ 290, 220 });

        accountLabel.setFont(font);
        accountLabel.setString("Username:");
        accountLabel.setCharacterSize(20);
        accountLabel.setFillColor(sf::Color::Black);
        accountLabel.setPosition({ 150, 150 });

        passwordLabel.setFont(font);
        passwordLabel.setString("Password:");
        passwordLabel.setCharacterSize(20);
        passwordLabel.setFillColor(sf::Color::Black);
        passwordLabel.setPosition({ 150, 220 });

       
        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Handle text field events
                accountField.handleEvent(event);
                passwordField.handleEvent(event);

                // Handle button clicks
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (loginButton.buttonClicked(window)) {
                        // Login button action
                        bool validity;
                        std::string username = accountField.getText();
                        std::string password = passwordField.getText();
                        validity = bankSystem.AdminLogin(username, password);
                        if (validity) {
                            // Open AdminDashboardWindow
                            AdminDashboardWindow dashboardWindow(window, bankSystem);
                            dashboardWindow.run();
                        }
                        else {
                            // Handle login failure (e.g., show error message)
                            std::cout << "Invalid login credentials!" << std::endl;
                        }
                        loginButton.setBackColor(sf::Color(22, 25, 84));
                    }


                    else if (signupButton.buttonClicked(window)) {
                        UserSignUpWindow signUpWindow(window, bankSystem); // Create an instance of UserSignUpWindow
                        signUpWindow.run(); // Call the run function of the created instance
                    }
                    else if (resetButton.buttonClicked(window)) {
                        // Reset button action
                        std::cout << "Reset:\n";
                        resetButton.setBackColor(sf::Color(22, 25, 84));
                    }
                    else if (backButton.buttonClicked(window)) {
                        // Handle back button click
                        cout << "Back button clicked\n";
                        // Close the window or perform other actions
                        return;

                    }
                }

                // Handle text field activation
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (accountField.isMouseOver(window)) {
                        accountField.setActive(true);
                        passwordField.setActive(false);
                    }
                    else if (passwordField.isMouseOver(window)) {
                        passwordField.setActive(true);
                        accountField.setActive(false);
                    }
                    else {
                        accountField.setActive(false);
                        passwordField.setActive(false);
                    }
                }
            }

            // Clear the window
            window.clear(sf::Color::White);
            background.drawTo(window);

            // Draw all UI components
            loginButton.drawTo(window);
            signupButton.drawTo(window);
            resetButton.drawTo(window);
            accountField.drawTo(window);
            passwordField.drawTo(window);
            backButton.drawTo(window);
            window.draw(accountLabel);
            window.draw(passwordLabel);
            

            // Display the window
            window.display();
        }
    }
};

#endif // ADMINLOGINWINDOW_H
