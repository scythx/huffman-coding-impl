#include "counter.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "util.h"

void generate_counter_tree(tree_t* tree, char* string_input){
	int i;
	int length = strlen(string_input);
	
	for(i=0; i<length; i++){
		counter_push(tree, string_input[i]);
	}
}

int counter_push(tree_t* tree, char character) {
	assert(tree != NULL);

	stack_t parent_stack;
	stack_init(&parent_stack, sizeof(counter_node_t**));
	
	counter_node_t** location = (counter_node_t**)&tree->head;
	while (*location != NULL_NODE) {
		if (stack_push(&parent_stack, location)) { 
			stack_delete(&parent_stack);
			return 1; 
		}

		if (character < (*location)->character) {
			location = &(*location)->left;
		} else if (character > (*location)->character) {
			location = &(*location)->right;
		} else {
			(*location)->count += 1;

			stack_delete(&parent_stack);
			return 0;
		}
	}

	counter_node_t* node = malloc(sizeof(counter_node_t));
	if (node == NULL) {
		return 1;
	}

	node->character = character;
	node->count     = 1;
	node->height	= 1;
	node->left     	= NULL_NODE;
	node->right     = NULL_NODE;

	*location = node;

	while ((location = stack_top(&parent_stack)) != NULL) {
		counter_node_height_calculate(*location);

		balance_factor_t balance = counter_node_balance_factor(*location);
		if (balance < LEFT) {
			if (counter_node_balance_factor((*location)->left) >= RIGHT) {
				(*location)->left = counter_node_rotate_left((*location)->left);
			}
			*location = counter_node_rotate_right(*location);
		} else if (balance > RIGHT) {
			if (counter_node_balance_factor((*location)->right) <= LEFT) {
				(*location)->right = counter_node_rotate_right((*location)->right);
			}
			*location = counter_node_rotate_left((*location));
		}
		stack_pop(&parent_stack);
	}

	stack_delete(&parent_stack);
	return 0;
}

void counter_node_height_calculate(counter_node_t* node) {
	assert(node != NULL_NODE);

	node->height = max(node->left->height, node->right->height) + 1;
}

counter_node_t* counter_node_rotate_left(counter_node_t* node) {
	assert(node != NULL_NODE);

	counter_node_t* root = node->right;	

	node->right = root->left;
	root->left = node;

	counter_node_height_calculate(node);
	counter_node_height_calculate(root);

	return root;
}

counter_node_t* counter_node_rotate_right(counter_node_t* node) {
	assert(node != NULL_NODE);

	counter_node_t* root = node->left;

	node->left = root->right;
	root->right = node;

	counter_node_height_calculate(node);
	counter_node_height_calculate(root);

	return root;
}

balance_factor_t counter_node_balance_factor(counter_node_t* node) {
	assert(node != NULL_NODE);

	return (node->right->height - node->left->height);
}


