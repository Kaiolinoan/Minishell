/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:15:44 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 16:17:55 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(char i, va_list args)
{
	int	count;

	count = 0;
	if (i == 'c')
		count += print_char(va_arg(args, int));
	else if (i == 's')
		count += print_str(va_arg(args, const char *));
	else if (i == 'p')
		count += print_pointer(va_arg(args, void *));
	else if (i == 'd')
		count += print_numbers(va_arg(args, int));
	else if (i == 'i')
		count += print_numbers(va_arg(args, int));
	else if (i == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	else if (i == 'x')
		count += print_hex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (i == 'X')
		count += print_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (i == '%')
		count += print_char('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	size_t	i;

	if (!str)
		return (-1);
	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == '%')
		{
			count += check_type(str[++i], args);
			if (count == -1)
				return (-1);
			if (str[i + 1] == '\0')
				return (count);
			i++;
		}
		count += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	char c = 'A';
	char *str = "isso e uma string";
	unsigned int unb = 42;
	int nb = -42;

	printf("\ntexto normal:\n"); 
	int r1 = ft_printf("%s\n", str);
	printf("caracteres impressos: %d\n", r1);
	 r1 =    printf("%s\n", str);
	 printf("caracteres impressos: %d\n", r1);
	   
	printf("\nstring:\n");
	int r2 = ft_printf("%s\n",str);
	printf("caracteres impressos: %d\n", r2);
	r2 = printf("%s\n",str);
	printf("caracteres impressos: %d\n", r2);


	printf("\nchar:\n");
	int r3 = ft_printf("%c%c%c\n",c, 'a', '3');
	printf("caracteres impressos: %d\n", r3);
	r3 = printf("%c%c%c\n",c, 'a', '3');
	printf("caracteres impressos: %d\n", r3);


	printf("\ndecimal:\n");
	int r4 = ft_printf("%d\n", nb);
	printf("caracteres impressos: %d\n", r4);
	r4 = printf("%d\n", nb);
	printf("caracteres impressos: %d\n", r4);

	printf("\ninteger:\n");
	int r5 = ft_printf("%i\n", nb);
	printf("caracteres impressos: %d\n", r5);
	r5 = printf("%i\n", nb);
	printf("caracteres impressos: %d\n", r5);

	printf("\nunsigned:\n");
	int r6 = ft_printf("%u\n", unb);
	printf("caracteres impressos: %d\n", r6);
	r6 = printf("%u\n", unb);
	printf("caracteres impressos: %d\n", r6);

	printf("\nlow hexadecimal:\n");
	int r7 = ft_printf("%x\n", nb);
	printf("caracteres impressos: %d\n", r7);
	r7 = printf("%x\n", nb);
	printf("caracteres impressos: %d\n", r7);

	printf("\nupper decimal:\n");
	int r8 = ft_printf("%X\n", nb);
	printf("caracteres impressos: %d\n", r8);
	r8 = printf("%X\n", nb);
	printf("caracteres impressos: %d\n", r8);

	printf("\npointer:\n");
	int r9 = ft_printf("%p\n", &str);
	printf("caracteres impressos: %d\n", r9);
	r9 = printf("%p\n", &str);
	printf("caracteres impressos: %d\n", r9);

	printf("\nteste %%:\n");
	int r10 = ft_printf("%%\n");
	printf("caracteres impressos: %d\n", r10);
	r10 = printf("%%\n");
	printf("caracteres impressos: %d\n", r10);
} */