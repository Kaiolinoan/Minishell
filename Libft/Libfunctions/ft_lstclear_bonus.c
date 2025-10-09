/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:44:49 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 10:54:44 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		ft_lstdelone(temp, (del));
		temp = next;
	}
	*lst = NULL;
}

/* int main ()
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*node4;
	t_list	*temp;

	node1 = malloc(sizeof(t_list));
	node2 = malloc(sizeof(t_list));
	node3 = malloc(sizeof(t_list));
	node4 = malloc(sizeof(t_list));
	node1->content = ft_strdup("1");
	node2->content = ft_strdup("2");
	node3->content = ft_strdup("3");
	node4->content = ft_strdup("4");
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;;
	temp = node1;
	printf("Antes\n");
	while(temp)
	{
		printf("\n%s\n",  (char *)temp->content);
		temp = temp->next;
	}
	temp = node1;
	ft_lstclear(&node1, free);
	printf("Depois:\n");
	if (node1 == NULL)
		printf("Limpeza realizada com sucesso\n");
	else
		printf("Erro ao limpar");
}
 */