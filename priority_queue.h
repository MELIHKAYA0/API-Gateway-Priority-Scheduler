#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

typedef struct {
    int request_id;
    int urgency;
    char endpoint[64];
} Request;

typedef struct {
    Request* array;
    size_t capacity;
    size_t size;
} PriorityQueue;

PriorityQueue* create_queue(size_t initial_capacity);
void free_queue(PriorityQueue* pq);
void insert(PriorityQueue* pq, Request req);
Request extract_min(PriorityQueue* pq);
void heapify_up(PriorityQueue* pq, int index);
void heapify_down(PriorityQueue* pq, int index);

#endif