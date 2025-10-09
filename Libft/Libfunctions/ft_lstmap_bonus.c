/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:57:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 17:10:29 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = ((f)(lst->content));
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/* static void	*put_a(void *content)
{
	char	*str;

	str = (char *)content;
	str[0] = 'a';
	return (str);
}
static void	free_content(void *content)
{
	free(content);
}
int	main(void)
{
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;
	t_list *node5;
	t_list *temp;
	t_list *new_list;
	t_list *head = NULL;

	node1 = ft_lstnew(ft_strdup("1"));
	node2 = ft_lstnew(ft_strdup("2"));
	node3 = ft_lstnew(ft_strdup("3"));
	node4 = ft_lstnew(ft_strdup("4"));
	node5 = ft_lstnew(ft_strdup("5"));

	ft_lstadd_back(&head, node1);
	ft_lstadd_back(&head, node2);
	ft_lstadd_back(&head, node3);
	ft_lstadd_back(&head, node4);
	ft_lstadd_back(&head, node5);

	temp = head;
	printf("Lista original:\n");
	while (temp)
	{
		printf("\n%s\n", (char *)temp->content);
		temp = temp->next;
	}

	new_list = ft_lstmap(head, put_a, free_content);

	temp = new_list;
	printf("Lista nova:\n");
	while (temp)
	{
		printf("\n%s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&new_list, free);
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);

} */