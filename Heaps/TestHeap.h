//
// Created by vahna on 07.12.2019.
//
#pragma once
#ifndef HEAPS_12_2019__TESTHEAP_H
#define HEAPS_12_2019__TESTHEAP_H

#include "IHeap.h"
#include <set>

struct TestHeap : public IHeap {
private:
    std::multiset<int> all;


public:
    virtual void Insert(int key);

    virtual int GetMin();

    virtual int ExtractMin();

    virtual void Merge(IHeap &x);

    virtual int size();
};

void TestHeap::Insert(int key) {
    all.insert(key);
}

int TestHeap::GetMin() {
    return *all.begin();
}

int TestHeap::ExtractMin() {
    int min = *all.begin();
    all.erase(all.begin());
    return min;
}

void TestHeap::Merge(IHeap &x) {
    TestHeap &a = dynamic_cast<TestHeap &>(x);
    all.insert(a.all.begin(), a.all.end());

}

int TestHeap::size() {
    return all.size();
}

#endif //HEAPS_12_2019__TESTHEAP_H
