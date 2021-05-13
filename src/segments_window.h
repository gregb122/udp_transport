//Grzegorz Bielecki 288388

#include "segment.h"

typedef struct {
    segment_t   *record_tab;
    addr         via_router_addr;
    int          bytes_to_download;
    int          count;
    int          max_s;
} segments_window_t;

int construct_window(int size, segments_window_t *table_out);
int add_segment(segments_window_t *table, segment_t *r);
int rm_record(segments_window_t *table, int idx);
int handle_data_packet(segments_window_t *table, int start, int size, int data);
int perform_window_sends(segments_window_t *table, addr network_ip);
int write_and_move_window_if_possible(segments_window_t *table);
