/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:26 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 15:22:15 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_loop(char **env, char **res, char *cmd, int j)
{
	int		i;
	int		k;
	char	*m;

	i = 0;
	k = 0;
	(void)j;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			m = get_name(env[i]);
		else
			m = ft_strdup(env[i]);
		if (ft_strcmp(m, cmd) != 0)
			res[k++] = ft_strdup(env[i]);
		i++;
		free(m);
	}
	res[k] = NULL;
}

void	ft_unset_export(t_pip *p, char *cmd, int i, int j)
{
	char	**res;

	if (!p->export)
		return ;
	while (cmd[j] && cmd[j] != '=')
		j++;
	while (p->export[i])
		i++;
	if (i == 1)
	{
		res = NULL;
		free_double(p->export);
		p->export = res;
		g_global.status = 0;
		return ;
	}
	res = malloc(sizeof (char *) * i);
	if (!res)
		return ;
	unset_loop(p->export, res, cmd, j);
	free_double(p->export);
	p->export = res;
	g_global.status = 0;
}

void	ft_unset_help(t_pip *p, char *cmd, int i, int j)
{
	char	**res;

	if (if_valid_name(cmd, 0))
	{
		if (!p->envp)
			return ;
		if (!if_exist(p, cmd))
		{
			g_global.status = 0;
			return ;
		}
		while (cmd[j] && cmd[j] != '=')
			j++;
		while (p->envp[i])
			i++;
		res = malloc(sizeof (char *) * i);
		if (!res)
			return ;
		unset_loop(p->envp, res, cmd, j);
		free_double(p->envp);
		p->envp = res;
		g_global.status = 0;
	}
	else
		ft_error("not a valid identifier", 1, cmd, "unset");
}

void	ft_unset(t_pip *p, t_cmd *cmds)
{
	int	i;

	i = 1;
	g_global.status = 0;
	if (cmds->args[1])
	{
		while (cmds->args[i])
		{
			if (ft_strchr(cmds->args[i], '=') || ft_strchr(cmds->args[i], '+'))
				ft_error("not a valid identifier", 1, cmds->args[i], "unset");
			else
				ft_unset_help(p, cmds->args[i], 0, 0);
			i++;
		}
	}
}
