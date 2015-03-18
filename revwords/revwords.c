#include "helpers.h"

int main()
{
	const int buf_size = 8192;
	char buf[buf_size];
	char rev_word[buf_size];

	size_t read_off = 0;
	ssize_t rd = 0; 
	int w_sz = 0;
	int i;
	int word_start;
	do
	{
		rd = read_until(STDIN_FILENO, buf + read_off, buf_size - read_off, ' ');
		i = 0;
		while (i < read_off + rd) {
			rev_word[buf_size - 1] = ' ';
			w_sz = 1;
			word_start = buf_size - 1;
			while ((buf[i] != ' ') && (i < read_off + rd))
			{
				rev_word[buf_size - w_sz - 1] = buf[i];
				i = i + 1;
				w_sz = w_sz + 1;
				word_start = word_start - 1;
			}
			if (buf[i] == ' ') {
				write_(STDOUT_FILENO, rev_word + buf_size - w_sz, w_sz);
				i = i + 1;
			}
		}
		int j = 0;
		int l = (i - w_sz) + 1;
		while (j + l < read_off + rd)
		{
			buf[j] = buf[j + l];
			j = j + 1;
		}
		read_off = j;

	} while (rd > 0);

	write_(STDOUT_FILENO, rev_word + buf_size - w_sz, w_sz - 1);

	return 0;
}
