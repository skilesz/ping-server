/*
Application that sends an echo_request to specified server, then waits for an echo_reply in order to determine
RTT (min, max, and avg) and the loss percentage based on the number of packets sent and received.

Programmed by Zach Skiles, skilesz@purdue.edu
Last Updated: 4-23-2020 8:15 pm
*/

#include "ping_server.h"
#include <errno.h>


//Checksum for incoming packets
int checksum(void *bin, int len) {
  return 1;
} //checksum()

//DNS lookup
char *dns_lookup(char *dest_name, struct sockaddr_in *addr) {
  printf("\nDNS lookup...\n");
  struct hostent *host_ent;
  char *ip_addr = (char *) malloc(NI_MAXHOST*sizeof(char));

  //If no hostname found
  if ((host_ent = gethostbyname(dest_name)) == NULL) {
    return NULL;
  }

  //Setup
  strcpy(ip_addr, inet_ntoa(*(struct in_addr *) host_ent->h_addr));
  addr->sin_family = host_ent->h_addrtype;
  addr->sin_port = htons(PORT_NO);
  addr->sin_addr.s_addr = *(long *) host_ent->h_addr;

  return ip_addr;
} //dns_lookup()

//Reverse DNS lookup
char *reverse_lookup(char *dest_ip) {
  struct sockaddr_in temp_addr;
  socklen_t len;
  char buf[NI_MAXHOST];
  char *ret_buf;

  temp_addr.sin_family = AF_INET;
  temp_addr.sin_addr.s_addr = inet_addr(dest_ip);
  len = sizeof(struct sockaddr_in);

  if (getnameinfo((struct sockaddr *) &temp_addr, len, buf, sizeof(buf), NULL, 0, NI_NAMEREQD)) {
    printf("\nCould not perform reverse lookup of hostname.\n");
    return NULL;
  }

  ret_buf = (char *) malloc((strlen(buf) + 1) * sizeof(char));
  strcpy(ret_buf, buf);

  return ret_buf;
} //reverse_lookup()

//Send and receive ping requests
void ping(int master_socket, struct sockaddr_in *addr, char *name, char *ip_addr, char *input, int ttl_val) {
  printf("PING!\n");
} //ping()

//Interrupt handler
void sig_handle(int signal) {
  ping_cont = 0;
} //sig_handle()

int main(int argc, char *argv[]) {
  int master_socket;
  char *ip_addr;
  char *host_name;
  struct sockaddr_in addr;
  int ttl_val = 64;

  if (argc < 2) {
    printf("\nUSAGE: ./ping_server <host_name_or_ip> (<ttl_val>)\n");
    return 0;
  }

  if (argc >= 3) {
    int valid = 1;

    for (int i = 0; i < strlen(argv[2]); i++) {
      if (!isdigit(argv[2][i])) {
        valid = 0;
      }
    }

    if (!valid) {
      printf("\nInvalid ttl_val specified.\n");
      return 0;
    }

    ttl_val = atoi(argv[2]);
  }

  ip_addr = dns_lookup(argv[1], &addr);

  if (!ip_addr) {
    printf("\nCould not resolve hostname.\n");
    return 0;
  }

  host_name = reverse_lookup(ip_addr);
  printf("Trying to connect to %s (IP: %s)\n", argv[1], ip_addr);
  printf("Reverse lookup domain: %s\n", host_name);

  //Socket setup
  master_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (master_socket < 0) {
    int errsv = errno;
    printf("ERRNO: %d\n", errsv);
    printf("Failed to create socket.\n");
    return 0;
  }

  printf("Socket created (file descriptor %d)\n", master_socket);

  //Catch SIGINT
  signal(SIGINT, sig_handle);

  //Send pings
  ping(master_socket, &addr, host_name, ip_addr, argv[1], ttl_val);

  return 0;
} //main()
