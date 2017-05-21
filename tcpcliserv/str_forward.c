#include	"unp.h"


void
str_forward(int cltFd)
{
	long		arg1, arg2;
	ssize_t		n;
	char		line[MAXLINE];
	const char* host = "14.215.177.37";
	int 		port = 80;
	int 		flags = 0;

	int					sockfd;
	struct sockaddr_in	servaddr;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	printf("processing %d...\n", cltFd);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	Inet_pton(AF_INET, host, &servaddr.sin_addr);
	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	flags = Fcntl(sockfd, F_GETFL, 0);
	if(Fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		printf("sockfd Fcntl\n");
	}
	if(Fcntl(cltFd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		printf("cltFd Fcntl\n"); 
	}

	for ( ; ; ) 
	{
		//从clt读取，写入到svr

		/* connection closed by other end */
		if((n = read(cltFd, line, MAXLINE)) == 0)
		{
			err_quit("client disconnect\n");
		}
		else if(n == EWOULDBLOCK)
		{
			err_msg("client EWOULDBLOCK...\n");
		}
		else if(n > 0)
		{
			printf("read from client...\n");
			Writen(1, line, n);
			Writen(sockfd, line, n);
		}
		else
		{
			// printf("read client %d.\n", n);
			// sleep(1);
		}

		
		if((n = read(sockfd, line, MAXLINE)) == 0)
		{
			err_quit("server disconnect\n");
		}
		else if(n == EWOULDBLOCK)
		{
			err_msg("server EWOULDBLOCK...\n");
		}
		else if(n > 0)
		{
			printf("read from server, len=%d.\n", n);
			// Writen(1, line, n);
			Writen(cltFd, line, n);
		}
		else
		{
			// printf("read server %d.\n", n);
			// sleep(1);
		}
	}
}
