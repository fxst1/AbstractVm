#ifndef LEXERID_H
# define LEXERID_H

namespace	lexerparser
{
	class		LexerId
	{
		protected:

			std::string			_str;
			size_t				_length;

		public:

			LexerId(void);
			LexerId(const std::string &src);
			LexerId(const LexerId &src);
			virtual ~LexerId(void);

			LexerId				&operator=(const LexerId& rhs);

			/*
			**	String
			*/

			static size_t		stringCompare(LexerId *id, const std::string& s);
			static size_t		stringCompare(LexerId *lid, const char *s);
			static size_t		stringLength(const LexerId *lid);

			/*
			**	Regex
			*/

			static size_t		regexCompare(LexerId *lid, const std::string& s);
			static size_t		regexCompare(LexerId *lid, const char *s);
			static size_t		regexLength(const LexerId *lid);

			/*
			**	Enclosed
			*/

			static size_t		enclosedCompare(LexerId *lid, const std::string& s);
			static size_t		enclosedCompare(LexerId *lid, const char *s);
			static size_t		enclosedLength(const LexerId *lid);

		};
};

#endif
