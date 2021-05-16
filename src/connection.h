//Grzegorz Bielecki 288388

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
int send_segment(char* _message);
int create_connection(char* s_addr, int s_port);
int close_socket();
int receive(char buffer[]);
int listen_for_packets(int time, char buffer[]);