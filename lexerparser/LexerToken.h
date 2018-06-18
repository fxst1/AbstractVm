#ifndef LEXERTOKEN_H
# define LEXERTOKEN_H
# include <list>
# include "LexerId.h"
# include "Parser.h"

namespace	lexerparser
{
	template<typename T, typename D>
	class		LexerToken: public LexerId, public std::list< LexerToken<T,D>* >
	{
		private:

			typedef std::list< LexerToken<T,D>* >	node;

		protected:

			int										_priority;

		public:

			int										_line;
			int										_col;

			LexerToken(void):
				LexerId(),
				node(),
				_priority(0),
				_line(0),
				_col(0)
			{}

			LexerToken(const LexerToken& id):
				LexerId(id),
				node(id),
				_priority(id._priority),
				_line(id._line),
				_col(id._col)
			{}

			LexerToken(const std::string& id, int priority = 0):
				LexerId(id),
				node(),
				_priority(priority),
				_line(0),
				_col(0)
			{}

			virtual ~LexerToken(void)
			{}

			using node::operator=;
			typedef typename node::iterator	iterator;

			int							getPriority(void) const
			{
				return (this->_priority);
			}

			virtual void				debug(int rec = 0) const
			{
				int						i = 0;

				while (i < rec)
				{
					std::cout << "\t";
					i++;
				}

				std::cout << this->toString() << std::endl;

				for (auto it = this->begin(); it != this->end(); it++)
					if (*it)
						(*it)->debug(rec + 1);
			}

			LexerToken<T,D>				*get(size_t index)
			{
				size_t								i = 0;

				for (auto it = this->begin(); it != this->end() ; it++)
					if (i == index)
						return (*it);
					else
						i++;
				return (NULL);
			}

			/*
			**	Virtual
			*/

			virtual LexerToken<T,D>		*nud(Parser<T,D> &root, D data)
			{
				throw ParserAbortException("Syntax error: Undefined token " + this->toString());
				(void)root;
				(void)data;
			}

			virtual LexerToken<T,D>		*led(Parser<T,D> &root, LexerToken<T,D> *left, D data)
			{
				throw ParserAbortException("Syntax error: Unexpected token " + this->toString());
				(void)root;
				(void)left;
				(void)data;
			}

			virtual T					execute(D data)
			{
				throw ParserAbortException("Parse error: Undefined execution " + this->toString());
				(void)data;
			}

			virtual T					execute(void)
			{
				throw ParserAbortException("Parse error: Undefined execution " + this->toString());
			}

			virtual LexerToken<T,D>		*clone(const char *s)
			{
				return (nullptr);
				(void)s;
			}

			virtual std::string			toString() const
			{
				return (this->_str);
			}

			virtual size_t				compare(const char *s)
			{
				return (LexerId::regexCompare((LexerToken<T,D>*)this, s));
			}

			virtual size_t				compare(const std::string &s)
			{
				return (LexerId::regexCompare(this, s));
			}

			virtual size_t				length(void)
			{
				return (LexerId::regexLength(this));
			}

			/*
			**	Helpers
			*/

			static LexerToken<T,D>		*helperLineNud(LexerToken<T,D> *tok, Parser<T,D> &parser, D data)
			{
				LexerToken<T,D>			*tmp = NULL;

				while (true)
				{
					tmp = parser.expression(data, tok->_priority);
					if (tmp == NULL)
						break ;
					tok->push_back(tmp);
				}
				return (tok);
			}

			static LexerToken<T,D>		*helperLineLed(LexerToken<T,D> *tok, Parser<T,D> &parser, LexerToken<T,D> *left, D data)
			{
				LexerToken<T,D>			*tmp = NULL;

				tok->push_back(left);
				while (true)
				{
					tmp = parser.expression(data, tok->_priority);
					if (tmp == NULL)
						break ;
					tok->push_back(tmp);
				}
				return (tok);
			}

			static T					helperLineEval(LexerToken<T,D> *tok, D data)
			{
				T						tmp = NULL;
				T						ltmp = NULL;
				size_t					i = 0;

				while (i < tok->size())
				{
					tmp = tok->get(i)->execute(data);
					if (!tmp)
						break ;
					else
						ltmp = tmp;
					i++;
				}
				return (ltmp);
			}

			static LexerToken<T,D>		*helperNud(LexerToken<T,D> *tok, Parser<T,D> &parser, D data)
			{
				tok->push_back(parser.expression(data, tok->_priority));
				return (tok);
			}

			static LexerToken<T,D>		*helperLed(LexerToken<T,D> *tok, Parser<T,D> &parser, LexerToken<T,D> *left, D data)
			{
				tok->push_back(left);
				tok->push_back(parser.expression(data, tok->_priority));
				return (tok);
			}

	};

};

#endif
