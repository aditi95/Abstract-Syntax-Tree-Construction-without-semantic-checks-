#include <iostream>
using namespace std;
class obj
{
	int a;
	public :
	virtual ~obj(){}
	
};
class a : public obj
{
	public:
	~a()
	{
		cout << "destructor of a"<<endl;
	}
};
int main()
{
	int a = 55;
	int *b, *c;
	b = new int;
	*b = 56;
	c = b;
		cout << b <<" " << c<< endl;

	delete c;
	cout << b <<" " << c<< endl;

	
}
