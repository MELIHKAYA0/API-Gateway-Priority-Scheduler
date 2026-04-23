#ifndef RFC_PARSER_H
#define RFC_PARSER_H

#include "priority_queue.h"

Request parse_rfc_priority(int id, const char* endpoint, const char* priority_header);

#endif