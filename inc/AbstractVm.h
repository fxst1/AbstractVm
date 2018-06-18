#ifndef ABSTRACTVM_H
# define ABSTRACTVM_H
# include <fstream>
# include <list>
# include <limits>
# include <iostream>
# include <cmath>
# include "lexerparser.h"
# include "Operand.h"
# include "Instr.h"
# include "TokenInstr.h"
# include "TokenNumber.h"
# include "TokenDouble.h"
# include "TokenOperand.h"
# include "OperandFactory.h"

class			AbstractVm
{
	private:

		class	Parser: public lexerparser::Parser<Instr*, AbstractVm&>
		{
			public:

				Instr									*_instr;

				Parser(void);
				Parser(const Parser &src);
				~Parser(void);

				Parser			&operator=(const Parser &rhs);
		};

		typename std::list<Instr*>::iterator	_cursor;
		std::list<std::string>					_buffer;
		std::list<Instr*>						_lines;

	public:

		std::stack<const IOperand*>				_stack;
		Parser									_parser;
		bool									_stop;
		bool									_print_newline;

		AbstractVm(void);
		AbstractVm(const AbstractVm &src);
		~AbstractVm(void);

		AbstractVm			&operator=(const AbstractVm &rhs);

		bool				readFile(std::istream &file);
		bool				readFile(const std::string &filename);
		bool				syntaxParser(void);
		bool				syntaxLookExit(void);
		void				execute(void);

};

#endif
