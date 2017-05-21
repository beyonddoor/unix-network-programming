#include	"unp.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		buf[MAXLINE];

again:
	while ( (n = read(sockfd, buf, MAXLINE)) > 0)
	{
		Writen(sockfd, buf, n);
		// print_str(buf, n);
	}

	//~ if eq 0, normally closed
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}


void print_str(const char* msg, int n)
{
	Writen(1, msg, n);
	// char buf[1024];
	// while(n > 0) 
	// {
	// 	strncpy(buf, msg, n);
	// 	buf[n] = '\0';
	// 	printf("%s", buf);
	// 	n -= 1024;
	// }
}