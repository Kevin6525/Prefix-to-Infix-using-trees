#include <iostream> //For input
#include <algorithm> //Modify input

using namespace std;
//Creation of our treeNode class
//We just need to have access to the data inside the node and two pointers (left and right)

class treeNode {
	public:
		char data;
		treeNode* leftPointer;
		treeNode* rightPointer;
};

bool isOperator(string);
void modifyInput(string, char*);
char* createTree(treeNode** tree, char*);
void printTree(treeNode* tree);

//Check if the char is an operator, we will use this to determine when to return from recursion and create a child
bool isOperator(char inputValue)
{
	if(inputValue == '+' || inputValue == '-' || inputValue == '*' || inputValue == '/')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//This function modifies the input to ensure there are no whitespaces between characters
void modifyInput(string inputExpression, char* newExpression)
{
	//Note: remove does not actually remove anything so we use erase to do so. Remove just finds where the whitespace is
	inputExpression.erase(remove(inputExpression.begin(), inputExpression.end(), ' '), inputExpression.end());
	for(int i = 0; i < inputExpression.size(); i ++)
	{
		newExpression[i] = inputExpression[i];
	}
}
char* createTree(treeNode** tree, char* charPointer)
{
	//While the pointer is not pointing to the end of the expression
	while(*charPointer != '\0')
	{
		//Create a second pointer and set it to null
		char* charPointer2 = NULL;
		//If the tree is empty we create a new tree node and have the node be set to the data and both children set to null
		if(*tree == NULL)
		{
			
			treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
			newNode->data = *charPointer;
			newNode->leftPointer = NULL;
			newNode->rightPointer = NULL;
			*tree = newNode;
		}
		//We use recursion to fill out the tree Ex. Expression: *+AB/CD
		//Note: Think of the tree as operator
		//                           /     \
		//                       operand1   operand2
		else
		{
			//If we are pointing to an operand, we return and this is our child
			if(!isOperator(*charPointer))
			{
					
				return charPointer;
			}
			//We create the left side of the tree, this will create the left child from the root node of + as *
			//It will then create the left child of A, and since this is an operand it returns, exiting the method
			//This will then go to the next line, which calls for the right child of the node *
			//We increment the second pointer to point to B, repeat algorithm due to recursion until the tree is done
			charPointer2 = createTree(&(*tree)->leftPointer, charPointer +1);
			//We create the right side of the tree
			charPointer2 = createTree(&(*tree)->rightPointer, charPointer2 +1);
			return charPointer2;
		}
	}
	return '\0';
}
//We print out to confirm the tree is in the right order. (Left operand is left child, node is operator, right operand is right child)
//Use recursion to print the tree
void printTree(treeNode* tree)
{
	if(tree == NULL)
	{
		return;
	}
	else
	{
		//Use recursion, print left most first and then its parent, and then the sibling
		printTree(tree->leftPointer);
		cout<<tree->data;
		printTree(tree->rightPointer);
	}
}
int main() {
	treeNode* tree = NULL;
	string inputExpression;
	cout<<"Please enter a prefix expression: "<<endl;
	getline(cin, inputExpression);
	char newExpression[inputExpression.size()];
	modifyInput(inputExpression, newExpression);
	createTree(&tree, newExpression);
	printTree(tree);
	return 0;
}
