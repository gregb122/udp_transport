//Grzegorz Bielecki 288388

#include <arpa/inet.h>

#include "segment.h"

int construct_segment(int _size, int _start, segment_t *seg_out){
    seg_out->is_ready = 0;
    seg_out->start = _start;
    seg_out->size = _size;
    return 0;
}

int send_packet(segment_t *seg){
    if(seg->is_ready || (seg->size == 0)){
        return EXIT_SUCCESS;
    }

    char buffer[IP_MAXPACKET+1];
    sprintf(buffer, "GET %d %d\n", seg->start, seg->size);
    if (send_segment(buffer) == EXIT_FAILURE){
        fprintf(stderr, "Send segment error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
