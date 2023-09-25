/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:19:43 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/22 20:02:39 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] == s2[i] && (s1[i] && s2[i]) != '\0')
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_front_token(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_add_back_token(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->back = tmp;
	}
}

void	dup_fd(t_pip *p, t_cmd *cmds)
{
	if (cmds->files[0])
	{
		if (p->sign_in == -1)
		{
			p->std_in = dup(0);
			dup2(cmds->in, 0);
			close(cmds->in);
		}
		if (p->sign_out == -1)
		{
			p->std_out = dup(1);
			dup2(cmds->out, 1);
			close(cmds->out);
		}
	}
}
