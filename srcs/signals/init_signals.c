/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 15:23:51 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/20 13:41:39 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
	int sigemptyset(sigset_t +set);
	int sigfillset(sigset_t *set);
	int sigadset(sigset_t *set, int sig);
	int sigdelset(sigset_t *set, int sig);
	int sigprocmask(int how, const sigset_t *nset, sigset_t *oset);
	int sigaction(int signum, const struct sigaction *new, struct sigaction *old);

	struct sigaction
	{
		void	(*handler)(int);
		sigset_t	sa_mask;
		int			sa_flag;
	};


*/

/*
**	Initialize some handlers functions for different signals.
*/

// NOT DONE YET
void	init_signals(void)
{
	struct sigaction	new;
	unsigned int		i;
	const int			sig_array[27] = 
	{
		SIGHUP, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGEMT, SIGFPE, \
		SIGBUS, SIGSEGV, SIGSYS, SIGPIPE, SIGALRM, SIGTERM, SIGURG, \
		SIGTSTP, SIGCONT, SIGCHLD, SIGTTIN, SIGTTOU, SIGIO, SIGXCPU, \
		SIGXFSZ, SIGVTALRM, SIGPROF, SIGINFO, SIGUSR1, SIGUSR2
	};

	new.sa_flags = 0;

	new.sa_handler = &(handle_sigint);
	sigfillset(&(new.sa_mask));
	sigaction(SIGINT, &new, NULL);



	// others

	new.sa_handler = &(handle_useless_signals);
	
	i = 0;
	while (i < (sizeof(sig_array) / sizeof(sig_array[0])))
	{
		sigaction(sig_array[i], &new, NULL);
		++i;
	}

}


/*
	WINCH : on le catch uniquement quand aucune commande est en running,
	sinon il est juste bloque/mask


	POUR LES "je touche pas", les recevoir ca casse les tcaps.
	Pour regler ca je peux catch le sig, si une commande est en running je la kill,
	puis jerestore les tcaps, puis restaurer le default handler du sig en question, puis envoyer (raise())
	le sig au 42sh. Est-ce utile ? En tout cas c'est pas un gros travail supplementaire.


	HUP je touche pas
	TRAP je touche pas


	INT
	{
		si une commande run (on le sait avec une variable globale),
		la commande est kill. Sinon on coupe l'edition de ligne pour
		en lancer une neuve.)
	}




*/
