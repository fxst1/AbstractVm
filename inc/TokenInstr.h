#ifndef TOKENINSTR_H
# define TOKENINSTR_H
# include "lexerparser.h"
# include <map>
# include <string.h>

class				Instr;
class				AbstractVm;

class				TokenInstr: public lexerparser::LexerToken<Instr*, AbstractVm&>
{
	private:

		static const std::string					names[11];
		const std::string							_name;

	public:

		TokenInstr(void);
		TokenInstr(const std::string &name);
		TokenInstr(const TokenInstr &src);
		~TokenInstr(void);

		TokenInstr			&operator=(const TokenInstr &rhs);

		lexerparser::LexerToken<Instr*, AbstractVm&>
							*nud(lexerparser::Parser<Instr*, AbstractVm&> &parser, AbstractVm &data);
		Instr				*execute(AbstractVm &data);

		size_t				compare(const std::string &s);
		size_t				compare(const char *s);
		size_t				length(void);

		std::string			toString(void) const;
		lexerparser::LexerToken<Instr*, AbstractVm&>
							*clone(const char *s);
};

#endif
