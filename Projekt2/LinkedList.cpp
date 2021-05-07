#define _CRT_SECURE_NO_WARNINGS

#include "LinkedList.h"
#include <cstdint>
#include <stdio.h>

void LinkedList::printForward() const{
	if (first != nullptr) {
		Node* current = first;
		Node* left = nullptr;
		while (current != nullptr) {
			printf("%d ", current->getKey());
			Node* tmp = XOR(left, current->getLink());
			left = current;
			current = tmp;
		}
	}
	else 
		printf("NULL");
	printf("\n");
}

void LinkedList::printBackward() const{
	if (last != nullptr) {
		Node* current = last;
		Node* right = nullptr;
		while (current != nullptr) {
			printf("%d ", current->getKey());
			Node* tmp = XOR(current->getLink(), right);
			right = current;
			current = tmp;
		}
	}
	else 
		printf("NULL");
	printf("\n");
}

void LinkedList::deleteActual(){
	if (actual != nullptr) {
		if (previous == nullptr) {
			first = next;
			if (next == nullptr) {
				delete actual;
				actual = nullptr;
				last = nullptr;
			}
			else {
				if (last == next) {
					last->setLink(XOR(nullptr, nullptr));
				}
				else {
					next->setLink(XOR(next->getLink(), actual));
					previous = XOR(last->getLink(), nullptr);
				}
				delete actual;
				actual = last;
				next = nullptr;
			}
		}
		else {
			Node* newPrevious = XOR(previous->getLink(), actual);
			previous->setLink(XOR(XOR(previous->getLink(), actual), next));
			if (next != nullptr)
				next->setLink(XOR(previous, XOR(actual, next->getLink())));
			else
				last = previous;
			delete actual;
			actual = previous;
			previous = newPrevious;
		}
		
	}

}

void LinkedList::deleteLast(){
	if (first == last) {
		if (last != nullptr) {
			delete last;
			last = nullptr;
		}
		first = nullptr;
		actual = nullptr;
	}
	else {
		Node* left = XOR(last->getLink(), nullptr);
		left->setLink(XOR(XOR(left->getLink(), last), nullptr));
		if (last == actual) {
			previous = XOR(left->getLink(), nullptr);
			actual = left;
			next = nullptr;
		}
		else if (left == actual)
			next = nullptr;
		delete last;
		last = left;
	}
}

void LinkedList::deleteFirst(){
	if (first == last) {
		if (first != nullptr) {
			delete first;
			first = nullptr;
		}
		last = nullptr;
		actual = nullptr;
	}
	else {
		Node* right = XOR(nullptr, first->getLink());
		right->setLink(XOR(nullptr, XOR(first, right->getLink())));
		if (first == actual) {
			previous = right == last ? nullptr : XOR(last->getLink(), nullptr);
			actual = last;
			next = nullptr;
		}
		else if (right == actual)
			previous = nullptr;
		delete first;
		first = right;
	}
}

Node* LinkedList::getNext(){
	if (actual == nullptr)
		return nullptr;
	else if (next == nullptr) {
		previous = nullptr;
		actual = first;
		next = XOR(nullptr, first->getLink());
	}
	else {
		Node* newPrevious = actual;
		Node* current = next;
		previous = newPrevious;
		actual = current;
		next = XOR(newPrevious, current->getLink());

	}
	return actual;
}

Node* LinkedList::getPrevious(){
	if (actual == nullptr)
		return nullptr;
	else if (previous == nullptr) {
		previous = XOR(last->getLink(), nullptr);
		actual = last;
		next = nullptr;
	}
	else {
		Node* current = previous;
		Node* newNext = actual;
		previous = XOR(current->getLink(), newNext);
		actual = current;
		next = newNext;
	}
	return actual;
}

Node* LinkedList::getActual(){
	return actual;
}

void LinkedList::addFirst(int key){
	Node* newNode = new Node(key, XOR(nullptr, first));
	if(first != nullptr)
		first->setLink(XOR(newNode, first->getLink()));
	first = newNode;
	if (actual != nullptr && previous == nullptr)
		previous = newNode;
	if (last == nullptr) {
		last = newNode;
		actual = newNode;
	}
}

void LinkedList::addLast(int key){
	Node* newNode = new Node(key, XOR(last, nullptr));
	if(last != nullptr)
		last->setLink(XOR(last->getLink(), newNode));
	last = newNode;
	if (actual != nullptr && next == nullptr)
		next = newNode;
	if (first == nullptr) {
		first = newNode;
		actual = newNode;
	}
}

Node* LinkedList::XOR(Node* left, Node* right) {
	return (Node*) (((uintptr_t)left) ^ ((uintptr_t)right));
}

void LinkedList::addActual(int key) {
	if (actual == nullptr || actual == first)
		addFirst(key);
	else {
		Node* newNode = new Node(key, XOR(previous, actual));
		previous->setLink(XOR(XOR(previous->getLink(), actual), newNode));
		actual->setLink(XOR(newNode, XOR(previous, actual->getLink())));
		previous = newNode;
	}
}

void LinkedList::deleteValues(int key) {
	Node* current = first;
	Node* left = nullptr;
	Node* right = nullptr;
	while (current != nullptr) {
		if (current->getKey() == key) {
			if (current == actual) {
				deleteActual();
				current = next;
				left = actual;
			}
			else if (current == first) {
				deleteFirst();
				current = first;
			}
			else if (current == last) {
				deleteLast();
				current = nullptr;
			}
			else {
				if (current == next) {
					next = XOR(actual, current->getLink());
					actual->setLink(XOR(XOR(actual->getLink(), current), next));
					next->setLink(XOR(actual, XOR(current, next->getLink())));
				}
				else if (current == previous) {
					previous = XOR(previous->getLink(), actual);
					actual->setLink(XOR(previous, XOR(current, actual->getLink())));
					previous->setLink(XOR(XOR(previous->getLink(), current), actual));
				}
				else {
					right = XOR(current->getLink(), left);
					left->setLink(XOR(XOR(left->getLink(), current), right));
					right->setLink(XOR(left, XOR(current, right->getLink())));
				}
				Node* tmp = XOR(current->getLink(), left);
				delete current;
				current = tmp;
			}
		}
		else {
			Node* tmp = XOR(left, current->getLink());
			left = current;
			current = tmp;
		}
	}
}