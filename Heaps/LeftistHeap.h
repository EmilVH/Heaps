//
// Created by vahna on 07.12.2019.
//
#pragma once
#ifndef HEAPS_12_2019__LEFTISTHEAP_H
#define HEAPS_12_2019__LEFTISTHEAP_H

#include "IHeap.h"

struct LeftistHeap : public IHeap {
protected:
    int size_ = 0;
    struct Vertex {
    public:
        Vertex *r = nullptr;
        Vertex *l = nullptr;
        int key = -1000;
        int rank = 1;
    };

    void destruct_(Vertex *x);

    Vertex *Merge_Roots(Vertex *r1, Vertex *r2);

    Vertex *head_ = nullptr;


private:
    int dist_(Vertex *x);

public:
    LeftistHeap() = default;

    LeftistHeap(Vertex *x) {
        head_ = x;
    }

    ~LeftistHeap() {
        destruct_(head_);
    }

    void Insert(int key);

    virtual int GetMin();

    virtual int ExtractMin();

    virtual void Merge(IHeap &x);

    virtual int size();
};

void LeftistHeap::Insert(int key) {
    LeftistHeap tmp;
    tmp.head_ = new Vertex;
    tmp.head_->key = key;
    tmp.size_++;
    Merge(tmp);
}

int LeftistHeap::GetMin() {
    return head_->key;
}

int LeftistHeap::ExtractMin() {
    int res = head_->key;
    Vertex *del = head_;
    LeftistHeap R(head_->r);
    head_ = head_->l;
    size_--;
    Merge(R);
    delete del;
    return res;
}

void LeftistHeap::Merge(IHeap &x) {
    LeftistHeap &a = dynamic_cast<LeftistHeap &>(x);
    head_ = Merge_Roots(head_, a.head_);
    size_+=a.size_;
    a.head_ = nullptr;
}


void LeftistHeap::destruct_(LeftistHeap::Vertex *x) {
    if (x == nullptr) {
        return;
    }
    destruct_(x->l);
    destruct_(x->r);
    delete x;
}

LeftistHeap::Vertex *LeftistHeap::Merge_Roots(LeftistHeap::Vertex *r1, LeftistHeap::Vertex *r2) {
    if (r1 == nullptr) {
        return r2;
    }
    if (r2 == nullptr) {
        return r1;
    }
    if (r2->key < r1->key) {
        std::swap(r1, r2);
    }
    r1->r = Merge_Roots(r1->r, r2);
    /*if (r1->r != nullptr && r1->l != nullptr) {
        r1->rank = std::min(r1->l->rank, r1->r->rank) + 1;
        if (r1->l->rank < r1->r->rank) {
            std::swap(r1->l, r1->r);
        }
    } else {
        r1->rank = 1;
        if(r1->l!= nullptr){
            std::swap(r1->l,r1->r);
        }
    }*/
    if (dist_(r1->r) > dist_(r1->l)) {
        std::swap(r1->l, r1->r);
    }
    r1->rank = dist_(r1->r) + 1;
    return r1;
}

int LeftistHeap::size() {
    return size_;
}

int LeftistHeap::dist_(LeftistHeap::Vertex *x) {
    if (x == nullptr) {
        return 0;
    } else {
        return x->rank;
    }
}

#endif //HEAPS_12_2019__LEFTISTHEAP_H