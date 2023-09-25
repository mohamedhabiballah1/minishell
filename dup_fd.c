/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:09:39 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/22 19:49:34 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(int read, int write)
{
	dup2(read, 0);
	dup2(write, 1);
}

void	first_dup(t_pip *p, t_cmd	*cmds)
{
	if (p->sign_out == -1)
		ft_dup(cmds->in, cmds->out);
	else
	{
		ft_dup(cmds->in, cmds->pipe_out);
		close(cmds->pipe_out);
	}
}

void	last_dup(t_pip *p, t_cmd *cmds)
{
	if (p->sign_in == -1)
		ft_dup(cmds->in, cmds->out);
	else
	{
		ft_dup(cmds->pipe_in, cmds->out);
		close(cmds->pipe_in);
	}
}

void	midle_dup(t_pip *p, t_cmd *cmds)
{
	if (p->sign_out == -1 && p->sign_in == -1)
		ft_dup(cmds->in, cmds->out);
	else
	{
		if (p->sign_out == -1)
		{
			ft_dup(cmds->pipe_in, cmds->out);
			close(cmds->pipe_in);
		}
		else if (p->sign_in == -1)
		{
			ft_dup(cmds->in, cmds->pipe_out);
			close(cmds->pipe_out);
		}
		else
		{
			ft_dup(cmds->pipe_in, cmds->pipe_out);
			close(cmds->pipe_in);
			close(cmds->pipe_out);
		}
	}
}
