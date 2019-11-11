/*
 * Parser.c
 *
 *  Created on: Nov 7, 2019
 *      Author: thebl
 */
#include <stdio.h>
#include "Parser.h"
#include "constants.h"

char symbol;
int hexNumber = 0x0;

int getNextToken(){

	FILE *fp;
	fp = fopen("input.txt", "r");
	symbol = fgetc(fp);



	return symbol;
}



int EE (int token){
	if (symbol == OR){
		symbol = getNextToken();
		int val = A();
		return EE(token | val);
	}
	else {
		return token;
	}
}



int AA(int token){
	if (symbol == XOR){
		symbol = getNextToken();
		int val = B();
		return AA(token ^ val);
	}
	else {
		return token;
	}
}



int BB(int token){
	if (symbol == AND){
		symbol = getNextToken();
		int val = C();
		return BB(token & val);
	}
	else {
		return token;
	}
}

int B(){
	int val = C();
	return BB(val);
}

int A(){
	int val = B();
	return AA(val);
}

int E() {
	int val = A();
	return EE(val);
}
int C(){
	if (symbol == SHIFTLEFT){
		return hexNumber << 1;

	}
	else if(symbol == SHIFTRIGHT){
		return hexNumber >> 1;
	}
	else if (symbol == NOT){
		return ~hexNumber;
	}
	else if (symbol == OPEN){
		return E();
	}
	else {
		return hexNumber;
	}
}


int main() {
	int val;
	symbol = getNextToken();
	while (symbol != EOF) {
		if (symbol != '\n') {
			val = E();
			printf(" = %x\n", val & 0xf);
		}
		if (symbol == EOF)
			break;

		symbol = getNextToken();
	}
	return 1;
}

