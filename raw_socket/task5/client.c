#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
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
#define MAC_ADDRESSES 6

unsigned short calculateChecksum(unsigned short *header, int length) {
  unsigned int sum = 0;
  unsigned short checksum = 0;

  while (length > 1) {
    sum += *header++;
    length -= 2;
  }

  if (length == 1) {
    *(unsigned char *)&checksum = *(unsigned char *)header;
    sum += checksum;
  }

  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  checksum = ~sum;

  return checksum;
}

int main() {
  unsigned char source_mac_address[MAC_ADDRESSES] = {0x12, 0xdd, 0x11,
                                                     0xaa, 0x66, 0x32};
  unsigned char destination_mac_address[MAC_ADDRESSES] = {0x55, 0x77, 0x88,
                                                          0x99, 0xed, 0x98};

  int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  if (sock < 0) {
    perror("create socket error");
    exit(1);
  }

  struct sockaddr_ll server;

  server.sll_family = AF_PACKET;
  server.sll_ifindex = if_nametoindex("eth0");

  server.sll_halen = MAC_ADDRESSES;
  memmove((void *)(server.sll_addr), (void *)destination_mac_address,
          MAC_ADDRESSES);

  int flag = 1;
  if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) < 0) {
    perror("erroe setsockopt");
    exit(1);
  }

  socklen_t lenght = sizeof(struct sockaddr_ll);

  char *message = calloc(SIZE - lenght, sizeof(char));
  message = "Hello!\n";

  char *packet = calloc(SIZE, sizeof(char));
  memmove(packet + sizeof(struct ether_header) + sizeof(struct iphdr) +
              sizeof(struct udphdr),
          message, strlen(message) - 1);

  struct ether_header *ether_header;

  ether_header = (struct ether_header *)packet;

  for (int i = 0; i < MAC_ADDRESSES; i++) {
    ether_header->ether_shost[i] = source_mac_address[i];
    ether_header->ether_dhost[i] = destination_mac_address[i];
  }

  ether_header->ether_type = htons(ETHERTYPE_IP);

  struct iphdr *ip_header;

  ip_header = (struct iphdr *)(packet + sizeof(struct ether_header));
  ip_header->ihl = 5;
  ip_header->version = 4;
  ip_header->tos = 0;
  ip_header->id = htonl(601);
  ip_header->frag_off = 0;
  ip_header->ttl = 255;
  ip_header->protocol = IPPROTO_UDP;
  ip_header->saddr = inet_addr("192.168.0.3");
  ip_header->daddr = inet_addr("192.168.0.2");
  ip_header->tot_len =
      htons(ip_header->ihl * 4 + sizeof(struct udphdr) + strlen(message) - 1);
  ip_header->check = 0;
  ip_header->check =
      calculateChecksum((unsigned short *)ip_header, ip_header->ihl * 4);

  struct udphdr *udp_header;

  udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) +
                                 sizeof(struct iphdr));
  udp_header->source = htons(7777);
  udp_header->dest = htons(8888);
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

    ether_header = (struct ether_header *)packet;
    unsigned short mac_flag = 1;
    for (int i = 0; i < MAC_ADDRESSES; i++) {
      if (ether_header->ether_dhost[i] != source_mac_address[i]) {
        mac_flag = 0;
        break;
      }
    }

    if (mac_flag == 0) {
      continue;
    }

    ip_header = (struct iphdr *)(packet + sizeof(struct ether_header));
    struct in_addr addr;
    addr.s_addr = ip_header->daddr;
    if (strcmp("192.168.0.3", inet_ntoa(addr)) != 0) {
      continue;
    }

    udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) +
                                   ip_header->ihl * 4);

    if (ntohs(udp_header->dest) != 8888) {
      continue;
    }

    else if (ntohs(udp_header->dest) == 8888) {
      struct in_addr saddr;
      saddr.s_addr = ip_header->saddr;

      printf("Server IP: %s\n", inet_ntoa(saddr));
      printf("Source PORT: %d\n", ntohs(udp_header->source));
      printf("Destination PORT: %d\n", ntohs(udp_header->dest));
      printf("lenght: %d\n", ntohs(udp_header->len));
      printf("Received packet: %d\n", header);
      printf("Modified message response: %s\n",
             (packet + sizeof(struct ether_header) + ip_header->ihl * 4 +
              sizeof(struct udphdr)));
      break;
    }
  }
  free(packet);
}