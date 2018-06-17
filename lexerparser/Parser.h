#ifndef PARSER_H
# define PARSER_H

# include "lexerparser.h"
namespace	lexerparser
{

	template<typename T, typename D>
	class		Parser
	{
		private:

			std::vector< LexerToken<T,D>* >							_tokens;
			std::list< LexerToken<T,D>* >							_symbols;
			LexerToken<T,D>*										_root;
			typename std::vector<LexerToken<T,D>*>::iterator		_it;

		protected:

			int														_line;
			int														_col;

		public:

			typename std::vector<LexerToken<T,D>*>::iterator		iterator;

			Parser<T,D>(void):
				_tokens(),
				_symbols(),
				_root(nullptr),
				_line(1),
				_col(1)
			{}

			Parser<T,D>(const Parser<T,D>& p):
				_tokens(p._tokens),
				_symbols(p._symbols),
				_root(p._root),
				_line(p._line),
				_col(p._col)
			{}

			virtual ~Parser<T,D>(void)
			{
				for (auto it = this->_symbols.begin(); it != this->_symbols.end(); it++)
					if (*it != NULL)
						delete (*it);

				this->_symbols.clear();

				for (auto it = this->_tokens.begin(); it != this->_tokens.end(); it++)
					if (*it != NULL)
						delete (*it);
			}

			void							debug(void) const
			{
				if (this->_root)
					this->_root->debug();
			}

			int								getLine(void) const
			{
				return (this->_line);
			}

			void							newline(void)
			{
				this->_line++;
				this->_col = 0;
			}

			virtual LexerToken<T,D>			*expression(D data, int priority = 0)
			{
				LexerToken<T,D>				*tok = NULL;
				LexerToken<T,D>				*left = NULL;

				if (this->_it == this->_tokens.end())
					return (NULL);

				tok = *(this->_it);
				this->advance();
				left = tok->nud(*this, data);

				while (left && this->_it != this->_tokens.end() &&
						priority < (*this->_it)->getPriority())
				{
					tok = *(this->_it);
					this->advance();
					left = tok->led(*this, left, data);
				}
				return (left);
			}

			bool							end()
			{
				return (this->_it == this->_tokens.end());
			}

			void							advance()
			{
				if (this->_it != this->_tokens.end())
					this->_it++;
			}

			LexerToken<T,D>*				getRoot(void) const
			{
				return (this->_root);
			}

			LexerToken<T,D>*				getToken(void)
			{
				if (this->_it != this->_tokens.end())
					return (*this->_it);
				return (nullptr);
			}

			void							find(const std::string id)
			{
				while (this->_it != this->_tokens.end() &&
						!(*this->_it)->compare(id))
					this->_it++;
			}

			void							useToken(LexerToken<T,D> *tok)
			{
				this->_symbols.push_back( tok );
			}

			std::list<LexerToken<T,D>*>		copyTokens(void) const
			{
				std::list<LexerToken<T,D>*>				lst;

				for (auto it = this->_symbols.begin(); it != this->_symbols.end(); it++)
					lst.push_back( (*it).clone("") );
				return (lst);
			}

			T								evaluate(const std::string s, D data)
			{
				this->tokenize(s);
				this->_it = this->_tokens.begin();
				this->_root = this->expression(data);
				if (this->_root)
				{
					if (this->_it != this->_tokens.end())
					{
						this->debug();
						throw ParserAbortException("Cannot parse `" + (*this->_it)->toString() + "`");
					}
					return (this->_root->execute( data ));
				}
				throw ParserAbortException("Cannot evaluate expression `" + s + "`");
			}

			void							clear(void)
			{
				this->_root = NULL;
				for (auto it = this->_tokens.begin(); it != this->_tokens.end(); it++)
					delete (*it);
				this->_tokens.clear();
			}

		private:

			void							addToken(LexerToken<T,D>* tok)
			{
				if (tok)
					this->_tokens.push_back( tok );
			}

			size_t							parseSymbol(const char *str)
			{
				size_t						tmp = 0;

				for (auto it = this->_symbols.begin(); it != this->_symbols.end(); it++)
				{
					tmp = (*it)->compare(str);
					if (tmp > 0)
					{
						std::string				s = std::string(str).substr(0, (*it)->length()).c_str();
						char					*stmp = (char*)s.c_str();
						LexerToken<T,D>			*tok = (*it)->clone(s.c_str());

						tok->_line = this->_line;
						tok->_col = this->_col;

						while (*stmp)
						{
							if (*stmp == '\n')
							{
								this->_line++;
								this->_col = 0;
							}
							else
								this->_col++;
							stmp++;
						}
						this->addToken(tok);
						return ((*it)->length());
					}
				}
				return (0);
			}

		protected:

			virtual void	tokenize(const char *str)
			{
				if (this->_symbols.size() == 0)
					throw ParserAbortException("No symbols");

				while (*str)
				{
					while (*str == '\n' || *str == '\t' || *str == ' ')
					{
						if (*str == '\n')
						{
							this->_line++;
							this->_col = 0;
						}
						else
							this->_col++;
						str++;
					}
					if (*str)
					{
						size_t		len = this->parseSymbol(str);

						if (!len)
						{
							std::string s = "Cannot parse `";
							s += *str;
							s += "` (";
							s += std::to_string(*str);
							s += ")";

							throw ParserAbortException(s, this->_line);
						}
						else
							str += (len <= strlen(str)) ? len : strlen(str);
					}
				}
			}

			virtual void	tokenize(const std::string str)
			{
				this->tokenize(str.c_str());
			}

	};
};

#endif
