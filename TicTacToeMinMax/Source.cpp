#include "TicTacToe.h"
#include <iostream>
#include <regex>

int TicTacToe::nFieldSide;
const std::string rules = R"(
Welcome to the TicTacToe game where you will be competing against AI
1. You play as X
2. The AI plays as O
3. You have the first move
4. To place X just click on the field
5. You choose the board size.
6. To leave press 'Esc'
To start the game type in the board size and press 'enter'.  
)";
int main()
{
    int size;
    std::cout << rules;

    std::string str;
    std::regex regex_int("-?[0-9]");
    while (true)
    {
        std::cin >> str;
        if (regex_match(str, regex_int))
        {
            if (std::stoi(str) > 6)
                std::cout << "MinMax algorithm isn`t efficient enough \n to play on a field this big" << std::endl;
            else if (stoi(str) <= 0)
                std::cout << "Input must be greater than 0" << std::endl;
            else if (stoi(str) == 1 || stoi(str) == 2)
                std::cout << "Wow you`re a tough guy that likes challenges arent you?\nCome on I`m not gonna let you do that" << std::endl;
            else
            {
                size = std::stoi(str);
                break;
            }
        }
        else
            std::cout << "Invalid input, try again" << std::endl;
    }

    TicTacToe game(size);
    game.start();
}