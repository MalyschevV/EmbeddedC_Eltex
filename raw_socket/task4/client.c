#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 256

int main() {
  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

  if (sock < 0) {
    perror("create socket error");
    exit(1);
  }

  struct sockaddr_in server;

  server.sin_family = AF_INET;
  server.sin_port = htons(7777);
  server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  int flag = 1;
  if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) < 0) {
    perror("erroe setsockopt");
    exit(1);
  }

  socklen_t lenght = sizeof(struct sockaddr_in);

  char *message = calloc(SIZE - lenght, sizeof(char));
  message = "Hello!\n";

  char *packet = calloc(SIZE, sizeof(char));
  memmove(packet + sizeof(struct iphdr) + sizeof(struct udphdr), message,
          strlen(message) - 1);

  struct iphdr *ip_header;

  ip_header = (struct iphdr *)packet;
  ip_header->ihl = 5;
  ip_header->version = 4;
  ip_header->tos = 0;
  ip_header->id = htonl(601);
  ip_header->frag_off = 0;
  ip_header->ttl = 255;
  ip_header->protocol = IPPROTO_UDP;
  ip_header->saddr = INADDR_ANY;
  ip_header->daddr = server.sin_addr.s_addr;

  struct udphdr *udp_header;

  udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));
  udp_header->source = htons(8888);
  udp_header->dest = htons(7777);
  udp_header->check = 0;
  udp_header->len = htons(strlen(message) - 1 + sizeof(struct udphdr));

  int header =
      sendto(sock, packet, SIZE, 0, (struct sockaddr *)&server, lenght);

  if (header < 0) {
    perror("error send to server");
    exit(1);
  }

  printf("Sended to server %d\n", header);

  while (1) {
    header =
        recvfrom(sock, packet, SIZE, 0, (struct sockaddr *)&server, &lenght);

    if (header < 0) {
      perror("error recieve");
      exit(1);
    }

    struct iphdr *ip_header = (struct iphdr *)packet;
    udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));

    if (ntohs(udp_header->dest) == 8888) {
      struct in_addr saddr;
      saddr.s_addr = ip_header->saddr;

      printf("Server IP: %s\n", inet_ntoa(saddr));
      printf("Source PORT: %d\n", ntohs(udp_header->source));
      printf("Destination PORT: %d\n", ntohs(udp_header->dest));
      printf("lenght: %d\n", ntohs(udp_header->len));
      printf("Received packet: %d\n", header);
      printf("Modified message response: %s\n",
             packet + sizeof(struct iphdr) + sizeof(struct udphdr));
      break;
    }
  }
  free(packet);
}