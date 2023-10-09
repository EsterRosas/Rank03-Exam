#include <stdio.h>

int	has_eol(char *s)
{
	int i = 0;

	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

int	main(void)
{
	char	*s = "\n";
	int		val;

	val = has_eol(s);
	printf("val: %i\n", s, val);
	


	return (0);
}
