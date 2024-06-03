#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "bank_system.h"
#include "UserLoginWindow.h"
#include "AdminLoginWindow.h"
#include "Picture.h" // Include Picture class

// Forward declaration to avoid circular dependency
class BankSystem;

class MainWindow {
private:
    sf::RenderWindow& window;
    Picture background; // Background image
    Button userButton;
    Button adminButton;
    Button exitButton; // Exit button
    BankSystem& bankSystem;
    User* user;

public:
    MainWindow(sf::RenderWindow& win, BankSystem& bs)
        : window(win), bankSystem(bs),
        userButton("User", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black),
        adminButton("Admin", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black),
        exitButton("Exit", { 100, 50 }, 20, sf::Color::Red, sf::Color::Black),
        background("Accounting.jpg") { // Initialize background with image file path

        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });
        // Position buttons
        userButton.setPosition({ 300, 200 });
        adminButton.setPosition({ 300, 300 });
        exitButton.setPosition({ 10, 10 }); // Position exit button at top-left corner
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (userButton.isMouseOver(window)) {
                        UserLoginWindow userLoginWindow(window, bankSystem,user);
                        userLoginWindow.run();
                    }
                    else if (adminButton.isMouseOver(window)) {
                        AdminLoginWindow adminLoginWindow(window, bankSystem);
                        adminLoginWindow.run();
                    }
                    else if (exitButton.isMouseOver(window)) {
                        window.close(); // Close the window when exit button is clicked
                    }
                }
            }

            window.clear();
            background.drawTo(window); // Draw background image
            userButton.drawTo(window);
            adminButton.drawTo(window);
            exitButton.drawTo(window); // Draw exit button
            window.display();
        }
    }
};

#endif // MAINWINDOW_H
