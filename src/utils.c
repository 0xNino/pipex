/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:22:39 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/01 19:54:39 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{	
	char	**cmd;

	printf("start execute\n");
	cmd = ft_split(argv, ' ');
	get_path(cmd[0], envp);
}

void	get_path(char *cmd, char **envp)
{
	char	**path_array;
//	char	*path;
	int		i;

	cmd = NULL;
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path_array = ft_split(envp[i], ':');
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
