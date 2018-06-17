# include "OperandFactory.h"
# include "Operand.h"

const IOperand	*OperandFactory::createOperand(eOperandType type, const std::string &value)
{
	static OperandFactory::factory fcts[5] = {
		OperandFactory::createInt8,
		OperandFactory::createInt16,
		OperandFactory::createInt32,
		OperandFactory::createFloat,
		OperandFactory::createDouble
	};

	return ((*fcts[type - 1])(value));
}

int				OperandFactory::getPrecision(const std::string &value, const int max)
{
	std::size_t	pos = value.find('.');

	if (pos == std::string::npos)
		return (0);
	return (std::min<std::size_t>(value.length() - pos - 1, max));
}

const IOperand	*OperandFactory::createInt8(const std::string &value)
{
	return (new Operand<int8_t>(value, Int8, 0));
}

const IOperand	*OperandFactory::createInt16(const std::string &value)
{
	return (new Operand<int16_t>(value, Int16, 0));
}

const IOperand	*OperandFactory::createInt32(const std::string &value)
{
	return (new Operand<int32_t>(value, Int32, 0));
}

const IOperand	*OperandFactory::createFloat(const std::string &value)
{
	return (new Operand<float>(value, Float, OperandFactory::getPrecision(value, 6)));
}

const IOperand	*OperandFactory::createDouble(const std::string &value)
{
	return (new Operand<double>(value, Double, OperandFactory::getPrecision(value, 10)));
}
