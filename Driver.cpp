#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Node
{
public:
	string word;
	Node* left;
	Node* right;
	int height;

};

int height(Node* N)
{
	if (N == NULL)
		return 0;
	else
		return N->height;
}
int getBalanceFactor(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
string max(string a, string b)
{
	return (a > b) ? a : b;
}


Node* newNode(string word)
{
	Node* N = new Node;
	N->word = word;
	N->left = NULL;
	N->right = NULL;
	N->height = 1;
	return (N);
}
Node* rightRotate(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(y->right)) + 1;
	return x;

}
Node* leftRotation(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(y->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

Node* insertNode(Node* N, string word)
{
	if (N == NULL)
		return (newNode(word));
	if (word < N->word)
		N->left = insertNode(N->left, word);
	else if (word > N->word)
		N->right = insertNode(N->right, word);
	else
		return N;
	N->height = max(height(N->left), height(N->right)) + 1;
	int balanceFactor = getBalanceFactor(N);
	if (balanceFactor > 1)
	{
		if (word < N->left->word)
			return rightRotate(N);
		else if (word > N->left->word)
		{
			N->left = leftRotation(N->left);
			return rightRotate(N);
		}
	}
	if(balanceFactor < -1)
	{
		if (word > N->right->word)
			return leftRotation(N);
		else if (word < N->right->word)
		{
			N->right = rightRotate(N->right);
			return leftRotation(N);
		}
	}
	return N;
}
void printTree(Node* root)
{
	if (root != NULL)
	{
		printTree(root->left);
		cout << root->word << "  -  ";
		printTree(root->right);
	}
}
Node* searchWord(string keyword,Node* temp)
{
	if (temp == NULL)
		return NULL;
	else if (temp->word == keyword)
	{
		return temp;
	}
	else if (temp->word < keyword)
		return searchWord(keyword, temp->right);
	else if (temp->word > keyword)
		return searchWord(keyword, temp->left);

}

int main()
{
	system("color 0B");
	Node* root = NULL;
	ifstream fin;
	string doc = "";
	string textFilesName = "Doc";  // all text files name should be same and numbered from 1-50 like Doc1,Doc2,Doc3...
	string DocumentName = "";
	string keyword1, keyword2;
	int count1 = 0, count2 = 0;
	int i = 1;
	bool foundWord1 = false, foundWord2 = false;
	int choice = 0;
	for (int i = 1; i <= 50; i++)
	{
		DocumentName = textFilesName + to_string(i) + ".txt";
		fin.open(DocumentName, ios::in);
		if (!fin)
			cout << "can't open document no: " << i << endl;
		else
		{
			while (!fin.eof())
			{
				fin >> doc;
				if (doc == "the" || doc == "a" || doc == "of")
					continue;
				else
					root = insertNode(root, doc);
			}
		}
		fin.close();
	}



	while (true)
	{
		cout << "\n\n************** Enter Choice *************"
			<< "\n1: To Print Tree"
			<< "\n2: To Search in Documents "
			<< "\n3: To Quit " << endl;

		cin >> choice;

		if (choice == 1)
		{
			printTree(root);

		}
		else if (choice == 2)
		{
			cout << "1: Search one word\n2: Search two words" << endl;
			cin >> choice;
			if (choice == 1)
			{
				cout << "Enter KeyWord You want to search: ";
				cin >> keyword1;
				while (i<=50)
				{
					DocumentName = textFilesName + to_string(i) + ".txt";
					fin.open(DocumentName, ios::in);
					if (!fin)
					{
						i++;
						continue;
					}
					else
					{
						while (!fin.eof())
						{
							fin >> doc;
							if (searchWord(keyword1, root)->word == doc)
							{
								count1++;
								foundWord1 = true;
							}
						}
					}
					if (foundWord1)
					{
						cout << "Found word (" << searchWord(keyword1, root)->word << ") in " << DocumentName << endl;
						foundWord1 = false;
					}
					else
					{
						cout << "Word (" << searchWord(keyword1, root)->word << ") Not Found in " << DocumentName << endl;
					}
					i++;
					fin.close();
				}
				cout << "No of times This word Exits = " << count1 << endl;
			}
			else if (choice == 2)
			{
				cout << "Enter first KeyWord: ";
				cin >> keyword1;
				cout << "Enter second KeyWord: ";
				cin >> keyword2;
				int ch = 1;
				cout << "1: AND (if both found)\n2: OR (if any one of found" << endl;
				cin >> ch;
				while (i <= 5) 
				{
					DocumentName = textFilesName + to_string(i) + ".txt";
					fin.open(DocumentName, ios::in);
					if (!fin)
					{
						i++;
						continue;
					}
					else
					{
						while (!fin.eof())
						{
							fin >> doc;
							if (searchWord(keyword1, root)->word == doc)
							{
								count1++;
								foundWord1 = true;
							}
							if (searchWord(keyword2, root)->word == doc)
							{
								count2++;
								foundWord2 = true;
							}
						}
					}
					
					if (ch == 1)
					{
						if (foundWord1 && foundWord2)
						{
							cout << "Found word (" << searchWord(keyword1, root)->word << ") AND (" << searchWord(keyword2, root)->word<<") in " << DocumentName << endl;
							foundWord1 = false;
							foundWord2 = false;
						}
						else
						{
							cout << "Word (" << searchWord(keyword1, root)->word <<" AND "<< searchWord(keyword2, root)->word<<") Not Found in " << DocumentName << endl;
						}
					}
					else if (ch == 2)
					{
						if (foundWord1)
						{
							cout << "Found word (" << searchWord(keyword1, root)->word << ") in " << DocumentName << endl;
							foundWord1 = false;
							cout << "No of times Word (" << searchWord(keyword1, root)->word << ") exists = " << count1 << endl;
						}
						else
							cout << "Word (" << searchWord(keyword1, root)->word << ") Not Found in " << DocumentName << endl;


						if (foundWord2)
						{
							cout << "Found word (" << searchWord(keyword2, root)->word << ") in " << DocumentName << endl;
							foundWord2 = false;
							cout << "No of times Word (" << searchWord(keyword2, root)->word << ") exists = " << count2 << endl;
						}
						else
							cout << "Word (" << searchWord(keyword2, root)->word << ") Not Found in " << DocumentName << endl;


					}
					i++;
					fin.close();

				}

			}
			else
				cout << "\t\tWrong Choice" << endl;
		}
		else if(choice==3)
		break;
		else
			cout << "\t\tWrong Choice" << endl;


	}
	return 0;
}