#include <stdio.h>
#include <stdlib.h>
int length(char string[])
{
	int i;
	for(i = 0; string[i] != '\0'; i++){}
	return i;
}
int char2int(char hex)
{
	if(hex == '0')
		return 0;
	if(hex == '1')
		return 1;
	if(hex == '2')
		return 2;
	if(hex == '3')
		return 3;
	if(hex == '4')
		return 4;
	if(hex == '5')
		return 5;
	if(hex == '6')
		return 6;
	if(hex == '7')
		return 7;
	if(hex == '8')
		return 8;
	if(hex == '9')
		return 9;
	return 10;
}
int power(int x, int y)
{
	int j=1;
	for(int i=0;i < y ;i++)
		j = j * x;
	return j;
}
int str2int(char string[])
{
	int num=0;
	int ln=length(string);
	for(int i = ln; i > 0; i--)
	{
		if(string[ln - i] != '-')
		{
			num += power(10, i - 1) * char2int(string[ln - i]);
		}
	}
	if(string[0] == '-')
		return -num;
	else
		return num;
}
int mod(int a, int b)
{
	int c = a % b;
	if(c < 0)
		c += b;
	return c;
}
void incgen(int argn, char *args[])
{
	char ch = 1;
	int *i = calloc(sizeof(int), (argn - 2));
	char cont = 1;
	while(cont)
	{
		char out = 0;
		cont = 0;
		for(int j = 0; j < (argn - 2); j++)
		{
			out = (out + args[j + 2][i[j]]) % 256;
			i[j]++;
			if(args[j + 2][i[j]] == '\0')
				i[j] = 0;
			if(i[j])
				cont = 1;
		}
		if(!out)
		{
			if(args[1][0] == 'r')
			{
				//replace null
				putchar(ch);
				ch++;
				if(!ch)
					ch++;
				continue;
			}
			if(args[1][0] == 'l')
			{
				//let the null
				putchar(out);
				continue;
			}
			if(args[1][0] ==  'i')
					continue;//ignore the null
		}
		else
			putchar(out);
	}
	//free(i);
}
void fincgen(int argn, char *args[])
{
	int keysize = str2int(args[2]);
	char *mem = calloc(keysize, 1);
	if(mem == NULL)
	{
		fprintf(stderr, "error in allocation\n");
		exit(1);
	}
	for(int i = 3; i < argn; i++)
	{
		int cur = 0;
		for(int j = 0; j < keysize; j++)
		{
			mem[j] += args[i][cur];
			cur++;
			if(args[i][cur] == '\0')
				cur = 0;
		}
		cur = 0;
		for(int j = 0; j < keysize; j++)
		{
			char cache = mem[j];
			if((signed char) args[i][cur] > 0)
			{
				for(int k = 0; k < (signed char) args[i][cur]; k++)
					mem[mod((j + k), keysize)] = mem[mod((j + k + 1), keysize)];
			}
			else
			{
				for(int k = 0; k > (signed char) args[i][cur]; k--)
					mem[mod((j + k + keysize), keysize)] = mem[mod((j + k - 1), keysize)];
			}
			mem[mod(keysize + j + ((signed char) args[i][cur]), keysize)] = cache;
			cur++;
			if(args[i][cur] == '\0')
				cur = 0;
		}
	}
	char ch = 1;
	for(int i = 0; i < keysize; i++)
	{
		if(mem[i])
			putchar(mem[i]);
		else
		{
			if(args[1][1] == 'r')
			{
				//replace null
				putchar(ch);
				ch++;
				if(!ch)
					ch++;
				continue;
			}
			if(args[1][1] == 'l')
			{
				//let the null
				putchar(mem[i]);
				continue;
			}
			if(args[1][1] ==  'i')
					continue;//ignore the null
		}
	}
	for(int i = 0; i < keysize; i++)
		mem[i] = 0;
	//free(mem);//this was replaced by the the loop above because for some reason on my ends sometimes it give segmentation fault or invalid pointer error when one of the keys is big. and the memory will be freed automatically after program exits
}
int main(int argn, char* args[])
{
	if(argn < 4)
	{
		printf("a long pseudo-random key genration tool using multiple small memorable keys.\nusage:\nfor the legacy algorithm:\n%s Opt Key1 Key2 ...\nfor the new algorithm, add f before the options (fl, fr, fi) and the key size in Bytes. (PS. this will require to maintain the same sorting of sub passwords)\n", args[0]);
		return 1;
	}
	if(args[1][0] == 'f')
		fincgen(argn, args);
	else
		incgen(argn, args);
	return 0;
}
