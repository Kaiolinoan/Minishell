/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:20:31 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 11:02:15 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

/* int main ()
{
  t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;
	t_list *node5;
	t_list *head;

	node1 = ft_lstnew("Node 1");
	node2 = ft_lstnew("Node 2");
	node3 = ft_lstnew("Node 3");
	node4 = ft_lstnew("Node 4");
	node5 = ft_lstnew("Node 5");

	node1->next = node2;
	node1->next->next = node3;
	node1->next->next->next = node4;
	node1->next->next->next->next = node5;

	head = node1;
	while(node1 != NULL)
	{
		printf("\n%s\n",  (char *)node1->content);
		node1 = node1->next;
	}
	printf("Contagem de nodes: %d", ft_lstsize(head));
} */