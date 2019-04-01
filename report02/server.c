#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

void str_echo(int sockfd)
{
	int n;
	char buf[1024];
	while(1)
	{
		if( n = read(sockfd, buf, 1024) == 0)
			return;
		write(sockfd, buf, 1024);
	}
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;

}

int main()
{
	int sfd,cfd;
	struct sockaddr_in servaddr;
	pid_t pid;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd < 0)
	{
		perror("socket error!");
		exit(0);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7777);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));

	listen(sfd, 10);
	
	signal(SIGCHLD, sig_chld);

	while(1)
	{
		cfd = accept(sfd, (struct sockaddr*)NULL, NULL);
		printf("one connect, fd = %d\n", cfd);
		pid = fork();
		if(pid == 0)
		{
			close(sfd);
			str_echo(cfd);
			exit(0);
		}
		close(cfd);		
	}
	return 0;
}
