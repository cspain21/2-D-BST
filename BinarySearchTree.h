/*
 *    Data Structures Featuring C++  (c) 2021 Sridhar Radhakrishnan
 */

#include <iostream>
using namespace std;

#ifndef __BINARYSEARCHTREE__H
#define __BINARYSEARCHTREE__H

#include <cstdlib>


int max(int a, int b)
{
	if (a < b) return b;
	else return a;
}

class Exception {};

class BinaryTreeException : Exception {};
class BinaryTreeMemory : BinaryTreeException {};
class BinaryTreeEmptyTree : BinaryTreeException {};

class BinarySearchTreeException : BinaryTreeException {};
//class BinarySearchTreeChangedSubtree : BinarySearchTreeException {};
class BinarySearchTreeNotFound : BinarySearchTreeException {};

template <class DataType>
class BinarySearchTree;

template <class DataType>
ostream& operator << (ostream& s, BinarySearchTree<DataType>& X);

// /////////////////////////////////////////////////////////////
template <class DataType>
class BinarySearchTree
	// /////////////////////////////////////////////////////////////
{
	friend ostream& operator<< <DataType> (ostream& s, BinarySearchTree<DataType>& X);
protected:
	DataType* _root; //Node
	BinarySearchTree<DataType>* _left; //Left Child Pointer
	BinarySearchTree<DataType>* _right; //Right Child Pointer
	BinarySearchTree<DataType>* _yTree; //Y Tree Pointer
	bool _subtree;
	int ID; //ID value for Y tree nodes
	virtual BinarySearchTree<DataType>* makeSubtree(); //Makes a subtree
	virtual void copyTree(BinarySearchTree<DataType>* bst); //copies root, left, right, and yTree of given BST into the BST this function is called on
	virtual void _makeNull(); //makes BST root, left, right, yTree, and ID Null
	BinarySearchTree<DataType>* _find(const DataType& data); //Internal find function: Finds and returns BST object that has the root = the given data
															//If not found: returns an empty BST pointing to the child of the BST that this root should be inserted at
public:
	BinarySearchTree(); //Default constructor
	BinarySearchTree(const DataType& data); //Non-default constructor, takes data in as root value
	virtual ~BinarySearchTree(); //Destructor
	virtual bool isEmpty();
	// returns true if tree is empty,
	// but otherwise returns false
	virtual int height();
	// returns the height (or depth) of the tree
	virtual int size();
	// returns the number of nodes in the tree
	virtual DataType& root();
	// returns data from the root
	virtual int id();
	//returns ID
	virtual BinarySearchTree<DataType>* left();
	// returns the left subtree
	virtual BinarySearchTree<DataType>* right();
	// returns the right subtree
	virtual BinarySearchTree<DataType>* yTree();
	//returns the yTree
	virtual bool subtree(); //returns subtree bool
	virtual void makeEmpty(); //makes a BST empty
	virtual void inOrder_xTreeDisplay(); //Inorder display method for xTree
	virtual void inOrder_yTreeDisplay(); //Inorder display method for yTree
	virtual void preOrder_xTreeDisplay(); //Preorder display method for xTree
	virtual void preOrder_yTreeDisplay(); //Preorder display method for yTree
	virtual void find(const DataType& x, const DataType& y); //Finds the given x tree node, as well as the given y tree node of the x tree
	virtual void remove(const DataType& data); //Removes a given node from the BST
	virtual void _remove(const DataType& x, const DataType& y); //Modified remove that uses remove to remove the given xy coordinate
	virtual void rangeSearch(const DataType& low, const DataType& high); //Searches for nodes in a given range
	virtual void _rangeSearch(const DataType& xlow, const DataType& xHigh, const DataType& yLow, const DataType& yHigh); //Modified rangeSearch to support y tree
	virtual void insert(const DataType& data); //Inserts a node into the BST
	virtual void _insert(const DataType& x, const DataType& y, const DataType& id); //Modified insert to support y tree
	virtual int getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index); //Inorder traversal of given BST
	virtual int getPreorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** preOrderArray, int index); //Preorder traversal of given BST
	virtual BinarySearchTree<DataType>* GlobalRebalance(BinarySearchTree<DataType>** inOrderArray, int l, int r); //Rebalances a BST based on Inorder array
	virtual void yBalance(const DataType& x); //Balances given y BST


};
template <class DataType>
//Outputs the Inorder and Preorder traversal of given BST
ostream& operator<< (ostream& s, BinarySearchTree<DataType>& X) {
	cout << "INORDER TRAVERSAL: " << endl;
	//Calls on display method for xTree inOrder
	X.inOrder_xTreeDisplay();

	cout << "PREORDER TRAVERSAL: " << endl;
	//Calls on display method for xTree preOrder
	X.preOrder_xTreeDisplay();
	return s;
}
// ==============================================================

