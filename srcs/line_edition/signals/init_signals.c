/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 15:23:51 by cfermier          #+#    #+#             */
/*   Updated: 2018/09/19 20:01:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

/*
**	Initialize some handlers functions for different signals.
*/

// NOT DONE YET
void	init_signals(void)
{

}



/*
    POUR LES "je touche pas", les recevoir ca casse les tcaps.
    Pour regler ca je peux catch le sig, restore les tcaps, puis
    restaurer le default handler du sig en question, puis envoyer (raise())
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
