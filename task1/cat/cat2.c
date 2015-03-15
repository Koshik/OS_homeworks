#include "helpers.h"


int main()
{
    const ssize_t buf_size = 1;

	char buf[buf_size];
	int readed = 0;
	do
	{
		readed = read_(STDIN_FILENO, buf, buf_size);
		write_(STDOUT_FILENO, buf, readed);
	} while (readed > 0);
	
	return 0;
}


