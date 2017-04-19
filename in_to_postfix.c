/*infix to postfix*/
/*LiLi.Tam*/
#include <stdio.h>
#include <stdlib.h>
#define N 100
#define OP 5

char op[OP] = {'(','+','-','*','/',};
int op_priority[OP] = {0,1,1,2,2};//Operator priority

int priority(char c);
void to_postfix(char infix[], char postfix[]);


char stack[N]; 
int top=-1;


/* push */
void push(char item){
	if (top>=N-1){
		printf("Stack full!\n");
		exit(-1);
	}
	stack[++top]=item;
}
// ------------------------------------ 

/* pop */
int pop(){
	if (top==-1){
		printf("Stack empty!\n");
		exit(-1);
	}
	return stack[top--];
}

void stackPrint(){
	int i;
	printf("stack =");
	for (i=0; i<=top; i++)
		printf(" %c", stack[i]);
	printf("\n");
}
// ----------------------

bool IsEmpty(void)
{
	return (top < 0) ? true : false; 
}

bool IsFull()
{
	return (top >= N - 1) ? true : false;
}

/* return top data */
char top_data()
{
	return stack[top]; 
}
// ---------------------------

/* return  Operator priority */
int priority(char c)
{
	int i;
	
	for( i=0; i < OP; i++)
	if(op[i] == c)
	return op_priority[i];
	return -1;
}
// ------------------------------------

/* infix to postfix */
void to_postfix(char infix[], char postfix[])
{
	int i=0, j=-1;
	char x, y;

	while((x=infix[i++]) != '\0'){
		switch(x){
			case '(' : push(x);
					   break;
			case ')' : while(! IsEmpty() && (x=pop()) != '(')
						postfix[++j]=x;
						break;
			case '+' :
			case '-' :
			case '*' :
			case '/' : y=top_data();
					while(priority(y) >= priority(x)){
							postfix[++j]=pop();
							y=top_data();
					}
					push(x);
					break;
			default : // x 鮋綅呾啋
					postfix[++j]=x;
		}
	}
	while(! IsEmpty())
		postfix[++j]=pop();
	postfix[++j]='\0';
}
// ------------------------------------

bool IsDight(char c)
{
	return c>='0' && c<='9';
}

/*count */
int calculate(char postfix[])
{
	int point=0;
	while(postfix[point]!='\0')
	{
		while(IsDight(postfix[point]))
			push(postfix[point++]);
	int a=pop()-'0', b=pop()-'0',c=0;
	switch(postfix[point])
	{
		case'+':c=b+a;
				break;
		case'-':c=b-a;
				break;
		case'*':c=b*a;
				break;
		case'/':c=b/a;
				break;
	}
	push(c+'0');
	point++;
	}
	return pop()-'0';
}
// ------------------------------------


int main(void)
{ 
	char infix[50], postfix[50];

	printf("infix:   ") ;
	scanf("%s",infix);
	to_postfix(infix,postfix); 
	printf("postfix: %s\n",infix , postfix);
	printf("Value:\t %d\n", calculate(postfix));
	return 0;
}