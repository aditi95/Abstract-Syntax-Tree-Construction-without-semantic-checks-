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
	// 	protected:
	// 	// virtual void setType(basic_types) = 0;
	// private:
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
			cout<< "("<<exp_name << " ";
			left->print();
			cout<<")"; 
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
			cout<< "("<<exp_name << " ";
			left->print();
			cout<<" ";
			right->print();
			cout<<")"; 
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

class func_astnode : public exp_astnode
{
	private:
		string val;
		vector <exp_astnode *> args;
	public:
		func_astnode(string s){
			val = s;
			args = new vector<exp_astnode*>();
		}
		void addEXPASTVec(vector <exp_astnode *> a)
		{
			args = a;
		}
		virtual void print()
		{
			cout<< "(" <<val ;
			for(int i = 0; i <args.size();i++)
			{
				args[i]->print();
				cout<<endl;
			} 
			cout<<")"; 
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
		exp_astnode * left, *right;
	public:
		ass_astnode(exp_astnode *l, exp_astnode *r)
		{
			stmt_name = "Ass";
			left = l;
			right = r;
		}
		virtual void print()
		{
			cout<< "("<<stmt_name << " ";
			left->print();
			cout<<" ";
			right->print();
			cout<<")"; 
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
			cout<< "("<<stmt_name << " ";
			left->print();
			cout<<"\n";
			middle->print();
			cout<<"\n";
			right->print();
			cout<<")"; 
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
			cout<< "("<<stmt_name << " ";
			left->print();
			cout<<")"; 
		}

};


class for_astnode : public stmt_astnode
{
	private:
		exp_astnode * left, *middle, *right;
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
			cout<< "("<<stmt_name <<" ";
			left->print();
			cout<<"\n";
			middle->print();
			cout<<"\n";
			right->print();
			cout<<"\n";
			stmt->print();
			cout<<")"; 
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
			cout<< "("<<stmt_name << " ";
			left->print();
			cout<<"\n";
			stmt->print();
			cout<<")"; 
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
			cout<< "(";
			stmt->print();
			cout<<"\n";
			list->print();
			cout<<")"; 
		}

};

class block_astnode : public stmt_astnode
{
	private:
		list_astnode *block;
	public:
		block_astnode(list_astnode *l)
		{
			stmt_name = "Block";
			block = l;
		}

		virtual void print()
		{
			cout<< "(Block [";
			block->print();
			cout<<"])";
		}

};

class ref_astnode : public abstract_astnode
{
	protected:
		string ref_name;
};

class id_astnode : public ref_astnode
{
	private:
		string id_name;
	public:
		id_astnode(string name)
		{
			ref_name = "Id";
			id_name = name;
		}

		virtual void print()
		{
			cout<< "("<<ref_name<<" \"" <<id_name<<"\" )" ;
		}

};

class arrref_astnode : public ref_astnode
{
	private:
		id_astnode *id;
		vector <exp_astnode *> params;
	public:
		arrref_astnode(id_astnode *a,vector <exp_astnode *> b)
		{
			id=a;
			params = new vector<exp_astnode*>();
		}

		void addEXPAST(exp_astnode * exp_ast)
		{
			(*params).push_back(exp_ast);
		}

		virtual void print()
		{
			cout<< "(";
			id->print();
			cout<<" [ ";
			for(int i = 0; i<params.size();i++)
			{
				params[i]->print();
				cout<<"\n";
			}
			cout<<"]";
		}

};

class ptr_astnode : public ref_astnode
{
	private:
		ref_astnode *id;
	public:
		ptr_astnode(ref_astnode *a)
		{
			id=a;
		}

		virtual void print()
		{
			cout<< "( *";
			id->print();
			cout<<")";
		}

};

class deref_astnode : public ref_astnode
{
	private:
		ref_astnode *id;
	public:
		deref_astnode(ref_astnode *a)
		{
			id=a;
		}

		virtual void print()
		{
			cout<< "( &";
			id->print();
			cout<<")";
		}

};
