#include <gtest.h>
#include "iterator.h"

TEST(Iterator, can_create_iterator)
{
    TSingleLinkedList<int> list;
    ASSERT_NO_THROW(list.begin());
}
TEST(Iterator, is_possible_to_prefix_increment)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    auto iter = list.begin();
    ASSERT_NO_THROW(++iter);
}

TEST(Iterator, is_possible_to_postfix_increment)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    auto iter = list.begin();
    ASSERT_NO_THROW(iter++);
}

TEST(Iterator, can_dereference_iterator)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    auto iter = list.begin();
    ASSERT_NO_THROW(*iter);
}

TEST(Iterator, is_dereference_iterator_correct)
{
    TSingleLinkedList<int> list;
    int value = 5;
    list.Add(value);
    auto iter = list.begin();
    EXPECT_EQ(*iter, value);
}

TEST(Iterator, is_right_prefix_increment)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    auto iter = list.begin();
    auto next = ++iter;
    EXPECT_EQ(6, *next);
}

TEST(Iterator, is_right_postfix_increment)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    auto iter = list.begin();
    auto next = iter++;
    EXPECT_EQ(5, *next);
}

TEST(Iterator, is_possible_to_add)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    auto iter = list.begin();
    ASSERT_NO_THROW(iter+3);
}
TEST(Iterator, is_addition_right)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    auto iter = list.begin();
    auto res = iter + 3;
    EXPECT_EQ(*res, 8);
}

TEST(Iterator, can_init_iterator)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    auto iter = list.begin();
    ASSERT_NO_THROW(Iterator<int>(iter));
}

TEST(Iterator, can_set_iterator)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    auto iter = list.begin();
    Iterator<int> new_iter;
    ASSERT_NO_THROW(new_iter = iter);
}

TEST(Iterator, is_set_iterator_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    auto iter = list.begin();
    Iterator<int> new_iter;
    new_iter = iter;
    EXPECT_EQ(*iter, *new_iter);
}

TEST(Iterator, is_init_iterator_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    auto iter = list.begin();
    EXPECT_EQ(*iter, *Iterator<int>(iter));
}