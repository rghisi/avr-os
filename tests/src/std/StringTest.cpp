//
// Created by ghisi on 04.09.22.
//

#include <gtest/gtest.h>
#include "../../../avr/src/std/String.h"

TEST(String, ShouldReturnIndexOfFirstOccurence_WhenProvidedCharExistsInString) {
    auto string = "abcde";

    auto indexOfC = String::findFirst('c', string);
    ASSERT_EQ(2, indexOfC);
}

TEST(String, ShouldReturnMinusOne_WhenProvidedCharDoesNotExistInString) {
    auto string = "abcde";

    auto indexOfC = String::findFirst('y', string);
    ASSERT_EQ(-1, indexOfC);
}

TEST(String, ShouldReturnMinusOne_WhenProvidedStringIsEmpty) {
    auto string = "";

    auto indexOfC = String::findFirst('y', string);
    ASSERT_EQ(-1, indexOfC);
}

TEST(String, ShouldReturnMinusOne_WhenProvidedStringIsNullptr) {
    auto string = nullptr;

    auto indexOfC = String::findFirst('y', string);
    ASSERT_EQ(-1, indexOfC);
}

TEST(String, ShouldReturnIndexOfFirstOccurence_WhenProvidedCharExistsInStringNonConst) {
    auto string = new char[6] {'a', 'b', 'c', 'd', 'e', 0};

    auto indexOfC = String::findFirst('c', string);
    ASSERT_EQ(2, indexOfC);
}