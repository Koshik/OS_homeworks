#include "helpers.h"
#include <string.h>

const size_t buf_sz = 4096;

int main(int argc, char * const argv[])
{
	if (argc < 2)
		exit(EXIT_FAILURE);

	char* args[argc + 1];
	size_t i;
	for (i = 1; i < argc; i++)
	{
		args[i - 1] = argv[i];
	}

	char arg[buf_sz];
	args[argc - 1] = arg;
	args[argc] = 0;

	size_t off = 0;
	char buf[buf_sz];
	int rd;
	int sp;

	while(1)
	{
		rd = read_(STDIN_FILENO, buf + off, buf_sz - off);
		if (rd == 0 && off == 0)
			exit(EXIT_SUCCESS);

		i = 0;
		while (buf[i] != '\n')
		{
			arg[i] = buf[i];
			i++;
		}
		arg[i] = 0;
		memmove(buf, buf + (i + 1), off + rd - i - 1);
		off = off + rd - i - 1;
		
		sp = spawn(args[0], args);
		if (sp == 0)
			write_(STDOUT_FILENO, arg, i);
	}

	return 0;
}

