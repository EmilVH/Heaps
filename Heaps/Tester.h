//
// Created by vahna on 08.12.2019.
//
#pragma once
#ifndef HEAPS_12_2019__TESTER_H
#define HEAPS_12_2019__TESTER_H

#include <random>
#include "IHeap.h"
#include "LeftistHeap.h"
#include "BinomialHeap.h"
#include "SkewHeap.h"
#include "TestHeap.h"
#include <gtest/gtest.h>

void tester(std::vector<IHeap *> tested, std::vector<IHeap *> standard, int key, int count) {
    srand(key);
    int exist = tested.size();
    for (int i = 0; i < count; i++) {
        if (exist == 0) {
            break;
        }
        int x = rand();
        int y = rand() % exist;
        if (x % 4 == 0) {
            int value = rand();
            tested[y]->Insert(value);
            standard[y]->Insert(value);
        }
        if (x % 4 == 1) {
            if (standard[y]->size() > 0) {
                ASSERT_EQ(tested[y]->GetMin(), standard[y]->GetMin());
            }
        }
        if (x % 4 == 2) {
            if (standard[y]->size() > 0) {
                ASSERT_EQ(tested[y]->ExtractMin(), standard[y]->ExtractMin());
            }
        }
        if (x % 4 == 3) {
            if (y != exist - 1) {
                tested[y]->Merge(*tested[exist - 1]);//Тут может быть ошибка
                standard[y]->Merge(*standard[exist - 1]);
                exist--;
            }
        }
    }
}

void delete_vector(std::vector<IHeap *> &a) {
    for (int i = 0; i < a.size(); i++) {
        delete a[i];
    }
}

void create_test_vector(std::vector<IHeap *> &a) {
    a.resize(5000);
    for (int i = 0; i < 5000; i++) {
        a[i] = new TestHeap;
    }
}


class TesterHeap : public ::testing::Test {
protected:
    IHeap *getHeap_(int x) {
        IHeap *ans;
        if (x == 1) {
            ans = new BinomialHeap;
        }
        if (x == 2) {
            ans = new SkewHeap;
        }
        if (x == 3) {
            ans = new LeftistHeap;
        }
        return ans;
    }

    virtual void SetUp(int x) {
        all.resize(5000);
        for (int i = 0; i < 5000; i++) {
            all[i] = getHeap_(x);
        }
        create_test_vector(standard);
    }

    virtual void TearDown() {
        delete_vector(all);
        delete_vector(standard);

    }

    std::vector<IHeap *> all;
    std::vector<IHeap *> standard;
};

/*class TestLeftistHeap : public ::testing::Test {
protected:
    void SetUp() {
        all.resize(5000);
        for (int i = 0; i < 5000; i++) {
            all[i] = new LeftistHeap;
        }
        create_test_vector(standard);
    }

    void TearDown() {
        delete_vector(all);
        delete_vector(standard);

    }

    std::vector<IHeap *> all;
    std::vector<IHeap *> standard;
};

class TestSkewHeap : public ::testing::Test {
protected:
    void SetUp() {
        all.resize(5000);
        for (int i = 0; i < 5000; i++) {
            all[i] = new SkewHeap;
        }
        create_test_vector(standard);
    }

    void TearDown() {
        delete_vector(all);
        delete_vector(standard);

    }

    std::vector<IHeap *> all;
    std::vector<IHeap *> standard;
};

class TestBionomialHeap : public ::testing::Test {
protected:
    void SetUp() {
        all.resize(5000);
        for (int i = 0; i < 5000; i++) {
            all[i] = new BinomialHeap;
        }
        create_test_vector(standard);
    }

    void TearDown() {
        delete_vector(all);
        delete_vector(standard);

    }

    std::vector<IHeap *> all;
    std::vector<IHeap *> standard;
};
*/
TEST_F (TesterHeap,
        BinomialHeap) {
    SetUp(1);
    tester(all, standard, 345, 1000000);

}

TEST_F (TesterHeap,
        SkewHeap) {
    SetUp(2);
    tester(all, standard, 345, 1000000);
}

TEST_F (TesterHeap,
        LeftistHeap) {
    SetUp(3);
    tester(all, standard, 345, 1000000);
}


int test() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#endif //HEAPS_12_2019__TESTER_H
