/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:24 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/17 10:43:44 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.h"

static void executeFromFile(const char *av)
{
	AbstractVm		avm;

	if (avm.readFile(av) && avm.syntaxParser())
		avm.execute();
}

static void executeFromCin(void)
{
	AbstractVm		avm;

	if (avm.readFile(std::cin) && avm.syntaxParser())
		avm.execute();
}

int 		main(int argc, char **argv)
{
	if (argc == 2)
		executeFromFile( *(argv + 1) );
	else if (argc == 1)
		executeFromCin();

	return (1);
}
