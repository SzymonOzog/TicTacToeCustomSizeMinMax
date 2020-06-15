#include "gtest/gtest.h"
#include "TicTacToe.h"
TEST(FieldTests, HasWonTest)
{
    int fieldSide = 5;
    Field f(fieldSide);
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
            EXPECT_TRUE(f.hasWon());
           // check veritically
            f.nullify();
            f[0 + i] = p;
            f[5 + i] = p;
            f[10 + i] = p;
            f[15 + i] = p;
            EXPECT_TRUE(f.hasWon());
        }
        //check diagonally
        f.nullify();
        f[0] = p;
        f[6] = p;
        f[12] = p;
        f[18] = p;
        EXPECT_TRUE(f.hasWon());
        //check second diagonal
        f.nullify();
        f[4] = p;
        f[8] = p;
        f[12] = p;
        f[16] = p;
        EXPECT_TRUE(f.hasWon());
    }
}
TEST(FieldsTest, SeparatedFour)
{
    int fieldSide = 5;
    Field f(fieldSide);
    for (auto p : { player::AI, player::Human })
    {
        for (int i = 0; i < fieldSide; i++)
        {
            //check horizontally
            f.nullify();
            f[0 + i * fieldSide] = p;
            f[1 + i * fieldSide] = p;
            f[2 + i * fieldSide] = p;
            f[4 + i * fieldSide] = p;
            EXPECT_TRUE(!f.hasWon());
            // check veritically
            f.nullify();
            f[0 + i] = p;
            f[5 + i] = p;
            f[10 + i] = p;
            f[20 + i] = p;
            EXPECT_TRUE(!f.hasWon());
        }
        //check diagonally
        f.nullify();
        f[0] = p;
        f[6] = p;
        f[12] = p;
        f[24] = p;
        EXPECT_TRUE(!f.hasWon());
        //check second diagonal
        f.nullify();
        f[4] = p;
        f[8] = p;
        f[12] = p;
        f[20] = p;
        EXPECT_TRUE(!f.hasWon());
    }
}
TEST(FieldTests, isDrawTest)
{
    Field field(3);
    field[0] = player::AI;
    field[1] = player::Human;
    field[2] = player::AI;
    field[3] = player::AI;
    field[4] = player::Human;
    field[5] = player::AI;
    field[6] = player::Human;
    field[7] = player::AI;
    field[8] = player::Human;
    EXPECT_TRUE(field.isDraw());
    field[0] = player::None;
    EXPECT_TRUE(!field.isDraw());
}
//Not really a test, just checking how long will the AI think 
//when provided with an empty field
TEST(AITests, EmptyFieldTimeElapse)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(5);
    AI ai(field);
    std::pair<int, int> choice = ai.findBestMove();
}
TEST(AITests, lastNodeIsBestMoveTimeElapse)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(5);
    AI ai(field);
    (*field)[0] = player::AI;
    (*field)[6] = player::Human;
    (*field)[12] = player::Human;
    (*field)[18] = player::Human;
    (*field)[1] = player::AI;

    std::pair<int, int> choice = ai.findBestMove();
}
TEST(AITests, WillWin)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(5);
    AI ai(field);
    (*field)[0] = player::AI;
    (*field)[1] = player::AI;
    (*field)[2] = player::AI;
    (*field)[8] = player::Human;
    (*field)[4] = player::Human;
    (*field)[7] = player::Human;
    (*field)[15] = player::Human;

    std::pair<int, int> choice = ai.findBestMove();
    EXPECT_EQ(choice.second, 3);
}
TEST(AITests, WillBlockPlayerWin)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(4);
    AI ai(field);
    (*field)[0] = player::AI;
    (*field)[1] = player::AI;
    (*field)[9] = player::AI;
    (*field)[4] = player::Human;
    (*field)[5] = player::Human;
    (*field)[6] = player::Human;
    std::pair<int, int> choice = ai.findBestMove();
    EXPECT_EQ(choice.second, 7);
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
        if (f->hasWon())
            std::cout << std::endl;
        EXPECT_TRUE(!f->hasWon());

        bestMove = ai.findBestMove().second;
        if (bestMove == -1)//TIE
        {
            *it = player::None;
            break;
        }
        (*f)[bestMove] = player::AI;
        if (f->hasWon())//AI WIN
        {
            *it = player::None;
            (*f)[bestMove] = player::None;
            break;
        }

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
    playEveryBoard(ai, field);
}
