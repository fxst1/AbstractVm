#ifndef INSTR_H
# define INSTR_H
# include "AbstractVm.h"

class			AbstractVm;

class			Instr
{
	public:

		typedef void (*Method)(const Instr *, AbstractVm &);

	private:

		std::string			_method_name;
		eOperandType		_type;
		std::string			_value;
		int					_line;

		std::map<std::string, Instr::Method>	createMap(void);
		Method									getMethod(const std::string &name);

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
		void				compute(AbstractVm &avm);
};

#endif
