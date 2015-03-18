#include "helpers.h"

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

	

