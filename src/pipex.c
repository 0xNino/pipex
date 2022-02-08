/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:07:12 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/08 18:55:15 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_view	pipex;

	if (argc == 5)
	{
		init_view(argc, argv, envp, &pipex);
		process_args(&pipex);
		close_files(&pipex);
	}
	else if (argc > 5)
		error("Error\nToo many arguments\n", 1);
	else if (argc < 5)
		error("Error\nToo few arguments\n", 1);
	return (0);
}

void	process_args(t_view *pipex)
{
	int		i;
	char	*cmd;

	i = 0;
	while (i < pipex->cmd_count)
	{
		cmd = get_path(pipex->argv[i + 2], pipex->envp);
		if (access(cmd, X_OK) == 0)
			execute_cmd(pipex->infile, cmd, pipex, i);
		i++;
	}
}

static void	execute_cmd(int infile, char *cmd, t_view *pipex, int index)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		error("Error\nfork error", 1);
	else if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		if (index == 1)
			dup2(pipex->outfile, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execute(pipex->argv, pipex->envp);
	}
	waitpid(pid, NULL, 0);
	pipex->infile = fd[0];
	close(fd[1]);
}
/*
void	child_process(char **argv, char **envp, int *fd)
{
	int	file_in;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
		error("Error\nOpen file_in error\n", 1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	file_out;

	file_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_out == -1)
		error("Error\nOpen file_out error\n", 1);
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	close (fd[1]);
	execute(argv[3], envp);
}
*/