#include <iostream>
#include <string>

using namespace std;

class abstract_astnode
{
	public:
		virtual void print () = 0;
		// virtual string generate_code(const symbolTable&) = 0;
		// virtual basic_types getType() = 0;
		// virtual bool checkTypeofAST() = 0;
		protected:
		// virtual void setType(basic_types) = 0;
	private:
		// typeExp astnode_type;
};
class exp_astnode : public abstract_astnode
{
	protected:
		string exp_name;
};
class unary_astnode : public exp_astnode
{
	private:
		exp_astnode * left;
	public:
		unary_astnode(string s, exp_astnode *l)
		{
			exp_name = s;
			left = l;
		}
		virtual void print()
		{
			cout<< "("<<exp_name << " "<<left->print()<<")"; 
		}
};

class binary_astnode : public exp_astnode
{
	private:
		exp_astnode * left, *right;
	public:
		binary_astnode(string s, exp_astnode *l, exp_astnode* r)
		{
			exp_name = s;
			left = l;
			right = r;
		}
		virtual void print()
		{
			cout<< "("<<exp_name << " "<<left->print()<<" "<<right->print()<<")"; 
		}
};


class float_astnode : public exp_astnode
{
	private:
		string val;
	public:
		float_astnode(string s){val = s;}
		virtual void print()
		{
			cout<< "(FloatConst " << " "<<val<<")"; 
		}
};

class int_astnode : public exp_astnode
{
	private:
		string val;
	public:
		int_astnode(string s){val = s;}
		virtual void print()
		{
			cout<< "(IntConst " << " "<<val<<")"; 
		}
};

class string_astnode : public exp_astnode
{
	private:
		string val;
	public:
		string_astnode(string s){val = s;}
		virtual void print()
		{
			cout<< "(StringConst " << " "<<val<<")"; 
		}
};


class id_astnode : public exp_astnode
{
	private:
		string val;
	public:
		id_astnode(string s){val = s;}
		virtual void print()
		{
			cout<< "(Id " << " \""<<val<<"\")"; 
		}
};


class stmt_astnode : public abstract_astnode
{
	protected:
		string stmt_name;
};




class ass_astnode : public stmt_astnode
{
	private:
		exp_astnode * left, right;
	public:
		ass_astnode(exp_astnode *l, exp_astnode *r)
		{
			stmt_name = "Ass";
			left = l;
			right = r;
		}
		virtual void print()
		{
			cout<< "("<<stmt_name << " "<<left->print() <<" " << right->print()<<")"; 
		}

};


class if_astnode : public stmt_astnode
{
	private:
		exp_astnode * left;
		stmt_astnode *middle, *right;
	public:
		if_astnode(exp_astnode *l, stmt_astnode * m, stmt_astnode *r)
		{
			stmt_name = "If";
			left = l;
			right = r;
			middle = m;
		}
		virtual void print()
		{
			cout<< "("<<stmt_name << " "<<left->print() <<"\n"<<middle->print<<"\n" << right->print()<<")"; 
		}

};


class empty_astnode : public stmt_astnode
{
	public:
		empty_astnode(){stmt_name = "Empty";}

		virtual void print()
		{
			cout<< "("<<stmt_name<<")"; 
		}

};


class return_astnode : public stmt_astnode
{
	private:
		exp_astnode * left;
	public:
		return_astnode(exp_astnode *l)
		{
			stmt_name = "Return";
			left = l;
		}

		virtual void print()
		{
			cout<< "("<<stmt_name << " "<<left->print()<<")"; 
		}

};


class for_astnode : public stmt_astnode
{
	private:
		exp_astnode * left, middle, right;
		stmt_astnode *stmt;
	public:
		for_astnode(exp_astnode *l, exp_astnode *m, exp_astnode *r, stmt_astnode *s)
		{
			stmt_name = "For";
			left = l;
			middle = m;
			right = r;
			stmt = s;
		}

		virtual void print()
		{
			cout<< "("<<stmt_name <<" "<<left->print()<<"\n"<<middle->print()<<"\n"<<right->print()<<"\n"<<stmt->print()<<")"; 
		}

};

class while_astnode : public stmt_astnode
{
	private:
		exp_astnode * left;
		stmt_astnode * stmt;
	public:
		while_astnode(exp_astnode *l, stmt_astnode *s)
		{
			stmt_name = "While";
			left = l;
			stmt = s;
		}

		virtual void print()
		{
			cout<< "("<<stmt_name << " "<<left->print()<<"\n"<<stmt->print()<<")"; 
		}

};
class block_astnode : public stmt_astnode
{
	private:
		list_astnode *block;
	public:
		while_astnode(list_astnode *l)
		{
			stmt_name = "Block";
			block = l;
		}

		virtual void print()
		{
			cout<< "(Block ["<<list->print()<<"])";
		}

};

class list_astnode : public stmt_astnode
{
	private:
		stmt_astnode * stmt;
		list_astnode * list;
	public:
		list_astnode(stmt_astnode *s, list_astnode *l)
		{
			stmt = s;
			list = l;
		}
		virtual void print()
		{
			cout<< "("<<stmt->print()<<"\n"<<list->print()<<")"; 
		}

};

