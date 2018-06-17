#ifndef TOKENDOUBLE_H
# define TOKENDOUBLE_H
# include "lexerparser.h"
# include <map>
# include <string.h>

# define REGEXDOUBLE "^[+-]?[0-9]+[.][0-9]+"

class				TokenDouble: public lexerparser::LexerToken<Instr*, AbstractVm&>
{
	private:

		std::string			_value;

	public:

		TokenDouble(void);
		TokenDouble(const std::string &value);
		TokenDouble(const TokenNumber &src);
		~TokenDouble(void);

		TokenDouble			&operator=(const TokenDouble &rhs);

		lexerparser::LexerToken<Instr*, AbstractVm&>
							*nud(lexerparser::Parser<Instr*, AbstractVm&> &parser, AbstractVm &data);
		lexerparser::LexerToken<Instr*, AbstractVm&>
							*led(lexerparser::Parser<Instr*, AbstractVm&> &parser, lexerparser::LexerToken<Instr*, AbstractVm&> *left, AbstractVm &data);
		Instr				*execute(AbstractVm &data);
		lexerparser::LexerToken<Instr*, AbstractVm&>
							*clone(const char *s);
};

#endif
