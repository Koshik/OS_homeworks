#include "helpers.h"


int main()
{
	const ssize_t buf_size = 4096;

	char buf[buf_size];
	int rd = 0;
	do
	{
		rd = read_(STDIN_FILENO, buf, buf_size);
		if (rd == 0)
			exit(EXIT_FAILURE);
		write_(STDOUT_FILENO, buf, rd);
	} while (1);

	return 0;
}

