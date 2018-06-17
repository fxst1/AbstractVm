#ifndef LEXERPARSER_HPP
# define LEXERPARSER_HPP
# include <iostream>
# include <string>
# include <exception>
# include <list>
# include <vector>
# include <string.h>
# include <regex>

namespace		lexerparser
{
	class		LexerId;

	template<typename T, typename D>
	class		LexerToken;

	template<typename T, typename D>
	class		Parser;
};

#include "ParserException.h"
#include "LexerId.h"
#include "LexerToken.h"
#include "Parser.h"

#endif
