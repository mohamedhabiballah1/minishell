/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:28:41 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 10:00:48 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_value(char *str, int i, int j)
{
	char	*ret;
	int		k;

	while (str[i] && str[i] != '=')
		i++;
	if (str[i + 1] == '\0')
		return (ft_strdup(""));
	i++;
	k = i;
	while (str[i++])
		j++;
	ret = malloc(sizeof(char) * j + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (str[k])
	{
		ret[i] = str[k];
		i++;
		k++;
	}
	ret[i] = '\0';
	return (ret);
}

void	print_qoutes(char *env)
{
	char	*name;
	char	*value;
	char	**split;

	split = ft_split(env, '=');
	if (split[0])
	{
		name = get_name(env);
		write(1, name, ft_strlen(name));
		write(1, "=\"", 2);
		free(name);
	}
	if (split[1])
	{
		value = get_value(env, 0, 0);
		write(1, value, ft_strlen(value));
		free(value);
	}
	write(1, "\"", 1);
	write (1, "\n", 1);
	free_double(split);
}

void	print_env(char *env)
{
	write (1, "declare -x ", 11);
	if (ft_strchr(env, '='))
	{
		print_qoutes(env);
	}
	else
	{
		write(1, env, ft_strlen(env));
		write (1, "\n", 1);
	}
}

void	print_export(t_pip *p)
{
	int	i;

	i = 0;
	if (p->envp)
	{
		while (p->envp[i])
		{
			print_env(p->envp[i]);
			i++;
		}
	}
	g_global.status = 0;
}
