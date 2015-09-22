/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年09月22日 10时33分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "ping.h"

int main(int argc, char *argv[])
{
	int size = 50 * 1024;
        int errno = -1;
        int ttl = 64;
        void *tret;
        pthread_t send_id, recv_id;
        struct in_addr ipv4_addr;
        struct hostent *ipv4_host;
        struct protoent *protocol = NULL;

        if (argc < 2)
        {
                printf("usage: ./ping <host>\n");
                return -1;
        }
        if ((protocol = getprotobyname("icmp")) == NULL)
        {
                printf("unknow protocol\n");
                return -1;
        }

        if ((sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0)
        {
                printf("socket fail\n");
                return -1;
        }
        setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
        setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
        setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        memset(&dst_addr, 0, sizeof(dst_addr));
        dst_addr.sin_family = AF_INET;
        errno = inet_aton(argv[1], &ipv4_addr);
        if (errno == 0) {
                ipv4_host = gethostbyname(argv[1]);
                if (NULL == ipv4_host)
                {
                        printf("connect: Invalid argument\n");
                        return -1;
                }
                memcpy(&(dst_addr.sin_addr), ipv4_host->h_addr, sizeof(struct in_addr));
        } else {
                memcpy(&(dst_addr.sin_addr), &(ipv4_addr.s_addr), sizeof(struct in_addr));
        }

        pid = getpid();
        printf("PING %s (%s) %d bytes of data.\n", argv[1], inet_ntoa(dst_addr.sin_addr), bytes);
        signal(SIGINT, statistics);

        errno = pthread_create(&send_id, NULL, send_ping, NULL);
        if (errno != 0)
        {
                printf("send_ping thread fail\n");
                return -1;
        }
        errno = pthread_create(&recv_id, NULL, recv_ping, NULL);
        if (errno != 0)
        {
                printf("recv_ping thread fail\n");
                return -1;
        }
        pthread_join(send_id, &tret);
        pthread_join(recv_id, &tret);

	return EXIT_SUCCESS;
}
