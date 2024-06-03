// main.cpp

#include <SFML/Graphics.hpp>
#include "bank_system.h"
#include "MainWindow.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600),"Bank Management System");

    BankSystem bankSystem;
    bankSystem.loadUsersFromFile();



    MainWindow mainWindow(window, bankSystem);
    mainWindow.run();

    return 0;
}
