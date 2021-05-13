//Grzegorz Bielecki 288388

#include <stdint.h>
#include "connection.h"

typedef struct in_addr addr;

typedef struct {
    int is_ready;// 1 via or 0 direct 
    int start;
    int size;
    char *data_to_write;
} segment_t;

int construct_segment(int _size, segment_t *rec_out);
u_int8_t prepare_packet_to_send(segment_t *rec);
int send_packet(u_int8_t buffer);