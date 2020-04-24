/*
HEADER FILE FOR ping_server.c

Programmed by Zach Skiles, skilesz@purdue.edu
Last Update: 4-23-2020 7:41 pm
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#define PACKET_SIZE 64
#define PORT_NO 2601
#define PING_SLEEP_RATE 1000000 x
#define TIMEOUT 1

typedef struct pack {
  struct icmphdr header;
  char data[PACKET_SIZE - sizeof(struct icmphdr)];
} packet;

int checksum(void *bin, int len);
char *dns_lookup(char *dest_name, struct sockaddr_in *addr);
char *reverse_lookup(char *dest_ip);
void ping(int master_socket, struct sockaddr_in *addr, char *name, char *ip_addr, char *input);
