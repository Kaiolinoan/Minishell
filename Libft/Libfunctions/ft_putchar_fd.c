/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:48:41 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 11:01:47 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int main(void)
{
	int fd = open("test.txt", O_WRONLY);
	char str[] = "Hello, World!";
	for (size_t  i = 0; i < ft_strlen(str); i++)
		ft_putchar_fd(str[i], fd);
	close(fd);
} */