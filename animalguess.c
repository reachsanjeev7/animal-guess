#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 50

struct node {
	char data[SIZE];
	struct node *left;
	struct node *right;
};

struct node *create_node(char *value)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));

	strcpy(new_node->data, value);
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

char yes_or_no(void)
{
	char buf[SIZE] = {0};

	fgets(buf, sizeof(buf), stdin);
	buf[strlen(buf) - 1] = '\0';
	return buf[0];
}

void ask_question(struct node *prev)
{
	char animal[SIZE] = {0};
	char option;
	char question[SIZE] = {0};

	printf("The animal you are thinking was a ?\n");

	fgets(animal, sizeof(animal), stdin);
	animal[strlen(animal) - 1] = '\0';

	printf("Please type a question that would ");
	printf("differentiate %s from %s\n", prev->data, animal);

	fgets(question, sizeof(question), stdin);
	question[strlen(question) - 1] = '\0';

	printf("for %s the answer is\n", animal);

	option = yes_or_no();

	if (option == 'n') {
		prev->right = create_node(prev->data);
		prev->left = create_node(animal);
	} else if (option == 'y') {
		prev->left = create_node(prev->data);
		prev->right = create_node(animal);
	}

	strcpy(prev->data, question);
}

int end_node(struct node *root)
{
	if (root->left == NULL && root->right == NULL)
		return 1;
	else
		return 0;
}

void traverse(struct node *root, struct node *prev)
{
	char option;

	if (root == NULL) {
		ask_question(prev);
		return;
	}
	if (end_node(root))
		printf("Is it ");
	printf("%s ? : ", root->data);
	option = yes_or_no();
	if (option == 'n') {
		prev = root;
		traverse(root->left, prev);
	} else if (option == 'y') {
		if (end_node(root)) {
			printf("Why don't you try another animal ?\n");
			return;
		}
		prev = root;
		traverse(root->right, prev);
	}
}

int main(void)
{
	struct node *root = NULL;
	struct node *prev = NULL;
	char option;

	root = create_node("Does it swim ? : ");/*MAIN NODE OF TREE*/
	root->left = create_node("bird");	/*default left node to main*/
	root->right = create_node("fish");	/*default right node to main*/
	prev = root;	/*prev is to maintain the address of parent node*/
	while (1) {
		printf("You are guessing a animal ? : ");
		option = yes_or_no();

		if (option == 'y') {
			printf("%s", root->data);
			option = yes_or_no();
			if (option == 'y')
				traverse(root->right, prev);
			else if (option == 'n')
				traverse(root->left, prev);
		}
	}
}
