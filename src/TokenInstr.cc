#include "AbstractVm.h"

const std::string TokenInstr::names[11] = {
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit"
};

TokenInstr::TokenInstr(void):
	lexerparser::LexerToken<Instr*, AbstractVm&>("", 2),
	_name()
{}

TokenInstr::TokenInstr(const std::string &name):
	lexerparser::LexerToken<Instr*, AbstractVm&>("", 2),
	_name(name)
{}

TokenInstr::TokenInstr(const TokenInstr &src):
	lexerparser::LexerToken<Instr*, AbstractVm&>(src),
	_name(src._name)
{ *this = src; }

TokenInstr::~TokenInstr(void)
{}

TokenInstr					&TokenInstr::operator=(const TokenInstr &rhs)
{
	if (this != &rhs)
	{

	}
	return (*this);
}

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenInstr::nud(lexerparser::Parser<Instr*, AbstractVm&> &parser, AbstractVm &data)
{
	this->push_back( parser.expression(data, this->_priority) );
	return (this);
}

Instr						*TokenInstr::execute(AbstractVm &data)
{
	if (!this->get(0) && (this->_name == "push" || this->_name == "assert"))
		throw lexerparser::ParserWarningException("Missing Operand", this->_line);

	try
	{
		data._parser._instr = new Instr();
		data._parser._instr->setMethod( this->_name );
		data._parser._instr->setLine( this->_line );

		if (this->get(0))
			( this->get(0) )->execute(data);
	}
	catch (const lexerparser::ParserWarningException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (data._parser._instr);
}

size_t						TokenInstr::compare(const char *s)
{
	for (int i = 0; i < 11; i++)
	{
		if (strncmp(s, TokenInstr::names[i].c_str(), TokenInstr::names[i].length()) == 0)
		{
			this->_str = names[i];
			this->_length = TokenInstr::names[i].length();
			return (this->_length);
		}
	}
	return (0);
}

size_t						TokenInstr::compare(const std::string &s)
{
	return (this->compare( s.c_str() ));
}

size_t						TokenInstr::length(void)
{
	return (this->_length);
}

std::string					TokenInstr::toString(void) const
{
	return ("Instr");
};

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenInstr::clone(const char *s)
{
	return (new TokenInstr(std::string(s)));
}
