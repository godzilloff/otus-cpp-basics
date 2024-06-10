#include <iostream>

#include <container_list.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(List, Empty) {
    // Arrange
    ContainerList<int> lst;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(lst.size(), static_cast<size_t>(0));
    ASSERT_TRUE(lst.empty());
}

TEST(List, PushBack) {
    // Arrange
    const size_t count = 10;
    ContainerList<int> lst;

    // Act
    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    // Assert
    ASSERT_EQ(lst.size(), count);
    ASSERT_FALSE(lst.empty());
}

TEST(List, PushFront) {
    // Arrange
    const size_t count = 10;
    ContainerList<int> lst;
    ContainerList<int> lst2;

    // Act
    for (size_t i = 0; i < (count - 1); ++i) {
        lst.push_back(static_cast<int>(i));
    }

    lst.push_front(10);
    // lst.insert(0,10);

    lst2.push_back(static_cast<int>(10));
    for (size_t i = 0; i < (count - 1); ++i) {
        lst2.push_back(static_cast<int>(i));
    }

    // Assert
    ASSERT_EQ(lst.size(), count);
    ASSERT_FALSE(lst.empty());

    ASSERT_EQ(lst, lst2);
    
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration
        ASSERT_EQ(lst[ii], lst2[ii]);
    }
}

TEST(List, InsertCenter) {
    // Arrange
    const size_t count = 7;
    ContainerList<int> lst;
    ContainerList<int> lst2;

    // Act
    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    lst.insert(6, 99);
    lst.insert(4, 98);
    lst.insert(2, 97);

    lst2.push_back(static_cast<int>(0));
    lst2.push_back(static_cast<int>(1));
    lst2.push_back(static_cast<int>(97));
    lst2.push_back(static_cast<int>(2));
    lst2.push_back(static_cast<int>(3));
    lst2.push_back(static_cast<int>(98));
    lst2.push_back(static_cast<int>(4));
    lst2.push_back(static_cast<int>(99));
    lst2.push_back(static_cast<int>(5));
    lst2.push_back(static_cast<int>(6));

    // Assert
    ASSERT_EQ(lst.size(), lst2.size());
    ASSERT_FALSE(lst.empty());

    // ASSERT_EQ(lst, lst2);
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(lst[ii], lst2[ii]);
    }
}

TEST(List, PopBack) {
    // Arrange
    const size_t count = 10;
    ContainerList<int> lst;

    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        lst.pop_back();
    }

    // Assert
    ASSERT_EQ(lst.size(), static_cast<size_t>(0));
    ASSERT_TRUE(lst.empty());
}

TEST(List, EraseFirst) {
    // Arrange
    const size_t count_create = 10;
    const size_t count_delete = 5;
    ContainerList<int> lst;
    ContainerList<int> lst2;

    // Act
    for (size_t i = 0; i < count_create; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    for (size_t i = 0; i < count_delete; ++i) {
        lst.erase(0);
    }

    lst2.push_back(static_cast<int>(5));
    lst2.push_back(static_cast<int>(6));
    lst2.push_back(static_cast<int>(7));
    lst2.push_back(static_cast<int>(8));
    lst2.push_back(static_cast<int>(9));

    // Assert
    ASSERT_EQ(lst.size(), lst2.size());
    ASSERT_FALSE(lst.empty());

    ASSERT_EQ(lst, lst2);
}

TEST(List, EraseCenter) {
    // Arrange
    const size_t count = 10;
    ContainerList<int> lst;
    ContainerList<int> lst2;

    // Act
    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    lst.erase(2);
    lst.erase(3);
    lst.erase(4);

    lst2.push_back(static_cast<int>(0));
    lst2.push_back(static_cast<int>(1));
    lst2.push_back(static_cast<int>(3));
    lst2.push_back(static_cast<int>(5));
    lst2.push_back(static_cast<int>(7));
    lst2.push_back(static_cast<int>(8));
    lst2.push_back(static_cast<int>(9));

    // Assert
    ASSERT_EQ(lst.size(), lst2.size());
    ASSERT_FALSE(lst.empty());

    ASSERT_EQ(lst, lst2);
}

TEST(List, CheckItem) {
    // Arrange
    const size_t count = 42;
    ContainerList<int> lst;

    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    // Act

    // Assert
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(lst[ii], ii);
    }
}

TEST(List, CheckSize) {
    // Arrange
    const size_t count = 42;
    ContainerList<int> lst;

    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    // Act

    // Assert
    ASSERT_EQ(lst.size(), count);
    ASSERT_FALSE(lst.empty());
}

TEST(List, Copy) {
    // Arrange
    const size_t count = 10;
    ContainerList<int> lst;

    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    // Act
    ContainerList<int> lst_for_cpy = ContainerList<int>(lst);

    // Assert
    ASSERT_EQ(lst.size(), lst_for_cpy.size());
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(lst[ii], lst_for_cpy[ii]);
    }
}

TEST(List, Copy2) {
    // Arrange
    const size_t count = 10;
    ContainerList<int> lst;
    ContainerList<int> lst_for_cpy;

    for (size_t i = 0; i < count; ++i) {
        lst.push_back(static_cast<int>(i));
    }

    // Act
    lst_for_cpy = lst;

    // Assert
    ASSERT_EQ(lst.size(), lst_for_cpy.size());
    for (size_t ii = 0; ii < count; ii++) {
        SCOPED_TRACE(ii); // write to the console in which iteration the error
        ASSERT_EQ(lst[ii], lst_for_cpy[ii]);
    }
}

