#include <stdio.h>
#include "priority_queue.h"
#include "rfc_parser.h"

int main() {
    PriorityQueue* pq = create_queue(4);

    Request r1 = parse_rfc_priority(101, "/api/login", "u=1");
    Request r2 = parse_rfc_priority(102, "/api/get_data", "u=5, i");
    Request r3 = parse_rfc_priority(103, "/api/payment", "u=0");
    Request r4 = parse_rfc_priority(104, "/api/background_sync", "u=7");
    Request r5 = parse_rfc_priority(105, "/api/profile", NULL); 

    insert(pq, r1);
    insert(pq, r2);
    insert(pq, r3);
    insert(pq, r4);
    insert(pq, r5);

    printf("API Gateway Testi (Min-Heap Sira Ciktisi):\n\n");

    while (pq->size > 0) {
        Request current = extract_min(pq);
        printf("ID: %d | Endpoint: %-20s | Urgency: %d\n", 
               current.request_id, current.endpoint, current.urgency);
    }

    free_queue(pq);
    return 0;
}