/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:47:43 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/20 10:49:17 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_paths(char *cmd, char **envp)
{
	int	i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*path_cmd(char **cmds)
{
	DIR	*dir;

	dir = opendir(cmds[0]);
	if (dir)
	{
		g_global.status = 126;
		closedir(dir);
		return (NULL);
	}
	else if (access(cmds[0], F_OK) == 0)
	{
		if (access(cmds[0], X_OK) != 0)
		{
			g_global.status = 126;
			return (NULL);
		}
		g_global.status = 127;
		return (ft_strdup(cmds[0]));
	}
	g_global.status = 127;
	return (NULL);
}

char	*ft_get_pathcmd(char **cmds, char **paths)
{
	char	*cmd;
	char	*join;
	int		i;

	i = 0;
	if (ft_strchr(cmds[0], '/'))
		return (path_cmd(cmds));
	else
	{
		while (paths[i])
		{
			if (strchr(cmds[0], '.'))
				return (g_global.status = 127, NULL);
			join = ft_strjoin(paths[i], "/");
			cmd = ft_strjoin(join, cmds[0]);
			if (!cmd)
				return (free(join), NULL);
			if (access(cmd, F_OK) == 0)
				return (free(join), cmd);
			free(cmd);
			free(join);
			i++;
		}
	}
	return (NULL);
}

int	check_cmd(t_pip *p, char *cmd, char **envp, t_cmd *cmds)
{
	p->cmd = NULL;
	if (if_builtins(cmd))
		return (0);
	p->path = ft_get_paths(cmd, envp);
	if (p->path == NULL)
		return (ft_error("No such file or directory", 127, NULL, cmds->cmd));
	p->paths = ft_split(p->path, ':');
	p->cmd = ft_get_pathcmd(cmds->args, p->paths);
	if (!p->cmd)
		return (cmd_error(p, cmds));
	free_double(p->paths);
	return (0);
}

void	check_pipe(t_pip *p, t_cmd *cmds)
{
	int		count;
	t_cmd	*tmp;
	t_cmd	*temp;

	count = 0;
	tmp = cmds;
	temp = cmds;
	p->std_in = 0;
	p->std_out = 1;
	cmds->in = 0;
	cmds->out = 1; 
	while (tmp)
	{
		tmp->i = count;
		tmp = tmp->next;
		count++;
	}
	signal(SIGINT, ff);
	if (count > 1)
	{
		p->nb_cmd = count;
		multiple_pipe(p, temp, count);
	}
	else
		single_cmd(p, cmds);
}
