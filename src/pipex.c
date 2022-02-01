/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:07:12 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/01 19:54:14 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;

	printf("start pipex\n");
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("Error\nPipe error\n");
		pid1 = fork();
		if (pid1 < 0)
			error("Error\nFork error\n");
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else if (argc > 5)
		error("Error\nToo many arguments\n");
	else if (argc < 5)
		error("Error\nToo few arguments\n");
	return (0);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	file_in;

	printf("start child process\n");
	file_in = open(argv[1], O_RDONLY, 0777);
	printf("file_in = %d\n", file_in);
	if (file_in == -1)
		error("Error\nOpen file_in error\n");
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);
	close(fd[0]);
	printf("test\n");
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	file_out;

	printf("start parent_process\n");
	file_out = open(argv[4], O_CREAT, O_WRONLY, O_TRUNC, 0777);
	if (file_out == -1)
		error("Error\nOpen file_out error\n");
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	close (fd[1]);
	execute(argv[3], envp);
}
