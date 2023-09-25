/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:08:14 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/22 20:35:40 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_handledes(char **dst)
{
	int		j;
	char	*s;

	j = 0;
	s = NULL;
	while (dst[j])
	{
		s = ft_strjoin_get(s, dst[j]);
		j++;
	}
	return (s);
}

void	str_handle(char **dst, t_list **lst)
{
	char	**tmp;
	int		temp;
	char	*dest;

	temp = 0;
	dest = str_handledes(dst);
	tmp = split_string(dest, ' ');
	if (!tmp)
		ft_add_back_token(lst, ft_new_token("", 1));
	if (tmp)
		while (tmp[temp])
			ft_add_back_token(lst, ft_new_token(tmp[temp++], 0));
	free(dest);
	ft_free_str(tmp);
	ft_free_str(dst);
}
