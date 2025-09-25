#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void MyRand(int *value, int *ncalls){
	static int count = 0; //vai ser a memória das contagens
	// nao é preciso contar as rands, apenas o numero de vezes
	//que a funçao é chamada
	count++;
	*value = rand() % 101 ;
	*ncalls = count;
}

int main(void){
	int val = 0;
	int ncalls = 0;

	srand(time(NULL));

	for(int n=0; n < 13; n++)
	{
		MyRand(&val, &ncalls);
		printf("Value: %d and Ncalls: %d\n", val, ncalls);
	}

	return 0;
}