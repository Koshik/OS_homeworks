#include <stdlib.h>
#include <unistd.h>
#include "bufio.h"

int main()
{
	size_t buf_size = 2048;
	struct buf_t* buf = buf_new(buf_size);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	ssize_t w, r;
	while((r = buf_fill(STDIN_FILENO, buf, buf_size)) > 0 &&
			(w = buf_flush(STDOUT_FILENO, buf, buf->size)) > 0);

	buf_free(buf);
	if (w == -1 || r == -1)
		exit(EXIT_FAILURE);
	return 0;
}
