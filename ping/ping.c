/*
 * =====================================================================================
 *
 *       Filename:  ping.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年09月22日 10时03分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

/* -------------------- global var -------------------- */

#include "ping.h"

struct sockaddr_in dst_addr;
struct sockaddr_in recv_addr;
struct timeval tvrecv;
char icmp_pkt[1024] = { 0 };
char recv_pkt[1024] = { 0 };
int sockfd = 0;
int bytes = 56;
int nsend_pkt = 0;
int nrecv_pkt = 0;
pid_t pid;

/* ------------------- function ---------------------- */

void statistics()
{
        printf("\n--- %s ping statistics ---\n", inet_ntoa(dst_addr.sin_addr));
        printf("%d packets transmitted, %d recvived, %.3f%c packet loss\n",
                        nsend_pkt, nrecv_pkt, (double)100*(nsend_pkt - nrecv_pkt)/nsend_pkt, '%');
        close(sockfd);

        exit(0);
}

int in_checksum(unsigned short *buf, int size)
{
        int nleft = size;
        int sum = 0;
        unsigned short *w = buf;
        unsigned short ans = 0;

        while (nleft > 1)
        {
                sum += *w++;
                nleft -= 2;
        }
        if (nleft == 1)
        {
                *(unsigned char *)(&ans) = *(unsigned char *)w;
                sum += ans;
        }
        sum = (sum >> 16) + (sum & 0xFFFF);
        sum += (sum >> 16);
        ans = ~sum;

        return ans;
}

int pack(int send_pkt)
{
        struct icmp *pkt = (struct icmp *)icmp_pkt;
        struct timeval *time = NULL;

        pkt->icmp_type = ICMP_ECHO;
        pkt->icmp_cksum = 0;
        pkt->icmp_seq = htons(nsend_pkt);
        pkt->icmp_id = pid;
        time = (struct timeval *)pkt->icmp_data;
        gettimeofday(time, NULL);
        pkt->icmp_cksum = in_checksum((unsigned short *)pkt, bytes + 8);

        return bytes + 8;
}

void *send_ping()
{
        int send_bytes = 0;
        int ret = -1;

        while ( 1 )
        {
                nsend_pkt++;
                send_bytes = pack(nsend_pkt);

                ret = sendto(sockfd, icmp_pkt, send_bytes, 0,
                                (struct sockaddr *)&dst_addr, sizeof(dst_addr));
                if (ret == -1)
                {
                        printf("send fail\n");
                        sleep(1);
                        continue;
                }
                sleep(1);
        }
}

void tv_sub(struct timeval *out, struct timeval *in)
{
        if ((out->tv_usec -= in->tv_usec) < 0)
        {
                --out->tv_sec;
                out->tv_usec += 1000000;
        }

        out->tv_sec -= in->tv_sec;
}

int unpack(char *recv_pkt, int size)
{
        struct iphdr *ip = NULL;
        int iphdrlen;
        struct icmp *icmp;
        struct timeval *tvsend;
        double rtt;

        ip = (struct iphdr *)recv_pkt;
        iphdrlen = ip->ihl << 2;
        icmp = (struct icmp *)(recv_pkt + iphdrlen);

        size -= iphdrlen;
        if (size < 8)
        {
                printf("ICMP size is less than 8\n");
                return -1;
        }

        if ((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid)) {
                tvsend = (struct timeval *)icmp->icmp_data;
                tv_sub(&tvrecv, tvsend);
                rtt = tvrecv.tv_sec * 1000 + (double)tvrecv.tv_usec / (double)1000;
                printf("%d byte from %s: icmp_seq = %d ttl=%d rtt=%.3fms\n",
                                size, inet_ntoa(recv_addr.sin_addr), ntohs(icmp->icmp_seq), ip->ttl, rtt);
        } else {
                return -1;
        }

        return 0;
}

void *recv_ping()
{
        fd_set rd_set;
        struct timeval time;
        time.tv_sec = 5;
        time.tv_usec = 0;
        int ret = 0, nread = 0, recv_len = 0;

        recv_len = sizeof(recv_addr);
        while ( 1 )
        {
                FD_ZERO(&rd_set);
                FD_SET(sockfd, &rd_set);
                ret = select(sockfd + 1, &rd_set, NULL, NULL, &time);
                if (ret <= 0) {
                        continue;
                } else if (FD_ISSET(sockfd, &rd_set)) {
                        nread = recvfrom(sockfd, recv_pkt, sizeof(recv_pkt), 0,
                                        (struct sockaddr *)&recv_addr, (socklen_t *)&recv_len);
                        if (nread < 0)
                                continue;
                        gettimeofday(&tvrecv, NULL);

                        if (unpack(recv_pkt, nread) == -1)
                                continue;
                        nrecv_pkt++;
                }
        }
}
