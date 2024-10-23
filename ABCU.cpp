#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
// define a structure to hold bid information
struct Course {
	string courseId; // unique identifier
	string title;
	vector<string> prereq;
	Course() {
		prereq = {};
	}
	void print() {
		cout << "|*| " << courseId << " || " << title;

		cout << "\n Prerequisites: ";
		if (prereq.size() > 0) {
			for (int i = 0;i < prereq.size() - 1;i++)
			{
				cout << prereq[i] << " , ";
			}
			cout << prereq[prereq.size() - 1] << endl;
		}
		else {
			cout << "None" << endl;
		}
		cout << endl;
	}
};

// Internal structure for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;

	// default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with a bid
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Course couse);
	void inOrder(Node* node);
	void postOrder(Node* node);
	void preOrder(Node* node);
	Node* removeNode(Node* node, string courseId);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void PostOrder();
	void PreOrder();
	void Insert(Course course);
	void Remove(string courseId);
	Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	// FixMe (1): initialize housekeeping variables
	//root is equal to nullptr
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
	//FixMe (2)
	// recurse from root deleting every node
	postOrder(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	// FixMe (3a): In order root
	// call inOrder fuction and pass root 
	inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
	// FixMe (4a): Post order root
	// postOrder root
	postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
	// FixMe (5a): Pre order root
	// preOrder root
	preOrder(root);
}



/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
	// FIXME (6a) Implement inserting a bid into the tree
	Node* node = new Node(course);

	// if root equarl to null ptr
	if (root == nullptr)
		// root is equal to new node bid
		root = node;
	// else
	else {
		// add Node root and bid
		addNode(root, course);
	}
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string courseId) {
	// FIXME (7a) Implement removing a bid from the tree
	// remove node root bidID
	removeNode(root, courseId);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
	// FIXME (8) Implement searching the tree for a bid
	// set current node equal to root
	Node* node = root;
	// keep looping downwards until bottom reached or matching bidId found
	while (node != nullptr) {
		Course course = node->course;
		// if match found, return current bid
		if (course.courseId == courseId)
			return node->course;
		// if bid is smaller than current node then traverse left
		else if (courseId < course.courseId)
			node = node->left;
		// else larger so traverse right
		else
			node = node->right;
	}
	Course bid;
	return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
	// FIXME (6b) Implement inserting a bid into the tree
	// if node is larger then add to left
	if (node->course.courseId > course.courseId) {
		// if no left node
		if (node->left == nullptr)
			// this node becomes left
			node->left = new Node(course);
		// else recurse down the left node
		else
			addNode(node->left, course);
	}
	// else
	else {
		// if no right node
		if (node->right == nullptr)
			// this node becomes right
			node->right = new Node(course);
		//else
		else
			// recurse down the left node
			addNode(node->right, course);
	}
}
void BinarySearchTree::inOrder(Node* node) {
	// FixMe (3b): Pre order root
	//if node is not equal to null ptr
	if (node != nullptr) {
		//InOrder not left
		inOrder(node->left);
		//output bidID, title, amount, fund
		Course course = node->course;
		course.print();
		//InOder right
		inOrder(node->right);
	}
}

void BinarySearchTree::postOrder(Node* node) {
	// FixMe (4b): Pre order root
	//if node is not equal to null ptr
	if (node != nullptr) {
		//postOrder left
		postOrder(node->left);
		//postOrder right   
		postOrder(node->right);
		//delete node
		delete node;
	}
}

void BinarySearchTree::preOrder(Node* node) {
	// FixMe (5b): Pre order root
	//if node is not equal to null ptr
	if (node != nullptr) {
		//output bidID, title, amount, fund
		Course course = node->course;
		course.print();
		//postOrder left
		postOrder(node->left);
		//postOrder right   
		postOrder(node->right);
	}
}
/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
	// FIXME (7b) Implement removing a bid from the tree
	// if node = nullptr return node
	if (node == nullptr)
		return node;

	// (otherwise recurse down the left subtree)
	// check for match and if so, remove left node using recursive call 
	if (node->course.courseId > courseId)
		node->left = removeNode(node->left, courseId);

	// (otherwise recurse down the right subtree)
	// check for match and if so, remove right node using recursive call
	else if (node->course.courseId < courseId)
		node->right = removeNode(node->right, courseId);

	// (otherwise no children so node is a leaf node)
	else {
		// if left node = nullptr && right node = nullptr delete node 
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return nullptr;
		}

		// (otherwise check one child to the left)
		// if left node != nullptr && right node = nullptr delete node 
		else if (node->left != nullptr && node->right == nullptr) {
			Node* temp = node->right;
			delete node;
			return temp;
		}


		// (otherwise check one child to the right)
		// if left node = nullptr && right node != nullptr delete node
		else if (node->left == nullptr && node->right != nullptr) {
			Node* temp = node->left;
			delete node;
			return temp;
		}

		// (otherwise more than one child so find the minimum)
		else {
			// create temp node to right
			Node* temp = node->right;
			// while left node is not nullptr keep moving temp left
			while (node->left != nullptr)
				node = temp->left;
			// make node bid (right) equal to temp bid (left)
			node->right = temp;
			// remove right node using recursive call
			removeNode(node->right, courseId);
		}
	}

	return node; //return node
}


void loadData(string filePath, BinarySearchTree* bst) {
	cout << "Loading CSV file " << filePath << "...";
	string line;

	ifstream file(filePath);
	// loop to read rows of a CSV file

	if (file.is_open()) {

		while (getline(file, line)) {
			vector<string> row;
			stringstream lineStream(line);
			string cell;

			while (getline(lineStream, cell, ',')) {
				row.push_back(cell);
			}

			Course course;
			if (row.size() < 2) {
				cout << "invalid file format" << endl;
				return;
			}
			else if (row.size() > 2) {
				if (row[2] != "") {
					for (int i = 2;i < row.size();i++) {
						course.prereq.push_back(row[i]);
					}
				}
			}
			course.courseId = row[0];
			course.title = row[1];

			bst->Insert(course);
		}
		file.close();
		cout << "Done!" << endl << endl;
	}
	else {
		cerr << "error opening file: " << filePath << endl;
	}
}


int main()
{
	string filepath = "CS 300 ABCU_Advising_Program_Input.csv";
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	bool loaded = false;
	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Course Data" << endl;
		cout << "  2. Print All Courses" << endl;
		cout << "  3. Print Course Info" << endl;
		cout << "  9. Exit" << endl;
		Course course;
		string courseId;
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			choice = 0;
		}
		switch (choice) {
		case 1:
			if (!loaded) {
				loadData(filepath, bst);
				loaded = true;
			}
			else {
				string yn;
				cout << "Do you want to reload course data?(y/n)" << endl;
				while (yn=="") {
					cin >> yn;
					if (yn == "y" || yn == "Y") {
						delete bst;
						bst = new BinarySearchTree();
						loadData(filepath, bst);
						break;
					}
					else if (yn == "n" || yn == "N") {
						break;
					}
					else {
						cout << "please enter y/n"<<endl;
						yn = "";
					}
				}

			}
			break;
		case 2:
			if (loaded)	bst->InOrder();
			else cout << "No data loaded. Please Load data first." << endl;
			break;
		case 3:
			cout << "Enter course Id:" << endl;
			cin >> courseId;
			course = bst->Search(courseId);
			if (course.courseId != "") {
				course.print();
			}
			else {
				cout << "Course: " << courseId << " not found." << endl;
			}
			break;
		case 9:
			delete bst;
			cout << "Exiting program...";
			break;
		default:
			cout << "invalid input\n" << endl;
			break;

		}
	}
}
