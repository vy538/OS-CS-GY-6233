#include <stdio.h>
#include <unistd.h>


int main(void)
{
	
	int i = 0;
	for (int i = 0; i <= 4; i++)
	{
		printf("\ti=%d oof\n",i );
		if(i % 2 == 0){
			printf("fork\n");
			fork();
		}
		printf("i=%d foo\n",i);
	}
	return 0;
}