//Default constructor
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree()
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_yTree = NULL;
	ID = NULL;
	_subtree = false;
}
// --------------------------------------------------------------

//Non-default constructor, takes data in as root value
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const DataType& data)
{
	_subtree = false;
	_root = new DataType(data);
	_left = makeSubtree();
	_right = makeSubtree();

	//_yTree and ID initially set to null as nodes are only given a _yTree or ID through insertion function
	_yTree = NULL;
	ID = NULL;
}
// --------------------------------------------------------------

//Makes a subtree, returns empty/default BST
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree()
{
	BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType>();
	bst->_subtree = true;
	return bst;
}
// --------------------------------------------------------------

//Destructor
template <class DataType>
BinarySearchTree<DataType>::~BinarySearchTree()
{
	if (_root != NULL)
		delete _root;
	_root = NULL;
	if (_left != NULL)
		delete _left;
	_left = NULL;
	if (_right != NULL)
		delete _right;
	_right = NULL;
	if (_yTree != NULL)
		delete _yTree;
	_yTree = NULL;
	if (ID != NULL) 
		ID = NULL;
}
// --------------------------------------------------------------

//Checks if the BST is empty
template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
	return (_root == NULL);
}
// --------------------------------------------------------------

//returns yTree 
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::yTree() { return _yTree; }
// --------------------------------------------------------------

//returns height
template <class DataType>
int BinarySearchTree<DataType>::height()
{
	if (isEmpty()) return 0;
	return (1 + max(_left->height(), _right->height()));
	// max() is in stdlib.h
}
// --------------------------------------------------------------

//returns size
template <class DataType>
int BinarySearchTree<DataType>::size()
// returns the number of nodes in the tree
{
	if (isEmpty())
		return 0;
	//if (_yTree != NULL)
		//return (1 + _left->size() + _right->size() + _yTree->size());
	return (1 + _left->size() + _right->size());
}
// --------------------------------------------------------------

//returns ID
template <class DataType>
int BinarySearchTree<DataType>::id() {
	if (ID != NULL) {
		return ID;
	}
}
// --------------------------------------------------------------

//returns data from the root
template <class DataType>
DataType& BinarySearchTree<DataType>::root()
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_root;
}
// --------------------------------------------------------------

// returns the left subtree
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left() { return _left; }
// --------------------------------------------------------------

// returns the right subtree
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right() { return _right; }
// --------------------------------------------------------------

//returns subtree bool
template <class DataType>
bool BinarySearchTree<DataType>::subtree() { return _subtree; }
// --------------------------------------------------------------

//Makes a BST empty
template <class DataType>
void BinarySearchTree<DataType>::makeEmpty()
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	if (_root != NULL)
		delete _root;
	_root = NULL;
	if (_left != NULL)
		delete _left;
	_left = NULL;
	if (_right != NULL)
		delete _right;
	_right = NULL;
	if (_yTree != NULL) 
		delete _yTree;
	_yTree = NULL;
	if (ID != NULL)
		ID = NULL;
}
// --------------------------------------------------------------

