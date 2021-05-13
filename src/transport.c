//Grzegorz Bielecki 288388

#include <time.h>

#include "segments_window.h"

int prepare_server(char _sender_ip_str[]){
	memset(_sender_ip_str, 0, sizeof(char) * 16);
	return create_socket();
}

void close_server(int sockfd){
	close_socket(sockfd);
}

int transport(){
	int sendafter = 5;
	u_int8_t _buffer[9];
	char _sender_ip_str[16];

	int sockfd = prepare_server(_sender_ip_str);
	struct timespec tv1, tv2;

	clock_gettime(CLOCK_REALTIME, &tv1);
	for(;;){
		clock_gettime(CLOCK_REALTIME, &tv2);	
		double time = (double) (tv2.tv_sec - tv1.tv_sec) / 1000000 +
         			  (double) (tv2.tv_sec - tv1.tv_sec);
		if(time > sendafter){
			printf("A tu sobie wyślę hehe! :0\n");
			broadcast();
			clock_gettime(CLOCK_REALTIME, &tv1);
		}
		printf("nasłuchuję!!!\n");
		listen_for_packets(sockfd, sendafter, _buffer, _sender_ip_str);
	}
	close_server(sockfd);
    return EXIT_FAILURE;
}

int main() {
	printf("Halo gdzie się schowałeś segfault");
	router();
	return 0;
}
