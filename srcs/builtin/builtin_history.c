/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:08:07 by cyfermie          #+#    #+#             */
/*   Updated: 2018/09/18 20:43:56 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

void    builtin_history(char **argv, char **envp, t_exec *exe)
{



    exit(0);
}


/*
    go faire une fonction au debut du main qui check et cree si necessaire le dossier .42sh
    avec dedans le fichier .42sh_alias et le fichier .42sh_history dont je m'occupe

    la fonction add_history() doit aussi ajouter l'element au fichier, faut 
    que je fasse ca en premier je pense.
    J'ouvre le fichier history une seule fois au lancement du shell, puis
    je peux l'editer avec add_history() pour ajouter et history --clear /-d n pour delete des trucs.
    Le fichier sera proprement ferme par le_free_datas_and_history().

    il peut y avoir 0 argument ou 1 mais pas plus

    sans aucun argument, go afficher lhistorique avecun numero a cote,
    l'element le plus vieux cest 1

    si ya 1 argument et qu'il est numerique, go afficher les n derniers elements 
    (avec leur vrai numero, genre si n == 4 les numeros c'est pas 1 a 4 
    (sauf si ya que 4 elements lol) )

    --clear ca supprime tout l'historique (la liste chainee + le fichier qui est vidé)

    -d n  delete l'element numero n (dans la liste et dans le fichier)

*/