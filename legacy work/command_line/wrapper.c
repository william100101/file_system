#include "wrapper.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

//Process Calls
pid_t Fork(void){
	int pid;

  	pid = fork();
	
	if (pid < 0) { //error occurred 

		perror("Fork Failed");
		exit(-1);
	}

	return pid;
}

ssize_t Read(int fd, void *buf, size_t nbyte){
	ssize_t readValue;

	if((readValue = read(fd, buf, nbyte)) == -1){
		perror("read error");
		exit(-1);
	}
	else{
		return readValue;
	}
}

ssize_t Write(int fd, void *buf, size_t nbyte){
        ssize_t writeValue;

        if((writeValue = write(fd, buf, nbyte)) == -1){
                perror("write error");
                exit(-1);
        }
        else{
                return writeValue;
        }
}

int Pipe(int fd[2]){
	int pipeValue;

	if ((pipeValue = pipe(fd)) == -1){
		perror("Pipe failed");
		exit(-1);
	}
	else{
		return pipeValue;
	}
}

pid_t Wait(int *stat_loc){
	int waitValue;

	if ((waitValue = wait(stat_loc)) == -1){
		perror("Wait failed");
		exit(-1);
	}
	else{
		return waitValue;
	}
}

pid_t Waitpid(pid_t pid, int *stat_loc, int options){
	int waitpidValue;
	
	if ((waitpidValue = waitpid(pid, stat_loc, options)) == -1){
		perror("Waitpid failed");
		exit(-1);
	}
	else{
		return waitpidValue;
	}
}


//File Manipulation Calls
int Open(const char *path, int oflag){
	int openValue;

        if ((openValue = open(path, oflag)) < 0) {
                perror("open failed");
                exit(-1);
        }
        else{
                return openValue;
        }
}

int Close(int filedes){
	int closeValue;

	if ((closeValue = close(filedes)) < 0) {
                perror("close failed");
                exit(-1);
        }
        else{
                return closeValue;
        }
}


//Networking Calls
int Connect(int socket, const struct sockaddr *address, socklen_t address_len){
	int connectValue;

	if ((connectValue = connect(socket, address, address_len)) < 0) {
		perror("connect failed");
		exit(-1);
	}
	else{
		return connectValue;
	}
}

int Bind(int socket, const struct sockaddr *address, socklen_t address_len){
	int bindValue;
	
	if ((bindValue = bind(socket, address, address_len)) < 0) {
		perror("bind failed");
		exit(-1);
	}
	else{
		return bindValue;
	}
}

int Listen(int socket, int backlog){
	int listenValue;	

	if ((listenValue =  listen(socket, backlog)) < 0) {
		perror("listen failed");
		exit(-1);
	}
	else{
		return listenValue;
	}
}

int Accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len){
        int acceptValue;


	if ((acceptValue = accept(socket, address, address_len)) < 0){
		perror("ECHOD: accept failed\n");
			exit(-1);
	}
	else{
		return acceptValue;
	}

}
