#include <gtest.h>
#include "tsinglelinkedlist.h"

TEST(TSingleLinkedList, can_create_list)
{
    ASSERT_NO_THROW(TSingleLinkedList <int> list);
}

TEST(TSingleLinkedList, can_copy_list)
{
    TSingleLinkedList <int> list;
    list.Add(1);
    list.Add(2);
    list.Add(3);
    list.Add(4);
    ASSERT_NO_THROW(TSingleLinkedList <int> n_list(list));
}

TEST(TSingleLinkedList, can_add_element)
{
    TSingleLinkedList<int> list;
    ASSERT_NO_THROW(list.Add(5));
}

TEST(TSingleLinkedList, can_add_elements)
{
    TSingleLinkedList<int> list;
    ASSERT_NO_THROW(list.Add(5));
    ASSERT_NO_THROW(list.Add(6));
    ASSERT_NO_THROW(list.Add(7));
}

TEST(TSingleLinkedList, is_added_element_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    auto iter = list.begin();
}

TEST(TSingleLinkedList, can_insert_element)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    ASSERT_NO_THROW(list.Insert(list.begin() + 1, 3));
}

TEST(TSingleLinkedList, is_inserted_element_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    list.Insert(list.begin() + 1, 3);
    EXPECT_EQ(*(list.begin()+1), 3);
}

TEST(TSingleLinkedList, can_remove_first_element_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    auto iter = list.begin();
    ASSERT_NO_THROW(list.Remove(iter));
}

TEST(TSingleLinkedList, can_remove_middle_element_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    auto iter = list.begin() + 2;
    ASSERT_NO_THROW(list.Remove(iter));
}

TEST(TSingleLinkedList, can_remove_last_element_correct)
{
    TSingleLinkedList<int> list;
    list.Add(5);
    list.Add(6);
    list.Add(7);
    list.Add(8);
    list.Add(9);
    auto iter = list.tail();
    ASSERT_NO_THROW(list.Remove(iter));
}