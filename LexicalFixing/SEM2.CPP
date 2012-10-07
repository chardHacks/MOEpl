#include<stdio.h>
#include<conio.h>
#include<string.h>

void program();
void SL();
void SLP();
void S();

void D();
void V(char*);
void dt(char*, int);
void dtp(char*);
void dterm(char*);

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
void consumeStatement();

void error(char*);
void warning(char*);

char token[30];
char lexeme[100];
int iptr = 1;
FILE* mlxFile;
char mlxName[30];
char mtbName[30];
int atEnd;
int success = 1;

int iLn = 1;
int iLnLast = 1;

int isConst = 0;
int validType(char[], char[]);
int inTable();
int writeToTable(int, char*);

void clrWord(char *arry)
{
 int max = strlen(arry);
 int i;
 for(i = 0; i < max; i++)
 {
 arry[i] = '\0';
 }
}

void error(char*mess)
{
 success = 0;
 printf("\nLine %d ERROR MESSAGE: %s",iLnLast ,mess);
}

void warning(char*mess)
{
 success = 0;
 printf("\nLine %d WARNING MESSAGE: %s",iLnLast ,mess);
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
 clrWord(token);
 clrWord(lexeme);
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
  clrWord(lexeme);
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

int inTable()
{
 int isConst;
 char type[30];
 char word[100];
 int lnNo;
 int isDef;
 int isUsed;
 FILE*writeFile = fopen(mtbName,"r");
 while(fscanf(writeFile, "%d      %s      %s      %d      %d      %d\n", &isConst, &type, &word, &isDef, &isUsed) != EOF)
 {
  if(!strcmp(word,lexeme))
  {
   fclose(writeFile);
   return 1;
  }
 }
 fclose(writeFile);
 return 0;
}

int writeToTable(char* type)
{
 if(inTable())
  return 0;

 FILE* writeFile = fopen(mtbName,"a");
 if(writeFile == NULL)
 {
  printf("\nERROR. COULD NOT CREATE FILE %s",mtbName);
  return 0;
 }

 fprintf(writeFile, "%d      %s      %s      0      0      %d\n",isConst, type, lexeme, iLn);
 fclose(writeFile);

 return 1;
}


int validType(char from[30], char to[30])
{
  if(!(strcmp(from,"INT_TYP") && strcmp(from, "INTEGER")))
   if(!(strcmp(to, "INTEGER") && strcmp(to, "INT_TYP")))
    return 1;

  if(!(strcmp(from,"STR_TYP") && strcmp(from, "STRING_LITERAL")))
   if(!(strcmp(to, "STRING_LITERAL")  && strcmp(to, "STR_TYP")))
    return 1;

  if(!(strcmp(from,"FLT_TYP") && strcmp(from, "FLOAT")))
   if(!(strcmp(to,"FLOAT") && strcmp(to, "INTEGER")  && strcmp(to, "FLT_TYP")))
    return 1;

  if(!(strcmp(from,"BOOL_TYP") && strcmp(from, "FALSE") && strcmp(from, "TRUE")))
   if(!(strcmp(to,"TRUE") && strcmp(to,"FALSE")  && strcmp(to, "BOOL_TYP")))
    return 1;

   return 0;
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
   printf("\n\t");
   once = 0;
  }
  printf(" %s",lexeme);
  consume();
  if(atEnd)
   break;
 }
 consume();
 printf(";");
 }
 isConst = 0;
}

void D()
{
 if(!strcmp("CONSTANT",token))
 {
  isConst = 1;
  consume();
 }
 if(!(strcmp("FLT_TYP",token) && strcmp("INT_TYP",token) && strcmp("STR_TYP",token) && strcmp("BOOL_TYP",token)))
 {
  char type[30];
  strcpy(type, token);
  consume();
  V(type);
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

void V(char* type)
{
 dt(type,0);
 if(!strcmp("COM",token))
 {
 consume();
 V(type);
 }
}

void dt(char* type, int mode)
{
 if(!strcmp("ID",token))
 {
  if(!mode)
  {
   if(!writeToTable(type))
   {
    char err[100] = "Multple declaration for \'";
    strcat(err, lexeme);
    strcat(err, "\'");
    error(err);
   }
  }
  else
  {
   if(!inTable())
   {
    char err[100] = "Undeclared variable \'";
    strcat(err, lexeme);
    strcat(err, "\'");
    error(err);
   }
  }
  consume();
  dtp(type);
 }
 else
 {
  if(mode)
   error("Declaration syntax error. Identifier missing.");
  else
   error("Declaration syntax error. Value missing.");
  consumeStatement();
 }
}

void dtp(char* type)
{
 if(!strcmp("ASSIGN",token))
 {
  consume();
  dterm(type);
 }
}

void dterm(char* type)
{
 if(!(strcmp("SUB", token) && strcmp("ADD", token)))
  consume();

 if(!strcmp("NOT", token))
  {
   consume();
  }

 if(!(strcmp("INTEGER",token) && strcmp("FLOAT",token) && strcmp("STRING_LITERAL",token) && strcmp("TRUE",token) && strcmp("FALSE",token)))
  {
   consume();
  }
 else
  dt(type, 1);
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
strcpy(mtbName, mlxName);
mtbName[size - 2] = 't';
mtbName[size - 1] = 'b';
remove(mtbName);
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
