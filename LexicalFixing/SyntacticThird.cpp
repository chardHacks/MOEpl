#include<stdio.h>
#include<conio.h>
#include<string.h>

void program();
void SL();
void SLP();
void S();

void D();
void V();
void dt();
void dtp();
void dterm();

void A();
void AP();
void ex();
void exp();
void md();
void mdp();
void pow();
void powp();
void neg();
void term();

void cnd();
void cndp();

void cnt();

void io();
void out();
void write();

void consume();
void vommit();
void clrLexeme();
void clrToken();
void consumeStatement();

char token[30];
char lexeme[100];
int iptr = 1;
FILE* mlxFile;
char mlxName[30];
int atEnd;
int success = 1;
int iLn = 1;
int iLnLast = 1;

void error(char*mess)
{
 success = 0;
 printf("\nLine %d ERROR MESSAGE: %s",iLnLast ,mess);
}

void clrLexeme()
{
 int i;
 for(i = 0; i < 100; i++)
 {
 lexeme[i] = '\0';
 }
}

void clrToken()
{
 int i;
 for(i = 0; i < 100; i++)
 {
 token[i] = '\0';
 }
}

void vommit()
{
 iptr-=2;
 atEnd = 0;
 consume();
}

void consume()
{
 if(atEnd)
 {
 clrToken();
 clrLexeme();
 return;
 }

 char red;
 char temp[30];

 FILE* readFile = fopen(mlxName,"r");

 if(readFile == NULL)
 {
 printf("\nERROR READING .mlx FILE.");
 return;
 }

 int tmp = 0;
 iLnLast = iLn;
 while(tmp<iptr)
 {
 fscanf(readFile,"%d      %s      ",&iLn,token);
 if(!strcmp(token,"STRING_LITERAL"))
 {
  char c;
  clrLexeme();
  int strIn = 0;
  c = fgetc(readFile);
  lexeme[strIn] = c;
  strIn++;
  while(1)
  {
   c = fgetc(readFile);
   lexeme[strIn] = c;
   strIn++;
   if(c == '\'')
    break;
  }
  fgetc(readFile);
  char d = fgetc(readFile);
  if(!feof(readFile))
  ungetc(d,readFile);
 }
 else
 fscanf(readFile,"%s ",lexeme);

 tmp++;
 }
 //printf("\n%s\t%s",lexeme,token);
 if(feof(readFile))
  atEnd = 1;
 iptr++;

 fclose(readFile);

}

void consumeStatement()
{
 while(strcmp("STMNT_END",token))
 {
  consume();
  if(atEnd)
   break;
 }
}

void program()
{
 if(!strcmp("run",lexeme))
 {
  consume();
  if(!strcmp("P_START",token))
  {
   consume();
   if(!strcmp("P_END",token))
   {
    consume();
    if(!strcmp("B_START",token))
    {
     consume();
     SL();
     if(!strcmp("B_END",token))
      consume();
     else
      error("Expecting } symbol");
    }
    else
    error("Expecting { symbol");
   }
   else
   error("Expecting ) symbol");
  }
  else
  error("Expecting ( symbol");
 }
 else
 error("Expecting run method");

 if(strcmp("",token))
 {
  iLnLast = 0;
  error("Unreached statements found.");
 }
}


void SL()
{
 S();
 SLP();
}

void SLP()
{
 if(atEnd);

 else if(strcmp("B_END",token))
 {
 S();
 SLP();
 }
}

void S()
{
 if(!(strcmp("CONSTANT",token) && strcmp("FLT_TYP",token) && strcmp("BOOL_TYP",token) && strcmp("INT_TYP",token) && strcmp("STR_TYP",token)))
  D();
 else if(!strcmp("ID",token))
  A();
 else if(!strcmp("IF_",token))
  cnd();
 else if(!strcmp("LOOP_THIS",token))
  cnt();
 else if(!(strcmp("INPT_DATA",token) && strcmp("PRNT_DATA",token)))
  io();
 else if(!strcmp("B_START",token))
 {
  consume();
  SL();
  if(!strcmp("B_END",token))
   consume();
  else
   error("Expecting } symbol");
 }
 else if(!strcmp("STMNT_END",token))
  consume();
 else
 {
 int once = 1;
 iLnLast = iLn;
 error("Unknown statement");
 while(strcmp("STMNT_END",token))
 {
  if(once)
  {
   printf("\n\t\t");
   once = 0;
  }
  printf("%s ",lexeme);
  consume();
  if(atEnd)
   break;
 }
 consume();
 }
}

void D()
{
 if(!strcmp("CONSTANT",token))
  consume();
 if(!(strcmp("FLT_TYP",token) && strcmp("INT_TYP",token) && strcmp("STR_TYP",token) && strcmp("BOOL_TYP",token)))
 {
  consume();
  V();
  if(!strcmp("STMNT_END",token))
   consume();
  else
   error("Declaration syntax error, terminator missing.");
 }
 else
 {
  error("Declaration syntax error, constant datatype missing.");
  consumeStatement();
  consume();
 }
}

void V()
{
 dt();
 if(!strcmp("COM",token))
 {
 consume();
 V();
 }
}

