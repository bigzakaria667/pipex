/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:27 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/23 15:06:38 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "functions/ft_printf/ft_printf.h"
# include "functions/libft/libft.h"

/*----------------  pipex.c  ---------------*/
int	read_infile(char *s);
int	write_outfile(char *s);
int	main(int argc, char **argv, char **envp);

/*----------------  cmd1.c  ---------------*/
char	*get_path(char **envp);
char	*find_cmd_path(char **cmd, char **envp);
int	cmd1(int fd_infile, char **argv, int *pipefd, char **envp);

/*----------------  cmd1.c  ---------------*/
int	cmd2(int fd_outfile, char **argv, int *pipefd, char **envp);
#endif
