/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:30:11 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 11:04:23 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

/* int main()
{
	int fd = open("test.txt", O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (1);
	char str[] = "Hello, World!";
	ft_putstr_fd(str, fd);
	close(fd);
} */