void dt()
{
 if(!strcmp("ID",token))
 {
  consume();
  dtp();
 }
 else
 {
  error("Declaration syntax error. ");
  consumeStatement();
 }
}

void dtp()
{
 if(!strcmp("ASSIGN",token))
 {
  consume();
  dterm();
 }
 //if//kelangan katabi lang ni dtp is statement end or may isa pa
}

void dterm()
{
 if(!(strcmp("INTEGER",token) && strcmp("FLOAT",token) && strcmp("STRING_LITERAL",token) && strcmp("TRUE",token) && strcmp("FALSE",token)))
 consume();
 else
 dt();
}

void A()
{
 consume();
 if(!strcmp("ASSIGN",token))
  {
   consume();
   AP();
  }
 else
  {
   error("Assignment syntax error, invalid assignment statement.");
   consumeStatement();
   consume();
  }
}

void AP()
{
 if(!strcmp("ID",token))
 {
  consume();
  if(!strcmp("ASSIGN",token))
  {
   vommit();
   A();
  }
   else
  {
   vommit();
   ex();
   if(!strcmp("STMNT_END",token))
    consume();
   else
   {
    error("Assignment syntax error, missing ; terminator.");
    consumeStatement();
    consume();
   }//else
  }//else
 }
 else
 {
  ex();
  if(!strcmp("STMNT_END",token));
  else
  {
   error("Assignment syntax error, missing ; terminator.");
   consumeStatement();
  }//else
  consume();
 }//else
}

void ex()
{
 md();
 exp();
}

void exp()
{
 if(!(strcmp("LESSTH",token) && strcmp("GRTRTH",token) && strcmp("EQL",token) && strcmp("LESSEQL",token) && strcmp("GRTREQL",token) && strcmp("NOTEQL",token) && strcmp("AND",token) && strcmp("OR",token) && strcmp("ADD",token) && strcmp("SUB",token)))
 {
 consume();
 md();
 exp();
 }
}

void md()
{
 pow();
 mdp();
}

void mdp()
{
 if(!(strcmp("MUL",token) && strcmp("DIV",token) && strcmp("TRUNC_DIV",token) && strcmp("MOD",token)))
 {
 consume();
 pow();
 mdp();
 }
}

void pow()
{
 neg();
 powp();
}

void powp()
{
 if(!strcmp("RAISE",token))
 {
 consume();
 neg();
 powp();
 }
}

void neg()
{
 if(!strcmp("NOT",token))
  consume();
 if(!strcmp("ADD",token))
  consume();
 if(!strcmp("SUB",token))
  consume();
 term();
}

void term()
{
 if(!(strcmp("INTEGER",token) && strcmp("STRING_LITERAL",token) && strcmp("FLOAT",token) && strcmp("TRUE",token) && strcmp("FALSE",token) && strcmp("ID",token)))
  consume();
 else if(!strcmp("P_START",token))
 {
 consume();
 ex();
 if(!strcmp("P_END",token))
  consume();
 else
  {
   error("Expecting ) symbol.");
   consumeStatement();
  }
 }//else if
 else
 {
  error("Expression syntax error. ");
  consumeStatement();
 }

}

void cnd()
{
  consume();
  ex();
  if(!strcmp("COND_END",token))
  {
   consume();
   S();
   cndp();
  }
  else
  {
   error("Conditional syntax error. Expecting ? symbol.");
   consumeStatement();
  }
}

void cndp()
{
 if(!strcmp("ELSE_",token))
 {
  consume();
  S();
 }
}

void cnt()
{
 consume();
 cnd();
}

void io()
{
 if(!strcmp("INPT_DATA",token))
 {
  consume();
  if(!strcmp("ID",token))
  {
   consume();
  }
  else
  {
  error("Input statement syntax error, missing an Identifier.");
  consumeStatement();
  }
 }
 else
 {
  consume();
  ex();
 }
 if(!strcmp("STMNT_END",token))
  consume();
 else
  error("IO syntax error, missing ; symbol.");
}

void out()
{
 write();
 if(!strcmp("ADD",token))
 {
  consume();
  out();
 }
}

void write()
{
 if(!strcmp("STRING_LITERAL",token))
  consume();
 else
  ex();
}

void main()
{
clrscr();

printf("Enter symbol table: ");
gets(mlxName);

mlxFile = fopen(mlxName,"r");

if(mlxFile == NULL)
  {
  printf("FILE NOT FOUND.\nPROGRAM EXIT.");
  getch();
  return;
  }

size_t size = strlen(mlxName);
if(!(mlxName[size-4] == '.' && mlxName[size-3] == 'm'  && mlxName[size-2] == 'l' && mlxName[size-1] == 'x'))
        {
        printf("FILE NOT IN SPECIFIED FORMAT.\nPROGRAM EXIT.");
        getch();
        return;
        }
printf("STARTING SYNTAX ANALYSIS\n");
fclose(mlxFile);
consume();
program();
//while(!atEnd)
//{
//consume();
//printf("\n%d      %s      %s",iLn,token,lexeme);
//}
printf("\nProgram parsing : ");
if(success)
printf("Sucessful");
else
printf("FAILED");
getch();

}
