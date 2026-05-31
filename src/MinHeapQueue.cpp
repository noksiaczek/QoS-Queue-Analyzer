//
// Created by kamil on 5/31/2026.
//
#include "../include/MinHeapQueue.h"

void MinHeapQueue::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = ( index - 1 ) / 2;
        if (heap[index].prio < heap[parentIndex].prio) {
            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

void MinHeapQueue::heapifyDown(int index) {
    while (index*2 + 1 < heap.size()) {
        int leftChildIndex = index * 2 + 1;
        int rightChildIndex = index * 2 + 2;
        int smallestChildIndex = leftChildIndex;

        if (index*2+2 < heap.size() && heap[rightChildIndex].prio < heap[smallestChildIndex].prio)
            smallestChildIndex = rightChildIndex;

        if (heap[index].prio > heap[smallestChildIndex].prio) {
            std::swap(heap[smallestChildIndex], heap[index]);
            index = smallestChildIndex;
        } else
            break;
    }
}

void MinHeapQueue::pop() {
    if (heap.empty())
        return;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

void MinHeapQueue::insert(const NetworkPacket &newPacket) {
    heap.push_back(newPacket);
    const int lastIndex = heap.size() - 1;
    heapifyUp(lastIndex);
}

bool MinHeapQueue::empty() const {
    return heap.empty();
}

const NetworkPacket & MinHeapQueue::front() const {
    if (empty())
        throw std::runtime_error("Kolejka jest pusta");
    else
        return heap.front();
}

void MinHeapQueue::increaseKey(const int index, const int newPrio) {
    if (index >= heap.size())
        throw std::runtime_error("Nie istnieje element kopca o takim indeksie");
    heap[index].prio = newPrio;
    heapifyDown(index);
}
