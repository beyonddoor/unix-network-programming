#include <stdio.h>
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>

#include	<errno.h>		/* ANSI C header file */

#define SA struct sockaddr


void err_exit(char* msg)
{
    int no = errno;
    char* etext = strerror(no);
    char errbuf[1024];
    printf("errno %d\n", no);
    if(etext)
    {
        snprintf(errbuf, 1024, "%s", etext);
        printf("%s: %s", msg, errbuf);
        // printf("%s: %x", msg, etext);
    }
    exit(1);
}

void info(char* msg)
{
    printf(msg);
    printf("\n");
    // flush();
}

int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in addr;
    char buf[1024];
    int n=0;

    info(strerror(97));

    if(argc < 3) 
    {
        info("usage: addr port");
        return 1;
    }

    if((sockfd = socket(9999, SOCK_STREAM, 0)) < 0)
    {
        err_exit("socket");
    }
    info("socket.");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    if(inet_pton(AF_INET, argv[1], &addr.sin_addr) < 0)
    {
        err_exit("inet_pton");
    }
    
    info("inet_pton.");

    if(connect(sockfd, (SA*)&addr, sizeof(addr)) <0 )
    {
        err_exit("connect");
    }

    info("connect.");

    sprintf(buf, "GET / HTTP/1.0\n\n\n\n");
    write(sockfd, buf, 1024);
    info("write.");

    while((n = read(sockfd, buf, 1024)) >0)
    {
        buf[n] = 0;
        puts(buf);
    }
    err_exit("read");
    // info("read.");
}