

%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT IF ELSE WHILE FOR RETURN IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL EQ_OP NE_OP LE_OP GE_OP AND_OP OR_OP INC_OP PTR_OP STRUCT

%polymorphic STRING : std::string; EXPAST : exp_astnode*; STMAST : stmt_astnode*; REFAST : ref_astnode* ; INT : int; FLOAT : float;

%type<STRING> unary_operator IDENTIFIER STRING_LITERAL
%type<INT> INT_CONSTANT
%type<FLOAT> FLOAT_CONSTANT
%type<EXPAST> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression primary_expression postfix_expression l_expression
%type<STMAST> compound_statement statement assignment_statement selection_statement iteration_statement
%type<REFAST> id_astnode arrref_astnode ptr_astnode deref_astnode

%%

translation_unit 
        :  struct_specifier
 	| function_definition 
 	| translation_unit function_definition 
        | translation_unit struct_specifier
        ;

struct_specifier 
        : STRUCT IDENTIFIER '{' declaration_list '}' ';'
        ;

function_definition
	: type_specifier fun_declarator compound_statement 
	;

type_specifier
        : base_type
        | type_specifier '*'
        ;

base_type 
        : VOID 	
        | INT {std::cout<<"dval "<<d_val__<<endl;}  
	| FLOAT 
        | STRUCT IDENTIFIER 
        ;

fun_declarator
	: IDENTIFIER '(' parameter_list ')' 
	| IDENTIFIER '(' ')' 
	;

parameter_list
	: parameter_declaration 
	| parameter_list ',' parameter_declaration 
	;

parameter_declaration
	: type_specifier declarator 
        ;

declarator
	: IDENTIFIER 
	| declarator '[' constant_expression ']' 
        ;

constant_expression 
        : INT_CONSTANT
        | FLOAT_CONSTANT 
        ;

compound_statement
	: '{' '}' 
	{
		$$ = new block_astnode(new vector<stmt_astnode *> ());
		($$)->print();
	}
	| '{' statement_list '}' 
	{
		$$ = new block_astnode($2);
		($$)->print();
	}
        | '{' declaration_list statement_list '}' 
        {
		$$ = new block_astnode($3);
		($$)->print();
	}
	;

statement_list
	: statement	
	{
		$$ = new vector<stmt_astnode *>();
		($$)->push_back($1);
	}	
        | statement_list statement	
        {
        	((vector<stmt_astnode *>*)$1)->push_back($2);
        	$$ = $1;
        }
	;

statement
        : '{' statement_list '}'  //a solution to the local decl problem
        {
		$$ = new block_astnode($2);
	  }
        | selection_statement 
        {
        	$$ = $1;
        }	
        | iteration_statement 
        {
        	$$ = $1;
        }	
	| assignment_statement	
	{
		$$ = $1;
	}
        | RETURN expression ';'
        {
        	$$ = new return_astnode($2);
        }	
        ;

assignment_statement
	: ';' 	
	{
		$$ = new empty_astnode();
	}							
	|  l_expression '=' expression ';'
	{
		$$ = new ass_astnode($1,$3);
	}	
	;

expression
	: logical_and_expression
	{
		$$ = $1;
	}
        | expression OR_OP logical_and_expression
        {
        	$$ = new binary_astnode("OR",$1,$3);
        }
	;
logical_and_expression
        : equality_expression
        {
        	$$ = $1;
        }
        | logical_and_expression AND_OP equality_expression 
        {
        	$$ = new binary_astnode("AND",$1,$3);
        }
	;

equality_expression
	: relational_expression 
	{
		$$ = $1;
	}
        | equality_expression EQ_OP relational_expression 	
        {
        	$$ = new binary_astnode("EQ_OP",$1,$3);
        }
	| equality_expression NE_OP relational_expression
	{
		$$ = new binary_astnode("NE_OP",$1,$3);
	}
	;
relational_expression
	: additive_expression
	{
		$$ = $1;
	}
        | relational_expression '<' additive_expression 
        {
        	$$ = new binary_astnode("LT",$1,$3);
        }
	| relational_expression '>' additive_expression 
	{
		$$ = new binary_astnode("GT",$1,$3);
	}
	| relational_expression LE_OP additive_expression
	{
		$$ = new binary_astnode("LE_OP",$1,$3);
	} 
        | relational_expression GE_OP additive_expression 
        {
        	$$ = new binary_astnode("GE_OP",$1,$3);
        }
	;

additive_expression 
	: multiplicative_expression
	{
		$$ = $1;
	}
	| additive_expression '+' multiplicative_expression
	{
		$$ = new binary_astnode("Plus",$1,$3);
	} 
	| additive_expression '-' multiplicative_expression 
	{
		$$ = new binary_astnode("Minus",$1,$3);
	}
	;

multiplicative_expression
	: unary_expression
	{
		$$ = $1;
	}
	| multiplicative_expression '*' unary_expression 
	{
		$$ = new binary_astnode("Mult",$1,$3);
	}
	| multiplicative_expression '/' unary_expression 
	{
		$$ = new binary_astnode("Div",$1,$3);
	}
	;
unary_expression
	: postfix_expression 
	{
		$$ = $1;
	} 				
	| unary_operator postfix_expression
	{
		$$ = new unary_astnode($1,$2);
	} 
	;

postfix_expression
	: primary_expression  	
	{
		$$ = $1;
	}			
        | IDENTIFIER '(' ')' 		
        {
        	$$ = new func_astnode(new id_astnode($1));
        }		
	| IDENTIFIER '(' expression_list ')' 
	{
		$$ = new func_astnode(new id_astnode($1));
		((func_astnode *)$$)->addEXPASTVec($3);
	}
	| l_expression INC_OP 	
	{
		$$ = new unary_astnode("PP",$2);
	}			
	;

primary_expression
	: l_expression
	{
		$$ = $1;
	}
        | l_expression '=' expression   
        | INT_CONSTANT
	| FLOAT_CONSTANT
        | STRING_LITERAL
	| '(' expression ')' 
	{
		$$ = $2;
	}	
	;

l_expression
        : IDENTIFIER
        | l_expression '[' expression ']' 	
        | '*' l_expression
        | '&' l_expression // & and * are similar
        | l_expression '.' IDENTIFIER
        | l_expression PTR_OP IDENTIFIER	
        ;

expression_list
        : expression
        | expression_list ',' expression
	;

unary_operator
        : '-'	
	| '!' 	
	;

selection_statement
        : IF '(' expression ')' statement ELSE statement 
	;

iteration_statement
	: WHILE '(' expression ')' statement 	
	| FOR '(' expression ';' expression ';' expression ')' statement  //modified this production
        ;

declaration_list
        : declaration  					
        | declaration_list declaration
	;

declaration
	: type_specifier declarator_list';' 
	;

declarator_list
	: declarator
	| declarator_list ',' declarator 
 	;