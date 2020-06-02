#include "gtest/gtest.h"
#include "TicTacToe.h"
int TicTacToe::nFieldSide;
TEST(FieldTests, HasWonTest)
{
    int fieldSide = 5;
    Field f(fieldSide * fieldSide);
    for (auto p : { player::AI, player::Human })
    {
        for (int i = 0; i < fieldSide; i++)
        {
            //check horizontally
            f.nullify();
            f.set(0 + i * fieldSide ,p);
            f.set(1 + i * fieldSide ,p);
            f.set(2 + i * fieldSide ,p);
            f.set(3 + i * fieldSide ,p);
            f.set(4 + i * fieldSide ,p);
            EXPECT_EQ(f.getState(), field::Won);
           // check veritically
            f.nullify();
            f.set(0 + i, p);
            f.set(5 + i, p);
            f.set(10 + i, p);
            f.set(15 + i, p);
            f.set(20 + i, p);
            EXPECT_EQ(f.getState(), field::Won);
        }
        //check diagonally
        f.nullify();
        f.set(0, p);
        f.set(6, p);
        f.set(12, p);
        f.set(18, p);
        f.set(24, p);
        EXPECT_EQ(f.getState(), field::Won);
        //check second diagonal
        f.nullify();
        f.set(4, p);
        f.set(8, p);
        f.set(12, p);
        f.set(16, p);
        f.set(20, p);
        EXPECT_EQ(f.getState(), field::Won);
    }
}

TEST(FieldTests, isDrawTest)
{
    Field field(5 * 5);
    field.set(0, player::AI);
    field.set(4, player::Human);
    field.set(6, player::Human);
    field.set(8, player::AI);
    field.set(10, player::Human);
    field.set(12, player::AI);
    field.set(16, player::AI);
    field.set(18, player::Human);
    field.set(22, player::Human);
    field.set(24, player::AI);
    EXPECT_EQ(field.getState(), field::Draw);
    field.set(24, player::None);
    EXPECT_EQ(field.getState(), field::None);
}

TEST(FieldTest, fullFieldWin)
{
    Field field(3 * 3);
    field.set(1, player::AI);
    field.set(2, player::AI);
    field.set(3, player::AI);
    field.set(4, player::Human);
    field.set(5, player::Human);
    field.set(6, player::AI);
    field.set(7, player::Human);
    field.set(8, player::AI);
    field.set(9, player::Human);
    EXPECT_EQ(field.getState(), field::Won);
}
//Not really a test, just checking how long will the AI think 
//when provided with an empty field
TEST(AITests, EmptyFieldTimeElapse)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(4 * 4);
    AI ai(field);
    std::pair<int, int> choice = ai.findBestMove();
}
TEST(AITests, WillWin)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(4 * 4);
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
    std::shared_ptr<Field> field = std::make_shared<Field>(4 * 4);
    AI ai(field);
    (*field)[0] = player::AI;
    (*field)[1] = player::AI;
    (*field)[9] = player::AI;
    (*field)[4] = player::Human;
    (*field)[5] = player::Human;
    (*field)[6] = player::Human;
    (*field)[8] = player::Human;
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
    std::shared_ptr<Field> field = std::make_shared<Field>(3 * 3);
    AI ai(field);
    playEveryBoard(ai, field);
}
