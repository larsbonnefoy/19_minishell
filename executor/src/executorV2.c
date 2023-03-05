#include"../../src/minishell.h"
#include <fcntl.h>
#include <unistd.h>

int change_in_redir(t_simple_cmds *cmd, int fd_in);
int change_out_redir(t_simple_cmds *cmd, int fd_out);
int get_in_redir(t_simple_cmds *cmd,int fd_in);
int is_infile(t_lexer *redirection);
int get_out_redir(t_simple_cmds *cmd, int pipe_write);
int is_outfile(t_lexer *redirections);
int process(int fd_in, int fd_pipe[2], t_simple_cmds *cmd, char **env);
void wait_for_process(t_simple_cmds *cmd);

void executorV2(t_simple_cmds *cmd, char **env)
{
	t_simple_cmds *curr;
	int fd_pipe[2];
	int fd_in;
	
	curr = cmd;
	while (curr)
	{
		if (curr->redirections)
			lexer_print_list(&curr->redirections);
		if (curr->next != NULL)
		{
			if (pipe(fd_pipe) == -1)
				return ;
		}
		fd_in = process(fd_in, fd_pipe, cmd, env);
		curr=curr->next;
	}
	wait_for_process(cmd);

}

int process(int fd_in, int fd_pipe[2], t_simple_cmds *cmd, char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->next != NULL || is_outfile(cmd->redirections)) //we need to change the output of the cmd to the write end of pipe (fd_pipe[1]) or to the outfile if there is one
			change_out_redir(cmd, fd_pipe[1]);	
		ft_execve(cmd->av, env);
	}
	return (fd_pipe[0]); //return the  read-end of the pipe in order to have the input for the next file
}

int change_out_redir(t_simple_cmds *cmd, int fd_out)
{

	fd_out = get_out_redir(cmd, fd_out);
	if (fd_out == -1)
		return -1;
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int change_in_redir(t_simple_cmds *cmd, int fd_in)
{
	int new_fd_in;

	new_fd_in = get_in_redir(cmd, fd_in);
	if (new_fd_in == -1)
		return -1;
	close(fd_in);
	dup2(new_fd_in, STDIN_FILENO);
	close(new_fd_in);
	return (0);
}

void wait_for_process(t_simple_cmds *cmd)
{
	t_simple_cmds *curr;

	curr = cmd;
	while (curr)
	{
		waitpid(curr->pid, NULL, 0);
		curr=curr->next;
	}
}

/*
 * opens fd of infile redirection if there is one, else returns fd_in
 *
*/
int get_in_redir(t_simple_cmds *cmd,int fd_in)
{
	t_lexer *redir; 	
	int 	fd;
	char 	*file;
	
	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == LOWER)
			file = redir->str;
		redir=redir->next;
	}
	fd = open(file, O_RDONLY);
	printf("opened %s on %d\n", file, fd);
	if (fd == -1)
		perror("open");
	return (fd);
}

int get_out_redir(t_simple_cmds *cmd, int pipe_write)
{
	t_lexer *redir;
	int fd;
	char *file;
	int  token;

	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == GREATER || redir->token == D_GREATER)
		{
			file = redir->str;
			token = redir->token;
		}	
		redir = redir->next;
	}
	if (file)
	{ 
		if (token == D_GREATER)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		printf("fd_pipe[1] = %d\n", fd);
		close(pipe_write);
		return (fd);
	}
	return (pipe_write);
}

int is_infile(t_lexer *redirection)
{
	t_lexer *curr_redir;
	curr_redir = redirection;
	while (curr_redir)
	{
		if (curr_redir->token == LOWER)
			return (1);
		curr_redir=curr_redir->next;
	}
	return (0);
}

int is_outfile(t_lexer *redirections)
{
	t_lexer *curr_redir;
	curr_redir = redirections;
	while (curr_redir)
	{
		if (curr_redir->token == D_GREATER || curr_redir->token == GREATER)
			return (1);
		curr_redir=curr_redir->next;

	}
	return (0);
}

void print_input_cmd_line(char **av)
{
	int i;

	i = 0;
	while (av[i] != NULL)
	{
		printf("[%s] ", av[i]);
		i++;
	}
	printf("\n");
}
