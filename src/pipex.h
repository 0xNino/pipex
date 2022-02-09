/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:48:20 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/09 15:54:21 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_view {
	int		argc;
	char	**argv;
	char	**envp;
	int		infile;
	int		outfile;
	int		cmd_count;
}	t_view;

int			pipex(int argc, char **argv, char **envp);
void		child_process(char **argv, char **envp, int *fd);
void		parent_process(char **argv, char **envp, int *fd);
void		error(char *error, int code);
void		execute(char *argv, char **envp);
char		*get_path(char *cmd, char **envp);
void		init_view(int argc, char **argv, char **envp, t_view *pipex);
void		open_files(t_view *pipex);
void		close_files(t_view *pipex);
static void	execute_cmd(int infile, char *cmd, t_view *pipex, int index);
void		process_args(t_view *pipex);

#endif