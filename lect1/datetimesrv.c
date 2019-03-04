#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char* gettime();

int main(char argc,char* argv[])
{
	int sfd,cfd;
	struct sockaddr_in serv_addr;
	char buf[1024];

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd < 0)
	{
		perror("socket error!");
		exit(0);
	}
	
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(13);
	
	bind(sfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr));

	listen(sfd, 10);

	while(1)
	{
		cfd = accept(sfd, (struct sockaddr*)NULL, NULL);
		strcpy(buf,gettime());
		write(cfd, buf, strlen(buf));
		close(cfd);
	}
	return 0;
}

char* gettime()
{
  time_t timep;
  struct tm *p;
	char buf[1024];
  time(&timep);
  p = gmtime(&timep);
	snprintf(buf, 1024, "%d-%02d-%02d %02d:%02d:%02d\n", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday,   8+p->tm_hour, p->tm_min, p->tm_sec);
	return buf;
}

