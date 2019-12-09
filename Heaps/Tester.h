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
    enum {
        Insert, GetMin, ExtractMin, Merge
    };
    for (int i = 0; i < count; i++) {
        if (exist == 0) {
            break;
        }
        int x = rand();
        int y = rand() % exist;
        if (x % 4 == Insert) {
            int value = rand();
            tested[y]->Insert(value);
            standard[y]->Insert(value);//Завести enum
        }

        if (x % 4 == GetMin) {
            if (standard[y]->size() > 0) {
                ASSERT_EQ(tested[y]->GetMin(), standard[y]->GetMin());
            }
        }
        if (x % 4 == ExtractMin) {
            if (standard[y]->size() > 0) {
                ASSERT_EQ(tested[y]->ExtractMin(), standard[y]->ExtractMin());
            }
        }
        if (x % 4 == Merge) {
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

enum {
    BinomialHeapKey, SkewHeapKey, LeftistHeapKey
};

class TesterHeap : public ::testing::Test {
protected:
    IHeap *getHeap_(int x) {
        IHeap *ans;
        if (x == BinomialHeapKey) {
            ans = new BinomialHeap;
        }
        if (x == SkewHeapKey) {
            ans = new SkewHeap;
        }
        if (x == LeftistHeapKey) {
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
    SetUp(BinomialHeapKey);
    tester(all, standard, 345, 1000000);

}

TEST_F (TesterHeap,
        SkewHeap) {
    SetUp(SkewHeapKey);
    tester(all, standard, 345, 1000000);
}

TEST_F (TesterHeap,
        LeftistHeap) {
    SetUp(LeftistHeapKey);
    tester(all, standard, 345, 1000000);
}

/*TEST(construtor,first){
    SkewHeap x(5);
    EXPECT_EQ(5,x.ExtractMin());

}*/
int test() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

#endif //HEAPS_12_2019__TESTER_H
