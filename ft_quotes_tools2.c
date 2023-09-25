/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:05:54 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/22 20:09:06 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_arg(char *str, int *i)
{
	int		len;
	int		y;

	y = (*i);
	len = 0;
	while (!is_quote(str[*i]) && str[*i])
	{
		(*i)++;
		len++;
	}
	return (ft_substr(&str[y], 0, len));
}

char	*ret_quote(char *str, int *i)
{
	int		y;
	int		len;
	char	c;

	y = (*i);
	len = 0;
	c = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != c)
	{
		(*i)++;
		len++;
	}
	if (str[*i] == c)
	{
		(*i)++;
		len++;
	}
	return (ft_substr(&str[y], 0, len + 1));
}

t_list	*get_lexed_list(char **dst, t_pip *p)
{
	t_list	*new;
	t_list	*after;

	new = NULL;
	new = ft_lex(dst);
	if (!new)
		return (ft_free_token(new), NULL);
	if (if_error(new))
		return (ft_free_token(new), NULL);
	after = ft_env2(&new, p->envp);
	if (!after)
		return (ft_free_token(new), ft_free_token(after), NULL);
	if (ft_quotes(&after))
		return (ft_free_token(new), ft_free_token(after), NULL);
	ft_free_token(new);
	return (after);
}
