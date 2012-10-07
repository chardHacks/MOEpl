%start ROOT

%token MOEPL		

%token NUM_INTEGER 	
%token NUM_FLOAT 	

%token ADD 			
%token SUBTRACT 	
%token DIVIDE 		
%token MULTIPLY 	
%token RAISETO 		
%token MODULUS 		
%token DIVTRUNC 	
%token CMPR_LESSTH 	
%token CMPR_GRTRTH 	
%token CMPR_EQLTO 	
%token CMPR_LESSEQLTO
%token CMPR_GRTEEQLTO
%token CMPR_NOTEQLTO 
%token LOGI_OR		
%token LOGI_AND 	
%token LOGISP_NOT 	
%token COND_TERMINATE
%token ASSIGN 		
%token COMMA		
%token PAREN_START	
%token PAREN_END	
%token BLOCK_START 	
%token BLOCK_END 	
%token TERMINATE	
%token COMMENT 		
%token LIST_ADD 	
%token TYPE_ARRAY 	
%token ITR_AS 		
%token TYPE_BOOL 	
%token CNSTNT_KEY 	
%token LIST_DEQUEUE 
%token LIST_ENQUEUE 
%token BOOLVAL_FALSE 
%token BOOLVAL_TRUE 
%token TYPE_FLOAT 	
%token INPUT_KEY 	
%token IF_KEY 		
%token ITERATE		
%token TYPE_LIST 	
%token ELSE_KEY 	
%token TYPE_INT 	
%token LIST_POP 	
%token PRINT_KEY 	
%token LIST_PUSH 	
%token LOOP_KEY 	
%token RETURN_KEY 	
%token STRING_TYP 	
%token IDENTIFIER 	
%token STRING_LITERAL

%%

ROOT:
	MOEPL { execute($1); }
;

statement:
	