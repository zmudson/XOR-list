#include "Node.h"

Node::Node(int key, Node* link) {
	this->key = key;
	this->link = link;
}

void Node::setLink(Node* link) {
	this->link = link;
}

Node* Node::getLink() const {
	return link;
}

int Node::getKey() const {
	return key;
}