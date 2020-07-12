#include "gtest/gtest.h"
#include "TicTacToe.h"
#include "TranspositionTable.h"
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
TEST(FieldTests, SeparatedFour)
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
    (*field)[field->size() / 2] = player::Human;
    int choice = ai.findBestMove();
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

    int choice = ai.findBestMove();
    EXPECT_EQ(choice, 24);
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

    int choice = ai.findBestMove();
    EXPECT_EQ(choice, 3);
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
    int choice = ai.findBestMove();
    EXPECT_EQ(choice, 7);
}

TEST(TranspositionTableTest, RecalculateHash)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(5);
    TranspositionTable ttable(field);
    (*field)[0] = player::AI;
    (*field)[2] = player::AI;
    (*field)[3] = player::Human;
    (*field)[6] = player::Human;
    auto hash = ttable.recalculateHash();
    (*field)[7] = player::Human;
    EXPECT_EQ(ttable.calculateHash(hash, 7), ttable.recalculateHash());
}

TEST(TranspositionTableTest, EntryOperator)
{
    std::pair <int, int> scoreMove = { 0,0 };
    unsigned long long hash = 1;
    Entry e1 = Entry(scoreMove, hash, 0);
    Entry e2 = Entry(scoreMove, hash, 0);
    EXPECT_TRUE(e1 == e2);
    e2.hash = 2;
    EXPECT_TRUE(e1 != e2);
}

TEST(TranspositionTableTest, PlaceEntry)
{
    std::shared_ptr<Field> field = std::make_shared<Field>(3);
    TranspositionTable ttable(field);
    (*field)[0] = player::Human;
    int hash = ttable.recalculateHash();
    ttable.placeEntry(hash, { 1,1 }, 0);
    Entry e = Entry({ 1,1 }, hash, 0);
    EXPECT_TRUE(ttable[hash] == e);
    EXPECT_TRUE(ttable[hash] != ttable.nullEntry);
}
