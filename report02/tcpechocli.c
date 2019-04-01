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

int main(char argc,char* argv[])
{
	int cfd;
	struct sockaddr_in serv_addr;
	
	if(argc != 2)
	{
		printf("usage: ./tcpechocli <ipaddress>\n");
		exit(0);
	}
	
	if( (cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("%d\n",cfd);
		perror("socket error");
		exit(0);
	}
	
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(7777);
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr);
	
	connect(cfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr));

	str_cli(cfd);	
	
	return 0;
}