//copies root, left, right, and yTree of given BST into the BST this function is called on
template <class DataType>
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst)
{
	_root = bst->_root;
	_left = bst->_left;
	_right = bst->_right;
	_yTree = bst->_yTree;
}
// --------------------------------------------------------------

//makes a BST Null
template <class DataType>
void BinarySearchTree<DataType>::_makeNull()
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_yTree = NULL;
	ID = NULL;
}
// --------------------------------------------------------------

//Display for xTree inOrder, calls on the yTree inOrder display within itself
template <class DataType>
void BinarySearchTree<DataType>::inOrder_xTreeDisplay() {

	//Creates an array of the xTree for the getInOrderTraversal function
	BinarySearchTree<DataType>** inOrderArray = new BinarySearchTree<DataType>*[this->size()];

	//Fills the inOrderArray with all xTree nodes in order
	this->getInorderTraversal(this, inOrderArray, 0);

	//Loops through the xTree and displays each x node, and calls to display each x node's y tree if they have one
	for (int i = 0; i < this->size(); i++) {
		//Outputs root value of xTree
		cout << inOrderArray[i]->root() << ": " << endl;

		//Calls display for current x node's y tree (if it has a yTree)
		if (inOrderArray[i]->_yTree != NULL) inOrderArray[i]->inOrder_yTreeDisplay();
	}
}
// --------------------------------------------------------------

//Display for yTree inOrder
template <class DataType>
void BinarySearchTree<DataType>::inOrder_yTreeDisplay() {

	//Creates an array of the yTree for getInOrderTraversal function
	BinarySearchTree<DataType>** inOrderArray = new BinarySearchTree<DataType>*[this->yTree()->size()];

	//Fills the inOrderArray with all yTree nodes in order
	this->yTree()->getInorderTraversal(this->yTree(), inOrderArray, 0);

	//Loops through each yTree node
	for (int i = 0; i < this->yTree()->size(); i++) {

		//Outputs the root value along with the ID of the current yTree node
		cout << " " << inOrderArray[i]->root() << "(" << inOrderArray[i]->id() << ") ";

	}
	cout << endl;
}
// --------------------------------------------------------------

//Display for xTree preOrder
template <class DataType>
void BinarySearchTree<DataType>::preOrder_xTreeDisplay() {

	//Creates an array of the xTree for the getPreOrderTraversal function
	BinarySearchTree<DataType>** preOrderArray = new BinarySearchTree<DataType>*[this->size()];

	//Fills the preOrderArray with all xTree nodes in preorder
	this->getPreorderTraversal(this, preOrderArray, 0);

	//Loops through the xTree and displays each x node, and calls to display each x node's y tree if they have one
	for (int i = 0; i < this->size(); i++) {

		//Outputs root value of xTree
		cout << preOrderArray[i]->root() << ": " << endl;

		//Calls display for current x node's y tree (if it has a yTree)
		if (preOrderArray[i]->_yTree != NULL) preOrderArray[i]->preOrder_yTreeDisplay();
	}
}
// --------------------------------------------------------------

//Display for yTree preOrder
template <class DataType>
void BinarySearchTree<DataType>::preOrder_yTreeDisplay() {

	//Creates an array of the yTree for getPreOrderTraversal function
	BinarySearchTree<DataType>** preOrderArray = new BinarySearchTree<DataType>*[this->yTree()->size()];

	//Fills the preOrderArray with all yTree nodes in preorder
	this->yTree()->getPreorderTraversal(this->yTree(), preOrderArray, 0);

	//Loops through each yTree node
	for (int i = 0; i < this->yTree()->size(); i++) {

		//Outputs the root value along with the ID of the current yTree node
		cout << " " << preOrderArray[i]->root() << "(" << preOrderArray[i]->id() << ") ";

	}
	cout << endl;
}
// --------------------------------------------------------------

