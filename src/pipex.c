/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:07:12 by 0xNino            #+#    #+#             */
/*   Updated: 2022/01/28 16:57:22 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
	}
	else if (argc > 5)
	{
		ft_putstr_fd("Error\nToo many arguments\n", 1);
		exit(1);
	}
	else if (argc < 5)
	{
		ft_putstr_fd("Error\nToo few arguments\n", 1);
		exit (1);
	}
	return (pipex.status);
}
