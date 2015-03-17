#include "helpers.h"

ssize_t read_(int fd, void* buf, size_t count)
{
	ssize_t readed = 0;
	int cnt = 1;
	while (count - readed > 0 && cnt > 0) 
	{
		cnt = read(fd, buf + readed, count - readed);
		if (cnt < 0)
			exit(EXIT_FAILURE);
		readed = readed + cnt;
	}
	return readed;
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

	

