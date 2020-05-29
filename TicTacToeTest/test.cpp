#include "gtest/gtest.h"
#include "TicTacToe.h"
const int fieldSide = 4;
int TicTacToe::nFieldSide;
TicTacToe t(fieldSide);
std::vector<player> f(fieldSide* fieldSide);

TEST(FieldTests, HasWonTest)
{
    Field f(5 * 5);
    for (auto p : { player::AI, player::Human })
    {
        for (int i = 0; i < fieldSide; i++)
        {
            //check horizontally
            f.nullify();
            f[0 + i * fieldSide] = p;
            f[1 + i * fieldSide] = p;
            f[2 + i * fieldSide] = p;
            f[3 + i * fieldSide] = p;
            f[4 + i * fieldSide] = p;
            EXPECT_EQ(f.hasWon(), true);
           // check veritically
            f.nullify();
            f[0 + i] = p;
            f[5 + i] = p;
            f[10 + i] = p;
            f[15 + i] = p;
            f[20 + i] = p;
            EXPECT_EQ(f.hasWon(), true);
        }
        //check diagonally
        f.nullify();
        f[0] = p;
        f[6] = p;
        f[12] = p;
        f[18] = p;
        f[24] = p;
        EXPECT_EQ(f.hasWon(), true);
        //check second diagonal
        f.nullify();
        f[4] = p;
        f[8] = p;
        f[12] = p;
        f[16] = p;
        f[20] = p;
        EXPECT_EQ(f.hasWon(), true);
    }
}

TEST(FieldTests, isDrawTest)
{
    Field field(5 * 5);
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
    EXPECT_TRUE(field.isDraw());
    field[24] = player::None;
    EXPECT_TRUE(!field.isDraw());
}
//Not really a test, just checking how long will the AI think 
//when provided with an empty field
TEST(AITests, EmptyFieldTimeElapse)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(4);
    AI ai(field);
    std::pair<int, int> choice = ai.findBestMove();
}
TEST(AITests, WillWin)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(4);
    AI ai(field);
    (*field)[5] = player::AI;
    (*field)[6] = player::AI;
    (*field)[7] = player::AI;
    (*field)[8] = player::AI;
    std::pair<int, int> choice = ai.findBestMove();
    EXPECT_EQ(choice.second, 9);
}
TEST(AITests, WillBlockPlayerWin)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(4);
    AI ai(field);
    (*field)[0] = player::AI;
    (*field)[1] = player::AI;
    (*field)[2] = player::AI;
    (*field)[5] = player::Human;
    (*field)[6] = player::Human;
    (*field)[7] = player::Human;
    (*field)[8] = player::Human;
    std::pair<int, int> choice = ai.findBestMove();
    EXPECT_EQ(choice.second, 9);
}

void playEveryBoard(AI ai, std::shared_ptr<Field> f)
{
    int bestMove = 0;
    auto it = f->begin();
    while (true)
    {
        it = std::find(it, f->end(), player::None);
        if (it == f->end())
            break;
        *it = player::Human;
        //if (g.hasWon())
        //    std::cout << std::endl;
        EXPECT_TRUE(!g.hasWon());

        bestMove = ai.findBestMove().second;
        if (bestMove == -1)//TIE
            break;

        (*f)[bestMove] = player::AI;
        if (f->hasWon())//AI WIN
           break;

        playEveryBoard(ai, f);

        *it = player::None;
        (*f)[bestMove] = player::None;
        if (it == f->end())
            break;
        it++;
    }
}
TEST(AcceptanceTest, EveryBoard)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(3);
    AI ai(field);
    playEveryBoard(g);
}
