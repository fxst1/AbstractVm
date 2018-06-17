#include "AbstractVm.h"

TokenNumber::TokenNumber(void):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXNUMBER, 0),
	_value()
{}

TokenNumber::TokenNumber(const std::string &value):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXNUMBER, 0),
	_value(value)
{}

TokenNumber::TokenNumber(const TokenNumber &src):
	lexerparser::LexerToken<Instr*, AbstractVm&>(src),
	_value()
{ *this = src; }

TokenNumber::~TokenNumber(void)
{}

TokenNumber					&TokenNumber::operator=(const TokenNumber &rhs)
{
	if (this != &rhs)
		this->_value = rhs._value;
	return (*this);
}

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenNumber::nud(lexerparser::Parser<Instr*, AbstractVm&> &parser,
											  AbstractVm &data)
{
	return (this);
	(void)parser;
	(void)data;
}

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenNumber::led(lexerparser::Parser<Instr*, AbstractVm&> &parser,
											  lexerparser::LexerToken<Instr*, AbstractVm&> *left,
											  AbstractVm &data)
{
	return (this);
	(void)parser;
	(void)data;
	(void)left;
}

Instr						*TokenNumber::execute(AbstractVm &data)
{
	if (data._parser._instr)
		data._parser._instr->setValue( this->_value );
	return (nullptr);
}

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenNumber::clone(const char *s)
{
	return (new TokenNumber(s));
}
