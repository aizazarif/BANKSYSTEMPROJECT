#pragma once
#ifndef USERDASHBOARDWINDOW_H
#define USERDASHBOARDWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "UserDepositeWindow.h"
#include "UserBalanceWindow.h"
#include "UserWithdrawWindow.h"
#include "UserLoanWindow.h"
#include "UserTransferWindow.h"
using namespace std;
using namespace sf;



class UserDashboardWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    Font font;
    Button viewButton;
    Button depButton;
    Button withdrawButton;
    Button takeloanButton;
    Button repayloanButton;
    Button transferButton;
    Button logoutButton;
    Picture background;
    User* user;

public:
    UserDashboardWindow(sf::RenderWindow& win, BankSystem& bs, User* usr)
        : window(win), bankSystem(bs), user(usr),
        viewButton("View Balance", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        depButton("Deposit", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        withdrawButton("Withdraw", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        takeloanButton("Take Loan", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        repayloanButton("Repay Loan", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        transferButton("Transfer Money", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        background("Accounting.jpg"),
        logoutButton("Logout", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black) {

        // Load the font
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
            throw runtime_error("Failed to load font.");
        }

        // Set font for all buttons
        viewButton.setFont(font);
        depButton.setFont(font);
        withdrawButton.setFont(font);
        takeloanButton.setFont(font);
        repayloanButton.setFont(font);
        transferButton.setFont(font);
        logoutButton.setFont(font);

        // Set positions for buttons
        float startX = (window.getSize().x - 300.f) / 2;
        float startY = (window.getSize().y - 6 * (50.f + 20.f) + 20.f) / 2; // Updated to 6 buttons
        sf::Vector2f buttonPosition(startX, startY);

        viewButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        background.setScale({ 800, 600 });
        background.setPosition({ 0, 0 });

        depButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        withdrawButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        takeloanButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        repayloanButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        transferButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        logoutButton.setPosition(buttonPosition);
    }


    void run() {
        while (window.isOpen()) {
            // Event handling
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                // Check for mouse button press
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Check for button clicks only when the mouse button is pressed
                    if (viewButton.buttonClicked(window)) {
                        // View Balance button action
                        cout << "View Balance button clicked." << endl;
                        UserViewBalanceWindow balanceWindow(window, bankSystem, user);
                        balanceWindow.run();
                    }
                    else if (depButton.buttonClicked(window)) {
                        // Deposit button action
                        cout << "Deposit button clicked." << endl;
                        UserDepositWindow depositWindow(window, bankSystem, user);
                        depositWindow.run(); // Navigate to the UserDepositWindow
                    }
                    else if (withdrawButton.buttonClicked(window)) {
                        // Withdraw button action
                        cout << "Withdraw button clicked." << endl;
                        UserWithdrawWindow withdrawWindow(window, bankSystem, user);
                        withdrawWindow.run();
                    }
                    else if (takeloanButton.buttonClicked(window)) {
                        // Take Loan button action
                        cout << "Take Loan button clicked." << endl;
                        UserLoanWindow loanWindow(window, bankSystem, user);
                        loanWindow.run();
                    }
                    else if (repayloanButton.buttonClicked(window)) {
                        // Repay Loan button action
                        cout << "Repay Loan button clicked." << endl;
                    }
                    else if (transferButton.buttonClicked(window)) {
                        // Transfer Money button action
                        cout << "Transfer Money button clicked." << endl;
                        UserTransferWindow transferWindow(window, bankSystem, user);
                        transferWindow.run();
                    }
                    else if (logoutButton.buttonClicked(window)) {
                        // Logout button action
                        cout << "Logout button clicked." << endl;
                        return;
                    }
                }
            }

            window.clear(sf::Color::Blue); // Clear the window with blue color
            background.drawTo(window);

            // Draw all buttons
            viewButton.drawTo(window);
            depButton.drawTo(window);
            withdrawButton.drawTo(window);
            takeloanButton.drawTo(window);
            repayloanButton.drawTo(window);
            transferButton.drawTo(window);
            logoutButton.drawTo(window);
            window.display();
        }
    }
};

#endif // USERDASHBOARDWINDOW_H