//Internal find function: Finds and returns BST pointer that has the root value equal to the given data
//If not found: returns an empty BST pointing to the location of the BST that this root should be inserted at
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find(const DataType& data)
{
	//Pointer to BST that will be returned
	BinarySearchTree<DataType>* bst = this;

	//Loops until it either finds a matching root or an empty tree
	while (true)
	{
		if (bst->isEmpty())
			//returns empty bst pointer that is at location the given data should be inserted
			return bst;
		if (*(bst->_root) < data)
		{
			//If root is smaller than the given data, searches right
			bst = bst->_right;
		}
		else if (*(bst->_root) > data)
		{
			//If root is bigger than given data, searches left
			bst = bst->_left;
		}
		else
		{
			//returns bst pointer with root equal to given data
			return bst;
		}
	}
}
// --------------------------------------------------------------

//Finds the given x tree node, as well as the given y tree node of the x tree
template <class DataType>
void BinarySearchTree<DataType>::find(const DataType& x, const DataType& y)
{
	//Uses _find to get location of given xTree
	BinarySearchTree<DataType>* xTree = _find(x);

	//Checks if the tree is found
	try {
		if (xTree->isEmpty()) throw BinarySearchTreeNotFound();

		//If found, searches for location of given yTree
		BinarySearchTree<DataType>* yTree = xTree->yTree()->_find(y);

		//If given yTree is not found, outputs message and returns
		if (yTree->isEmpty()) {
			cout << "\nSorry!!! Coordinate is not found in the Y tree" << endl;
			return;
		}

		//Outputs coordinates and yTree id value
		cout << "\nThe coordinates " << xTree->root() << ", "<< yTree->root() << " is found in the tree with ID value " << yTree->id() << endl;
		return;
	}
	catch (BinarySearchTreeNotFound e)
	{
		//If coordinate is not found, outputs this instead
		cout << "\nSorry!!! Coordinate is not found in the X tree" << endl;
		return;
	}
}
// --------------------------------------------------------------

//Inserts a node into the BST
template <class DataType>
void BinarySearchTree<DataType>::insert(const DataType& data)
{
	//Pulls location to insert given data, or the location of the given data if it is already in the tree
	BinarySearchTree<DataType>* bst = _find(data);

	//If the given data is not found, inserts it at the position from _find
	if (bst->isEmpty())
	{
		bst->_root = new DataType(data);
		bst->_left = makeSubtree();
		bst->_right = makeSubtree();
	}
	//If the given data is found, copies the given data 
	else
	{
		delete bst->_root;
		bst->_root = new DataType(data);
	}
}
// --------------------------------------------------------------

//Modified insert to support y tree
template <class DataType>
void BinarySearchTree<DataType>::_insert(const DataType& x, const DataType & y, const DataType& id) {

	//Outputs the x, y, and id to be inserted
	cout << x << " " << y << " " << id << endl;
	//Inserts the given x
	this->insert(x);

	//Pulls location of inserted x
	BinarySearchTree<DataType>* xTree = _find(x);

	//If the x has no yTree, creates one with the given y value and id
	if (xTree->_yTree == NULL) {
		xTree->_yTree = new BinarySearchTree(y);
		xTree->_yTree->ID = id;
	}
	//If the x already has a yTree, insert the given y value into the x's yTree
	else {
		xTree->_yTree->insert(y);

		//Pulls location of inserted y
		BinarySearchTree<DataType>* inserted_yNode = xTree->_yTree->_find(y);

		//Sets the ID of the inserted y to the given id
		inserted_yNode->ID = id;
	}
}
// --------------------------------------------------------------

