#ifndef __WRAPPER__
#define __WRAPPER__

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


// Process Calls
pid_t Fork(void);

ssize_t Read(int fd, void *buf, size_t nbyte);

ssize_t Write(int fd, void *buf, size_t nbyte);

int Pipe(int fd[2]);

pid_t Wait(int *stat_loc);

pid_t Waitpid(pid_t pid, int *stat_loc, int options);


// File Manipulation Calls
int Open(const char *path, int oflag);

int Close(int fildes);

// Networking Calls
int Connect(int socket, const struct sockaddr *address, socklen_t address_len);

int Bind(int socket, const struct sockaddr *address, socklen_t address_len);

int Listen(int socket, int backlog);

int Accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);


#endif
