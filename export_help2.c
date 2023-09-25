/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:00:50 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/27 15:53:23 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exist(t_pip *p, char *name)
{
	int		i;
	int		j;
	char	*n;
	char	*m;

	j = 0;
	i = 0;
	if (ft_strchr(name, '='))
		n = get_name(name);
	else
		n = ft_strdup(name);
	if (ft_strchr(n, '+'))
		n = without_plus(n);
	while (p->envp[i])
	{
		if (ft_strchr(p->envp[i], '='))
			m = get_name(p->envp[i]);
		else
			m = ft_strdup(p->envp[i]);
		if (ft_strcmp(m, n) == 0)
			return (free(m), free(n), 1);
		i++;
		free(m);
	}
	return (free(n), 0);
}

int	if_valid_name(char *name, int i)
{
	if (ft_strlen(name) == 0)
		return (0);
	if (name[0] == '=')
		return (0);
	if (name[0] >= '0' && name[0] <= '9')
		return (0);
	if (ft_strlen(name) == 1 && name[0] == '+')
		return (0);
	while (name[i])
	{
		if (name[i] == '+' && name[i + 1] != '\0')
			return (0);
		if ((name[i] >= 0 && name[i] < 43)
			|| (name[i] >= 44 && name[i] <= 47)
			|| (name[i] >= 58 && name [i] < 61)
			|| (name[i] > 61 && name [i] < 65)
			|| (name[i] > 90 && name [i] < 95)
			|| (name[i] > 122 && name [i] <= 127)
			|| name[i] == 96)
			return (0);
		i++;
	}
	return (1);
}

void	replace_value(t_pip *p, char *new, int i, int j)
{
	char	*unset;

	unset = NULL;
	unset = ft_strdup(p->envp[j]);
	if (ft_strchr(unset, '='))
	{
		ft_unset_env(p, unset, 0);
		unset = ft_strjoin_get(unset, &new[i + 2]);
		ft_export_help(p, unset);
		free(unset);
	}
	else
	{
		ft_unset_env(p, unset, 0);
		unset = ft_strjoin_get(unset, "=");
		unset = ft_strjoin_get(unset, &new[i + 2]);
		ft_export_help(p, unset);
		free(unset);
	}
}

void	replace_new_value(t_pip *p, char *new, int i, int j)
{
	char	*n;
	char	*m;

	m = NULL;
	if (ft_strchr(new, '='))
		n = get_name(new);
	else
		n = ft_strdup(new);
	if (ft_strchr(n, '+'))
		n = without_plus(n);
	while (new[i] != '+')
		i++;
	while (p->envp[j])
	{
		if (ft_strchr(p->envp[j], '='))
			m = get_name(p->envp[j]);
		else
			m = ft_strdup(p->envp[j]);
		if (ft_strcmp(m, n) == 0)
			replace_value(p, new, i, j);
		j++;
		free(m);
	}
	free(n);
}
