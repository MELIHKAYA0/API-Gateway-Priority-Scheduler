#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

PriorityQueue* create_queue(size_t initial_capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        exit(EXIT_FAILURE);
    }
    
    pq->array = (Request*)malloc(sizeof(Request) * initial_capacity);
    if (pq->array == NULL) {
        free(pq);
        exit(EXIT_FAILURE);
    }
    
    pq->capacity = initial_capacity;
    pq->size = 0;
    return pq;
}

void swap_requests(Request* a, Request* b) {
    Request temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;
    
    if (index > 0 && pq->array[parent].urgency > pq->array[index].urgency) {
        swap_requests(&pq->array[parent], &pq->array[index]);
        heapify_up(pq, parent);
    }
}

void insert(PriorityQueue* pq, Request req) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->array = (Request*)realloc(pq->array, sizeof(Request) * pq->capacity);
        if (pq->array == NULL) {
            exit(EXIT_FAILURE);
        }
    }
    
    pq->array[pq->size] = req;
    heapify_up(pq, pq->size);
    pq->size++;
}

void heapify_down(PriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->array[left].urgency < pq->array[smallest].urgency)
        smallest = left;

    if (right < pq->size && pq->array[right].urgency < pq->array[smallest].urgency)
        smallest = right;

    if (smallest != index) {
        swap_requests(&pq->array[index], &pq->array[smallest]);
        heapify_down(pq, smallest);
    }
}

Request extract_min(PriorityQueue* pq) {
    if (pq->size == 0) {
        Request empty_req = {-1, -1, ""}; 
        return empty_req;
    }

    Request min_req = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    
    heapify_down(pq, 0);
    
    return min_req;
}

void free_queue(PriorityQueue* pq) {
    if (pq != NULL) {
        if (pq->array != NULL) {
            free(pq->array);
        }
        free(pq);
    }
}