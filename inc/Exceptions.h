#include <exception>
#include "IOperand.h"

struct Overflow: public std::exception
{
	const char *what(void) const noexcept
	{
		return ("Overflow");
	}
};

struct DivideModulusError: public std::exception
{
	const char *what(void) const noexcept
	{
		return ("Division or Modulus by zero");
	}
};

struct Underflow: public std::exception
{
	const char *what(void) const noexcept
	{
		return ("Underflow");
	}
};

template<typename T>
bool		checkOverflow(T result, eOperandType type)
{
	if (type == Int8)
		return (result > std::numeric_limits<int8_t>::max());
	else if (type == Int16)
		return (result > std::numeric_limits<int16_t>::max());
	else if (type == Int32)
		return (result > std::numeric_limits<int32_t>::max());
	else if (type == Float)
		return (result > std::numeric_limits<float>::max());
	else
		return (result > std::numeric_limits<double>::max());

	return (false);
}

template<typename T>
bool		checkUnderflow(T result, eOperandType type)
{
	if (type == Int8)
		return (result < std::numeric_limits<int8_t>::min());
	else if (type == Int16)
		return (result < std::numeric_limits<int16_t>::min());
	else if (type == Int32)
		return (result < std::numeric_limits<int32_t>::min());
	else if (type == Float)
		return (result < std::numeric_limits<float>::lowest());
	else
		return (result < std::numeric_limits<double>::lowest());
}
