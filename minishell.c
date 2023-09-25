/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:54 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/22 19:48:24 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_shlvl(char *join, char *it, char **split)
{
	free(join);
	free(it);
	free_double(split);
}

void	upgrad_shlvl(t_pip *p, int i)
{
	char	**split;
	int		lvl;
	char	*join;
	char	*it;

	join = NULL;
	if (!get_env("SHLVL", p))
	{
		ft_export_help(p, "SHLVL=1");
		return ;
	}
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], "SHLVL", 5) == 0)
			break ;
		i++;
	}
	split = ft_split(p->envp[i], '=');
	lvl = ft_atoi(split[1]);
	lvl++;
	it = ft_itoa(lvl);
	join = ft_strjoin("SHLVL=", it);
	ft_export_help(p, join);
	free_shlvl(join, it, split);
}

void	ft_exec(t_pip *p, char **envp, t_cmd *cmds)
{
	if (ft_strcmp(p->cmd, "./minishell") == 0)
	{
		upgrad_shlvl(p, 0);
	}
	else
	{
		execve(p->cmd, cmds->args, envp);
	}
}
