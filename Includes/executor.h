/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 15:00:55 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <fcntl.h>
# include "minishell.h"

typedef struct s_heredoc
{
	char	*limiter;
	int		expand;
}	t_heredoc;

typedef struct s_filedes
{
	int	fd_pipe[2];
	int	fd_in;
	int	std_in;
	int	std_out;
}	t_fildes;

typedef struct s_envs
{
	char	***env;
	t_env	**l_env;
}	t_envs;

//executor
void	executor(t_simple_cmds *cmd, char ***env, t_env **l_env);
void	restore_fildes(t_fildes *fildes);
int		handle_redir(t_simple_cmds *cmd, t_fildes *fildes, t_env **l_env);
int		process(t_simple_cmds *cmd, t_fildes *fildes, t_envs *envs);
//exec_cmd.c
int		exec_alone_cmds(t_simple_cmds *cmd, t_fildes *fildes, t_envs *envs);
int		exec_pipe_cmds(t_simple_cmds *cmd, t_fildes *fildes, t_envs *envs);
//ft_execve
void	ft_execve(t_simple_cmds *cmd, char ***env, t_env **l_env);
int		is_s_built(char *func_name, int cmd_pid);
int		exec_s_built(char **av, char ***env, t_env **l_env, int self_built_nb);

//ft_execve_utils
int		ft_void(char **av, char ***env, t_env **l_env);

//out_redir.c
int		get_out_fd(t_simple_cmds *cmd, int pipe_write);
char	*get_out_file(t_simple_cmds *cmd);
int		get_out_token(t_simple_cmds *cmd, char *file);
int		has_outfile(t_lexer *redirections);
//in_redir.c
int		get_in_fd(t_simple_cmds *cmd, int fd_in, t_env **l_env);
int		has_infile(t_lexer *redirection);
//error.c
int		ft_perror(char *cmd_name, char *msg, int error);

//heredoc.c
int		ft_heredoc(char *limiter, int expand, t_env **l_env);
int		handle_heredoc(t_simple_cmds *cmd, int std_in, t_env **l_env);
#endif
