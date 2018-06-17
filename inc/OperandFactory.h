#ifndef OPERANDFACTORY_H
# define OPERANDFACTORY_H
# include "IOperand.h"

class	OperandFactory
{
	public:

		typedef const IOperand *(*factory)(const std::string &);

		static const IOperand	*createOperand(eOperandType type, const std::string &value);

	private:

		static int				getPrecision(const std::string &value, const int max);

		static const IOperand	*createInt8(const std::string &value);
		static const IOperand	*createInt16(const std::string &value);
		static const IOperand	*createInt32(const std::string &value);
		static const IOperand	*createFloat(const std::string &value);
		static const IOperand	*createDouble(const std::string &value);
};

#endif
