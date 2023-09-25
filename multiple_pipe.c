/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:50:02 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 11:57:51 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_pipe(t_cmd *cmds, t_pip *p)
{
	t_cmd	*tmp;
	int		fd[2];

	tmp = cmds;
	p->if_here_doc = 0;
	p->std_in = dup(0);
	p->std_out = dup(1);
	while (tmp->next)
	{
		if (pipe(fd) == -1)
			ft_error("pipe error", 1, NULL, NULL);
		tmp->pipe_out = fd[1];
		tmp->next->pipe_in = fd[0];
		tmp = tmp->next;
	}
}

void	get_status(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_global.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (status == SIGINT || status == SIGQUIT)
				g_global.status = 128 + WTERMSIG(status);
		}
	}
}

void	parent_wait(t_cmd *cmds, t_pip *p)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
		if (tmp->in != 0)
			close(tmp->in);
		if (tmp->out != 1)
			close(tmp->out);
		tmp = tmp->next;
	}
	close_fd(p);
	if (p->if_here_doc)
		unlink("/tmp/tmp_file");
	get_status();
}

int	ft_child(t_pip *p, char *cmd, t_cmd *cmds, t_cmd *tmp)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		return (return_error(p, cmds));
	if (child == 0)
	{
		if (g_global.status != 0)
			exit(g_global.status);
		ft_closefd(tmp, p->i);
		if (p->i == 0)
			first_dup(p, cmds);
		else if (p->i == p->nb_cmd - 1)
			last_dup(p, cmds);
		else
			midle_dup(p, cmds);
		exec_cmd(p, cmd, cmds);
		if (if_builtins(cmd))
			exit(g_global.status);
	}
	return (0);
}

void	multiple_pipe(t_pip *p, t_cmd *cmds, int i)
{
	int		count;
	t_cmd	*tmp;

	tmp = cmds;
	count = i;
	creat_pipe(cmds, p);
	p->i = -1;
	while (count > 0 && cmds)
	{
		init_p(p, cmds);
		p->i++;
		if (cmds->cmd && g_global.status == 0)
		{
			g_global.status = check_cmd(p, cmds->cmd, p->envp, cmds);
			if (ft_child(p, cmds->cmd, cmds, tmp))
				break ;
			if (!if_builtins(cmds->cmd) && p->cmd)
				free(p->cmd);
		}
		count--;
		cmds = cmds->next;
	}
	parent_wait(tmp, p);
}
