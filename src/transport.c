//Grzegorz Bielecki 288388

#include <time.h>

#include "segments_window.h"

static segments_window_t window;

int transport(char ip[20], int port, char filename[128], int size){
	char packet_buffer[IP_MAXPACKET + 1];
	FILE *file = fopen(filename, "w");

	create_connection(ip, port);
	int send_after = 1;
	construct_window(size, &window);
	struct timespec tv1, tv2;

	clock_gettime(CLOCK_REALTIME, &tv1);
	for(;;){
		clock_gettime(CLOCK_REALTIME, &tv2);	
		double time = (double) (tv2.tv_sec - tv1.tv_sec) / 1000000 +
         			  (double) (tv2.tv_sec - tv1.tv_sec);
		if(time > send_after){
			perform_window_sends(&window);
			clock_gettime(CLOCK_REALTIME, &tv1);
		}
		if(listen_for_packets(send_after, packet_buffer) == 0){
			handle_data_packet(&window, packet_buffer);
		}
		if(window.window_tab[0].size == 0){
			printf("100.000%% done\n");
			break;
		}
		write_and_move_window_if_possible(&window, file, size);
	}
	close_socket();
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	char ip[20];
	int  port;
	char filename[128];
	int  size;
	if (argc != 5) {
		printf("All arguments need to be provided\n");
		exit(0);
    }
	if (0 == sscanf(argv[1], "%s", ip)) {
		printf("invalid PORT argument\n\n");
		exit(0);
	}
	if (0 == sscanf(argv[2], "%d", &port)) {
		printf("invalid PORT argument\n\n");
		exit(0);
	}
	if (0 == sscanf(argv[3], "%s", filename)) {
		printf("invalid file argument\n\n");
		exit(0);
	}
	if (0 == sscanf(argv[4], "%d", &size)) {
		printf("invalid size argument\n\n");
		exit(0);
	}
	transport(ip, port, filename, size);
	return 0;
}
