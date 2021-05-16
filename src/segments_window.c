//Grzegorz Bielecki 288388

#include "segments_window.h"

int find_segment(segments_window_t *window, int _start){
    for(int i = 0; i < WINDOW_LEN; i++){
        if(window->window_tab[i].start == _start){
            return i;
        }
    }
    return -1; // not found
}

int construct_window_from(segments_window_t *seg_out, int construct_start){
    for(int i=construct_start; i < WINDOW_LEN; i++){
        int full_size = seg_out->bytes_to_download;

        if(full_size < DATA_SIZE){
            construct_segment(full_size, seg_out->next_start, &seg_out->window_tab[i]);
            seg_out->bytes_to_download = 0;
        } else {
            construct_segment(DATA_SIZE, seg_out->next_start, &seg_out->window_tab[i]);
            seg_out->bytes_to_download -= DATA_SIZE;
            seg_out->next_start += DATA_SIZE;
        }
    }
    return 0;
}

/* args 1 size of table list, 2 out for table */
int construct_window(int bytes_to_download, segments_window_t *seg_out){
    seg_out->bytes_to_download = bytes_to_download;
    seg_out->next_start = 0;
    construct_window_from(seg_out, 0);
    return 0;
}

int handle_data_packet(segments_window_t *window, char buffer_data[IP_MAXPACKET + 1]){
    int             start;
    int             size;
    sscanf(buffer_data, "DATA %d %d", &start, &size);
    int idx = find_segment(window, start);
    if (idx < 0){
        return 0;
    }
    if (window->window_tab[idx].is_ready){
        return 0;
    }
    char *start_of_data = strchr(buffer_data, '\n');
    memcpy(window->window_tab[idx].data_to_write, start_of_data + 1, size);
    window->window_tab[idx].is_ready = 1;
    return 0;
}

int perform_window_sends(segments_window_t *window){
    for(int i=0; i < WINDOW_LEN; i++){
        send_packet(&window->window_tab[i]);
    }
    return EXIT_SUCCESS;
}

int write_and_move_window_if_possible(segments_window_t *window, FILE *file, int full_size){
    int i = -1;
    while(i + 1 < WINDOW_LEN && window->window_tab[i + 1].is_ready && window->window_tab[i + 1].size != 0){
        i++;
        printf ("%.3f%% done\n", ((float) window->window_tab[i].start/ (float) full_size)*(float)100);
        if(fwrite(window->window_tab[i].data_to_write,
            sizeof(char),
            window->window_tab[i].size,
            file) == 0){
                fprintf(stderr, "fwrite error: %s\n", strerror(errno)); 
		        return EXIT_FAILURE;
        }
    }
    if (i >= 0){
        if(i >= WINDOW_LEN - 1){
            construct_window_from(window, 0);
            return EXIT_SUCCESS;
        }
        memmove(&window->window_tab[0], &window->window_tab[i + 1], (WINDOW_LEN - i - 1) * sizeof(segment_t));
        
        construct_window_from(window, WINDOW_LEN - i - 1);
    }
    return EXIT_SUCCESS;
}
