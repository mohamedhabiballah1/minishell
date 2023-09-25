/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:51:19 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/15 18:51:49 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_handled(char **dst, char *str)
{
	int		j;
	char	*s;
	char	*tmp;

	j = 0;
	s = NULL;
	while (dst[j])
	{
		if (is_quote(dst[j][0]))
		{
			tmp = ft_substr(dst[j], 1, ft_strlen(dst[j]) - 1);
			s = ft_strjoin_get(s, tmp);
			free(tmp);
		}
		else
			s = ft_strjoin_get(s, dst[j]);
		j++;
	}
	free(str);
	ft_free_str(dst);
	return (s);
}

char	*split_str(char *str, char **env)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char *) * (calc_word(str) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			dst[j++] = ret_quote(str, &i);
		else
			dst[j++] = ret_arg(str, &i);
	}
	dst[j] = NULL;
	j = 0;
	while (dst[j])
	{
		dst[j] = replace_env_variables(dst[j], env);
		j++;
	}
	return (str_handled(dst, str));
}
