#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void	put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	put_num(long num, int base, int *len)
{
	char	*hexa = "0123456789abcdef";

	if (num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}	
	if (num >= base)
		put_num((num / base), base, len);
	*len += write(1, &hexa[num % base], 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len = 0;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				put_str(va_arg(ap, char *), &len);
			else if (*format == 'd')
				put_num((long)va_arg(ap, int), 10, &len);
			else if (*format == 'x')
				put_num((long)va_arg(ap, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}
