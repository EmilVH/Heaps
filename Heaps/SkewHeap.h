//
// Created by vahna on 07.12.2019.
//
#pragma once
#ifndef HEAPS_12_2019__SKEWHEAP_H
#define HEAPS_12_2019__SKEWHEAP_H

#include "IHeap.h"

struct SkewHeap : public IHeap {
protected:

    int size_ = 0;
    struct Vertex_ {
    public:
        Vertex_ *r = nullptr;
        Vertex_ *l = nullptr;
        int key = -1000;
    };

    void destruct_(Vertex_ *x);

    Vertex_ *MergeRoots_(Vertex_ *r1, Vertex_ *r2);

    Vertex_ *head_ = nullptr;

public:
    SkewHeap() = default;

    SkewHeap(Vertex_ *x) {
        head_ = x;
    }

    ~SkewHeap() {
        destruct_(head_);
    }

    void Insert(int key);

    virtual int GetMin();

    virtual int ExtractMin();

    virtual void Merge(IHeap &x);

    virtual int size();
};

void SkewHeap::Insert(int key) {
    SkewHeap tmp;
    tmp.head_ = new Vertex_;
    tmp.head_->key = key;
    tmp.size_++;
    Merge(tmp);
}

int SkewHeap::GetMin() {
    return head_->key;
}

int SkewHeap::ExtractMin() {
    int res = head_->key;
    Vertex_ *del = head_;
    SkewHeap R(head_->r);
    head_ = head_->l;
    size_--;
    Merge(R);
    delete del;
    return res;
}


void SkewHeap::destruct_(SkewHeap::Vertex_ *x) {
    if (x == nullptr) {
        return;
    }
    destruct_(x->l);
    destruct_(x->r);
    delete x;
}


int SkewHeap::size() {
    return size_;
}


void SkewHeap::Merge(IHeap &x) {
    SkewHeap &a = dynamic_cast<SkewHeap &>(x);
    head_ = MergeRoots_(head_, a.head_);
    size_ += a.size_;
    a.head_ = nullptr;
}

SkewHeap::Vertex_ *SkewHeap::MergeRoots_(SkewHeap::Vertex_ *r1, SkewHeap::Vertex_ *r2) {
    if (r1 == nullptr) {
        return r2;
    }
    if (r2 == nullptr) {
        return r1;
    }
    if (r1->key >= r2->key) {
        std::swap(r1, r2);
    }
    r1->r = MergeRoots_(r1->r, r2);
    std::swap(r1->l, r1->r);
    return r1;
}

#endif //HEAPS_12_2019__SKEWHEAP_H
