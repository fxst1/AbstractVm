#include "AbstractVm.h"

TokenDouble::TokenDouble(void):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXDOUBLE, 0),
	_value()
{}

TokenDouble::TokenDouble(const std::string &value):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXDOUBLE, 0),
	_value(value)
{}

TokenDouble::TokenDouble(const TokenNumber &src):
	lexerparser::LexerToken<Instr*, AbstractVm&>(src),
	_value()
{ *this = src; }

TokenDouble::~TokenDouble(void)
{}

TokenDouble					&TokenDouble::operator=(const TokenDouble &rhs)
{
	if (this != &rhs)
		this->_value = rhs._value;
	return (*this);
}


lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenDouble::nud(lexerparser::Parser<Instr*, AbstractVm&> &parser,
											  AbstractVm &data)
{
	return (this);
	(void)parser;
	(void)data;
}


lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenDouble::led(lexerparser::Parser<Instr*, AbstractVm&> &parser,
											  lexerparser::LexerToken<Instr*, AbstractVm&> *left,
											  AbstractVm &data)
{
	return (this);
	(void)data;
	(void)parser;
	(void)left;
}

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenDouble::clone(const char *s)
{
	return (new TokenDouble(s));
}

Instr						*TokenDouble::execute(AbstractVm &data)
{
	if (data._parser._instr)
		data._parser._instr->setValue( this->_value );
	return (nullptr);
}
