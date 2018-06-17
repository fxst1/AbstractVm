#include "AbstractVm.h"

TokenOperand::TokenOperand(void):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXOPERAND_START, 3),
	_type(Undef)
{}

TokenOperand::TokenOperand(eOperandType type):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXOPERAND_START, 3),
	_type(type)
{}

TokenOperand::TokenOperand(const TokenOperand &src):
	lexerparser::LexerToken<Instr*, AbstractVm&>(src),
	_type(src._type)
{ *this = src; }

TokenOperand::~TokenOperand(void)
{}

TokenOperand					&TokenOperand::operator=(const TokenOperand &rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs._type;
	}
	return (*this);
}

lexerparser::LexerToken<Instr*, AbstractVm&>
								*TokenOperand::nud(lexerparser::Parser<Instr*, AbstractVm&> &parser, AbstractVm &data)
{
	this->push_back( parser.expression(data, this->_priority) );
	if (!parser.getToken() || parser.getToken()->toString() != "TokenOperandClose")
		throw lexerparser::ParserAbortException("Missing `)` after expression");
	parser.advance();
	return (this);
}

Instr							*TokenOperand::execute(AbstractVm &data)
{
	if (!this->get(0))
		throw lexerparser::ParserWarningException("Missing value between `(` and `)`");

	try
	{
		if (this->_type == Int32 && !dynamic_cast<TokenNumber*>( this->get(0) ))
			throw lexerparser::ParserWarningException("Not a N value");
		else if (this->_type == Int16 && !dynamic_cast<TokenNumber*>( this->get(0) ))
			throw lexerparser::ParserWarningException("Not a N value");
		else if (this->_type == Int8 && !dynamic_cast<TokenNumber*>( this->get(0) ))
			throw lexerparser::ParserWarningException("Not a N value");
		else if (this->_type == Float && !dynamic_cast<TokenDouble*>( this->get(0) ))
			throw lexerparser::ParserWarningException("Not a Z value");
		else if (this->_type == Double && !dynamic_cast<TokenDouble*>( this->get(0) ))
			throw lexerparser::ParserWarningException("Not a Z value");
	}
	catch (lexerparser::ParserWarningException &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Reinterpreting value" << std::endl;
	}

	try
	{
		if (data._parser._instr)
			data._parser._instr->setType( this->_type );

		this->get(0)->execute(data);
	}
	catch (const lexerparser::ParserWarningException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (nullptr);
}

std::string						TokenOperand::toString(void) const
{
	return ("Operand");
};

lexerparser::LexerToken<Instr*, AbstractVm&>
								*TokenOperand::clone(const char *s)
{
	std::string		str;

	for (size_t i = 0; i < strlen(s) - 1; i++)
		str += std::tolower(s[i]);

	if (str == "int32")
		return (new TokenOperand(Int32));
	else if (str == "int16")
		return (new TokenOperand(Int16));
	else if (str == "int8")
		return (new TokenOperand(Int8));
	else if (str == "float")
		return (new TokenOperand(Float));
	else if (str == "double")
		return (new TokenOperand(Double));
	throw lexerparser::ParserAbortException("Undefined operand type `" + str + "`", this->_line);
}

/*
**	TokenOperandClose
*/

TokenOperand::TokenOperandClose::TokenOperandClose(void):
	lexerparser::LexerToken<Instr*, AbstractVm&>(REGEXOPERAND_END, 1)
{}

TokenOperand::TokenOperandClose::TokenOperandClose(const TokenOperand::TokenOperandClose &src):
	lexerparser::LexerToken<Instr*, AbstractVm&>(src)
{ *this = src; }

TokenOperand::TokenOperandClose::~TokenOperandClose(void)
{}

std::string					TokenOperand::TokenOperandClose::toString(void) const
{
	return ("TokenOperandClose");
};

lexerparser::LexerToken<Instr*, AbstractVm&>
							*TokenOperand::TokenOperandClose::clone(const char *s)
{
	return (new TokenOperandClose(*this));
	(void)s;
}
