/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:47:48 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 11:02:26 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && (del) != NULL)
	{
		(del)(lst->content);
		free(lst);
	}
}

/* int main()
{
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;
	t_list *temp;


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

	node2->next = node4;
	temp = node1;
	ft_lstdelone(node3, free);
	while(temp)
	{
		printf("\n%s\n",  (char *)temp->content);
		temp = temp->next;
	}
} */