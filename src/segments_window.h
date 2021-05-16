//Grzegorz Bielecki 288388

#include "segment.h"

#define WINDOW_LEN 700

typedef struct {
    segment_t    window_tab[WINDOW_LEN];
    int          bytes_to_download;
    int          next_start;
} segments_window_t;

int construct_window(int bytes_to_download, segments_window_t *table_out);
int handle_data_packet(segments_window_t *table, char buffer_data[]);
int perform_window_sends(segments_window_t *table);
int write_and_move_window_if_possible(segments_window_t *table, FILE *file, int full_size);
