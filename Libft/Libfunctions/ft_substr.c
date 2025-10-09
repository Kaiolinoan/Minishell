/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:37:17 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 17:07:47 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*sub;

	if (s == NULL || *s == '\0' || start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	count = 0;
	while (count < len && s[start + count])
		count++;
	sub = (char *)malloc((count + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, &s[start], count + 1);
	return (sub);
}
/* 
int main()
{
	char *s1 = ft_substr("eu vou copiar esta string", 8, 6);
	printf("Teste 1: \"%s\"\n", s1);
	free(s1);

	char *s2 = ft_substr("inicio", 0, 3);
	printf("Teste 2: \"%s\"\n", s2);
	free(s2);

	char *s3 = ft_substr("final", 3, 10);
	printf("Teste 3: \"%s\"\n", s3);
	free(s3);

	char *s4 = ft_substr("abc", 3, 2);
	printf("Teste 4: \"%s\"\n", s4);
	free(s4);

	char *s5 = ft_substr("1", 42, 42000000);
	printf("Teste 5: \"%s\"\n", s5);
	free(s5);

	char *s6 = ft_substr("abcde", 2, 0);
	printf("Teste 6: \"%s\"\n", s6);
	free(s6);

	char *s7 = ft_substr("", 0, 5);
	printf("Teste 7: \"%s\"\n", s7);
	free(s7);
} */
