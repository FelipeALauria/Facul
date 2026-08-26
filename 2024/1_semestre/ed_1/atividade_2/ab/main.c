#include <stdio.h>
#include <stdlib.h>
#include "AB.h"

int main() {
	
	//Exemplo
	//     a 
	//   /   \
	//  b     c
	//   \   / \
	//   d  e   f 
	
	//sub-árvore 'd'
	No *t1 = cria ('d', criavazia(), criavazia());
	//sub-árvore 'b'
	No *t2 = cria ('b', criavazia(), t1);
	
	//sub-árvore 'e'
	No *t3 = cria ('e', criavazia(), criavazia());
	//sub-árvore 'f'
	No *t4 = cria ('f', criavazia(), criavazia());
	//sub-árvore 'c'
	No *t5 = cria ('c', t3, t4);
	
	//árvore 'a'
	No *t = cria ('a', t2, t5);
	
	//imprime
	imprime(t);
	
	return 0;
}
