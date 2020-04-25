#include "PriorityQueue.h"

void PriorityQueue::insert(const Node &n, Key k) {
    HandleType handle = __queue.emplace(n, k);
    __handles[n] = handle;
}

void PriorityQueue::clear() {
    __queue.clear();
    __handles.clear();
}

void PriorityQueue::remove(const Node &n) {
    auto h_it = __handles.find(n);
    if (h_it != __handles.end()) {
        __queue.erase(h_it->second);
        __handles.erase(h_it);
    }
}

void PriorityQueue::update(const Node &n, Key k) {
    HandleType h = __handles[n];
    __queue.update(h, ElemType(n, k));
}

void PriorityQueue::pop() {
    __handles.erase(__queue.top().first);
    __queue.pop();
}

Key PriorityQueue::topKey() {
    return __queue.top().second;
}

Node PriorityQueue::topNode() {
    return __queue.top().first;
}

int PriorityQueue::size() {
    return __queue.size();
}

bool PriorityQueue::empty() {
    return __queue.empty();
}
