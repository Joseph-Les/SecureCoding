#include "gtest/gtest.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <ctime>

// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment {
public:
  ~Environment() override {}

  void SetUp() override {
    srand(time(nullptr));
  }

  void TearDown() override {}
};

// Create our test class to house shared data between tests
class CollectionTest : public ::testing::Test {
protected:
  std::unique_ptr<std::vector<int>> collection;

  void SetUp() override { 
    collection.reset(new std::vector<int>);
  }

  void TearDown() override { 
    collection->clear();
    collection.reset(nullptr);
  }

  void add_entries(int count) {
    // Handle count of 0 without asserting
    if (count <= 0) return;
    for (auto i = 0; i < count; ++i)
      collection->push_back(rand() % 100);
  }
};

// Test that a collection smart pointer is not null when created.
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull) {
  ASSERT_TRUE(collection);
  ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate) {
  ASSERT_TRUE(collection->empty());
  ASSERT_EQ(collection->size(), 0);
}

// Test that always fails (intended to illustrate a failing test)
TEST_F(CollectionTest, AlwaysFail) {
  FAIL();
}

// Test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector) {
  EXPECT_TRUE(collection->empty());
  EXPECT_EQ(collection->size(), 0);

  add_entries(1);

  EXPECT_FALSE(collection->empty());
  EXPECT_EQ(collection->size(), 1);
}

// Test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector) {
  add_entries(5);
  EXPECT_EQ(collection->size(), 5);
}

// Test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize) {
  std::vector<int>::size_type sizes[] = {0, 1, 5, 10};
  for (auto size : sizes) {
    add_entries(size);
    EXPECT_GE(collection->max_size(), collection->size());
    collection->clear();
  }
}

// Test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize) {
  std::vector<int>::size_type sizes[] = {0, 1, 5, 10};
  for (auto size : sizes) {
    add_entries(size);
    EXPECT_GE(collection->capacity(), collection->size());
    collection->clear();
  }
}

// Test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollection) {
  collection->resize(10);
  EXPECT_EQ(collection->size(), 10);
}

// Test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollection) {
  add_entries(10);
  collection->resize(5);
  EXPECT_EQ(collection->size(), 5);
}

// Test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreasesCollectionToZero) {
  add_entries(10);
  collection->resize(0);
  EXPECT_EQ(collection->size(), 0);
}

// Test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) {
  add_entries(10);
  collection->clear();
  EXPECT_TRUE(collection->empty());
}

// Test to verify erase(begin, end) erases the collection
TEST_F(CollectionTest, EraseErasesCollection) {
  add_entries(10);
  collection->erase(collection->begin(), collection->end());
  EXPECT_TRUE(collection->empty());
}

// Test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacity) {
  auto original_capacity = collection->capacity();
  collection->reserve(10);
  EXPECT_GT(collection->capacity(), original_capacity);
  EXPECT_EQ(collection->size(), 0);
}

// Test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
TEST_F(CollectionTest, OutOfRangeException) {
  add_entries(5);
  ASSERT_THROW(collection->at(10), std::out_of_range);
}

// Custom positive test: Verify that a sorted collection remains sorted
TEST_F(CollectionTest, CollectionRemainsSorted) {
  add_entries(10);
  std::sort(collection->begin(), collection->end());
  EXPECT_TRUE(std::is_sorted(collection->begin(), collection->end()));
}

// Custom negative test: Verify that accessing a negative index throws an exception
TEST_F(CollectionTest, AccessingNegativeIndexThrowsException) {
  add_entries(5);
  EXPECT_ANY_THROW(collection->at(-1));
}
