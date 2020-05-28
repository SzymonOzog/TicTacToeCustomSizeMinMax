#include "gtest/gtest.h"
#include "TicTacToe.h"
const int fieldSide = 4;
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
   // check for AI and Human victory
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
            t.vecField = f;
            EXPECT_EQ(t.hasWon(), true);
           // check veritically
            nullifyVector(f);
            f[0 + i] = p;
            f[5 + i] = p;
            f[10 + i] = p;
            f[15 + i] = p;
            f[20 + i] = p;
            t.vecField = f;
            EXPECT_EQ(t.hasWon(), true);
        }
        //check diagonally
        nullifyVector(f);
        f[0] = p;
        f[6] = p;
        f[12] = p;
        f[18] = p;
        f[24] = p;
        t.vecField = f;
        EXPECT_EQ(t.hasWon(), true);
        //check second diagonal
        nullifyVector(f);
        f[4] = p;
        f[8] = p;
        f[12] = p;
        f[16] = p;
        f[20] = p;
        t.vecField = f;
        EXPECT_EQ(t.hasWon(), true);
    }
}

TEST(TicTacToeTests, isDrawTest)
{
    std::vector<player> field(5 * 5);
    TicTacToe game(5);
    field[0] = player::AI;
    field[4] = player::Human;
    field[6] = player::Human;
    field[8] = player::AI;
    field[10] = player::Human;
    field[12] = player::AI;
    field[16] = player::AI;
    field[18] = player::Human;
    field[22] = player::Human;
    field[24] = player::AI;
    game.vecField = field;
    EXPECT_TRUE(game.isDraw());
    field[24] = player::None;
    game.vecField = field;
    EXPECT_TRUE(!game.isDraw());
}
//Not really a test, just checking how long will the AI think 
//when provided with an empty field
TEST(AITests, EmptyFieldTimeElapse)
{
    nullifyVector(f);
    t.vecField = f;
    std::pair<int, int> choice = t.findBestMove();
}
TEST(AITests, WillWin)
{
    nullifyVector(f);
    f[5] = player::AI;
    f[6] = player::AI;
    f[7] = player::AI;
    f[8] = player::AI;
    t.vecField = f;
    std::pair<int, int> choice = t.findBestMove();
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
    t.vecField = f;
    std::pair<int, int> choice = t.findBestMove();
    EXPECT_EQ(choice.second, 9);
}

void playEveryBoard(TicTacToe g)
{
    int bestMove = 0;
    auto it = g.vecField.begin();
    while (true)
    {
        it = std::find(it, g.vecField.end(), player::None);
        if (it == g.vecField.end())
            break;
        *it = player::Human;
        //if (g.hasWon())
        //    std::cout << std::endl;
        EXPECT_TRUE(!g.hasWon());

        bestMove = g.findBestMove().second;
        if (bestMove == -1)//TIE
            break;

        g.vecField[bestMove] = player::AI;
        if (g.hasWon())//AI WIN
           break;

        playEveryBoard(g);

        *it = player::None;
        g.vecField[bestMove] = player::None;
        if (it == g.vecField.end())
            break;
        it++;
    }
}
TEST(AcceptanceTest, EveryBoard)
{
    TicTacToe g(3);
    playEveryBoard(g);
}
