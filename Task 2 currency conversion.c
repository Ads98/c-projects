#include <stdio.h>
#include <stdlib.h>

void printPSP(int p)
{   int pound;
    int shill;
    int pennies;
    int remp;
	pound=p/240;
	remp=p%240;
	shill=p/12;
	remp=p%12;
	pennies=(remp);
	printf("%u pennies is %u  Pound(s) %u Shillings %u pennies\n",p,pound,shill,pennies);
}


int main(void) {
	printPSP(11);
	printPSP(13);
	printPSP(42);
	printPSP(100);
}
