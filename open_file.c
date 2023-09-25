/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:12:39 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/23 10:42:13 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in_file(t_cmd *cmds, t_pip *p, char *file, char *type)
{
	p->sign_in = -1;
	if (ft_strlen(file) == 0)
		return (file_error(cmds, p, file));
	if (ft_strcmp(type, "R") == 0)
	{
		cmds->in = open(file, O_RDONLY);
		if (cmds->in < 0)
		{
			p->sign_in = 1;
			return (check_permission(file, 'r'));
		}
	}
	else if (ft_strcmp(type, "H") == 0)
	{
		p->if_here_doc = 1;
		ft_read_here_doc(cmds, p, file);
	}
	return (0);
}

int	open_out_file(t_cmd *cmds, t_pip *p, char *file, char *type)
{
	p->sign_out = -1;
	if (ft_strlen(file) == 0)
		return (file_error(cmds, p, file));
	if (ft_strcmp(type, "R") == 0)
	{
		cmds->out = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmds->out < 0)
		{
			p->sign_out = 1;
			return (check_permission(file, 'w'));
		}
	}
	else if (ft_strcmp(type, "H") == 0)
	{
		cmds->out = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (cmds->out < 0)
		{
			p->sign_out = 1;
			return (check_permission(file, 'w'));
		}
	}
	return (0);
}

static void	close_in(t_pip *p, t_cmd *cmds, int i)
{
	if (cmds->files[i + 1]
		&& ft_strcmp(cmds->type_file[i + 1], "in" ) == 0 && p->sign_in == -1)
		close(cmds->in);
	if (p->if_here_doc)
		unlink("/tmp/tmp_file");
}

static void	close_out(t_pip *p, t_cmd *cmds, int i)
{
	if (cmds->files[i + 1]
		&& ft_strcmp(cmds->type_file[i + 1], "out") == 0 && p->sign_out == -1)
		close(cmds->out);
}

int	open_files(t_pip *p, t_cmd *cmds, int i)
{
	if (cmds->files[0])
	{
		while (cmds->files[i])
		{
			if (ft_strcmp(cmds->type_file[i], "in") == 0)
			{
				g_global.status = open_in_file(cmds, p, cmds->files[i],
						cmds->type[i]);
				close_in(p, cmds, i);
				if (g_global.status != 0)
					return (g_global.status);
			}
			else if (ft_strcmp(cmds->type_file[i], "out") == 0)
			{
				g_global.status = open_out_file(cmds, p, cmds->files[i],
						cmds->type[i]);
				close_out(p, cmds, i);
				if (g_global.status != 0)
					return (g_global.status);
			}
			i++;
		}
	}
	return (0);
}
