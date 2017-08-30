/*
 ============================================================================
 Name        : hi.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

double calcE(double m, double c)
{
	double e;
	e=(m*(c*c));
	return(e*10);
}
void printE(double m, double c)
{
	double res;
	res=calcE(m,c);
	printf("Energy available from object of mass %g kg is %.2f PJ\n ",m,res);

}
int main(void) {
	printE(1,2.99792458);
	printE(3.142,2.99792458);
	printE(10,2.99792458);
	printE(42,2.99792458);
	return(0);
}
