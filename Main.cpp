#include <iostream>
#include <conio.h>
#include "Player.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "\tRo1zer present\t\n"
        << "\t---My player---\t\n";
    system("pause");
    system("cls");
    Player obj;
    while(true)
    {
        system("cls");
        std::cout << "   _(Menu)_\n";
        std::cout << "(0) Get all music\n"
            << "(1) Update list\n"
            << "(2) Play\n"
            << "(Esc) Exit\n";
        char keyPressed;
        keyPressed = _getch();
        if (keyPressed == 27) {
            return 0;
        }
        else if (keyPressed == 48) {
            system("cls");
            obj.getAll();
        }
        else if (keyPressed == 49) {
            system("cls");
            obj.scanAndAdd();
        }
        else if (keyPressed == 50) {
            int num;
            system("cls");
            obj.getAll();
            std::cout << "Enter your music: ";
            std::cin >> num;
            obj.play(num);
        }
        
    }
}
