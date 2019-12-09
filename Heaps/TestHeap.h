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
    std::multiset<int> all_;


public:
    virtual void Insert(int key);

    virtual int GetMin();

    virtual int ExtractMin();

    virtual void Merge(IHeap &x);

    virtual int size();
};

void TestHeap::Insert(int key) {
    all_.insert(key);
}

int TestHeap::GetMin() {
    return *all_.begin();
}

int TestHeap::ExtractMin() {
    int min = *all_.begin();
    all_.erase(all_.begin());
    return min;
}

void TestHeap::Merge(IHeap &x) {
    TestHeap &a = dynamic_cast<TestHeap &>(x);
    all_.insert(a.all_.begin(), a.all_.end());

}

int TestHeap::size() {
    return all_.size();
}

#endif //HEAPS_12_2019__TESTHEAP_H
