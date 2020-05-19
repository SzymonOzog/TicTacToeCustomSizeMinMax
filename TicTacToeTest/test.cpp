#include "gtest/gtest.h"
#include "../TicTacToeMinMax/TicTacToe.h"
const int fieldSide = 5;
int TicTacToe::nFieldSide;
TicTacToe t(fieldSide);
std::vector<player> f(fieldSide* fieldSide);

void nullifyVector(std::vector<player> &f)
{
    for (auto& x : f)
    {
        x = player::None;
    }
}
TEST(TicTacToeTests, HasWonTest)
{
    std::vector<player> v = { player::AI, player::Human };
    //check for AI and Human victory
    for (auto p : v)
    {
        for (int i = 0; i < fieldSide; i++)
        {
            //check horizontally
            nullifyVector(f);
            f[0 + i * fieldSide] = p;
            f[1 + i * fieldSide] = p;
            f[2 + i * fieldSide] = p;
            f[3 + i * fieldSide] = p;
            f[4 + i * fieldSide] = p;
            EXPECT_EQ(t.hasWon(f), true);
            //check veritically
            nullifyVector(f);
            f[0 + i] = p;
            f[5 + i] = p;
            f[10 + i] = p;
            f[15 + i] = p;
            f[20 + i] = p;
            EXPECT_EQ(t.hasWon(f), true);
        }
        //check diagonally
        nullifyVector(f);
        f[0] = p;
        f[6] = p;
        f[12] = p;
        f[18] = p;
        f[24] = p;
        EXPECT_EQ(t.hasWon(f), true);
        //check second diagonal
        nullifyVector(f);
        f[4] = p;
        f[8] = p;
        f[12] = p;
        f[16] = p;
        f[20] = p;
        EXPECT_EQ(t.hasWon(f), true);
    }
}

//Not really a test, just checking how long will the AI think 
//when provided with an empty field
TEST(AITests, EmptyFieldTimeElapse)
{
    nullifyVector(f);
    std::pair<int, int> choice = t.findBestMove(f);
}
TEST(AITests, WillWin)
{
    nullifyVector(f);
    f[5] = player::AI;
    f[6] = player::AI;
    f[7] = player::AI;
    f[8] = player::AI;
    std::pair<int, int> choice = t.findBestMove(f);
    EXPECT_EQ(choice.second, 9);
}
TEST(AITests, WillBlockPlayerWin)
{
    nullifyVector(f);
    f[0] = player::AI;
    f[1] = player::AI;
    f[2] = player::AI;
    f[5] = player::Human;
    f[6] = player::Human;
    f[7] = player::Human;
    f[8] = player::Human;
    std::pair<int, int> choice = t.findBestMove(f);
    EXPECT_EQ(choice.second, 9);
}
