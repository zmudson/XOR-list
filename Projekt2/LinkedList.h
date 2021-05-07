#pragma once

#include "Node.h"

class LinkedList {
private:
	Node* first = nullptr;
	Node* last = nullptr;
	Node* actual = nullptr;
	Node* next = nullptr;
	Node* previous = nullptr;
public:
	void printForward() const;
	void printBackward() const;
	void deleteActual();
	void deleteLast();
	void deleteFirst();
	Node* getNext();
	Node* getPrevious();
	Node* getActual();
	void addFirst(int key);
	void addLast(int key);
	static Node* XOR(Node* left, Node* right);
	void addActual(int key);
	void deleteValues(int key);
};

