#include <stdio.h>
#include <stdlib.h>
int main(int argn, char* args[])
{
	if(argn < 4)
	{
		printf("a long pseudo-random key genration tool using multiple small memorable keys.\nusage:\n%s Opt Key1 Key2 ...\nthe current options are:\nr: replace the null bytes with other bytes\nl: let the null bytes in the key\ni: ignore the null bytes.", args[0]);
		return 1;
	}
	char ch = 1;
	int *i;
	i = calloc(sizeof(int), (argn - 2));
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
			switch(args[1][0])
			{
				case 'r':
					//replace null bytes by different bytes
					putchar(ch);
					ch++;
					if(!ch)
						ch++;
				case 'l':
					//let the null bytes in the key
					putchar(out);
				case 'i':
					//simply ignore them and dont iclude null bytes
					continue;
			}
		}
		else
			putchar(out);
	}
	return 0;
}
