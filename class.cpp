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
	public:
		virtual void print() = 0;
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
		float val;
	public:
		float_astnode(float s){val = s;}
		virtual void print()
		{
			cout<< "(FloatConst " << " "<<val<<")"; 
		}
};

class int_astnode : public exp_astnode
{
	private:
		int val;
	public:
		int_astnode(int s){val = s;}
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

class explist_astnode : public exp_astnode
{
	private:
		exp_astnode *l;
		exp_astnode *e;
	public:
		explist_astnode(exp_astnode *e1)
		{
			e = e1;
			l = 0;
		}
		explist_astnode(exp_astnode *y, exp_astnode *x)
		{
			l = y;
			e = x;
		}
		virtual void print()
		{
			
			if(l!=0){
				l->print();
				cout << "\n";
			}
			e->print(); 
		}
};

class func_astnode : public exp_astnode
{
	private:
		string val;
		exp_astnode * args;
	public:
		func_astnode(string s){
			val = s;
			args =0;
		}
		func_astnode(string s,exp_astnode * a){
			val = s;
			args =a;
		}
		virtual void print()
		{
			cout<< "(" <<val <<" ";
			if(args!=0)
				args->print(); 
			cout<<")"; 
		}
};

class stmt_astnode : public abstract_astnode
{
	protected:
		string stmt_name;
	public:
		virtual void print()=0;
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
class assgn_astnode : public stmt_astnode
{
	private:
		exp_astnode * left, *right;
	public:
		assgn_astnode()
		{
			stmt_name = "Ass";
			left = 0;
			right = 0;
		}
		assgn_astnode(exp_astnode *l, exp_astnode *r)
		{
			stmt_name = "Ass";
			left = l;
			right = r;
		}

		virtual void print()
		{
			cout<< "("<<stmt_name << " ";
			if(left!=0)left->print();
			cout <<" ";
			if(right!=0)right->print();
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
		stmt_astnode * list;
	public:
		list_astnode(stmt_astnode *s)
		{
			stmt = s;
			list = 0;
		}
		list_astnode(stmt_astnode *s, stmt_astnode *l)
		{
			stmt = s;
			list = l;
		}
		virtual void print()
		{
			cout<< "(";
			if(list != 0){
			list->print();
			cout<<"\n";}
			stmt->print();
			cout<<")"; 
		}

};

class block_astnode : public stmt_astnode
{
	private:
		stmt_astnode *block;
	public:
		block_astnode(stmt_astnode *l)
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

class ref_astnode : public exp_astnode
{
	protected:
		string ref_name;
	public:
		virtual void print()=0;
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
		exp_astnode *id;
		exp_astnode * params;
	public:
		arrref_astnode(exp_astnode *a,exp_astnode * b)
		{
			id=a;
			params = b;
		}

		virtual void print()
		{
			cout<< "(";
			id->print();
			cout<<" [ ";
			params->print();
			cout<<"]";
		}

};

class ptr_astnode : public ref_astnode
{
	private:
		exp_astnode *id;
	public:
		ptr_astnode(exp_astnode *a)
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
		exp_astnode *id;
	public:
		deref_astnode(exp_astnode *a)
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
