/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:49:56 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/25 13:22:23 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//fd[0] == read
//fd[1] == write
/*
	dup2 va permettre a notre process d'ecrire dans le fd du pipe au lieu d'ecrire dans l'entree standard
 */
int main(int argc, char **argv)
{
	int fd[2];
	if (pipe(fd) == -1)
		return (-1);
	int pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (pid1 == 0)
	{
		//Child process 1
		dup2(fd[1], STDOUT_FILENO);
		//After dup2, fd[1] (write part of pipe) is also opened on the std output
		//THIS MEANS THAT WE CAN CLOSE FD[1] AS THE STD OUTPUT IS GOING TO WRITE TO THE PIPE| 
		close(fd[1]);
		close(fd[0]);
		execlp("ping", "ping", "-c", "2", "google.com", NULL);
	}
	waitpid(pid1, NULL, 0);
	int pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round-trip", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
}


