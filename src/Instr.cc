#include "Instr.h"
#include "IOperand.h"

Instr::Instr(void):
	_method_name(),
	_type(Undef),
	_value(),
	_format(0),
	_line()
{}

Instr::Instr(const Instr &src):
	_method_name(),
	_type(Undef),
	_value(),
	_format(0),
	_line()
{ *this = src; }

Instr::~Instr(void)
{}

Instr									&Instr::operator=(const Instr &rhs)
{
	if (this != &rhs)
	{
		this->_method_name = rhs._method_name;
		this->_type = rhs._type;
		this->_value = rhs._value;
		this->_format = rhs._format;
		this->_line = rhs._line;
	}
	return (*this);
}

/*
**	Function Map
*/

std::map<std::string, Instr::Method>	Instr::createMap(void)
{
	std::map<std::string, Instr::Method>	map;

	map["push"] = Instr::push;
	map["pop"] = Instr::pop;
	map["add"] = Instr::add;
	map["sub"] = Instr::sub;
	map["mul"] = Instr::mul;
	map["div"] = Instr::div;
	map["mod"] = Instr::mod;
	map["dump"] = Instr::dump;
	map["print"] = Instr::print;
	map["assert"] = Instr::assert;
	map["exit"] = Instr::exit;

	return (map);
}

Instr::Method							Instr::getMethod(const std::string &name)
{
	static std::map<std::string, Instr::Method>	map = Instr::createMap();

	return (map[name]);
}
/*
void									Instr::format(void)
{
	std::stringstream					ss;

	if (this->_format == 'x' || this->_format == 'o' || this->_format == 'b')
	{
		if (this->_type == Int8)
		{
			int8_t			value = 0;

			ss << this->_value;
			ss >> value;
			this->_value = std::to_string(value);
		}
		else if (this->_type == Int16)
		{
			int16_t			value = 0;

			ss << this->_value;
			ss >> value;
			this->_value = std::to_string(value);
		}
		else if (this->_type == Int16)
		{
			int8_t			value = 0;

			ss << this->_value;
			ss >> value;
			this->_value = std::to_string(value);
		}
	}
}
*/
/*
**	Setters
*/

void									Instr::setMethod(const std::string &methodname)
{
	this->_method_name = methodname;
}

void									Instr::setType(const eOperandType type)
{
	this->_type = type;
}

void									Instr::setValue(const std::string &value)
{
	this->_value = value;
}

void									Instr::setFormat(const char c)
{
	this->_format = c;
}

void									Instr::setLine(const int line)
{
	this->_line = line;
}

/*
**	Instructions
*/

void									Instr::compute(AbstractVm &avm)
{
	if (this->_type == Int32)
		this->formate<int32_t>();
	else if (this->_type == Int16)
		this->formate<int16_t>();
	else if (this->_type == Int8)
		this->formate<int8_t>();

	(*Instr::getMethod(this->_method_name))(this, avm);
}

void									Instr::push(const Instr *i, AbstractVm &avm)
{
	if (i->_type == Undef || i->_value == "")
		throw lexerparser::ParserWarningException("Cannot push undefined value", i->_line);
	avm._stack.push( OperandFactory::createOperand(i->_type, i->_value) );
}

void									Instr::pop(const Instr *i, AbstractVm &avm)
{
	if (!avm._stack.empty())
	{
		delete avm._stack.top();
		avm._stack.pop();
	}
	else
		throw lexerparser::ParserWarningException("Pop on empty stack", i->_line);
	(void)i;
}

void									Instr::exit(const Instr *i, AbstractVm &avm)
{
	avm._stop = true;
	(void)i;
}

void									Instr::assert(const Instr *i, AbstractVm &avm)
{
	const IOperand	*tmp;

	tmp = OperandFactory::createOperand(i->_type, i->_value);

	if (!avm._stack.empty() && (*avm._stack.top() != *tmp))
	{
		throw lexerparser::ParserAbortException("Assert " + tmp->toString(), i->_line);
	}
	delete tmp;
	(void)i;
}

void									Instr::print(const Instr *i, AbstractVm &avm)
{
	const IOperand	*o;
	int				v;

	if (!avm._stack.empty())
	{
		o = avm._stack.top();
		if (o->getType() == Int8)
		{
			avm._print_newline = true;
			v = atoi(o->toString().c_str());
			std::cout << static_cast<char>(v);
		}
		else
			throw lexerparser::ParserAbortException("Not an Int8", i->_line);
	}
	else
		throw lexerparser::ParserAbortException("Not enough operand on stack", i->_line);

	(void)i;
}

static std::string						removeZeros(std::string s)
{
	int					i;

	if (s.find('.') != std::string::npos)
	{
		i = s.length() - 1;
		while (i >= 0 && s[i] == '0')
			i--;
		if (s[i] == '.')
			s = s.substr(0, i);
		else
			s = s.substr(0, i + 1);
	}

	return (s);
}

void									Instr::dump(const Instr *i, AbstractVm &avm)
{
	std::stack<const IOperand*>	tmp = avm._stack;

	if (!tmp.empty() && avm._print_newline)
	{
		std::cout << std::endl;
		avm._print_newline = false;
	}
	while (!tmp.empty())
	{
		std::cout << removeZeros(( tmp.top() )->toString()) << std::endl;
		tmp.pop();
	}
	(void)i;
}

void									Instr::add(const Instr *i, AbstractVm &avm)
{
	const IOperand	*right;
	const IOperand	*left;

	if (avm._stack.size() >= 2)
	{
		right = avm._stack.top();
		avm._stack.pop();

		left = avm._stack.top();
		avm._stack.pop();

		avm._stack.push(*left + *right);

		delete right;
		delete left;
	}
	else
		throw lexerparser::ParserAbortException("Not enough operand on stack", i->_line);
}

void									Instr::sub(const Instr *i, AbstractVm &avm)
{
	const IOperand	*right;
	const IOperand	*left;

	if (avm._stack.size() >= 2)
	{
		right = avm._stack.top();
		avm._stack.pop();

		left = avm._stack.top();
		avm._stack.pop();

		avm._stack.push(*left - *right);

		delete right;
		delete left;
	}
	else
		throw lexerparser::ParserAbortException("Not enough operand on stack", i->_line);
}

void									Instr::mul(const Instr *i, AbstractVm &avm)
{
	const IOperand	*right;
	const IOperand	*left;

	if (avm._stack.size() >= 2)
	{
		right = avm._stack.top();
		avm._stack.pop();

		left = avm._stack.top();
		avm._stack.pop();

		avm._stack.push(*left * *right);

		delete right;
		delete left;
	}
	else
		throw lexerparser::ParserAbortException("Not enough operand on stack", i->_line);
}

void									Instr::div(const Instr *i, AbstractVm &avm)
{
	const IOperand	*right;
	const IOperand	*left;

	if (avm._stack.size() >= 2)
	{
		right = avm._stack.top();
		avm._stack.pop();

		left = avm._stack.top();
		avm._stack.pop();

		avm._stack.push(*left / *right);

		delete right;
		delete left;
	}
	else
		throw lexerparser::ParserAbortException("Not enough operand on stack", i->_line);
}

void										Instr::mod(const Instr *i, AbstractVm &avm)
{
	const IOperand	*right;
	const IOperand	*left;

	if (avm._stack.size() >= 2)
	{
		right = avm._stack.top();
		avm._stack.pop();

		left = avm._stack.top();
		avm._stack.pop();

		avm._stack.push(*left % *right);

		delete right;
		delete left;
	}
	else
		throw lexerparser::ParserAbortException("Not enough operand on stack", i->_line);
}
