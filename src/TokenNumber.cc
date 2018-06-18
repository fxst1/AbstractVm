#include "AbstractVm.h"

TokenNumber::TokenNumber(void):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXNUMBER, 0),
	_value(),
	_format(0)
{}

TokenNumber::TokenNumber(const std::string &value):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXNUMBER, 0),
	_value(value),
	_format(0)
{}

TokenNumber::TokenNumber(const TokenNumber &src):
	lexerparser::LexerToken<Instr*, AbstractVm&>(src),
	_value(),
	_format()
{ *this = src; }

TokenNumber::~TokenNumber(void)
{}

TokenNumber					&TokenNumber::operator=(const TokenNumber &rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs._value;
		this->_format = rhs._format;
	}
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
	std::string				decimal_number;

	if (this->_value.length() > 2)
	{
		this->_format = this->_value[1];
		if (this->_value[1] == 'x')
			decimal_number = TokenNumber::hex2dec( this->_value.substr(2) );
		else if (this->_value[1] == 'o')
			decimal_number = TokenNumber::oct2dec( this->_value.substr(2) );
		else if (this->_value[1] == 'b')
			decimal_number = TokenNumber::bin2dec( this->_value.substr(2) );
		else
			decimal_number = this->_value;
	}
	else
		decimal_number = this->_value;
	if (data._parser._instr)
	{
		data._parser._instr->setValue( decimal_number );
		data._parser._instr->setFormat( this->_format );
	}
	return (nullptr);
}

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenNumber::clone(const char *s)
{
	return (new TokenNumber(s));
}

/*
**	Conversions
*/

std::string					TokenNumber::hex2dec(const std::string &s)
{
	std::stringstream		ss;
	int						value;

	ss << std::hex << s;
	ss >> value;
	return (std::to_string(value));
}

std::string					TokenNumber::oct2dec(const std::string &s)
{
	std::stringstream		ss;
	int						value;

	ss << std::oct << s;
	ss >> value;
	return (std::to_string(value));
}

std::string					TokenNumber::bin2dec(const std::string &s)
{
	std::bitset<64>			bs(s);

	return (std::to_string( bs.to_ulong() ));
}
