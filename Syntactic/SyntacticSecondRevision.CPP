
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
void dt1();
void dt2();

void A();
void AP();
void ex();
void exp();
void md();
void mdp();
void pow();
void powp();
void term();

void cnd();
void cndp();

void cnt();

void io();
void out();
void write();

void consume();
void vommit();



char token[30];
char lexeme[30];
int iptr = 1;
FILE* mlxFile;
char mlxName[20];
int atEnd = 0;
int success = 1;
int iLn = 0;

void error(char*mess)
{
 success = 0;
 printf("\nERROR MESSAGE: %s",mess);
}

void vommit()
{
 FILE* readFile = fopen(mlxName,"r");

 if(readFile == NULL)
 {
 printf("\nERROR READING .mlx FILE.");
 return;
 }

 int tmp = 0;

 iptr-=2;

 while(tmp<iptr)
 {
 fscanf(readFile,"%s      %s",lexeme,token);
 tmp++;
 }
 iptr++;

 fclose(readFile);
}

void consume()
{
 if(atEnd)
 {
 strcpy(token,"B_END");
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

 while(tmp<iptr)
 {
 fscanf(readFile,"%s      %s",lexeme,token);
 tmp++;
 }
 //printf("\n%s\t%s",lexeme,token);
 if(feof(readFile))
  atEnd = 1;
 iptr++;
 fclose(readFile);
}


void program()
{
 //printf("\nEnter <program>");
 consume();
 if(!strcmp(lexeme,"run"))
 {
  consume();
  if(!strcmp(token,"P_START"))
  {
   consume();
   if(!strcmp(token,"P_END"))
   {
    consume();
    if(!strcmp(token,"B_START"))
    {
     consume();
     SL();
     if(!strcmp(token,"B_END"))
     {
      consume();
      if(!atEnd)
       error("END OF FILE NOT REACHED. Unexpected }.");
     }
     else
     error("Expecting }");
    }//B start {
    else
     error("Expecting {");
   }//P close )
   else
    error("Expecting )");
  }//P start(
  else
   error("Expecting (");
 }//run
 else
  error("Expecting run method");

 //printf("\nExit <program>");
}//

void SL()
{
 //printf("\nEnter <SL>");
 S();
 SLP();
 //printf("\nExit <SL>");
}

void SLP()
{
 //printf("\nEnter <SLP>");

 //if(!(strcmp(token,"CONSTANT") && strcmp(token,"BOOL_TYP") && strcmp(token,"FLT_TYP") && strcmp(token,"INT_TYP") && strcmp(token,"STR_TYP") && strcmp(token,"BOOL_TYP") && strcmp(token,"ID") && strcmp(token,"IF_") && strcmp(token,"ELSE_") && strcmp(token,"LOOP_THIS") && strcmp(token,"INPT_DATA") && strcmp(token,"PRNT_DATA") && strcmp(token,"B_START")))
 {
  S();
  if(strcmp(token,"B_END"))
  SLP();
 }
 if(!strcmp(token,"B_END"));
 //else
 //{
 // error("Unexpected token ");
 // printf("%s %s. Missing a proper token",token,lexeme);
 // consume();
 //}

 //printf("\nExit <SLP>");
}

void S()
{
 //printf("\nEnter <S>");
 if(!(strcmp(token,"CONSTANT") && strcmp(token,"FLT_TYP") && strcmp(token,"BOOL_TYP") && strcmp(token,"INT_TYP") && strcmp(token,"STR_TYP")))
 D();
 else if(!strcmp(token,"ID"))
 A();
 else if(!strcmp(token,"IF_"))
 cnd();
 else if(!strcmp(token,"LOOP_THIS"))
 cnt();
 else if(!(strcmp(token,"INPT_DATA") && strcmp(token,"PRNT_DATA")))
 io();
 else if(!strcmp(token,"B_START"))
 {
  consume();
  SL();
  if(!strcmp(token,"B_END"))
  {
  consume();
  }
  else
  error("Unmatched {. Expecting }.");
 }
 //else if(!strcmp(token,"B_END"));

 else
  {
  error("Unknown statement.");
  while(strcmp(token,"STMNT_END"))
  {
   consume();
   if(!strcmp(token,"B_END"))
    break;
  }
  if(!strcmp(token,"STMNT_END"))
   consume();
  }
 //if(strcmp(token,"B_END"))
 // {
 // error("Unterminated Syntax.");
 // strcpy(token, "B_END");
 // }

 //printf("\nExit <S>");
}

void D()
{
 //printf("\nEnter <D>");
 if(!strcmp(token,"CONSTANT"))
 ///consume();

 if(!(strcmp(token,"FLT_TYP") && strcmp(token,"BOOL_TYP") && strcmp(token,"INT_TYP") && strcmp(token,"STR_TYP")))
 {
 consume();
 V();
 }

 if(!strcmp(token,"STMNT_END"))
  consume();
 else
  error("Declaration syntax error. Statement terminator missing ;");
 //printf("\nExit <D>");
}

void V()
{
 //printf("\nEnter <V>");
 dt();
 if(!strcmp(token,"COM"))
 {
 consume();
 V();
 }
 //printf("\nExit <V>");
}

void dt()
{
 //printf("\nEnter <dt>");
 if(!strcmp(token,"ID"))
 {
 consume();
 dt1();
 }
 else
 error("Declaration syntax error. Expecting IDENTIFIER or TERMINATOR");
 //printf("\nExit <dt>");
}

void dt1()
{
 //printf("\nEnter <dt1>");
 if(!strcmp(token,"ASSIGN"))
 {
  consume();
  dt2();
 }
 //printf("\nExit <dt1>");
}

void dt2()
{
 //printf("\nEnter <dt2>");
 if(!(strcmp(token,"INTEGER") && strcmp(token,"FLOAT") && strcmp(token,"TRUE") && strcmp(token,"FALSE") && strcmp(token,"STRING_LITERAL")))
 consume();
 else
 dt();
 //printf("\nExit <dt2>");
}

void A()
{
 if(!strcmp(token,"ID"))
 {
  consume();
  if(!strcmp(token,"ASSIGN"))
  {
   consume();
   AP();
  }
  else
   error("Assignment statement missing assignment operator");
 }
}

void AP()
{
if(!strcmp(token,"ID"))
{
 consume();
 if(!strcmp(token,"ASSIGN"))
 {
  vommit();
  A();
 }
}
else
 {
 ex();
 if(!strcmp(token,"STMNT_END"))
  consume();
 else
  error("Declaration syntax error. Statement terminator missing ;");
 }
}

void ex()
{
 if(!strcmp(token,"NOT"))
 {
  consume();
  md();
  exp();
 }
 else
 {
 md();
 if(!(strcmp(token,"LESSTH") && strcmp(token,"GRTRTH") && strcmp(token,"EQL") && strcmp(token,"LESSEQL") && strcmp(token,"GRTREQL") && strcmp(token,"NOTEQL") && strcmp(token,"EQLTO")))
 {
 consume();
 md();
 }
 else
 exp();
 }
}

void exp()
{
 if(!(strcmp(token,"ADD") && strcmp(token,"SUB") && strcmp(token,"OR") && strcmp(token,"AND")))
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
 if(!(strcmp(token,"MUL") && strcmp(token,"DIV") && strcmp(token,"MOD") && strcmp(token,"TRUNC_DIV")))
 {
 consume();
 pow();
 mdp();
 }
}


void pow()
{
 term();
 powp();
}

void powp()
{
 if(!strcmp(token,"RAISE"))
 {
 consume();
 term();
 powp();
 }
}

void term()
{
 if(!(strcmp(token,"INTEGER") && strcmp(token,"FLOAT") && strcmp(token,"TRUE") && strcmp(token,"FALSE") && strcmp(token,"ID")))
 {
 consume();
 }
 else if(!strcmp(token,"P_START"))
 {
 consume();
 ex();
 if(!strcmp(token,"P_END"))
 consume();
 else
  error("Unmatched (. Expecting ).");
 }
 else
  error("Invalid Expression. Expecting a value.");
}

void cnd()
{
 if(!strcmp(token,"IF_"))
 {
  consume();
  ex();
  if(!strcmp(token,"COND_END"))
  {
   consume();
   S();
   cndp();
  }
  else
  error("Condition terminator missing. Expecting ?.");
 }
}

void cndp()
{
 if(!strcmp(token,"ELSE_"))
 {
  consume();
  S();
 }
}

void cnt()
{
 if(!strcmp(token,"LOOP_THIS"))
 {
  consume();
  if(!strcmp(token,"IF_"))
  cnd();
  else
  error("Condition statement required after loop rpt");
 }
}

void io()
{
 if(!strcmp(token,"INPT_DATA"))
 {
  consume();
  if(!strcmp(token,"ID"))
  {
   consume();
  }
   else
   error("Input statement missing an IDENTIFIER.");
 }

 else if(!strcmp(token,"PRNT_DATA"))
 {
  consume();
  out();
  if(!strcmp(token,"STMNT_END"))
  consume();
  else
  error("Print statement syntax error. Expecting ;.");
 }

 if(!strcmp(token,"STMNT_END"))
  consume();
 else
  error("I/O syntax error. Statement terminator missing ;");
}

void out()
{
 write();
 if(!strcmp(token,"ADD"))
 {
  consume();
  out();
 }
}

void write()
{
 if(!strcmp(token,"STRING_LITERAL"))
 {
  consume();
 }
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
printf("STARTING SYNTAX ANALYSIS");
fclose(mlxFile);
program();
printf("\nProgram parsing : ");
if(success)
printf("Sucessful");
else
printf("FAILED");
getch();

}
