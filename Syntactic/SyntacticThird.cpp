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