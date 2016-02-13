

%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT IF ELSE WHILE FOR RETURN IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL EQ_OP NE_OP LE_OP GE_OP AND_OP OR_OP INC_OP PTR_OP STRUCT

%polymorphic STRING : std::string; EXPAST : exp_astnode*; STMAST : stmt_astnode*; REFAST : ref_astnode*; INT1 : int; FLOAT1 : float; 

%type<STRING> unary_operator INC_OP IDENTIFIER STRING_LITERAL
%type<INT1> INT_CONSTANT
%type<FLOAT1> FLOAT_CONSTANT
%type<EXPAST> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression primary_expression postfix_expression constant_expression expression_list
%type<STMAST> compound_statement statement selection_statement iteration_statement statement_list assignment_statement
%type<REFAST> declarator l_expression parameter_declaration

%%

translation_unit 
        :  struct_specifier{}
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
        | INT   
	| FLOAT 
        | STRUCT IDENTIFIER 
        ;

fun_declarator
	: IDENTIFIER '(' parameter_list ')' 
	| IDENTIFIER '(' ')' 
	;

parameter_list
	: parameter_declaration 
	{$$ = $1;}
	| parameter_list ',' parameter_declaration 
	;

parameter_declaration
	: type_specifier declarator 
        ;

declarator
	: IDENTIFIER 
	{$$ = new id_astnode($1);}
	| declarator '[' constant_expression ']' 
	{$$ = new arrref_astnode($1, $3);}
    ;
	

constant_expression 
        : INT_CONSTANT {$$ = new int_astnode($1); }
        | FLOAT_CONSTANT {$$ = new float_astnode($1);}
        ;

compound_statement
	: '{' '}' 
	{
		$$ = new empty_astnode();
		($$)->print(0);
		delete $$;
	}
	| '{' statement_list '}' 
	{
		$$ = new block_astnode($2);
		($$)->print(0);
		delete $$;
	}
        | '{' declaration_list statement_list '}' 
        {
		$$ = new block_astnode($3);
		($$)->print(0);
		delete $$;
	}
	;

statement_list
	: statement		
	{$$ = new list_astnode($1);}
        | statement_list statement
        {$$ = new list_astnode($2, $1);}	
	;

statement
        : '{' statement_list '}'  //a solution to the local decl problem
        {$$ = new block_astnode($2); }
        | selection_statement
        {$$ = $1;} 	
        | iteration_statement
        {$$ = $1;} 	
	| assignment_statement	
	{$$ = $1;}
        | RETURN expression ';'
        {$$ = new return_astnode($2);}	
        ;

assignment_statement
	: ';' 
	{$$ = new empty_astnode(); }								
	|  l_expression '=' expression ';'	
	{$$ = new assgn_astnode($1, $3);}
	;

expression
	: logical_and_expression
	{$$ = $1;}
        | expression OR_OP logical_and_expression
        {$$ = new binary_astnode("Or",$1,$3);}
	;
logical_and_expression
        : equality_expression
        {$$ = $1;}
        | logical_and_expression AND_OP equality_expression 
        {$$ = new binary_astnode("And",$1,$3);}
	;

equality_expression
	: relational_expression 
	{$$ = $1;}
    | equality_expression EQ_OP relational_expression 	
	        {$$ = new binary_astnode("EQ_OP",$1,$3);}
	| equality_expression NE_OP relational_expression
	        {$$ = new binary_astnode("NE_OP",$1,$3);}
	;

relational_expression
	: additive_expression
	{$$ = $1;}
        | relational_expression '<' additive_expression 
	    {$$ = new binary_astnode("LT",$1,$3);}

	| relational_expression '>' additive_expression 
	        {$$ = new binary_astnode("GT",$1,$3);}

	| relational_expression LE_OP additive_expression
	        {$$ = new binary_astnode("LE_OP",$1,$3);}
 
        | relational_expression GE_OP additive_expression 
                {$$ = new binary_astnode("GE_OP",$1,$3);}
	;

additive_expression 
	: multiplicative_expression
	{$$ = $1;}
	| additive_expression '+' multiplicative_expression 
	        {$$ = new binary_astnode("Plus",$1,$3);}

	| additive_expression '-' multiplicative_expression 
	        {$$ = new binary_astnode("Minus",$1,$3);}
	;

multiplicative_expression
	: unary_expression
	{$$ = $1;}
	| multiplicative_expression '*' unary_expression
	        {$$ = new binary_astnode("Multiply",$1,$3);}
 
	| multiplicative_expression '/' unary_expression 
	        {$$ = new binary_astnode("Divide",$1,$3);}
	;

unary_expression
	: postfix_expression  	
	{$$ = $1;}			
	| unary_operator postfix_expression 
	        {$$ = new unary_astnode($1,$2);}
	;

postfix_expression
	: primary_expression 
	{$$ = $1;} 				
        | IDENTIFIER '(' ')' 	
        {$$ = new func_astnode($1);}			
	| IDENTIFIER '(' expression_list ')'
	{$$ = new func_astnode($1, $3);} 
	| l_expression INC_OP 			
	{$$ = new unary_astnode("PP", $1);}	
	;

primary_expression
	: l_expression
	{$$ = $1;}
        | l_expression '=' expression   
        {$$ = new binary_astnode("Ass",$1, $3);}
        | '&' '(' l_expression ')'
        {$$ = new ptr_astnode($3);}
        | INT_CONSTANT {$$ = new int_astnode($1);}
	| FLOAT_CONSTANT {$$ = new float_astnode($1);}
        | STRING_LITERAL{$$ = new string_astnode($1);}
	| '(' expression ')' 	
	{$$ = $2;}
	;

l_expression
        : IDENTIFIER
        {$$ = new id_astnode($1);}
        | l_expression '[' expression ']'
        {$$ = new arrref_astnode($1, $3);  } 	
        | '*' '(' l_expression ')'
        {$$ = new deref_astnode($3);}
        | l_expression '.' IDENTIFIER
        {id_astnode *x = new id_astnode($3);
        $$ = new member_astnode($1,x);}
        | l_expression PTR_OP IDENTIFIER
        {id_astnode *x = new id_astnode($3);
        $$ = new arrow_astnode($1,x);}
        ;

expression_list
        : expression
        {$$ = new explist_astnode($1);}
        | expression_list ',' expression
        {$$ = new explist_astnode($1, $3);}
		;

unary_operator
        : '-'
        {$$ = "UMinus";}	
	| '!' 	
	{$$ = "Not";}
	;

selection_statement
        : IF '(' expression ')' statement ELSE statement 
        {$$ = new if_astnode($3, $5, $7);}
	;

iteration_statement
	: WHILE '(' expression ')' statement 
	{$$ = new while_astnode($3, $5);}	
	| FOR '(' expression ';' expression ';' expression ')' statement  //modified this production
	{$$ = new for_astnode($3,$5, $7, $9);	}
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