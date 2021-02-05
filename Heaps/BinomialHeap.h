//
// Created by vahna on 04.12.2019.
//
#pragma once


#ifndef HEAPS_12_2019__BINOMIALHEAP_H
#define HEAPS_12_2019__BINOMIALHEAP_H

#include "IHeap.h"

struct BinomialHeap : public IHeap {
private:
    int min_pos_ = -1;
    int min_value_ = INT32_MAX;//Integer max value
    int size_ = 0;
    struct Vertex {
    public:
        Vertex *sibling = nullptr;
        Vertex *son = nullptr;
        int key;
    };

    void destruct_(Vertex *x);

    std::vector<Vertex *> all_;

    Vertex *MergeSimilar_(Vertex *x, Vertex *y);

public:
    BinomialHeap() = default;

    BinomialHeap(int x) {
        Insert(x);
    };

    ~BinomialHeap() {
        for (int i = 0; i < all_.size(); i++) {
            destruct_(all_[i]);
        }
    }

    void Insert(int key);

    virtual int GetMin();

    virtual int ExtractMin();

    virtual void Merge(IHeap &a);

    virtual int size();
};

void BinomialHeap::Insert(int key) {
    Vertex *x = new Vertex;
    x->key = key;
    BinomialHeap tmp;
    tmp.all_.push_back(x);
    tmp.size_++;
    Merge(tmp);
}

int BinomialHeap::GetMin() {
    return min_value_;
}

int BinomialHeap::ExtractMin() {
    Vertex *curr = all_[min_pos_];
    all_[min_pos_] = nullptr;
    int res = min_value_;
    Vertex *del = curr;
    BinomialHeap tmp;
    tmp.all_.resize(min_pos_, nullptr);
    for (int i = min_pos_ - 1; i >= 0; i--) {
        tmp.all_[i] = curr->son;
        del = curr;
        curr = curr->sibling;
        delete del;
    }

    Merge(tmp);
    return res;
}

void BinomialHeap::Merge(IHeap &x) {
    BinomialHeap &a = dynamic_cast<BinomialHeap &>(x);
    Vertex *owed = nullptr;

    all_.resize(std::max(a.all_.size(), all_.size()), nullptr);
    a.all_.resize(std::max(a.all_.size(), all_.size()), nullptr);
    for (int i = 0; i < all_.size(); i++) {
        if (owed != nullptr) {
            if (a.all_[i] != nullptr) {
                owed = MergeSimilar_(owed, a.all_[i]);
            } else {
                if (all_[i] != nullptr) {
                    owed = MergeSimilar_(owed, all_[i]);
                    all_[i] = nullptr;
                } else {
                    all_[i] = owed;
                    owed = nullptr;
                }
            }
        } else {
            if (all_[i] == nullptr) {
                all_[i] = a.all_[i];
            } else {
                if (a.all_[i] != nullptr) {
                    owed = MergeSimilar_(all_[i], a.all_[i]);
                    all_[i] = nullptr;
                }
            }
        }
        a.all_[i] = nullptr;
    }

    if (owed != nullptr) {
        all_.push_back(owed);
    }
    size_ += a.size_;
    min_value_ = 1e9;
    for (int i = 0; i < all_.size(); i++) {
        if (all_[i] != nullptr && all_[i]->key < min_value_) {
            min_value_ = all_[i]->key;
            min_pos_ = i;
        }
    }
}

BinomialHeap::Vertex *BinomialHeap::MergeSimilar_(BinomialHeap::Vertex *x, BinomialHeap::Vertex *y) {
    if (x == nullptr) {
        exit(1);
    }
    if (y == nullptr) {
        exit(2);
    }
    Vertex *root = new Vertex;
    if (x->key < y->key) {
        root->key = x->key;
        root->sibling = x;
        root->son = y;
    } else {
        root->key = y->key;
        root->sibling = y;
        root->son = x;
    }
    return root;
}

void BinomialHeap::destruct_(BinomialHeap::Vertex *x) {
    if (x == nullptr) {
        return;
    }
    destruct_(x->sibling);
    destruct_(x->son);
    delete x;
}

int BinomialHeap::size() {
    return size_;
}

#endif //HEAPS_12_2019__BINOMIALHEAP_H
