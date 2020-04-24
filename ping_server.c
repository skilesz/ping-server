/*
Application that sends an echo_request to specified server, then waits for an echo_reply in order to determine
RTT (min, max, and avg) and the loss percentage based on the number of packets sent and received.

Programmed by Zach Skiles, skilesz@purdue.edu
Last Updated: 4-23-2020 8:15 pm
*/

#include "ping_server.h"


//Checksum for incoming packets
int checksum(void *bin, int len) {

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

} //reverse_lookup()

int main(int argc, char *argv[]) {
  int master_socket;
  char *ip_addr;
  char *host_name;
  struct sockaddr_in addr;

  if (argc < 2) {
    printf("\nUSAGE: ./ping_server <host_name_or_ip> (<ttl>)\n");
    return 0;
  }

  ip_addr = dns_lookup(argv[1], &addr);

  if (!ip_addr) {
    printf("\nCould not resolve hostname.\n");
    return 0;
  }

  host_name = reverse_lookup(ip_addr);
  printf("Trying to connect to %s IP: %s\n", argv[1], ip_addr);
  printf("Reverse lookup domain: %s\n", host_name);

  //Socket setup

  return 0;
} //main()
