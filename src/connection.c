//Grzegorz Bielecki 288388

#include "broadcaster.h"

int broadcast(u_int8_t buffer) {
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	int broadcastPermission = 1;
	setsockopt (sockfd, SOL_SOCKET, SO_BROADCAST,
	(void *)&broadcastPermission,
	sizeof(broadcastPermission)); 

	struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(54321);
	inet_pton(AF_INET, "255.255.255.255", &server_address.sin_addr);

	char* message = "Hello server!";
	ssize_t message_len = strlen(message);
	if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) &server_address, sizeof(server_address)) != message_len) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;		
	}
	close (sockfd);
	return EXIT_SUCCESS;
}
