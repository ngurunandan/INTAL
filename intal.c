#include "intal.h"

char *addition(char *num1, char *num2)
{
	if(num1[0]=='-' || num2[0]=='-')//Different sign cases
	{
		if(num1[0]!='-')
		{
			num2[0]='+';
			return subtraction(num1,num2);
		}
		else if(num2[0]!='-')
		{
			num1[0]='+';
			return subtraction(num2,num1);
		}
		else
		{
			num1[0]='+';
			num2[0]='+';
			char *res=addition(num1,num2);
			res[0]='-';//addition of two numbers with positive numbers and then negative sign is updated. 
			return res;
		}
	}	
	else
	{

		int i;
		int carry=0;
		int sum;
		int n=strlen(num1);
		char *res=(char *)malloc(sizeof(char )* (n+1));
		res[n+1]='\0';
		for(i=n;i>=1;i--)//Corresponding addition of numbers.
		{
			if(i!=1)
			{
			sum=val(num1[i-1])+val(num2[i-1])+carry;
			res[i]='0'+sum%10;
			
			carry=sum/10;
			}
			else
				res[1]='0'+carry;
			
		}
		res[0]='+';
		i=1;
		while(res[i]=='0' && res[i+1]!='\0') //removing the insignificant leading zeros
		{
			res[i]='+';
			res++;
		}
		
		return res;
	}
	return NULL;
}
char *subtraction(char *num1, char *num2)
{

	if(num1[0]=='-' || num2[0]=='-')//Difference sign cases
	{
		if(num1[0]!='-')
		{
			num2[0]='+';
			return addition(num1,num2);
		}
		else if(num2[0]!='-')
		{
			num1[0]='+';
			char *res=addition(num1,num2);
			res[0]='-';
			return res;
		}
		else
		{
			num1[0]='+';
			num2[0]='+';
			char *res=subtraction(num1,num2);
			res[0]='-';
			return res;
		}
	}	
	else
	{
		if(strcmp(num1,num2)<0)
		{
			char *res=subtraction(num2,num1);
			res[0]='-';
			return res;
		}
		int i;
		int borrow=0;
		int diff;
		int n=strlen(num1);
		char *res=(char *)malloc(sizeof(char )* (n+1));
		res[n]='\0';
		for(i=n-1;i>=1;i--)
		{
			diff=val(num1[i])-val(num2[i])-borrow;
			if(diff<0)
			{
				diff=10+diff;
				borrow=1;
			}
			else
				borrow=0;
			res[i]='0'+diff;
		
		}
		res[0]='+';
		i=1;
		while(res[i]=='0' && res[i+1]!='\0')	//removing the insignificant leading zeros
		{
			res[i]='+';
			res++;
		}
		
		return res;
	}
	return NULL;
}

char *division(char *num1, char *num2)
{
	char *res=(char *)malloc(strlen(num1)*sizeof(char));
	char *add=(char *)malloc(strlen(num2)*sizeof(char));
		
	int flag=0;
	res[0]='+';
		res[1]='0';
		res[2]='\0';
		add[0]='+';
		add[1]='1';
		add[2]='\0';
		
	char *dummy=num2;
	char sign;
	if((num1[0]=='-') ^ (num2[0]=='-'))
		sign='-';
	else
		sign='+';
	num1[0]='+';
	num2[0]='+';
	if(strcmp(num1,num2)<0)
	{
		if(sign=='+')
			return res;
		if(sign=='-')
			return "-1";
	}

	do
	{
		num2=dummy;
		padding(num1,num2);
		num1=subtraction(num1,num2);
		if(num1[0]=='+' && num1[1]=='0')
			flag=1;
		res=addition(res,add);	
	}
	while(num1[0]=='+'); //Repeating subtraction till num1 become negative
	padding(res,add);
	res=subtraction(res,add); //Removing an extra addition.
	if(sign=='-')
	{
		if(!flag) //Taking care of truncating in negative division
		{
			res= addition(res,add);
			res[0]='-';
			return res;
		}
		else
		{
			res[0]='-';
			return res;
		}

	}
	else 
		return res;
}

void padding(char *num1, char *num2)
{
	int diff,i;//padding length
	if(strlen(num1)>strlen(num2))
	{
		int n1=strlen(num1);
		int n2=strlen(num2);
		diff=n1-n2;
		num2[n2+diff]='\0';
		for (i=strlen(num2);i>=1;i--)
		{
			num2[i+diff]=num2[i];
		}
		for(i=1;i<=diff;i++)
			num2[i]='0';
	
	}

	else if(strlen(num1)<strlen(num2))
	{
		diff=strlen(num2)-strlen(num1);
		for (i=strlen(num1);i>=1;i--)
			num1[i+diff]=num1[i];
		for(i=1;i<=diff;i++)
			num1[i]='0';
	}

}
char *multiplication(char *num1, char *num2)
{
	char sign;
	if(num1[0]=='-' ^ num2[0]=='-') //Exactly one is negative
		sign='-';
	else
		sign='+';
	char *res=(char *)malloc((strlen(num1)+strlen(num2)+2)*sizeof(char));
	res=multiply(num1+1,num2+1,sign);
	
	return res;
}

char *multiply(char *s1, char *s2, char sign) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int i, j, k = 0, c = 0;
    char *r = (char *) malloc (l1+l2+2); // add one byte for the sign
    int temp;
    s1=rev(s1);
    s2= rev(s2);

    for (i = 1;i <l1+l2+1; i++) {
        r[i] = 0 + '0';
    }
    r[0]=sign;
    for (i = 0; i <l1; i ++) {
        c = 0; k = i+1;
        for (j = 0; j < l2; j++) {
            temp = val(s1[i]) * val(s2[j]);
            temp = temp + c + val(r[k]);
            c = temp /10;
            r[k] = temp%10 + '0';

            k++;
        }
        if (c!=0) {
            r[k] = c + '0';
            k++;
        }
    }
    r[k] = '\0';
    s1=rev(s1);
    s2=rev(s2);//Input strings are reversed back
    r=rev(r+1); //Reversing the string obtained except the sign
    r--;
     while(r[1]=='0' && r[2]!='\0')
     {
     	r[1]=sign;
    	r++;
    }
   	return r;
}
int val(char c) 
{
	return c-'0';
}
char *rev(char *r)// Reversing the whole string.
{
	
	int i;
	char temp1;
    int mid=strlen(r)/2;
    for(i=0;i<mid;i++)
    {
    	temp1=r[i];
    	r[i]=r[strlen(r)-i-1];
    	r[strlen(r)-i-1]=temp1;

    }
    return r;
}
char *exponential_intal(char *num1, char *num2)
{
	char sign;
	int i;
	char *res=(char *)malloc(sizeof(char) * (strlen(num1)*strlen(num2)+1));//One extra byte for sign
	if(val(num2[strlen(num2)-1])%2 && num1[0]=='-')
		sign='-';
	else
		sign='+';
	res[0]='+';
	res[1]='1';
	res[2]='\0';

    char *sub=(char *)malloc(sizeof(char)*3);
    sub[0]='+';
    sub[1]='1';
    sub[2]='\0';

    char sign2=num2[0];
    while(num2[1]=='0' && num2[2]!='\0')//Removing the insignificant leading zeros 
     {
     	num2[1]=sign2;
    	num2++;
    }
    
    while(!(num2[0]=='+' && num2[1]=='0'))
    {
    	res=multiplication(res,num1);
    	padding(num2,sub);
    	num2=subtraction(num2,sub);
    }
    return res;
}