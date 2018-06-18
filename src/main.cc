/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:24 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/18 12:11:04 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.h"

static void executeFromFile(const char *av)
{
	AbstractVm		avm;

	if (avm.readFile(av))
	{
		if (avm.syntaxParser() && avm.syntaxLookExit())
			avm.execute();
		else
			std::cerr << "Cannot execute code" << std::endl;
	}
}

static void executeFromCin(void)
{
	AbstractVm		avm;

	if (avm.readFile(std::cin))
	{
		if (avm.syntaxParser() && avm.syntaxLookExit())
			avm.execute();
		else
			std::cerr << "Cannot execute code" << std::endl;
	}
}

int 		main(int argc, char **argv)
{
	if (argc == 2)
		executeFromFile( *(argv + 1) );
	else if (argc == 1)
		executeFromCin();

	return (1);
}
