#include "bubble_sort.h"

#include <stdint.h>

#include "unity.h"
#include "unity_fixture.h"

#include "Helper/sort_functions.h"

TEST_GROUP(BubbleSort);

TEST_SETUP(BubbleSort) {
}

TEST_TEAR_DOWN(BubbleSort) {
}

TEST_GROUP_RUNNER(BubbleSort) {
    RUN_TEST_CASE(BubbleSort, BubbleSort_int);
    RUN_TEST_CASE(BubbleSort, BubbleSort_double);
    RUN_TEST_CASE(BubbleSort, BubbleSort_uint64);
}

TEST(BubbleSort, BubbleSort_int) {
    int unsorted_array[] = {5, 2, 3, 1000000, 9, 10, 11, 8, 9, 100};
    const int sorted_array[] = {2, 3, 5, 8, 9, 9, 10, 11, 100, 1000000};
    BubbleSort_sort(unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareInt);

    unsigned int i;
    for (i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_INT(unsorted_array[i], sorted_array[i]);
    }
}

TEST(BubbleSort, BubbleSort_double) {
    double unsorted_array[] = {5.8, 2.2, 3.1, 1.1, 9.1, 10.3, 11.2, 8.4, 9.2, 100.9};
    const double sorted_array[] = {1.1, 2.2, 3.1, 5.8, 8.4, 9.1, 9.2, 10.3, 11.2, 100.9};
    BubbleSort_sort(unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareDouble);

    unsigned int i;
    for (i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_DOUBLE(unsorted_array[i], sorted_array[i]);
    }
}

TEST(BubbleSort, BubbleSort_uint64) {
    uint64_t unsorted_array[] = {1111111, 55555555, 44444, 10000000000000, 212121, 1111, 1, 2, 5, 3};
    const uint64_t sorted_array[] = {1, 2, 3, 5, 1111, 44444, 212121, 1111111, 55555555, 10000000000000};
    BubbleSort_sort(unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareUint64);

    unsigned int i;
    for (i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_UINT64(unsorted_array[i], sorted_array[i]);
    }
}