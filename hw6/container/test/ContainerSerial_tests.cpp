#include <iostream>

#include <container_serial.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Serial, Empty) {
    // Arrange
    ContainerSerial<int> vec;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(vec.size(), static_cast<size_t>(0));
    ASSERT_TRUE(vec.empty());
}

TEST(Serial, PushBack) {
    // Arrange
    const size_t count = 10;
    ContainerSerial<int> vec;

    // Act
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Assert
    ASSERT_EQ(vec.size(), count);
    ASSERT_FALSE(vec.empty());
}

TEST(Serial, PushFront) {
    // Arrange
    const size_t count = 10;
    ContainerSerial<int> vec;
    ContainerSerial<int> vec2;

    // Act
    for (size_t i = 0; i < (count - 1); ++i) {
        vec.push_back(static_cast<int>(i));
    }

    vec.push_front(10);
    // vec.insert(0,10);

    vec2.push_back(static_cast<int>(10));
    for (size_t i = 0; i < (count - 1); ++i) {
        vec2.push_back(static_cast<int>(i));
    }

    // Assert
    ASSERT_EQ(vec.size(), count);
    ASSERT_FALSE(vec.empty());

    ASSERT_EQ(vec, vec2);
    // for (size_t ii = 0; ii < count; ii++) {
    //     SCOPED_TRACE(ii); // write to the console in which iteration the
    //     error occurred ASSERT_EQ(vec[ii], vec2[ii]);
    // }
}

TEST(Serial, InsertCenter) {
    // Arrange
    const size_t count = 7;
    ContainerSerial<int> vec;
    ContainerSerial<int> vec2;

    // Act
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    vec.insert(6, 99);
    vec.insert(4, 98);
    vec.insert(2, 97);

    vec2.push_back(static_cast<int>(0));
    vec2.push_back(static_cast<int>(1));
    vec2.push_back(static_cast<int>(97));
    vec2.push_back(static_cast<int>(2));
    vec2.push_back(static_cast<int>(3));
    vec2.push_back(static_cast<int>(98));
    vec2.push_back(static_cast<int>(4));
    vec2.push_back(static_cast<int>(99));
    vec2.push_back(static_cast<int>(5));
    vec2.push_back(static_cast<int>(6));

    // Assert
    ASSERT_EQ(vec.size(), vec2.size());
    ASSERT_FALSE(vec.empty());

    // ASSERT_EQ(vec, vec2);
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(vec[ii], vec2[ii]);
    }
}

TEST(Serial, PopBack) {
    // Arrange
    const size_t count = 10;
    ContainerSerial<int> vec;

    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        vec.pop_back();
    }

    // Assert
    ASSERT_EQ(vec.size(), static_cast<size_t>(0));
    ASSERT_TRUE(vec.empty());
}

TEST(Serial, EraseFirst) {
    // Arrange
    const size_t count_create = 10;
    const size_t count_delete = 5;
    ContainerSerial<int> vec;
    ContainerSerial<int> vec2;

    // Act
    for (size_t i = 0; i < count_create; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    for (size_t i = 0; i < count_delete; ++i) {
        vec.erase(0);
    }

    vec2.push_back(static_cast<int>(5));
    vec2.push_back(static_cast<int>(6));
    vec2.push_back(static_cast<int>(7));
    vec2.push_back(static_cast<int>(8));
    vec2.push_back(static_cast<int>(9));

    // Assert
    ASSERT_EQ(vec.size(), vec2.size());
    ASSERT_FALSE(vec.empty());

    ASSERT_EQ(vec, vec2);
}

TEST(Serial, EraseCenter) {
    // Arrange
    const size_t count = 10;
    ContainerSerial<int> vec;
    ContainerSerial<int> vec2;

    // Act
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    vec.erase(2);
    vec.erase(3);
    vec.erase(4);

    vec2.push_back(static_cast<int>(0));
    vec2.push_back(static_cast<int>(1));
    vec2.push_back(static_cast<int>(3));
    vec2.push_back(static_cast<int>(5));
    vec2.push_back(static_cast<int>(7));
    vec2.push_back(static_cast<int>(8));
    vec2.push_back(static_cast<int>(9));

    // Assert
    ASSERT_EQ(vec.size(), vec2.size());
    ASSERT_FALSE(vec.empty());

    ASSERT_EQ(vec, vec2);
}

TEST(Serial, CheckItem) {
    // Arrange
    const size_t count = 42;
    ContainerSerial<int> vec;

    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Act

    // Assert
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(vec[ii], ii);
    }
}

TEST(Serial, CheckSize) {
    // Arrange
    const size_t count = 42;
    ContainerSerial<int> vec;

    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Act

    // Assert
    ASSERT_EQ(vec.size(), count);
    ASSERT_FALSE(vec.empty());
}

TEST(Serial, Copy) {
    // Arrange
    const size_t count = 10;
    ContainerSerial<int> vec;

    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Act
    ContainerSerial<int> vec_for_cpy = ContainerSerial<int>(vec);

    // Assert
    ASSERT_EQ(vec.size(), vec_for_cpy.size());
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(vec[ii], vec_for_cpy[ii]);
    }
}

TEST(Serial, Copy2) {
    // Arrange
    const size_t count = 10;
    ContainerSerial<int> vec;
    ContainerSerial<int> vec_for_cpy;

    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Act
    vec_for_cpy = vec;

    // Assert
    ASSERT_EQ(vec.size(), vec_for_cpy.size());
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(vec[ii], vec_for_cpy[ii]);
    }
}
