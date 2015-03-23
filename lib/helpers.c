#include "helpers.h"
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

ssize_t read_(int fd, void* buf, size_t count)
{
	ssize_t rd = 0;
	int cnt = 1;
	while (count - rd > 0 && cnt > 0) 
	{
		cnt = read(fd, buf + rd, count - rd);
		if (cnt < 0)
			exit(EXIT_FAILURE);
		rd = rd + cnt;
	}
	return rd;
}

ssize_t write_(int fd, const void *buf, size_t count)
{
	int cnt = 0;
	ssize_t writed = 0;
	do
	{
		cnt = write(fd, buf + writed, count - writed);
		if (cnt < 0)
			exit(EXIT_FAILURE);
		writed = writed + cnt;
	} while (count - writed > 0);
	
	return writed;
}

ssize_t read_until(int fd, void* buf, size_t count, char delimeter)
{
	ssize_t rd = 0;
	int cnt = 1;
	char* ch_buf = (char*) buf;
	while (count - rd > 0 && cnt > 0)
	{
		cnt = read(fd, ch_buf + rd, count - rd);
		if (cnt < 0)
			exit(EXIT_FAILURE);

		int i = rd;
		while (i < rd + cnt)
		{
			if (ch_buf[i] == delimeter)
				return rd + cnt;
			i = i + 1;
		}
		rd = rd + cnt;
	}
	return rd;
}

	
int spawn(const char *file, char* const argv[])
{
    pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		int dev_null = open("/dev/null", O_WRONLY);
		if (dev_null < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}


		int dup_out = dup2(dev_null, STDOUT_FILENO);
		int dup_err = dup2(dev_null, STDERR_FILENO);
		if (dup_out < 0 || dup_err < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		
		int cl = close(dev_null);
		if (cl == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}

		execvp(file, argv);
		perror("exec");
		exit(EXIT_FAILURE);
	} else
	{
		int status;
		pid_t w = waitpid(pid, &status, 0);
		if (w < 0)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
		else
		{
			perror("child");
			exit(EXIT_FAILURE);
		}		
	}
}
