/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:53 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 16:08:42 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**loop_help(t_pip *p, char *name, int i)
{
	char	**res;
	char	*m;
	int		k;

	k = 0;
	m = NULL;
	res = malloc(sizeof (char *) * i);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (p->envp[i])
	{
		m = check_name(p->envp[i]);
		if (ft_strcmp(m, name) != 0)
			res[k++] = ft_strdup(p->envp[i]);
		i++;
		free(m);
	}
	res[k] = NULL;
	return (res);
}

void	ft_unset_env(t_pip *p, char *cmd, int i)
{
	char	**res;
	char	*n;

	if (!p->envp)
		return ;
	n = check_name(cmd);
	while (p->envp[i])
		i++;
	res = loop_help(p, n, i);
	free_double(p->envp);
	free(n);
	p->envp = res;
}

void	add_to_env(t_pip *p, char *new, int i)
{
	char	**ret;

	if (if_exist(p, new))
	{
		if (ft_strchr(new, '='))
			ft_unset_env(p, new, 0);
		else
			return ;
	}
	while (p->envp[i])
		i++;
	ret = malloc(sizeof (char *) * (i + 2));
	if (ret == NULL)
		return ;
	i = 0;
	while (p->envp[i])
	{
		ret[i] = ft_strdup(p->envp[i]);
		i++;
	}
	ret[i++] = ft_strdup(new);
	ret[i] = NULL;
	free_double(p->envp);
	p->envp = ret;
}

int	add_export(t_pip *p, char *new, char *name, char **split)
{
	free_double(split);
	if (p->flag_env)
	{
		if (count_plus(name) > 0)
			return (free(name),
				ft_error("not a valid identifier", 1, new, "export"));
	}
	if (if_valid_name(name, 0))
	{
		if (count_plus(name) == 1)
		{
			if (if_exist(p, name))
				replace_new_value(p, new, 0, 0);
			else
				add_new_without_plus(p, new);
		}
		else
			add_to_env(p, new, 0);
	}
	else
		return (free(name),
			ft_error("not a valid identifier", 1, new, "export"));
	free(name);
	return (0);
}

int	ft_export_help(t_pip *p, char *new)
{
	char	*plus;
	char	**split;
	char	*name;

	split = ft_split(new, '=');
	name = NULL;
	p->flag_env = 0;
	if (!split[0])
		return (free_double(split),
			ft_error("not a valid identifier", 1, new, "export"));
	plus = ft_strchr(split[0], '+');
	if (split[1])
		name = get_name(new);
	else
		name = check_egal(p, new);
	if (plus && split[1])
	{
		if (count_plus(name) > 1 || name[0] == '+')
			return (free_double(split), free(name),
				ft_error("not a valid identifier", 1, new, "export"));
	}
	return (add_export(p, new, name, split));
	return (0);
}
