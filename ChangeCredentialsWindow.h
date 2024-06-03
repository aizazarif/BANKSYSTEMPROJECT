#ifndef CHANGECREDENTIALSWINDOW_H
#define CHANGECREDENTIALSWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "bank_system.h"
#include "Picture.h"
#include "AdminDashboardWindow.h" // Ensure this includes the correct header

using namespace std;
using namespace sf;

class ChangeCredentialsWindow {
private:
    RenderWindow& window;
    BankSystem& bankSystem;
    User* user;
    AdminDashboardWindow* dashboardWindow; // Pointer to AdminDashboardWindow
    Font font;
    Picture background;
    RectangleShape oldCredentialsBox;
    RectangleShape newCredentialsBox;
    Picture freezeIcon;
    Text instructionText;
    Button freezeButton;
    Button backButton; // Back button to return to the admin dashboard
    Text oldCredentialsText;
    Text newCredentialsText;
    Text oldCredentialsPlaceholder;
    Text newCredentialsPlaceholder;
    std::string oldCredentials;
    std::string newCredentials;
    bool oldCredentialsActive;
    bool newCredentialsActive;
    bool enteringOldCredentials;

public:
    ChangeCredentialsWindow(RenderWindow& win, BankSystem& bs, User* usr, AdminDashboardWindow* dashWin)
        : window(win), bankSystem(bs), user(usr), dashboardWindow(dashWin),
        background("Accounting.jpg"),
        freezeIcon("lock.jpg"), // Replace with appropriate freeze icon
        freezeButton("Apply Changes", { 160, 50 }, 20, sf::Color(255, 51, 51), sf::Color::White),
        backButton("Back", { 100, 50 }, 20, sf::Color(0, 0, 255), sf::Color::White),
        oldCredentialsActive(false),
        newCredentialsActive(false),
        enteringOldCredentials(true) { // Start by entering old credentials

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
        instructionText.setString("Enter your old credentials:");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(Color::White);
        instructionText.setPosition(400 - instructionText.getGlobalBounds().width / 2, 150);

        // Set up the freeze button
        freezeButton.setFont(font);
        freezeButton.setPosition({ 400 - freezeButton.getSize().x / 2, 400 });

        // Set up the back button
        backButton.setFont(font);
        backButton.setPosition({ 10, 10 });

        // Set up the old credentials box
        oldCredentialsBox.setSize(Vector2f(300, 50));
        oldCredentialsBox.setFillColor(Color(255, 255, 255, 128));
        oldCredentialsBox.setPosition(400 - oldCredentialsBox.getSize().x / 2, 200);

        // Set up the new credentials box
        newCredentialsBox.setSize(Vector2f(300, 50));
        newCredentialsBox.setFillColor(Color(255, 255, 255, 128));
        newCredentialsBox.setPosition(400 - newCredentialsBox.getSize().x / 2, 300);

        // Set up the old credentials text
        oldCredentialsText.setFont(font);
        oldCredentialsText.setCharacterSize(20);
        oldCredentialsText.setFillColor(Color::Black);
        oldCredentialsText.setPosition(400 - oldCredentialsBox.getSize().x / 2 + 10, 210);

        // Set up the new credentials text
        newCredentialsText.setFont(font);
        newCredentialsText.setCharacterSize(20);
        newCredentialsText.setFillColor(Color::Black);
        newCredentialsText.setPosition(400 - newCredentialsBox.getSize().x / 2 + 10, 310);

        // Set up the old credentials placeholder
        oldCredentialsPlaceholder.setFont(font);
        oldCredentialsPlaceholder.setString("Enter old credentials");
        oldCredentialsPlaceholder.setCharacterSize(20);
        oldCredentialsPlaceholder.setFillColor(Color(128, 128, 128));
        oldCredentialsPlaceholder.setPosition(400 - oldCredentialsBox.getSize().x / 2 + 10, 210);

        // Set up the new credentials placeholder
        newCredentialsPlaceholder.setFont(font);
        newCredentialsPlaceholder.setString("Enter new credentials");
        newCredentialsPlaceholder.setCharacterSize(20);
        newCredentialsPlaceholder.setFillColor(Color(128, 128, 128));
        newCredentialsPlaceholder.setPosition(400 - newCredentialsBox.getSize().x / 2 + 10, 310);
    }

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed) {
                    if (freezeButton.buttonClicked(window)) {
                        if (enteringOldCredentials) {
                            cout << "Old Credentials Entered: " << oldCredentials << endl;
                            // Verify old credentials
                            if (user->getPassword() == oldCredentials) {
                                instructionText.setString("Enter your new credentials:");
                                enteringOldCredentials = false;
                            }
                            else {
                                cout << "Old credentials are incorrect.\n";
                                // Optionally display an error message to the user
                            }
                        }
                        else {
                            cout << "New Credentials Entered: " << newCredentials << endl;
                            // Change credentials using the bank system
                            if (bankSystem.changeCredentials(user->getUsername(), newCredentials)) {
                                cout << "Credentials changed successfully!\n";
                                // Optionally close the window or go back to the dashboard
                                return; // Exit the current run method
                            }
                            else {
                                cout << "Failed to change credentials!\n";
                                // Optionally display an error message to the user
                            }
                        }
                    }

                    // Check if the old credentials box was clicked
                    if (oldCredentialsBox.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        oldCredentialsActive = true;
                        newCredentialsActive = false; // Deactivate new credentials box
                    }
                    else {
                        oldCredentialsActive = false;
                    }

                    // Check if the new credentials box was clicked
                    if (newCredentialsBox.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        newCredentialsActive = true;
                        oldCredentialsActive = false; // Deactivate old credentials box
                    }
                    else {
                        newCredentialsActive = false;
                    }

                    // Check if the back button was clicked
                    if (backButton.buttonClicked(window)) {
                        cout << "Back button clicked\n";
                        // Switch to the admin dashboard window

                        // Call the run method of AdminDashboardWindow

                        return; // Exit the current run method
                    }
                }

                // Handle text input events for old credentials
                if (oldCredentialsActive && event.type == Event::TextEntered) {
                    if (event.text.unicode == 8) { // Handle backspace
                        if (!oldCredentials.empty()) {
                            oldCredentials.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13) { // Handle ASCII input except enter
                        oldCredentials += static_cast<char>(event.text.unicode);
                    }
                }

                // Update old credentials text
                oldCredentialsText.setString(oldCredentials);

                // Handle text input events for new credentials
                if (newCredentialsActive && event.type == Event::TextEntered) {
                    if (event.text.unicode == 8) { // Handle backspace
                        if (!newCredentials.empty()) {
                            newCredentials.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13) { // Handle ASCII input except enter
                        newCredentials += static_cast<char>(event.text.unicode);
                    }
                }

                // Update new credentials text
                newCredentialsText.setString(newCredentials);
            }

            window.clear();
            background.drawTo(window);
            freezeIcon.drawTo(window);
            window.draw(instructionText);
            freezeButton.drawTo(window);
            backButton.drawTo(window);
            window.draw(oldCredentialsBox);
            window.draw(newCredentialsBox);

            if (oldCredentials.empty() && !oldCredentialsActive) {
                window.draw(oldCredentialsPlaceholder);
            }
            else {
                window.draw(oldCredentialsText);
            }

            if (newCredentials.empty() && !newCredentialsActive) {
                window.draw(newCredentialsPlaceholder);
            }
            else {
                window.draw(newCredentialsText);
                Text(newCredentialsText);
            }

            window.display();
        }
    }
};

#endif // CHANGECREDENTIALSWINDOW_H

