#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>

#define SERVER_FIFO "seqnum_sv"
#define CLIENT_FIFO_TEMPLATE "seqnum_cl.%ld"
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE)+20)

struct request {
	pid_t pid;
	int seqLen;
};

struct response {
int seqnum;
};

typedef struct response response;
typedef struct request request;

void main(int argc,char *argv[]){

	int serverFD,dummyFD,clientFD;
	char clientFifo[CLIENT_FIFO_NAME_LEN];
	response resp;
	request req;
	int seqnum = 0;

	 umask(0);
	if(mkfifo(SERVER_FIFO,S_IRUSR | S_IWUSR | S_IWGRP ) == -1){
		printf("error in creating server_fifo\n");
		return ;
	}

	serverFD = open(SERVER_FIFO,O_RDONLY);
	if(serverFD==-1){
		printf("error in opening read end of fifo\n");
		return;
	}

	dummyFD = open(SERVER_FIFO,O_WRONLY);
	if(dummyFD==-1){
		printf("error in opening write end of server_fifo\n");
		return;
	}

	if(signal(SIGPIPE,SIG_IGN) == SIG_ERR){
		printf("ERROR\n");
		return;
	}
	while(1)
	{
		if(read(serverFD,&req,sizeof(request))!=sizeof(request)){
			fprintf(stderr, "error reading request; discarding\n");
		}
		/* Open client FIFO */

		snprintf(clientFifo,CLIENT_FIFO_NAME_LEN,CLIENT_FIFO_TEMPLATE,(long) req.pid);

		clientFD = open(clientFifo,O_WRONLY);
		if(clientFD==-1){
			printf("error in creating client fifo\n");
			continue;
		}

		/* Send response and close FIFO */
		resp.seqnum = seqnum;
		if (write(clientFD, &resp, sizeof(struct response))!= sizeof(struct response))
		fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
		if (close(clientFD) == -1)
		return;
		seqnum += req.seqLen;
	}
}

