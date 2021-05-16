//Grzegorz Bielecki 288388

#include <stdint.h>
#include "connection.h"

#define DATA_SIZE 1000

typedef struct in_addr addr;

typedef struct {
    int is_ready;// 1 via or 0 direct 
    int start;
    int size;
    int data_to_write[DATA_SIZE];
} segment_t;

int construct_segment(int _size, int _start, segment_t *seg_out);
int send_packet(segment_t *seg_out);