#ifndef INSTR_H
# define INSTR_H
# include "AbstractVm.h"

class			AbstractVm;

class			Instr
{
	public:

		typedef void (*Method)(const Instr *, AbstractVm &);
		std::string			_method_name;

	private:

		eOperandType		_type;
		std::string			_value;
		char				_format;
		int					_line;

		std::map<std::string, Instr::Method>	createMap(void);
		Method									getMethod(const std::string &name);

		template<typename T>
		void 									formate(void)
		{
			if (this->_format == 'x' || this->_format == 'o' || this->_format == 'b')
			{
				T			value = static_cast<T>( atoi(this->_value.c_str()) );

				this->_value = std::to_string( -(~(value) + 1) );
			}
		}

		static void			push(const Instr *i, AbstractVm& avm);
		static void			pop(const Instr *i, AbstractVm& avm);
		static void			dump(const Instr *i, AbstractVm& avm);
		static void			print(const Instr *i, AbstractVm& avm);
		static void			add(const Instr *i, AbstractVm& avm);
		static void			sub(const Instr *i, AbstractVm& avm);
		static void			mul(const Instr *i, AbstractVm& avm);
		static void			div(const Instr *i, AbstractVm& avm);
		static void			mod(const Instr *i, AbstractVm& avm);
		static void			assert(const Instr *i, AbstractVm& avm);
		static void			exit(const Instr *i, AbstractVm& avm);

	public:

		Instr(void);
		Instr(const Instr &src);
		~Instr(void);

		Instr				&operator=(const Instr &rhs);

		void				setMethod(const std::string &methodname);
		void				setLine(const int line);
		void				setType(const eOperandType type);
		void				setValue(const std::string &value);
		void				setFormat(const char c);

		void				compute(AbstractVm &avm);
};

#endif
