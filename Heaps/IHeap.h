//
// Created by vahna on 04.12.2019.
//
#pragma once
#ifndef HEAPS_12_2019__IHEAP_H
#define HEAPS_12_2019__IHEAP_H

#include <iostream>
#include <vector>

struct IHeap {

public:
    //Добавить конструктор от одного элемента
    virtual void Insert(int key) = 0;

    virtual int GetMin() = 0;

    virtual int ExtractMin() = 0;

    virtual void Merge(IHeap &x) = 0;

    virtual int size() = 0;
};

#endif //HEAPS_12_2019__IHEAP_H
