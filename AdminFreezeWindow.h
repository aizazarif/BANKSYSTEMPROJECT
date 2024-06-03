#ifndef USERFREEZEWINDOW_H
#define USERFREEZEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h"

// Forward declaration of AdminDashboardWindow class
class AdminDashboardWindow;

using namespace std;
using namespace sf;

class AdminFreezeWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    AdminDashboardWindow* dashboardWindow; // Pointer to AdminDashboardWindow
    Font font;
    Picture background;
    RectangleShape amountBox;
    Picture freezeIcon;
    Text instructionText;
    Button freezeButton;
    Button backButton; // Back button to return to the admin dashboard
    Text amountText;
    Text amountPlaceholder;
    std::string amount;
    bool amountActive;

public:
    AdminFreezeWindow(RenderWindow& win, BankSystem& bs, User* usr, AdminDashboardWindow* dashWin)
        : window(win), bankSystem(bs), user(usr), dashboardWindow(dashWin),
        background("Accounting.jpg"),
        freezeIcon("lock.jpg"), // Replace with appropriate freeze icon
        freezeButton("Freeze Account", { 160, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        backButton("Back", { 100, 50 }, 20, sf::Color(0, 0, 255), sf::Color::White),
        amountActive(false) {

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
        instructionText.setString("Are you sure you want to freeze your account?");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 150);

        // Set up the freeze button
        freezeButton.setFont(font);
        freezeButton.setPosition({ 400 - freezeButton.getSize().x / 2, 300 });

        // Set up the back button
        backButton.setFont(font);
        backButton.setPosition({ 10, 10 });

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

                    // Check if the amount box was clicked
                    if (amountBox.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        amountActive = true;
                    }
                    else {
                        amountActive = false;
                    }

                    // Check if the back button was clicked
                    if (backButton.buttonClicked(window)) {
                        cout << "Back button clicked\n";
                        // Switch to the admin dashboard window
                        
                        // Call the run method of AdminDashboardWindow
                        return; // Exit the current run method
                    }
                }

                if (amountActive && event.type == Event::TextEntered) {
                    if (event.text.unicode == 8) { // Handle backspace
                        if (!amount.empty()) {
                            amount.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13) { // Handle ASCII input except enter
                        amount += static_cast<char>(event.text.unicode);
                    }
                }
            }

            amountText.setString(amount);

            window.clear();
            background.drawTo(window);
            freezeIcon.drawTo(window);
            window.draw(instructionText);
            freezeButton.drawTo(window);
            backButton.drawTo(window);
            window.draw(amountBox);

            if (amount.empty() && !amountActive) {
                window.draw(amountPlaceholder);
            }
            else {
                window.draw(amountText);
            }

            window.display();
        }
    }
};

#endif // USERFREEZEWINDOW_H
