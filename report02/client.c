#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void str_cli(int sockfd)
{
	char buf[1024];
	while( fgets(buf, 1024, stdin) != NULL )
	{
		write(sockfd, buf, 1024);
		if(read(sockfd, buf, 1024) == 0)
			return;
		fputs(buf,stdout);
	}
}

int main()
{
	int cfd;
	struct sockaddr_in clieaddr;
	
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	clieaddr.sin_family = AF_INET;
	clieaddr.sin_port = htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &clieaddr.sin_addr.s_addr);
	
	connect(cfd, (struct sockaddr*)&clieaddr, sizeof(struct sockaddr));

	str_cli(cfd);	
	
	return 0;
}
