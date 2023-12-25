#include <gtest/gtest.h>

#include <list>
#include <set>

#include "./s21_containers.h"

// LIST

template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = true;
  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(ListTest, CompareLists) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  EXPECT_TRUE(compare_lists(my_list, std_list));
  std_list.push_back(6);
  EXPECT_FALSE(compare_lists(my_list, std_list));
  std_list.pop_back();
  my_list.push_front(0);
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, DefaultConstructor) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, SizeConstructor) {
  s21::list<int> my_list(1000000);
  std::list<int> std_list(1000000);
  EXPECT_EQ(my_list.size(), 1000000);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, SizeConstructorThrow) {
  try {
    s21::list<int> my_list(-1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Limit of the container is exceeded"));
  }
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> my_list{1, 2, 3, 7, 9};
  std::list<int> std_list{1, 2, 3, 7, 9};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, InitializerListConstructor_2) {
  std::initializer_list<int> b;
  s21::list<int> my_list{b};
  std::list<int> std_list{b};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, CopyConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, MoveAssignmentOperatorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, Front) {
  s21::list<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListTest, Back) {
  s21::list<int> my_list{1, 2, 3, 4, 99};
  std::list<int> std_list{1, 2, 3, 4, 99};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListTest, Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.empty(), std_list.empty());
  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListTest, Size) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, SizeEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, MaxSize) {
  s21::list<size_t> my_list_empty;
  std::list<size_t> std_list_empty;
  EXPECT_EQ(my_list_empty.max_size(), std_list_empty.max_size());
}

TEST(ListTest, Clear) {
  s21::list<int> my_list{1, 2, 3, 4};
  my_list.clear();
  std::list<int> std_list{1, 2, 5, 4, 3};
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, ClearEmpty) {
  s21::list<int> my_list;
  my_list.clear();
  std::list<int> std_list;
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_back(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_back();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_front(0);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Swap) {
  s21::list<int> my_list1{1, 2, 3, 4, 5};
  s21::list<int> my_list2{6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 2, 3, 4, 5};
  std::list<int> std_list2{6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, Swap_2) {
  s21::list<int> my_list1{1, 5, 8, 100};
  s21::list<int> my_list2;
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 5, 8, 100};
  std::list<int> std_list2;
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, begin_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_2) {
  s21::list<int> my_list1(4);

  std::list<int> std_list2(4);
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_3_throw) {
  s21::list<int> my_list1;
  std::list<int> std_list2;

  EXPECT_EQ(*my_list1.begin(), 0);
}

TEST(ListTest, end_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, end_2) {
  s21::list<int> my_list1(4);

  std::list<int> std_list2(4);
  EXPECT_EQ(*my_list1.end(), *std_list2.end());
}

TEST(ListTest, end_3) {
  s21::list<int> my_list1;

  std::list<int> std_list2;
  EXPECT_EQ(*my_list1.end(), *std_list2.end());
}

TEST(ListTest, Merge_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_3) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_5) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_6) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Reverse_1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_1) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Splice_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_2) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_3) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_3) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_4) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_5) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_6) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(my_list1.begin());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.begin());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_2_throw) {
  s21::list<int> my_list1{1, 9999, 20000};

  EXPECT_THROW(my_list1.erase(my_list1.end()), std::invalid_argument);
}

TEST(ListTest, Erase_3) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(--my_list1.end());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.end().operator--());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_4_throw) {
  s21::list<int> my_list1;

  EXPECT_THROW(my_list1.erase(my_list1.end()--), std::invalid_argument);
}

TEST(ListTest, Erase_5) {
  s21::list<int> my_list1(5);
  my_list1.erase(--my_list1.end());

  std::list<int> std_list1(5);
  std_list1.erase(std_list1.end().operator--());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

// SET

TEST(set, constructor) {
  s21::set<int> test;
  EXPECT_TRUE(test.empty());
}

TEST(set, init) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it;
  s21::set<int>::iterator it2 = test.begin();
  for (it = test2.begin(); it != test2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, copy_constructor) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2(test);
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2(set);
  std::set<int>::iterator it;
  s21::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, move_constructor) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2(std::move(test));
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2(std::move(set));
  std::set<int>::iterator it;
  s21::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test.size(), set.size());
}

TEST(set, move_assignment) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {7, 4, 8, 0, -1};
  test2 = std::move(test);
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1};
  set2 = std::move(set);
  std::set<int>::iterator it;
  s21::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test.size(), set.size());
}

TEST(set, begin) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int>::iterator it;
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2;
  it = test.begin();
  it2 = test2.begin();
  ASSERT_EQ(*it, *it2);
  it++;
  it2++;
  ASSERT_EQ(*it, *it2);
}

TEST(set, minus) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int>::iterator it;
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2;
  // как-то нкжно это пофиксить наверно
  it = test.begin();
  it2 = test2.begin();
  it++;
  it2++;
  it--;
  it2--;
  ASSERT_EQ(*it, *it2);
}

TEST(set, find) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int>::iterator it;
  it = test.find(45);
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2;
  it2 = test2.find(45);
  ASSERT_EQ(*it, *it2);
}

TEST(set, contains) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  bool check = test.contains(60);
  ASSERT_FALSE(check);
}