//Removes a given node from the BST
template <class DataType>
void BinarySearchTree<DataType>::remove(const DataType& data)
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DataType>* bst;
	BinarySearchTree<DataType>* bst2;
	BinarySearchTree<DataType>* bst3;

	bst = _find(data);
	if (bst->isEmpty()) throw BinarySearchTreeNotFound();

	// dispose of the existing data; the pointer will be overwritten
	delete bst->_root;

	// .............................................................
	if (bst->_left->isEmpty())
	{
		// the left subtree exists, but the pointer will be overwritten,
		// so we must dispose of it
		delete bst->_left;
		bst2 = bst->_right;		// save the pointer to the right subtree
		bst->copyTree(bst2);	// copy the right subtree;
		// this empties tree if right empty
		bst2->_makeNull();		// prepare right subtree for deletion
		delete bst2;				// delete right subtree to avoid garbage
	}

	else if (bst->_right->isEmpty())
	{
		// the right subtree exists, but the pointer will be overwritten,
		// so we must dispose of it
		delete bst->_right;
		bst2 = bst->_left;		// save the pointer to the left subtree
		bst->copyTree(bst2);	// copy the left subtree
		bst2->_makeNull();		// prepare left subtree for deletion
		delete bst2;				// delete left subtree to avoid garbage
	}

	else		// both subtrees non-empty
	{
		// move to the right
		bst2 = bst->_right;
		// then move down to the left as far as possible
		while (!bst2->_left->isEmpty()) bst2 = bst2->_left;
		// overwrite the data pointer
		bst->_root = bst2->_root;

		// bst2's left child is known to be empty and pointer will be overwritten
		delete bst2->_left;
		// now bst2's right child is copied into it
		if (bst2->_right->isEmpty())
		{
			delete bst2->_right;
			bst2->_makeNull();
		}
		else
		{
			bst3 = bst2->_right;
			bst2->copyTree(bst2->_right);
			bst3->_makeNull();
			delete bst3;
		}
	}
}
// --------------------------------------------------------------

//Modified remove that uses remove to remove the given xy coordinate
template <class DataType>
void BinarySearchTree<DataType>::_remove(const DataType& x, const DataType& y) {

	//Pulls position of given xTree value
	BinarySearchTree<DataType>* xTree = _find(x);

	//Outputs message and returns if the xTree is not found
	if (xTree->isEmpty()) {
		cout << "The element you are trying to remove is not in the tree " << endl;
		return;
	}
	//if xTree is found
	else {
		//Pulls position of given yTree value
		BinarySearchTree<DataType>* yTree = xTree->yTree()->_find(y);

		//Outputs message and returns if the yTree is not found
		if (yTree->isEmpty()) {
			cout << "The element you are trying to remove is not in the tree " << endl;
			return;
		}
		//Removes the y value from the xTree's yTree
		xTree->yTree()->remove(y);

		//Also removes the xTree if it no longer has a yTree after y removal
		if (xTree->yTree()->isEmpty()) {
			this->remove(x);
		}
	}
}
// --------------------------------------------------------------

//Searches for nodes in a given range
template <class DataType>
void BinarySearchTree<DataType>::rangeSearch(const DataType& low, const DataType& high)
{
	//Prints all root values that fall within the given range
	if (isEmpty()) return;
	if (*_root >= low)
	{
		_left->rangeSearch(low, high);
		if (*_root <= high)
		{
			cout << *_root << "  ";
		}
	}
	if (*_root <= high)
		_right->rangeSearch(low, high);
}
// --------------------------------------------------------------

//Modified rangeSearch to support y tree
template <class DataType>
void BinarySearchTree<DataType>::_rangeSearch(const DataType& xLow, const DataType& xHigh, const DataType& yLow, const DataType& yHigh) {

	//Prints all the xTree values that fall in a given x range, and then uses rangeSearch to print all yTree values within a given y range for every xTree within the given x range
	if (isEmpty()) return;

	//First looks for an xTree value that falls in the x range
	if (*_root >= xLow)
	{
		_left->_rangeSearch(xLow, xHigh, yLow, yHigh);

		//Once an xTree within the range is found, prints the root value
		if (*_root <= xHigh)
		{
			cout << *_root << " ";

			//Before looking for more xTrees, the current xTree's yTree is passed to rangedSearch with the y range, and all the yTree values for that xTree are printed
			if (this->_yTree != NULL) {
				cout << ": ";
				this->yTree()->rangeSearch(yLow, yHigh);
					cout << endl;
			}
		}
	}
	if (*_root <= xHigh)
		_right->_rangeSearch(xLow, xHigh, yLow, yHigh);
		
}
// --------------------------------------------------------------

