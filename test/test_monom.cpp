#include <gtest.h>
#include "monom.h"

TEST(Monom, can_create_monom)
{
    std::vector<int> degrees = {0, 0, 0};
    ASSERT_NO_THROW(Monom<int> (0, degrees));
}

TEST(Monom, can_sum_monoms)
{
    std::vector<int> degrees = {0, 0, 0};
    
    Monom<int> monom1 (0, degrees);
    Monom<int> monom2 (5, degrees);
    ASSERT_NO_THROW(monom1 + monom2);
}

TEST(Monom, is_sum_monoms_correct)
{
    std::vector<int> degrees = {0, 0, 0};
    
    Monom<int> monom1 (0, degrees);
    Monom<int> monom2 (5, degrees);
    Monom<int> result = monom1 + monom2;
    Monom<int> expected (5, degrees);
    EXPECT_EQ(expected, result);
}

TEST(Monom, can_sub_monoms)
{
    std::vector<int> degrees = {0, 0, 0};
    
    Monom<int> monom1 (0, degrees);
    Monom<int> monom2 (5, degrees);
    ASSERT_NO_THROW(monom1 - monom2);
}

TEST(Monom, is_sub_monoms_correct)
{
    std::vector<int> degrees = {0, 0, 0};
    
    Monom<int> monom1 (0, degrees);
    Monom<int> monom2 (5, degrees);
    Monom<int> result = monom1 - monom2;
    Monom<int> expected (-5, degrees);
    EXPECT_EQ(expected, result);
}

TEST(Monom, can_multiple_monoms)
{
    std::vector<int> degrees = {0, 0, 0};
    
    Monom<int> monom1 (0, degrees);
    Monom<int> monom2 (5, degrees);
    ASSERT_NO_THROW(monom1 * monom2);
}

TEST(Monom, is_multiple_monoms_correct)
{
    std::vector<int> degrees = {0, 0, 0};
    
    Monom<int> monom1 (0, degrees);
    Monom<int> monom2 (5, degrees);
    Monom<int> result = monom1 * monom2;
    Monom<int> expected (0, degrees);
    EXPECT_EQ(expected, result);
}