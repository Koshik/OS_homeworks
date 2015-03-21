#include "helpers.h"
#include <string.h>

int main(int args, char const* argv[])
{
	if (args < 2)
		exit(EXIT_FAILURE);
	char const* word = argv[1];
	int len = strlen(word);
	char w[len];

	size_t buf_size = 4096;
	char buf[buf_size];
	char write_buf[buf_size];
	size_t w_i = 0;

	ssize_t rd = 0;
	size_t start = 0;

	do 
	{
		ssize_t rd = read_(STDIN_FILENO, buf + start, buf_size - start);
		if (rd == 0) 
		{

			write_(STDOUT_FILENO, write_buf, w_i);
			write_(STDOUT_FILENO, buf, start);	
			exit(EXIT_SUCCESS);
		}
		int i = 0;
		while (i + len  - 1 < rd + start)
		{
			int k = 0;
			for (; k < len && k < rd + start; k++)
			{
				w[k] = buf[i + k];
			}
			while (k < len)
			{
				w[k] = 0;
				k++;
			}
			if (strcmp(w, word) != 0)
			{
				write_buf[w_i] = buf[i];
				w_i++;
				i++;
				if (w_i == buf_size)
				{
					write_(STDOUT_FILENO, write_buf, buf_size);
					w_i = 0;
				}
			} else
			{
				i = i + len;
			}
		}
		int j = 0;
		while (i < rd + start)
		{
			buf[j] = buf[i];
			i++;
			j++;
		}
		start = j;
	} while (1);


	return 0;
}