//Inorder traversal of given BST, stores the Inorder traversal in a given array
template <class DataType>
int BinarySearchTree<DataType>::getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index)
{
	//Throws error if given tree is empty
	try {
		if (node->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch (BinarySearchTreeNotFound e) {
		cout << "No tree for inorder traversal" << endl;
		return index;
	}

	//Recursively calls left child, root, then right child to fill the inOrderArray with the inorder representation of the given BST
	if (!this->isEmpty()) {
		if (node->left()->_root != NULL)
		{
			index = node->left()->getInorderTraversal(node->left(), inOrderArray, index);
		}

		inOrderArray[index++] = node;

		if (node->right()->_root != NULL)
		{
			index = node->right()->getInorderTraversal(node->right(), inOrderArray, index);
		}
	}

	//returns index that is used for recursive calls
	return index;
}
// --------------------------------------------------------------

//Preorder traversal of given BST
template <class DataType>
int BinarySearchTree<DataType>::getPreorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** preOrderArray, int index)
{
	//Throws error if given tree is empty
	try {
		if (node->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch (BinarySearchTreeNotFound e) {
		cout << "No tree for Preorder traversal" << endl;
		return index;
	}

	//Recursively calls root, then left child, then right child to fill the preOrderArray with the preorder representation of the given BST
	if (!this->isEmpty()) {
		preOrderArray[index++] = node;

		if (node->left()->_root != NULL)
		{
			index = node->left()->getPreorderTraversal(node->left(), preOrderArray, index);
		}

		if (node->right()->_root != NULL)
		{

			index = node->right()->getPreorderTraversal(node->right(), preOrderArray, index);
		}
	}

	//returns index that is used for recursive calls
	return index;
}
// --------------------------------------------------------------

//Rebalances a BST based on Inorder array
template<class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::GlobalRebalance(BinarySearchTree<DataType>** inOrderArray, int l, int r)
{
	int mid = 0;

	//Rebalanced tree to be returned
	BinarySearchTree<DataType>* temp = new BinarySearchTree<DataType>();

	//Recursively calls on the Inorder array to rebalance all values in the given inOrderArray representation of BST
	if (l <= r)
	{
		mid = ((l + r) / 2);
		temp = inOrderArray[mid];
		temp->_left = temp->_left->GlobalRebalance(inOrderArray, l, mid - 1);
		temp->_right = temp->_right->GlobalRebalance(inOrderArray, mid + 1, r);
	}

	//Rebalanced tree, recursively balances subtrees
	return temp;
}
// --------------------------------------------------------------

//Balances given yTree BST
template <class DataType>
void BinarySearchTree<DataType>::yBalance(const DataType& x) {

	//Finds the position of the given xTree, the yTree of the xTree will be rebalanced
	BinarySearchTree<DataType>* bst = _find(x);

	//Throws error if xTree not found
	try {
		if (bst->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch (BinarySearchTreeNotFound e) {
		cout << "No tree to balance" << endl;
		return;
	}

	//Pointer to the yTree of the given xTree
	BinarySearchTree<DataType>* bst_yTree = bst->yTree();

	//Creates an array to use for GlobalRebalance
	BinarySearchTree<DataType>** yArray = new BinarySearchTree<DataType>*[bst_yTree->size()];

	//Calls getInOrderTraversal on the yArray to fill it for GlobalRebalance
	this->getInorderTraversal(bst_yTree, yArray, 0);

	//Calls GlobalRebalance on the yTree to rebalance
	bst->_yTree = this->GlobalRebalance(yArray, 0, bst_yTree->size()-1);

}


#endif
