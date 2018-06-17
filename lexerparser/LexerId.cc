#include "lexerparser.h"

lexerparser::LexerId::LexerId(void):
	_str(""),
	_length(0)
{}

lexerparser::LexerId::LexerId(const std::string &src):
	_str(src),
	_length(src.length())
{}

lexerparser::LexerId::LexerId(const LexerId &src):
	_str(src._str),
	_length(src._length)
{ *this = src; }

lexerparser::LexerId::~LexerId(void)
{}

lexerparser::LexerId	&lexerparser::LexerId::operator=(const LexerId& rhs)
{
	this->_length = rhs._length;
	return (*this);
}

/*
**	String
*/

size_t					lexerparser::LexerId::stringCompare(LexerId *lid, const std::string& s)
{
	return (lexerparser::LexerId::stringCompare(lid, s.c_str()));
}

size_t					lexerparser::LexerId::stringCompare(LexerId *lid, const char *s)
{
	if (strncmp(s, lid->_str.c_str(), lid->_str.length()) == 0)
		return (lid->_str.length());
	else
		return (0);
}

size_t					lexerparser::LexerId::stringLength(const LexerId *lid)
{
	return (lid->_str.length());
}

/*
**	Regex
*/

size_t					lexerparser::LexerId::regexCompare(LexerId *lid, const std::string& s)
{
	std::smatch	pieces;

	lid->_length = 0;
	if (std::regex_search(s, pieces, std::regex(lid->_str)))
	{
		if (pieces.size() > 0)
		{
			lid->_length = pieces[0].str().length();
			return (lid->_length);
		}
	}
	return (lid->_length);
}

size_t					lexerparser::LexerId::regexCompare(LexerId *lid, const char *s)
{
	return (lexerparser::LexerId::regexCompare(lid, std::string(s)));
}

size_t					lexerparser::LexerId::regexLength(const LexerId *lid)
{
	return (lid->_length);
}

/*
**	Enclosed
*/

size_t					lexerparser::LexerId::enclosedCompare(LexerId *lid, const std::string& s)
{
	return (lexerparser::LexerId::enclosedCompare(lid, s.c_str()));
}

size_t					lexerparser::LexerId::enclosedCompare(LexerId *lid, const char *s)
{
	size_t	i = 0;
	int		open = 0;

	while (*s)
	{
		if (!strncmp(s, &lid->_str.c_str()[0], 1))
			open++;
		else if (!strncmp(s, &lid->_str.c_str()[1], 1))
			open--;
		else if (!open)
		{
			lid->_length = i;
			return (i);
		}
		i++;
		s++;
	}
	lid->_length = 0;
	return (i);
}

size_t					lexerparser::LexerId::enclosedLength(const LexerId *lid)
{
	return (lid->_length);
}
