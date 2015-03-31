#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bufio.h"
#define DEBUG

struct buf_t *buf_new(size_t capacity)
{
	struct buf_t* b = malloc(sizeof(struct buf_t));	
	if (b == NULL)
		return NULL;
	b->buf = malloc(capacity);
	if (b->buf == NULL)
		return NULL;

	b->size = 0;
	b->capacity = capacity;
	return b;
}

void buf_free(struct buf_t* buf)
{
	free(buf->buf);
	free(buf);
}

size_t buf_capacity(struct buf_t* buf)
{
	return buf->capacity;
}

size_t buf_size(struct buf_t* buf)
{
	return buf->size;
}

void abort_if(int condition)
{
#ifdef DEBUG
	if (condition)
		abort();
#endif
}

ssize_t buf_fill(int fd, struct buf_t *buf, size_t required)
{
	abort_if(buf == NULL || buf->capacity < required);
	ssize_t r = 1;
	while(buf->size < required && r != 0)
	{
		r = read(fd, buf->buf + buf->size, buf->capacity - buf->size);
		if (r == -1)
			return -1;
		buf->size += r;
	}
	return buf->size;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required)
{
	abort_if(buf == NULL);
	ssize_t w = 1;
	size_t offset = 0;
	size_t size = buf->size;
	while (w != 0 && offset < required)
	{
		w = write(fd, buf->buf + offset, size - offset);
		if (w == -1)
			return -1;
		offset += w;
		buf->size -= w;
	}
	memmove(buf->buf, buf->buf + offset, size - offset);
	return offset;
}
