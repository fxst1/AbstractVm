#ifndef TOKENOPERAND_H
# define TOKENOPERAND_H
# include "lexerparser.h"
# include "AbstractVm.h"
# include <string.h>

# define REGEXOPERAND_START "^([Ii]nt(8|16|32|)|[Ff]loat|[Dd]ouble)\\("
# define REGEXOPERAND_END "^\\)"

class				TokenOperand: public lexerparser::LexerToken<Instr*, AbstractVm&>
{
	private:

		eOperandType		_type;

	public:

		class		TokenOperandClose: public lexerparser::LexerToken<Instr*, AbstractVm&>
		{
			public:

				TokenOperandClose(void);
				TokenOperandClose(const TokenOperandClose &src);
				~TokenOperandClose(void);

				std::string			toString(void) const;

				lexerparser::LexerToken<Instr*, AbstractVm&>
									*clone(const char *s);
		};

		TokenOperand(void);
		TokenOperand(eOperandType type);
		TokenOperand(const TokenOperand &src);
		~TokenOperand(void);

		TokenOperand		&operator=(const TokenOperand &rhs);

		lexerparser::LexerToken<Instr*, AbstractVm&>
							*nud(lexerparser::Parser<Instr*, AbstractVm&> &parser, AbstractVm &data);
		Instr				*execute(AbstractVm &data);

		int					getType(void) const;
		std::string			toString(void) const;

		lexerparser::LexerToken<Instr*, AbstractVm&>
							*clone(const char *s);
};

#endif
