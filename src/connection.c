//Grzegorz Bielecki 288388

#include "connection.h"

static int sockfd = -1;
static uint16_t server_port = 40001;
static uint16_t client_port = 54321;
static char* server_ip = "192.168.56.101";


int send_segment(char* _message) {

	struct sockaddr_in recipient;
	bzero (&recipient, sizeof(recipient));

	recipient.sin_family = AF_INET;
	recipient.sin_port = htons(server_port);
	inet_pton(AF_INET, server_ip, &recipient.sin_addr);
		
	if (sendto(sockfd, _message, strlen(_message), 0, 
		(struct sockaddr*) &recipient, sizeof(recipient)) < 0) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;		
	}

	return EXIT_SUCCESS;
}

int create_connection(char* s_addr, int s_port){
	server_port = s_port;
	server_ip = s_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(client_port);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind (sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

int close_socket(){
    return close(sockfd);
}

int receive(char buffer[]) {
	char sender_ip_str[20];
	
	struct sockaddr_in 	sender;	
	socklen_t 			sender_len = sizeof(sender);
	ssize_t datagram_len = recvfrom (sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
	if (datagram_len < 0) {
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}
	inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));


	if (strcmp(server_ip, sender_ip_str) != 0) {
    	return 0;
  	}

	if (ntohs(sender.sin_port) != server_port) {
   		return 0;
    }	
	return EXIT_SUCCESS;
}

int listen_for_packets(int time, char buffer[]) {
		struct timeval tv = {
			tv.tv_sec = time,
			tv.tv_usec = 0
		};

		fd_set descriptors;
		FD_ZERO (&descriptors);
		FD_SET (sockfd, &descriptors);
		
		int ready = select (sockfd+1, &descriptors, NULL, NULL, &tv);
		if(ready < 0){
			fprintf(stderr, "select error: %s\n", strerror(errno));
			exit(1);
		}
		if(ready == 0){
			return -1;
		}
		if (receive(buffer) == EXIT_FAILURE){
			printf("recvfrom error: %s\n", strerror(errno));
			return 1;
		}
	return EXIT_SUCCESS;
}

