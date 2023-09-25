/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:16:20 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 16:09:57 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*without_plus(char *name)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(name));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (name[i])
	{
		if (name[i] != '+')
		{
			ret[j] = name[i];
			j++;
		}
		i++;
	}
	free(name);
	return (ret);
}

int	count_plus(char *name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (name[i])
	{
		if (name[i] == '+')
			count++;
		i++;
	}
	return (count);
}

char	*check_egal(t_pip *p, char *new)
{
	char	*name;

	if (ft_strchr(new, '='))
		name = get_name(new);
	else
	{
		p->flag_env = 1;
		name = ft_strdup(new);
	}
	return (name);
}

char	*check_name(char *name)
{
	char	*n;

	n = NULL;
	if (ft_strchr(name, '='))
		n = get_name(name);
	else
		n = ft_strdup(name);
	return (n);
}

void	add_new_without_plus(t_pip *p, char *new)
{
	char	*join;
	int		i;

	join = NULL;
	i = 0;
	join = remove_plus(new);
	ft_export_help(p, join);
	free(join);
}
