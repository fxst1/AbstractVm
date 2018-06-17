#ifndef TOKENNUMBER_H
# define TOKENNUMBER_H
# include "lexerparser.h"
# include <map>
# include <string.h>

# define REGEXNUMBER "^([+-]?[0-9]+|0x[0-9A-Fa-f]+|0o[0-7]+|0b[01]+)"

class				TokenNumber: public lexerparser::LexerToken<Instr*, AbstractVm&>
{
	private:

		std::string			_value;

	public:

		TokenNumber(void);
		TokenNumber(const std::string &value);
		TokenNumber(const TokenNumber &src);
		~TokenNumber(void);

		TokenNumber			&operator=(const TokenNumber &rhs);

		lexerparser::LexerToken<Instr*, AbstractVm&>
							*nud(lexerparser::Parser<Instr*, AbstractVm&> &parser, AbstractVm &data);
		lexerparser::LexerToken<Instr*, AbstractVm&>
							*led(lexerparser::Parser<Instr*, AbstractVm&> &parser, lexerparser::LexerToken<Instr*, AbstractVm&> *left, AbstractVm &data);
		Instr				*execute(AbstractVm &data);
		lexerparser::LexerToken<Instr*, AbstractVm&>
							*clone(const char *s);
};

#endif
