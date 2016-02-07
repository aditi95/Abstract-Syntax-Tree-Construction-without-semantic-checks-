#include <iostream>
#include <string>

using namespace std;
//add ident to print
/*void ident(int n)
{
	for(int i = 0; i <n; i++)cout<<' ';
}
*/
class abstract_astnode
{
	public:
		virtual void print (int ident) = 0;
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
		virtual void print(int ident) = 0;
		virtual ~exp_astnode(){};
};

class unary_astnode : public exp_astnode
{
	private:
		exp_astnode * left;
	public:
		unary_astnode(string s, exp_astnode *l)
		{
			cout<<"jkljlhknkkjbj";
			exp_name = s;
			left = l;
		}
		virtual void print(int ident)
		{
			
			cout<< "("<<exp_name << ' ';
			left->print(0);
			cout<<")"; 
		}
		virtual ~unary_astnode()
		{
			delete left;
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
		virtual void print(int ident)
		{
			cout<< "("<<exp_name << ' ';
			left->print(0);
			cout<<' ';
			right->print(0);
			cout<<")"; 
		}
		virtual ~binary_astnode()
		{
			delete left;
			delete right;
		}
		
};

class float_astnode : public exp_astnode
{
	private:
		float val;
	public:
		float_astnode(float s){val = s;}
		virtual void print(int ident)
		{
			cout<< "(FloatConst " << ' '<<val<<")"; 
		}
};

class int_astnode : public exp_astnode
{
	private:
		int val;
	public:
		int_astnode(int s){val = s;}
		virtual void print(int ident)
		{
			cout<< "(IntConst " << ' '<<val<<")"; 
		}
};

class string_astnode : public exp_astnode
{
	private:
		string val;
	public:
		string_astnode(string s){val = s;}
		virtual void print(int ident)
		{
			cout<< "(StringConst " << ' '<<val<<")"; 
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
		virtual void print(int ident)
		{
			if(l != 0){
				l->print(ident);
				cout<<"\n";
				cout<<string(ident, ' ');
				e->print(ident);
			}
			else 
			e->print(ident); 
		}
		virtual ~explist_astnode()
		{
			delete l ;
			delete e;
		}
		
};
class func_astnode : public exp_astnode
{
	private:
		string val; //identifier
		exp_astnode * args;
	public:
		func_astnode(string s){
			val = s;
			args = 0;
		}
		
		func_astnode(string s, exp_astnode * a){
			val = s;
			args = a;
		}
		virtual void print(int ident)
		{
			cout<< "(" <<val <<' ';
			if(args!=0)args->print(0);
			cout<<")"; 
		}
		virtual ~func_astnode()
		{
			delete args;
		}
};		

class stmt_astnode : public abstract_astnode
{
	protected:
		string stmt_name;
	public:
		virtual void print(int ident)=0;
		virtual ~stmt_astnode(){}
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
		virtual void print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			left->print(0);
			cout<<' ';
			right->print(0);
			cout<<")"; 
		}
		virtual ~ass_astnode()
		{
			delete left;
			delete right;
			cout<<"destroy assignment"<<endl;
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
		virtual void print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			left->print(0);
			cout<<"\n";
			cout<<string(ident + 4, ' ');
			middle->print(ident + 4);
			cout<<"\n";
			cout<<string(ident + 4, ' ');
			right->print(ident + 4);
			cout<<")"; 
		}
		virtual ~if_astnode()
		{
			delete left;
			delete middle;
			delete right;
			cout << "deleting if"<<endl;
		}
		

};

class empty_astnode : public stmt_astnode
{
	public:
		empty_astnode(){stmt_name = "Empty";}

		virtual void print(int ident)
		{
			cout<< "("<<stmt_name<<")"; 
		}
		virtual ~empty_astnode()
		{
			cout << "deleting empty\n";
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

		virtual void print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			left->print(0);
			cout<<")"; 
		}
		virtual ~return_astnode()
		{
			delete left;
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

		virtual void print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			if(left!=0)left->print(0);
			cout << ' ';
			if(right!=0)right->print(0);
			cout<<")"; 
		}
		virtual ~assgn_astnode()
		{
			delete left;
			delete right;
			cout << "deleting assgn" << endl;
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

		virtual void print(int ident)
		{
			cout<< "("<<stmt_name <<' ';
			left->print(0);
			cout<<"\n";
			cout<<string(ident + 5, ' ');
			middle->print(ident + 5);
			cout<<"\n";
			cout<<string(ident + 5, ' ');
			right->print(ident + 5);
			cout<<"\n";
			cout<<string(ident + 5, ' ');
			stmt->print(ident + 5);
			cout<<")"; 
		}
		virtual ~for_astnode()
		{
			delete left;
			delete middle;
			delete right;
			delete stmt;
			cout << "for destructor"<<endl;
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

		virtual void print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			left->print(0);
			cout<<"\n";
			cout<<string(ident + 7, ' ');
			stmt->print(ident + 7);
			cout<<")"; 
		}
		virtual ~while_astnode()
		{
			delete left;
			delete stmt;
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
		virtual void print(int ident)
		{
			if(list != 0){
				list->print(ident);
				cout<<"\n";
				cout<<string(ident, ' ');
				stmt->print(ident);
			}
			else 
			stmt->print(ident);
			
		}
		virtual ~list_astnode()
		{
			delete list;
			delete stmt;
			cout << "deleting list"<<endl;
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

		virtual void print(int ident)
		{
			cout<< "(Block [";
			block->print(ident + 8);
			cout<<"])";
		}
		virtual ~block_astnode()
		{
			cout << "destroying block"<<endl;
			delete block;
		}

		
};

class ref_astnode : public exp_astnode
{
	protected:
		string ref_name;
	public:
		virtual void print(int ident)=0;
		virtual ~ref_astnode(){}
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

		virtual void print(int ident)
		{
			cout<< "("<<ref_name<<" \"" <<id_name<<"\")" ;
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

		virtual void print(int ident)
		{
			cout<< "(";
			id->print(0);
			cout<<" [";
			params->print(0);
			cout<<"]";
		}
		virtual ~arrref_astnode()
		{
			delete id;
			delete params;
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

		virtual void print(int ident)
		{
			cout<< "( *";
			id->print(0);
			cout<<")";
		}
		virtual ~ptr_astnode()
		{
			delete id;
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

		virtual void print(int ident)
		{
			cout<< "( &";
			id->print(0);
			cout<<")";
		}
		virtual ~deref_astnode()
		{
			delete id;
		}
};