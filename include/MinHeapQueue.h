//
// Created by kamil on 5/31/2026.
//

#ifndef QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H
#define QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H

#include <vector>
#include <string>
#include <algorithm>

struct NetworkPacket {
    int prio;
    std::string type;
};

class MinHeapQueue {
private:
    std::vector<NetworkPacket> heap;

    void heapifyUp(int index) {
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

public:
    void insert(const NetworkPacket &newPacket) {
        heap.push_back(newPacket);
        const int lastIndex = heap.size() - 1;
        heapifyUp(lastIndex);
    }
};



#endif //QOS_QUEUE_ANALYZER_MINHEAPQUEUE_H
