#include "tree.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "counter.h"
#include "frequency.h"
#include "huffman.h"
#include "util.h"

int main() {
	tree_t tree;
	int choice, i, quantity, frequency;
	char *string_input, *encode_str;
	char letter;
	bool end=false;
	
	tree_init(&tree);
	printf("===Generate Huffman Code===\n\n");
	printf("1 : Based on Program ('HUFFMAN CODING')\n");
	printf("2 : Based on Input (String)\n");
	printf("3 : Based on Input (Frequency)\n");
	printf("Choice : ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1 :
			generate_counter_tree(&tree, "HUFFMAN CODING");
			counter_reinit_frequency(&tree);
		break;
		
		case 2 :
			string_input=malloc(100*sizeof(char)); //not effective
			clearstdin();
			gets(string_input);
			generate_counter_tree(&tree, string_input);
			counter_reinit_frequency(&tree);
		break;
		
		case 3 :
			printf("How Many Letters : ");
			scanf("%d", &quantity);
			
			for(i=0; i<quantity; i++){
				
				printf("Letter    :");scanf(" %c", &letter);
				printf("Frequency :");scanf("%d", &frequency);
				tree.head = frequency_push((frequency_node_t*)tree.head, letter, frequency);
				
			}
		break;
		
		default:
		
		break;		
	}
	frequency_reinit_huffman(&tree);
	printf("Huffman code generated...");
	getch();
	
	while(!end){
		system("cls");
		printf("===Main Menu===\n\n");
		printf("1 : Table of Huffman Code\n");
		printf("2 : Encoding\n");
		printf("3 : Decoding\n");
		printf("4 : Exit\n");
		printf("Choice : ");scanf("%d", &choice);
		
		switch(choice){
			case 1 :
				display_huffman_code(tree);
				getch();	
			break;
			
			case 2 :
				encode_str = malloc(100*sizeof(char)); //not effective
				printf("Input        : ");
				clearstdin();
				gets(encode_str);
				printf("Huffman Code : ");
				encode(tree, encode_str);
				getch();
			break;
			
			case 3 :
				decode();
			break;
			
			case 4 :
				end=true;
			break;
		}
	}

	tree_close(&tree);

	return 0;
}
