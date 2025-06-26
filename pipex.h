/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:27 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/06/26 18:08:39 by zel-ghab         ###   ########.fr       */
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
int		read_infile(char *s);
int		write_outfile(char *s);
void	instructions(char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

/*----------------  cmd1.c  ---------------*/
void	cmd1(int fd_infile, char **argv, int *pipefd, char **envp);
void	cmd2(int fd_outfile, char **argv, int *pipefd, char **envp);

/*----------------  utils.c  ---------------*/
char	*get_path(char **envp);
char	*find_cmd_path(char **cmd, char **envp);
void	free_split(char ***split);
void	close_all(int fd_infile, int fd_outfile, int *pipefd);

#endif