TEST(set, insert) {
  std::set<int> test = {52, 54, 45, 48, 53};
  std::pair<std::set<int>::iterator, bool> check = test.insert(45);
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  std::pair<s21::set<int>::iterator, bool> check2 = test2.insert(45);
  ASSERT_EQ(*check.first, *check2.first);
  ASSERT_EQ(check.second, check2.second);
}

TEST(set, insert2) {
  std::set<int> test = {52, 54, 45, 48, 53};
  std::pair<std::set<int>::iterator, bool> check = test.insert(0);
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  std::pair<s21::set<int>::iterator, bool> check2 = test2.insert(0);
  ASSERT_EQ(*check.first, *check2.first);
  ASSERT_EQ(check.second, check2.second);
}

TEST(set, clear) {
  std::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  test.clear();
  test2.clear();
  ASSERT_EQ(test.size(), test2.size());
}

TEST(set, size) {
  std::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  ASSERT_EQ(test.size(), test2.size());
}

TEST(set, empty) {
  s21::set<int> test2;
  ASSERT_TRUE(test2.empty());
  test2.insert(45);
  ASSERT_FALSE(test2.empty());
}

TEST(set, merge) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {7, 4, 8, 0, -1, 48, 53};
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1, 48, 53};
  test2.merge(test);
  set2.merge(set);
  std::set<int>::iterator it;
  s21::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, swap) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {7, 4, 8, 0, -1, 48, 53};
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1, 48, 53};
  test2.swap(test);
  set2.swap(set);
  std::set<int>::iterator it;
  s21::set<int>::iterator it2 = test2.begin();
  for (it = set2.begin(); it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  it2 = test.begin();
  for (it = set.begin(); it != set.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, erase) {
  std::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it = test.begin();
  s21::set<int>::iterator it2 = test2.begin();
  ++it;
  ++it2;
  test.erase(it);
  test2.erase(it2);
  it = test.begin();
  it2 = test2.begin();
  for (; it != test.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, insert_many) {
  s21::set<int> m = {3, 6, 1, -1, 5};

  m.insert_many(-2, -1, 7);

  std::set<int> std_m = {-2, -1, 3, 6, 1, 5, 7};
  s21::set<int>::iterator it = m.begin();
  std::set<int>::iterator it2;
  for (it2 = std_m.begin(); it2 != std_m.end(); it2++) {
    EXPECT_EQ(*it, *it2);
    it++;
  }
}

// MULTISET

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> mySet;
  ASSERT_TRUE(mySet.empty());
  ASSERT_EQ(mySet.size(), 0);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> mySet = {1, 2, 3};
  auto it = mySet.begin();
  mySet.erase(it);
  ASSERT_EQ(mySet.size(), 2);
  ASSERT_EQ(*mySet.begin(), 2);
}

TEST(MultisetTest, LowerUpperBound) {
  s21::multiset<int> mySet = {1, 2, 2, 3, 3, 3};
  auto lower = mySet.lower_bound(2);
  auto upper = mySet.upper_bound(2);

  ASSERT_EQ(*lower, 2);  // Первое вхождение 2
  ASSERT_EQ(*upper, 3);  // Первое вхождение, не равное 2
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> originalSet = {1, 2, 3};
  s21::multiset<int> copySet(originalSet);
  ASSERT_EQ(originalSet.size(), copySet.size());
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> originalSet = {1, 2, 3};
  s21::multiset<int> moveSet(std::move(originalSet));
  ASSERT_TRUE(originalSet.empty());
  ASSERT_FALSE(moveSet.empty());
}

TEST(multiset, init) {
  s21::multiset<int> test = {52, 52, 45, 48, 53};
  std::multiset<int> test2 = {52, 52, 45, 48, 53};
  std::multiset<int>::iterator it;
  s21::multiset<int>::iterator it2 = test.begin();
  for (it = test2.begin(); it != test2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(multiset, lower) {
  s21::multiset<int> test = {52, 54, 45, 48, 53};
  s21::multiset<int>::iterator it2;
  it2 = test.lower_bound(-2);
  std::multiset<int> test2 = {52, 54, 45, 48, 53};
  std::multiset<int>::iterator it3;
  it3 = test2.lower_bound(-2);
  EXPECT_EQ(*it2, *it3);
}

TEST(multiset, upper) {
  s21::multiset<int> test = {52, 54, 45, 48, 53};
  s21::multiset<int>::iterator it2;
  it2 = test.upper_bound(52);
  std::multiset<int> test2 = {52, 54, 45, 48, 53};
  std::multiset<int>::iterator it3;
  it3 = test2.upper_bound(52);
  EXPECT_EQ(*it2, *it3);
}

TEST(multiset, range) {
  s21::multiset<int> test = {52, 54, 45, 48, 53};
  std::multiset<int> test2 = {52, 54, 45, 48, 53};
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> check =
      test.equal_range(2);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> check2 =
      test2.equal_range(2);
  EXPECT_EQ(*check.first, *check2.first);
  EXPECT_EQ(*check.second, *check2.second);
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> mySet;
  auto result1 = mySet.insert(42);
  ASSERT_TRUE(result1.second);
  ASSERT_EQ(result1.first, mySet.begin());
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> mySet = {1, 2, 3};
  ASSERT_FALSE(mySet.empty());

  mySet.clear();
  ASSERT_TRUE(mySet.empty());
  ASSERT_EQ(mySet.size(), 0);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}