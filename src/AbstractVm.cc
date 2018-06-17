#include "AbstractVm.h"

AbstractVm::AbstractVm(void):
	_lines(),
	_stack(),
	_parser(),
	_stop()
{}

AbstractVm::AbstractVm(const AbstractVm &src):
	_lines(),
	_stack(),
	_parser(),
	_stop()
{ *this = src; }

AbstractVm::~AbstractVm(void)
{
	for (auto it : this->_lines)
		delete it;

	while (!this->_stack.empty())
	{
		delete this->_stack.top();
		this->_stack.pop();
	}
}

AbstractVm			&AbstractVm::operator=(const AbstractVm &rhs)
{
	if (this != &rhs)
	{
		this->_stack = rhs._stack;
		this->_parser = rhs._parser;
	}
	return (*this);
}

bool				AbstractVm::readFile(std::istream &file)
{
	std::string		s;
	bool			stop;

	stop = false;
	while (!stop && std::getline(file, s))
	{
		stop = (s.find(";;") != std::string::npos);

		std::size_t		pos = s.find(';');
		std::size_t		i = 0;

		while (std::isspace(s[i]))
			i++;

		if (pos != std::string::npos)
			s = s.substr(i, pos);

		this->_buffer.push_back(s);
	}
	return (true);
}

bool				AbstractVm::readFile(const std::string &filename)
{
	std::ifstream			file;
	std::string				s;

	file.open(filename);
	if (!file.is_open())
	{
		std::cerr << "Cannot open file " << filename << std::endl;
		return (false);
	}

	while (std::getline(file, s))
	{
		std::size_t		pos = s.find(';');
		std::size_t		i = 0;

		while (std::isspace(s[i]))
			i++;

		if (pos != std::string::npos)
			s = s.substr(i, pos);

		this->_buffer.push_back(s);
	}
	return (true);
}

bool				AbstractVm::syntaxParser(void)
{
	Instr			*i;

	try
	{
		for (auto it = this->_buffer.begin(); it != this->_buffer.end(); it++)
		{
			if ((*it).length() > 0)
			{
				i = this->_parser.evaluate( *it, *this );
				if (i)
					this->_lines.push_back(i);
				else
					throw lexerparser::ParserAbortException("Not an instruction", this->_parser.getLine());
			}
			this->_parser.clear();
			this->_parser.newline();
		}
	}
	catch (const lexerparser::ParserAbortException &e)
	{
		std::cerr << e.what() << std::endl;
		return (false);
	}
	catch (const lexerparser::ParserWarningException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (true);
}

void				AbstractVm::execute(void)
{
	this->_cursor = this->_lines.begin();
	while (!this->_stop && this->_cursor != this->_lines.end())
	{
		try
		{
			( *this->_cursor )->compute( *this );
		}
		catch (const lexerparser::ParserWarningException &e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const lexerparser::ParserAbortException &e)
		{
			std::cerr << e.what() << std::endl;
			break ;
		}
		catch (const Overflow &e)
		{
			std::cerr << e.what() << std::endl;
			break ;
		}
		catch (const Underflow &e)
		{
			std::cerr << e.what() << std::endl;
			break ;
		}
		catch (const DivideModulusError &e)
		{
			std::cerr << e.what() << std::endl;
			break ;
		}
		this->_cursor++;
	}
}

/*
**	Parser
*/

AbstractVm::Parser::Parser(void):
	lexerparser::Parser<Instr*, AbstractVm&>()
{
	this->useToken( new TokenInstr() );
	this->useToken( new TokenOperand() );
	this->useToken( new TokenOperand::TokenOperandClose() );
	this->useToken( new TokenDouble() );
	this->useToken( new TokenNumber() );
}

AbstractVm::Parser::Parser(const AbstractVm::Parser &src):
	lexerparser::Parser<Instr*, AbstractVm&>(src)
{}

AbstractVm::Parser::~Parser(void)
{}

AbstractVm::Parser			&AbstractVm::Parser::operator=(const AbstractVm::Parser &rhs)
{
	return (*this);
	(void)rhs;
}
