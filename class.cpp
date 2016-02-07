#include <iostream>
#include <string>
#include <algorithm>
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
		virtual int print (int ident) = 0;
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
		virtual int print(int ident) = 0;
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
		virtual int print(int ident)
		{
			
			cout<< "("<<exp_name << ' ';
			int x = left->print(ident + exp_name.size()+2);
			cout<<")"; 
			return x+3+exp_name.size();
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
		virtual int print(int ident)
		{
			cout<< "("<<exp_name << ' ';
			int x = left->print(ident+ exp_name.size()+2);
			cout<<' ';
			int y = right->print(ident+ exp_name.size()+2+x+1);
			cout<<")"; 
			return x+y+exp_name.size()+4;
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
		virtual int print(int ident)
		{
			cout<< "(FloatConst "<<val<<")"; 
			string s = to_string(val);
			return 13 + s.size();
		}
};

class int_astnode : public exp_astnode
{
	private:
		int val;
	public:
		int_astnode(int s){val = s;}
		virtual int print(int ident)
		{
			cout<< "(IntConst "<<val<<")"; 
			string s = to_string(val);
			return s.size() + 11;
		}
};

class string_astnode : public exp_astnode
{
	private:
		string val;
	public:
		string_astnode(string s){val = s;}
		virtual int print(int ident)
		{
			cout<< "(StringConst "<<val<<")"; 
			return val.size() + 14;
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
		virtual int print(int ident)
		{
			int x = 0, y = 0;
			if(l != 0){
				x = l->print(ident);
				cout<<"\n";
				cout<<string(ident, ' ');
				y = e->print(ident);
			}
			else 
			x = e->print(ident);
			return max(x, y); 
		
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
		virtual int print(int ident)
		{
			int x = 0;
			cout<< "(" <<val <<' ';
			if(args!=0)x = args->print(ident+2+val.size());
			cout<<")"; 
			return x + val.size() + 3;
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
		virtual int print(int ident)=0;
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
		virtual int print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			int x = left->print(ident+2+stmt_name.size());
			cout<<' ';
			int y = right->print(ident + 3 + stmt_name.size()+ x);
			cout<<")"; 
			return stmt_name.size()+x+y+4;
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
		virtual int print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			int x = left->print(ident + 2 + stmt_name.size());
			cout<<"\n";
			cout<<string(ident + 4, ' ');
			int y = middle->print(ident + 4);
			cout<<"\n";
			cout<<string(ident + 4, ' ');
			int z = right->print(ident + 4);
			cout<<")"; 
			return max(max(y,z), x + 4);
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

		virtual int print(int ident)
		{
			cout<< "("<<stmt_name<<")";
			return 2+ stmt_name.size(); 
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

		virtual int print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			int x = left->print(ident + 2 + stmt_name.size());
			cout<<")"; 
			return x  + stmt_name.size() + 3;
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

		virtual int print(int ident)
		{
			int x = 0, y = 0;
			cout<< "("<<stmt_name << ' ';
			if(left!=0)x = left->print(ident + stmt_name.size()+2);
			cout << ' ';
			if(right!=0)y = right->print(ident+ x+ 3 + stmt_name.size());
			cout<<")"; 
			return stmt_name.size() + 4 + x + y;
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

		virtual int print(int ident)
		{
			cout<< "("<<stmt_name <<' ';
			int x = left->print(ident+5);
			cout<<"\n";
			cout<<string(ident + 5, ' ');
			int y = middle->print(ident + 5);
			cout<<"\n";
			cout<<string(ident + 5, ' ');
			int z = right->print(ident + 5);
			cout<<"\n";
			cout<<string(ident + 5, ' ');
			int w = stmt->print(ident + 5);
			cout<<")"; 
			return max(5+x, max(y,max(z,w+1)));
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

		virtual int print(int ident)
		{
			cout<< "("<<stmt_name << ' ';
			int x = left->print(ident+7);
			cout<<"\n";
			cout<<string(ident + 7, ' ');
			int y = stmt->print(ident + 7);
			cout<<")";
			return max(7+x, y+1); 
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
		virtual int print(int ident)
		{
			int x = 0, y= 0;
			if(list != 0){
				x = list->print(ident);
				cout<<"\n";
				cout<<string(ident, ' ');
				y = stmt->print(ident);
			}
			else 
			y = stmt->print(ident);
			return max(x, y);
			
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

		virtual int print(int ident)
		{
			cout<< "(Block [";
			int x = block->print(ident + 8);
			cout<<"])";
			return 10 + x;
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
		virtual int print(int ident)=0;
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

		virtual int print(int ident)
		{
			cout<< "("<<ref_name<<" \"" <<id_name<<"\")" ;
			return 5+ref_name.size()+id_name.size();
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

		virtual int print(int ident)
		{
			cout<< "(";
			int x = id->print(ident+1);
			cout<<"[";
			int y = params->print(ident+2+x);
			cout<<"])";
			return 4+x+y;
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

		virtual int print(int ident)
		{
			cout<< "(* ";
			int x = id->print(ident);
			cout<<")";
			return 4+x;
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

		virtual int print(int ident)
		{
			cout<< "(& ";
			int x = id->print(ident);
			cout<<")";
			return 4 + x;

		}
		virtual ~deref_astnode()
		{
			delete id;
		}
};