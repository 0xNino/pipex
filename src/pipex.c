/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:07:12 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/10 10:37:04 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("Error\nPipe error\n", errno);
		pid1 = fork();
		if (pid1 < 0)
			error("Error\nFork error\n", errno);
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else if (argc > 5)
		error("Error\nToo many arguments\n", 1);
	else if (argc < 5)
		error("Error\nToo few arguments\n", 1);
	return (0);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		error(NULL, errno);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile == -1)
		error(NULL, errno);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close (fd[1]);
	execute(argv[3], envp);
}
