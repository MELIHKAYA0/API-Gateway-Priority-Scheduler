#include <stdio.h>
#include <string.h>
#include "rfc_parser.h"
#include "priority_queue.h"

Request parse_rfc_priority(int id, const char* endpoint, const char* priority_header) {
    Request req;
    req.request_id = id;
    
    strncpy(req.endpoint, endpoint, sizeof(req.endpoint) - 1);
    req.endpoint[sizeof(req.endpoint) - 1] = '\0'; 

    req.urgency = 3;

    if (priority_header != NULL) {
        const char* u_ptr = strstr(priority_header, "u=");
        
        if (u_ptr != NULL) {
            int urgency_val;
            if (sscanf(u_ptr, "u=%d", &urgency_val) == 1) {
                if (urgency_val >= 0 && urgency_val <= 7) {
                    req.urgency = urgency_val;
                }
            }
        }
    }

    return req;
}