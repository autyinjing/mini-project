/*
 * =====================================================================================
 *
 *       Filename:  ping.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年09月21日 21时12分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#ifdef __cplusplus

extern "C" 
{

#endif

#ifndef PING_H
#define PING_H

/* -------------------- head file -------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

/* -------------------- global var ------------------- */

extern struct sockaddr_in dst_addr;    /* 目的IP地址 */
extern struct sockaddr_in recv_addr;   /* 本地IP地址 */
extern struct timeval tvrecv;          /* 发送与接收的时间间隔 */
extern char icmp_pkt[1024];  /* 发送的ICMP数据报缓冲区 */
extern char recv_pkt[1024];  /* 接收缓冲区 */
extern int sockfd;      /* 要发送的socket描述符 */
extern int bytes;       /* 发送的数据报长度 */
extern int nsend_pkt;   /* 实际发送字节数 */
extern int nrecv_pkt;   /* 实际接收的字节数 */
extern pid_t pid;       /* 用进程pid作为标记 */

/* -------------- function declaration --------------- */

extern void statistics();       /* 打印统计信息 */
extern int in_checksum(unsigned short *buf, int size);  /* 计算ICMP报头的校验和 */
extern int pack(int send_pkt);  /* 打包 */
extern void *send_ping();       /* 发送数据报 */
extern int unpack(char *recv_pkt, int size);    /* 拆包 */
extern void *recv_ping();       /* 接收数据报 */
extern void tv_sub(struct timeval *out, struct timeval *in);    /* 计算时间差 */

#endif

#ifdef __cplusplus

}

#endif
