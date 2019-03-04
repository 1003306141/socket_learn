#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(char argc,char* argv[])
{
	int cfd;
	struct sockaddr_in serv_addr;
	char buf[1024];

	if(argc != 2)
	{
		printf("usage: ./datetimecli <ipaddress>\n");
		exit(0);
	}

	if( (cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
		exit(0);
	}	

	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(13);
	if( inet_pton(AF_INET,argv[1], &serv_addr.sin_addr) <= 0 )
	{
		perror("inet_pton error!");
		exit(0);
	}

	if( connect(cfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("connect error!");
		exit(0);
	}
	
	while(1)
	{
		int ret = read(cfd, buf, 1024);
		if(ret == 0)
			break;
		printf(buf);
	}
	
	close(cfd);
	return 0;
}


//132.163.97.2 success
