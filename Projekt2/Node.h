#pragma once
class Node {
private:
	int key;
	Node* link;
public:
	Node(int key, Node* link);
	void setLink(Node* link);
	Node* getLink() const;
	int getKey() const;
};

