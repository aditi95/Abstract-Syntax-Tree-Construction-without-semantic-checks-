

%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT IF ELSE WHILE FOR RETURN IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL EQ_OP NE_OP LE_OP GE_OP AND_OP OR_OP INC_OP PTR_OP STRUCT

%polymorphic STRING : std::string; EXPAST : exp_astnode*; STMAST : stmt_astnode*; INT : int; FLOAT : float;

%type<STRING> unary_operator IDENTIFIER STRING_LITERAL
%type<INT> INT_CONSTANT
%type<FLOAT> FLOAT_CONSTANT
%type<EXPAST> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression primary_expression postfix_expression l_expression
%type<STMAST> compound_statement statement assignment_statement selection_statement iteration_statement

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
        : INT_CONSTANT {std::cout<<"dvals "<<$1<<endl;}
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
        | statement_list statement	
	;

statement
        : '{' statement_list '}'  //a solution to the local decl problem
        | selection_statement 	
        | iteration_statement 	
	| assignment_statement	
        | RETURN expression ';'	
        ;

assignment_statement
	: ';' 								
	|  l_expression '=' expression ';'	
	;

expression
	: logical_and_expression
        | expression OR_OP logical_and_expression
	;
logical_and_expression
        : equality_expression
        | logical_and_expression AND_OP equality_expression 
	;

equality_expression
	: relational_expression 
        | equality_expression EQ_OP relational_expression 	
	| equality_expression NE_OP relational_expression
	;
relational_expression
	: additive_expression
        | relational_expression '<' additive_expression 
	| relational_expression '>' additive_expression 
	| relational_expression LE_OP additive_expression 
        | relational_expression GE_OP additive_expression 
	;

additive_expression 
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression 
	| additive_expression '-' multiplicative_expression 
	;

multiplicative_expression
	: unary_expression
	| multiplicative_expression '*' unary_expression 
	| multiplicative_expression '/' unary_expression 
	;
unary_expression
	: postfix_expression  				
	| unary_operator postfix_expression 
	;

postfix_expression
	: primary_expression  				
        | IDENTIFIER '(' ')' 				
	| IDENTIFIER '(' expression_list ')' 
	| l_expression INC_OP 				
	;

primary_expression
	: l_expression
        | l_expression '=' expression   
        | INT_CONSTANT {std::cout<<"dvalds "<<$1<<endl;}
	| FLOAT_CONSTANT
        | STRING_LITERAL
	| '(' expression ')' 	
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