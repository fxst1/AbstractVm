#ifndef PARSEREXCEPTION_H
# define PARSEREXCEPTION_H

namespace		lexerparser
{
	class		ParserException: public std::exception
	{
		private:

			const std::string		_error;

			static std::string			getError(const std::string &type, const std::string &error, const int line)
			{
				std::string		ret = "";

				if (type.length() > 0)
					ret = type + ": " + error;
				else if (type.length() > 0)
					ret = error;

				if (line > 0)
					ret += ": Line " + std::to_string(line);

				return (ret);
			}

		public:

			ParserException(void):
				_error("Undefined error")
			{}

			ParserException(const ParserException &src):
				_error(src._error)
			{}

			ParserException(const std::string &type, const std::string &error, const int line = 0):
				_error(ParserException::getError(type, error, line))
			{}

			virtual ~ParserException(void) throw()
			{}

			ParserException				&operator=(const ParserException &rhs)
			{
				return (*this);
				(void)rhs;
			}

			virtual const char			*what() const throw()
			{
				return (this->_error.c_str());
			}
	};

	class		ParserNoticeException: public ParserException
	{
		public:

			ParserNoticeException(const std::string &error, const int line = 0):
				ParserException("Notice", error, line)
			{}

			virtual ~ParserNoticeException(void) throw()
			{}
	};

	class		ParserWarningException: public ParserException
	{
		public:

			ParserWarningException(const std::string &error, const int line = 0):
				ParserException("Warning", error, line)
			{}

			virtual ~ParserWarningException(void) throw()
			{}

	};

	class		ParserAbortException: public ParserException
	{
		public:

			ParserAbortException(const std::string &error, const int line = 0):
				ParserException("Abort", error, line)
			{}

			virtual ~ParserAbortException(void) throw()
			{}
	};
};

#endif
