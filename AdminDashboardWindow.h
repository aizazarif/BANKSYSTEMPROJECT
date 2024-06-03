#pragma once
#ifndef ADMINDASHBOARDWINDOW_H
#define ADMINDASHBOARDWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "AdminFreezeWindow.h"
#include "AdminViewWindow.h"
#include "AdminUnFreezeWindow.h"
#include "AdminDeleteWindow.h"
#include "ChangeCredentialsWindow.h"
using namespace std;
using namespace sf;

class AdminDashboardWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    Admin* admin;
    Font font;
    AdminDashboardWindow* adw;
    Button viewacc;
    Button depButton;
    Button Freeze;
    Button Unfreeze;
    Button Delete;
    Button credentials;
    Button logoutButton;
    User* user;

public:
    AdminDashboardWindow(sf::RenderWindow& win, BankSystem& bs)
        : window(win), bankSystem(bs),
        viewacc("View Accoutn Details", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        Freeze("Freeze", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        Unfreeze("Unfreeze", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        Delete("Delete", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        credentials("Change Credentials", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black),
        logoutButton("Logout", sf::Vector2f(300.f, 50.f), 16, sf::Color(220, 220, 220), sf::Color::Black) {

        // Load the font
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
            throw runtime_error("Failed to load font.");
        }

        // Set font for all buttons
        viewacc.setFont(font);
        Freeze.setFont(font);
        Unfreeze.setFont(font);
        Delete.setFont(font);
        credentials.setFont(font);
        logoutButton.setFont(font);
       

        // Set positions for buttons
        float startX = (window.getSize().x - 300.f) / 2;
        float startY = (window.getSize().y - 6 * (50.f + 20.f) + 20.f) / 2; // Updated to 6 buttons
        sf::Vector2f buttonPosition(startX, startY);

        viewacc.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        Freeze.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        Unfreeze.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        Delete.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        credentials.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        logoutButton.setPosition(buttonPosition);
        buttonPosition.y += 50.f + 20.f;

        
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
                    if (viewacc.buttonClicked(window)) {
                        // View Balance button action
                        cout << "Account Details" << endl;
                        AdminViewWindow viewWindow(window, bankSystem, user);
                        viewWindow.run();
                    }
                    else if (Freeze.buttonClicked(window)) {
                        // Deposit button action
                        cout << "Freeze" << endl;
                        AdminFreezeWindow freezeWindow(window, bankSystem, user,adw);
                        freezeWindow.run(); // Navigate to the UserDepositWindow
                    }
                    else if (Unfreeze.buttonClicked(window)) {
                        // Withdraw button action
                        cout << "Unfreeze" << endl;
                        AdminUnFreezeWindow unfreezeWindow(window, bankSystem);
                        unfreezeWindow.run();;
                    }
                    else if (Delete.buttonClicked(window)) {
                        // Take Loan button action
                        cout << "Delete" << endl;
                        AdminDeleteWindow deleteWindow(window, bankSystem, user, adw);
                        deleteWindow.run();
                    }
                    else if (credentials.buttonClicked(window)) {
                        // Repay Loan button action
                        cout << "Change Credentials" << endl;
                        ChangeCredentialsWindow changeWindow(window, bankSystem, user, adw);
                        changeWindow.run();
                    }
                    else if (logoutButton.buttonClicked(window)) {
                        // Transfer Money button action
                        cout << "Logout" << endl;

                       
                    }
                   
                }
            }

            window.clear(sf::Color::Blue); // Clear the window with blue color

            // Draw all buttons
            viewacc.drawTo(window);
            Freeze.drawTo(window);
            Unfreeze.drawTo(window);
            Delete.drawTo(window);
            credentials.drawTo(window);
            logoutButton.drawTo(window);
            window.display();
        }
    }
};

#endif 
