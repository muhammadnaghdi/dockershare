#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MIN_DEG 4

struct _node {
	int* keys;
	int keys_size;
	struct _node** children;
	int children_size;
};

typedef struct _node node;

node* node_create(int* keys, int keys_size, node** children, int children_size) {
	node* n = (node*) malloc(sizeof(node));
	n->keys = keys;
	n->keys_size = keys_size;
	n->children = children;
	n->children_size = children_size;
	return n;
}

node* btree_create() {
	int* keys0 = (int*) malloc(sizeof(int) * 2);
	keys0[0] = 10; keys0[1] = 15;
	node* node0 = node_create(keys0, 2, NULL, 0);

	int* keys1 = (int*) malloc(sizeof(int) * 2);
	keys1[0] = 30; keys1[1] = 60;
	node* node1 = node_create(keys1, 2, NULL, 0);

	int* keys2 = (int*) malloc(sizeof(int));
	keys2[0] = 90;
	node* node2 = node_create(keys2, 1, NULL, 0);

	int* keys3 = (int*) malloc(sizeof(int) * 2);
	keys3[0] = 20; keys3[1] = 80;
	node** children3 = (node**) malloc(sizeof(node*) * 3);
	children3[0] = node0; children3[1] = node1; children3[2] = node2;
	node* node3 = node_create(keys3, 2, children3, 3);

	int* keys4 = (int*) malloc(sizeof(int));
	keys4[0] = 200;
	node* node4 = node_create(keys4, 1, NULL, 0);

	int* keys5 = (int*) malloc(sizeof(int) * 2);
	keys5[0] = 1200; keys5[1] = 1400;
	node* node5 = node_create(keys5, 2, NULL, 0);

	
	int* keys6 = (int*) malloc(sizeof(int) * 2);
	keys6[0] = 100; keys6[1] = 1000;
	node** children6 = (node**) malloc(sizeof(node*) * 3);
	children6[0] = node3; children6[1] = node4; children6[2] = node5;
	node* node6 = node_create(keys6, 2, children6, 3);

	return node6;
}

bool btree_search(node* root, int key) {
	for (int i = 0; i < root->keys_size; ++i) {
		if (key < root->keys[i]) {
			if (root->children_size) {
				return btree_search(root->children[i], key);
			}
		}
		if (key == root->keys[i]) {
			return true;
		}
	}
	if (root->children_size) {
		return btree_search(root->children[root->children_size - 1], key);
	}
	return false;
}

void keys_sort(int* keys, int keys_size) {
	for (int i = 0; i < keys_size - 1; ++i) {
		for (int j = 0; j < keys_size - i - 1; ++j) {
			if (keys[j] > keys[i]) {
				int tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
		}
	}
	return;
}

void keys_insert(int* keys, int keys_size, int key) {
	int* new = (int*) malloc(sizeof(int) * (keys_size + 1));
	memcpy(new, keys, sizeof(int) * keys_size);
	new[keys_size] = key;
	keys_sort(new, keys_size + 1);
	free(keys);
	keys = new;
	return;
}

void btree_insert(node* root, int key) {
	if (root->children_size) {
		for (int i = 0; i < root->keys_size; ++i) {
			if (key < root->keys[i]) {
				return btree_insert(root->children[i], key);
			}
			if (key == root->keys[i]) {
				return;
			}
			
		}
		return btree_insert(root->children[root->children_size - 1], key);
	}
	if (root->keys_size < (MIN_DEG - 1)) {
		keys_insert(root->keys, root->keys_size, key);
		++ root->keys_size;
		return;
	}
	return;
}

int main() {
	node* root = btree_create();
	btree_insert(root, 1100);
	printf("%d", btree_search(root, 1100));
	return 0;
}
