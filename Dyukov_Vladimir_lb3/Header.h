#pragma once

#include <iostream>


class Tree {

public:
	char info;
	Tree* left;
	Tree* right;

	Tree();
	~Tree();

	friend std::istream& operator>> (std::istream&, Tree**);
	friend std::ostream& operator<< (std::ostream&, Tree*);
};


class TwoTree {

private:
	Tree* first;
	Tree* second;

public:
	TwoTree();
	TwoTree(Tree*, Tree*);

	bool isEqual(Tree*, Tree*);
	bool isEqual();
	bool isMirrorEqual(Tree*, Tree*);
	bool isMirrorEqual();
	bool isSuch(Tree*, Tree*);
	bool isSuch();
	bool isMirrorSuch(Tree*, Tree*);
	bool isMirrorSuch();

	void printTrees(std::ostream&);
};