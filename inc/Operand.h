#ifndef OPERAND_H
# define OPERAND_H
# include <limits>
# include <cstdint>
# include <iostream>
# include <iomanip>
# include <sstream>
# include <cmath>
# include "IOperand.h"
# include "OperandFactory.h"
# include "Exceptions.h"

template<typename T>
T							getBytes(const std::string &value, const int precision)
{
	T						bytes;
	std::stringstream		ss;

	ss.precision(precision);
	ss << std::fixed;
	ss << value;
	ss >> bytes;
	return (bytes);
}

template<typename T>
std::string					getString(const T bytes, const int precision)
{
	std::stringstream		ss;

	ss.precision(precision);
	ss << std::fixed;
	ss << bytes;
	return (ss.str());
}

template<typename T>
class		Operand: public IOperand
{
	private:

		T							_bytes;
		std::string					_name;
		const eOperandType			_type;
		const int					_prec;

	public:

		Operand(void):
			_bytes(0),
			_name("0"),
			_type(Undef),
			_prec(Undef)
		{}

		Operand(const Operand &src):
			_bytes(src._bytes),
			_name(src._name),
			_type(src._type),
			_prec(src._prec)
		{}

		Operand(const std::string &s, const eOperandType type, int precision):
			_bytes(0),
			_name(s),
			_type(type),
			_prec(precision)
		{
			if (type < Float)
			{
				int64_t		value = atol( s.c_str() );

				if (checkOverflow<int64_t>(value, type))
					throw Overflow();
				else if (checkUnderflow<int64_t>(value, type))
					throw Underflow();

				this->_bytes = static_cast<T>( value );
				this->_name = getString<long double>(this->_bytes, this->_prec);
			}
			else
			{
				long double	value = stold(s);

				if (checkOverflow<long double>(value, type))
					throw Overflow();
				else if (checkUnderflow<long double>(value, type))
					throw Underflow();

				this->_bytes = static_cast<T>( value );
				this->_name = getString<long double>(this->_bytes, this->_prec);
			}
		}

		~Operand(void)
		{}

		Operand					&operator=(const Operand &rhs)
		{
			if (this != &rhs)
			{
				this->_bytes = rhs._bytes;
				this->_name = rhs._name;
			}
			return (*this);
		}

		int						getPrecision(void) const
		{
			return (this->_prec);
		}

		eOperandType			getType(void) const
		{
			return (this->_type);
		}

		const std::string		&toString(void) const
		{
			return (this->_name);
		}

		/*
		**	Operators
		*/

		IOperand const			*operator+(IOperand const &rhs) const
		{
			int						prec;
			eOperandType			ntype;
			long double				left = getBytes<long double>(this->_name, this->getPrecision());
			long double				right = getBytes<long double>(rhs.toString(), rhs.getPrecision());
			long double				result = left + right;

			ntype = std::max(this->getType(), rhs.getType());
			prec = std::max(this->getPrecision(), rhs.getPrecision());

			if (rhs.getType() < Float)			//Integer comparaison
			{
				if (checkOverflow<int64_t>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<int64_t>(result, ntype))
					throw Underflow();
			}
			else
			{
				if (checkOverflow<long double>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<long double>(result, ntype))
					throw Underflow();
			}

			return (OperandFactory::createOperand(ntype, getString<long double>(result, prec)));
		}

		IOperand const			*operator-(IOperand const &rhs) const
		{
			int						prec;
			eOperandType			ntype;
			long double				left = getBytes<long double>(this->_name, this->getPrecision());
			long double				right = getBytes<long double>(rhs.toString(), rhs.getPrecision());
			long double				result = left - right;

			ntype = std::max(this->getType(), rhs.getType());
			prec = std::max(this->getPrecision(), rhs.getPrecision());

			if (rhs.getType() < Float)			//Integer comparaison
			{
				if (checkOverflow<int64_t>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<int64_t>(result, ntype))
					throw Underflow();
			}
			else
			{
				if (checkOverflow<long double>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<long double>(result, ntype))
					throw Underflow();
			}

			return (OperandFactory::createOperand(ntype, getString<long double>(result, prec)));
		}

		IOperand const			*operator*(IOperand const &rhs) const
		{
			int						prec;
			eOperandType			ntype;
			long double				left = getBytes<long double>(this->_name, this->getPrecision());
			long double				right = getBytes<long double>(rhs.toString(), rhs.getPrecision());
			long double				result = left * right;

			ntype = std::max(this->getType(), rhs.getType());
			prec = std::max(this->getPrecision(), rhs.getPrecision());

			if (rhs.getType() < Float)			//Integer comparaison
			{
				if (checkOverflow<int64_t>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<int64_t>(result, ntype))
					throw Underflow();
			}
			else
			{
				if (checkOverflow<long double>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<long double>(result, ntype))
					throw Underflow();
			}

			return (OperandFactory::createOperand(ntype, getString<long double>(result, prec)));

		}

		IOperand const			*operator/(IOperand const &rhs) const
		{
			int						prec;
			eOperandType			ntype;
			long double				left = getBytes<long double>(this->_name, this->getPrecision());
			long double				right = getBytes<long double>(rhs.toString(), rhs.getPrecision());

			if (right == 0)
				throw DivideModulusError();

			long double				result = left / right;

			ntype = std::max(this->getType(), rhs.getType());
			prec = std::max(this->getPrecision(), rhs.getPrecision());

			if (rhs.getType() < Float)			//Integer comparaison
			{
				if (checkOverflow<int64_t>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<int64_t>(result, ntype))
					throw Underflow();
			}
			else
			{
				if (checkOverflow<long double>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<long double>(result, ntype))
					throw Underflow();
			}

			return (OperandFactory::createOperand(ntype, getString<long double>(result, prec)));
		}


		IOperand const			*operator%(IOperand const &rhs) const
		{
			int						prec;
			eOperandType			ntype;
			long double				left = getBytes<long double>(this->_name, this->getPrecision());
			long double				right = getBytes<long double>(rhs.toString(), rhs.getPrecision());

			if (right == 0)
				throw DivideModulusError();

			long double				result = left / right;

			ntype = std::max(this->getType(), rhs.getType());
			prec = std::max(this->getPrecision(), rhs.getPrecision());

			if (rhs.getType() < Float)			//Integer comparaison
			{
				if (checkOverflow<int64_t>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<int64_t>(result, ntype))
					throw Underflow();
			}
			else
			{
				if (checkOverflow<long double>(result, ntype))
					throw Overflow();
				else if (checkUnderflow<long double>(result, ntype))
					throw Underflow();
			}

			return (OperandFactory::createOperand(ntype, getString<long double>(result, prec)));
		}

		bool					operator!=( IOperand const& rhs ) const
		{
			long double				left = getBytes<long double>(this->_name, this->getPrecision());
			long double				right = getBytes<long double>(rhs.toString(), rhs.getPrecision());

			return (left != right);
		}

};

#endif
