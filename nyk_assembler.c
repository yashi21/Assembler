

//NYK_ASSEMBLER
//ROLL NO : Y13UC144
//	  : Y13UC177
//	  : Y13UC337

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//error checking and synbol table generation
void pass1(int prog)
{
	FILE *t,*p,*q,*s,*e;
	FILE *h;
	int i=0,line=1,label,temp,size,jumpflag=0;
	char c,c1,array[12],array3[5];
	int helpp;
	char *array1;
	array1=(char *)malloc(35*sizeof(char));
	switch(prog)
	{
		case 1:	p= fopen("program2.txt","r");
			s= fopen("symbol2.txt","w");
			e= fopen("error2.txt","w");
			break;
	}

	while((c=fgetc(p))!= EOF)
	{
		if(c == '\n')
			line++;
		if(c!=' ' && c!='\n' && c!=',' && c!='\r' )//&& c!=':')
		{
			array[i]=c;
		        i++;
		if( c == ':')
		{
			fprintf(s,"%s\t",array);

			int z=0,num,k;
			num=line;
				for (z = 15; z >= 0; z--)
				{
					k = num >> z;

					if (k & 1)
						fprintf(s,"1");
					else
						fprintf(s,"0");
				}
			fputc('\n',s);
		}

		}
		else
		{
			array[i]='\0';
			i=0;
			int nyk = 0;
				t = fopen("isa.txt","r");
				while((c1=fgetc(t))!= EOF)
				{
					if(c1!=' ' && c1!='\t' && c1!='\n' && c1!='\r')
					{
						   *(array1+i)=c1;
						       i++;
                    }
					else if(c1==' ' || c1=='\t' || c1=='\n')
					{
						*(array1+i)='\0';
						i=0;
					}
					if(i==0)
					{
                        if(jumpflag==1)
                        {nyk=1;
                        break;}
						if(!(strcmp(array1,array)))
						{
						nyk = 1;
                            if(!(strcmp("JMP", array)) || !(strcmp("JC", array)) || !(strcmp("JNC", array)) ||
				!(strcmp("JP", array)) || !(strcmp("JNC", array)) || !(strcmp("JM", array)) ||
				!(strcmp("JZ", array)) || !(strcmp("JNZ", array)) || !(strcmp("JPE", array)) ||
 				!(strcmp("JPO", array)) || !(strcmp("JR", array)) || !(strcmp("JNR", array)) )
                            {
                            jumpflag=1;
                            }
						break;
						}
                    }
                }
                fclose(t);

				if(nyk == 0)
				{
					temp = strlen(array);
					if(array[temp-1] == ':');
					else
					{
						if(array[0]>='0' && array[0]<='9');
						/*else{
						printf(" \n ERRORS \n------------------------------------------------------------- \n");
	
						if(array[0]=='R' && (array[1]>='0' && array[1]<='9'))
						{
							printf("Error at line no %d. \t %s Register not found\n",line  , array);
						}
						else
							printf("Error at line no %d. \t %s Pnemonic not found\n",line  , array);
						}
						printf("\n-------------------------------------------------------------\n");*/
						if(array[0]>='0' && array[0]<='9');
						else{
						if(array[0]=='R'&& (array[1]>='0' && array[1]<='9'))
						{
							fprintf(e,"Error at line no %d. \t %s Register not found\n",line  , array);
						}
						else
							fprintf(e,"Error at line no %d. \t %s Pnemonic not found\n",line  , array);
						}
					}
				}
                nyk=0;
				}

    }


	fclose(p);
	fclose(s);
	fclose(e);
	printf(" \n ERRORS \n------------------------------------------------------------- \n");
	switch(prog)
	{
		case 1:	e= fopen("error2.txt","r");
			break;
	}
	while((c=fgetc(e))!= EOF)
		printf("%c",c);
	printf("\n-------------------------------------------------------------\n");
	fclose(e);
	printf(" \n SYMBOL TABLE \n------------------------------------------------------------- \n");
	switch(prog)
	{
		case 1:	s= fopen("symbol2.txt","r");
			break;
	}
	while((c=fgetc(s))!= EOF)
		printf("%c",c);
	printf("\n-------------------------------------------------------------\n");
	fclose(s);

}
//Function to generate machine language file
void pass2(int prog)
{
	FILE *p,*q,*s,*t,*e;
	int i=0,ct,line=1,cout=0,size,sizeb;
	char c,c1,array[35],*array1;
	int jumpflag=0,syntaxflag=0,dataflag=0,flag=0,ctflag=0;
	array1=(char *)malloc(35*sizeof(char));
	t= fopen("isa.txt","r");
	switch(prog)
	{

		case 1:	p= fopen("program2.txt","r");
			q= fopen("binary2.txt","w");
			s= fopen("symbol2.txt","r");
			e= fopen("error2.txt","r");
			break;
	}
		printf("\n");
	i=0;
	ct = 0; line=1;
	while((c=fgetc(e))!=EOF)
	{
	size = ftell(e);
	}

if(!size){

	while((c=fgetc(p))!= EOF)
	{
		if(c!=' ' && c!='\n' && c!=',' && c!='\r')
		{
		   array[i]=c;
		       i++;
        	}
		else
		{
			array[i]='\0';
			i=0;
			flag=1;
		}
		if(c == '\n')
			{
			if(ct>32)
			{
			printf("INCOMPLETE INSTRUCTION AT LINE : %d \n PROGRAM TERMINATED \n", line);
			exit(0);
			}
			if(ct<32)
			{
			printf("INCOMPLETE INSTRUCTION AT LINE: %d \n PROGRAM TERMINATED \n", line);
			exit(0);
			}
			line++;
			}
		else if( c == ':')
			fputc('\n',q);


		if(i==0 && c!='\n' && array[0]!='\0')
		{
			int j=0;
			while(array[j]!='\0')
			{
				if(array[j]>='0' && array[j]<='9')
				{
					dataflag=0;
				}
				else
				{
					dataflag=1;
					break;
				}
				j++;
			}
			/*if(ct>32)
			{
			printf("wrong addressable at line no : %d", line);
			return;
			}*/
			if(ct == 32)
			{
				fprintf(q,"\n");
				ct = 0;
			}

			if(array[0] >= '0' && array[0] <='9' && dataflag==0)
			{
				printf("komal");
				int z=0,num,k;
				sscanf(array, "%d", &num);
				for (z = 15; z >= 0; z--)
				{
					k = num >> z;

					if (k & 1)
						fprintf(q,"1");
					else
						fprintf(q,"0");
				}
				ct+=16;
			}
			if(flag==1)
			{
				i=0;
				int isaflag=0;
				while((c1=fgetc(t))!= EOF)
				{
					if(c1!=' ' && c1!='\t' && c1!='\n' && c1!='\r')
					{
						   *(array1+i)=c1;
						       i++;
			        	}
					else if(c1=='\t' || c1=='\n')
					{
						*(array1+i)='\0';
						i=0;
					}
					if(i==0)
					{
						if(ctflag==1)
						{
							sscanf(array1, "%d", &cout);
							ct+=cout;
							ctflag=0;
						}
						if(isaflag==1)
						{
							fprintf(q,"%s",array1);
							ctflag=1;
							isaflag=0;
							flag=0;
						}
						if(!(strcmp(array1,array)))
						{
							isaflag=1;

						}
					}
				}

			}
if(!(strcmp("JMP", array)) || !(strcmp("JC", array)) || !(strcmp("JNC", array)) ||
				!(strcmp("JP", array)) || !(strcmp("JNC", array)) || !(strcmp("JM", array)) ||
				!(strcmp("JZ", array)) || !(strcmp("JNZ", array)) || !(strcmp("JPE", array)) ||
 				!(strcmp("JPO", array)) || !(strcmp("JR", array)) || !(strcmp("JNR", array)) )
                            {
                                jumpflag=1;
                            }
			if(jumpflag==1)
			{
				i=0;
				int labelflag=0;
				while((c1=fgetc(s))!= EOF)
				{
					if(c1!=' ' && c1!='\t' && c1!='\n' && c1!='\r' && c1!=':')
					{
						   *(array1+i)=c1;
						       i++;
                    }
					else if(c1==' ' || c1=='\t' || c1=='\n')
					{

						*(array1+i)='\0';
						i=0;
					}
					if(i==0)
					{
						if(labelflag==1)
						{
							fprintf(q,"%s",array1);
							ct+=16;
							labelflag=0;
							jumpflag=0;
						}
						if(!(strcmp(array1,array)))
						{
							labelflag=1;
						}
					}
				}
			}


			/*else if(array[0] >= '0' && array[0] <='9' && dataflag==1)
			{
				printf("SYNTAX ERROR in line %d\n",line);
			}*/
			t= fopen("isa.txt","r");
			switch(prog)
			{
				case 1:	s= fopen("symbol2.txt","r");
					break;
			}
		}
	}

}
	fclose(p);
	fclose(q);
	fclose(s);
	fclose(t);
	fclose(e);
	switch(prog)
	{
		case 1:	q= fopen("binary2.txt","r");
			e=fopen("error2.txt","r");
			break;
	}
	//sizeb=ftell(e);
	if(!size){
	printf("\n BINARY CODE \n-------------------------------------------------------------\n");
	while((c=fgetc(q))!= EOF)
		printf("%c",c);
	printf("\n-------------------------------------------------------------\n");
	}
	else
	printf("\n NO BINARY FILE GENERATED BECAUSE YOUR PROGRAM WAS ERRONEOUS \n Go to help.txt to view the correct format\n");
	printf("\n");
	fclose(q);
	fclose(e);
};

void main()
{
	FILE *p,*e;
	char c;
	int ch,prog,size;
	e=fopen("error2.txt","r");
	while((c=fgetc(e))!= EOF)
		size=ftell(e);
	fclose(e);
	do
	{
		printf("1. Display a program \n");
		printf("2. Binary of Program\n");
		printf("3. Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{

			case 1:
						prog=1;
					switch(prog)
					{
						case 1:	p= fopen("program2.txt","r");
								break;
					}
					printf("\n");
					while((c=fgetc(p))!= EOF)
						printf("%c",c);
					printf("\n");
					fclose(p);
						break;

			case 2:
					prog=1;
					pass1(prog);
					pass2(prog);
					if(!size)
					{
					printf("seems like your code has errors. Go to help.txt to view the correct format");
					}
					break;


			case 3:	      	break;
		}
	}while(ch != 3);
}


# Assembler
