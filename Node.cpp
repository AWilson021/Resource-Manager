#include "Node.h"
#include <iostream>

Node::Node() {
	next.clear();
	prev.clear();
	usable = true;
}

Node::~Node() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->next.clear();
		nodes.at(i)->prev.clear();
	}
	nodes.clear();
	del.clear();
}

void Node::createNode(std::string val) {

	if (searchDel(val) == false) {
		Node* newNode = new Node();
		nodes.push_back(newNode);
		newNode->setValue(val);
	}
	else {
		int loc = delLocation(val);
		nodes.push_back(del.at(loc));
		unDel = true;
		usable = true;
	}
}

void Node::removeNode(std::string val) {
	int loc = location(val);
	//Node* temp = nodes.at(loc);

	if (loc != -1) {
		if (nodes.at(loc)->hasPrev() == true)
			setFalse(val);
		if (nodes.at(loc)->hasNext() == true)
			removePrev(val);

		nodes.at(loc)->next.clear();
		nodes.at(loc)->prev.clear();
		del.push_back(nodes.at(loc)); //Store deleted nodes
		nodes.erase(nodes.begin() + loc);
	}
	else
		std::cout << val << " not found" << std::endl;
}

bool Node::searchNode(std::string val) {
	for (int i = 0; i < nodes.size(); i++) {
		if ((nodes.at(i)->getValue().compare(val)) == 0)
			return true;
	}

	return false;
}

bool Node::searchDel(std::string val) {
	for (int i = 0; i < del.size(); i++) {
		if ((del.at(i)->getValue().compare(val)) == 0)
			return true;
	}

	return false;
}

int Node::location(std::string val) {
	int i;
	
	for (i = 0; i < nodes.size(); i++) {
		if ((nodes.at(i)->getValue().compare(val)) == 0)
			return i;
	}

	return i = -1;
}

int Node::delLocation(std::string val) {
	int i;

	for (i = 0; i < del.size(); i++) {
		if ((del.at(i)->getValue().compare(val)) == 0)
			return i;
	}

	return i = -1;
}

bool Node::hasNext() {
	if (this->next.size() > 0)
		return true;
	else
		return false;
}

/*Node* Node::getNext() {
	int i;
	for (i = 0; i < 10; i++) {
		if (next[i] != NULL)
			return next[i];
		else
			return NULL;
	}
}*/


void Node::setNext(std::string firstNode, std::string secondNode) {

	int firstLoc;
	int secondLoc;
	bool exists = false;

	firstLoc = location(firstNode);
	secondLoc = location(secondNode);

	if (firstLoc != -1 && secondLoc != -1) {
		for (int i = 0; i < nodes.at(firstLoc)->next.size(); i++) {
			if (nodes.at(firstLoc)->next.at(i)->value.compare(secondNode) == 0) {
				std::cout << std::endl << "Nodes are already connected" << std::endl;
				exists = true;
			}
		}
		if (exists == false) {
			nodes.at(firstLoc)->next.push_back(nodes.at(secondLoc));
			nodes.at(secondLoc)->prev.push_back(nodes.at(firstLoc));
		}
		if (unDel == true)
			setTrue(firstNode);
	}
	else if (firstLoc == -1) {
		createNode(firstNode);
		//std::cout << firstNode << " created" << std::endl;
		setNext(firstNode, secondNode);
	}
	else if (secondLoc == -1){
		createNode(secondNode);
		//std::cout << secondNode << " created" << std::endl;
		setNext(firstNode, secondNode);	
	}
	
}

std::string Node::getValue() {
	return value;
}

void Node::setValue(std::string val) {
	value = val;
}

void Node::showResources() {
	
	

	for (int i = 0; i < nodes.size(); i++) {
		std::cout << nodes.at(i)->getValue() << " -> ";
		for (int j = 0; j < nodes.at(i)->next.size(); j++) {
			std::cout << nodes.at(i)->next.at(j)->getValue() << " ";
			if (nodes.at(i)->usable == false && j == nodes.at(i)->next.size() - 1) {
				if (checkNextList() == false)
					std::cout << " *Unusable";
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Node size: " << nodes.size() << std::endl;

	/*Node* tra = this;
	
	std::cout << tra->getValue() << " -> ";
	for (int i = 0; i < next.size(); i++) {
		if (tra->next.at(i) != NULL) {
			std::cout << tra->next.at(i)->getValue() << " ";
		}
	}*/
	
	
	/*while (tra != NULL)
	{
		std::cout << tra->getValue();  //Show Full Requirments
		tra = tra->getNext();
		std::cout << " -> ";
		numNodes++;
	}*/
}

int Node::getSize() {
	return nodes.size();
}

bool Node::hasPrev() {

	if (this->prev.size() > 0)
		return true;
	else
		return false;
}

void Node::setFalse(std::string val) {

	int loc = location(val);
	Node* temp = nodes.at(loc);

	for (int i = 0; i < temp->prev.size(); i++) {
		temp->prev.at(i)->usable = false;
	}
	for (int i = 0; i < temp->prev.size(); i++) {
		temp = temp->prev.at(i);
		setFalse(temp->value);
	}	
}

void Node::setTrue(std::string val) {
	int loc = location(val);
	Node* temp = nodes.at(loc);

	for (int i = 0; i < temp->next.size(); i++) {
		temp->next.at(i)->usable = true;
	}
	for (int i = 0; i < temp->next.size(); i++) {
		temp = temp->next.at(i);
		setTrue(temp->value);
	}
}

void Node::removePrev(std::string val) {
	int loc = location(val);
	Node* temp = nodes.at(loc);

	for (int i = 0; i < temp->next.size(); i++) {
		for (int j = 0; j < temp->next.at(i)->prev.size(); j++) {
			if (val.compare(temp->next.at(i)->prev.at(j)->value) == 0)
				temp->next.at(i)->prev.erase(temp->next.at(i)->prev.begin() + j);
		}
	}
}

bool Node::checkNextList() {
	bool found;

	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i)->next.size(); j++) {
			if (searchNode(nodes.at(i)->next.at(j)->getValue()) == true)
				found = true;
			else
				found = false;
		}
	}
	
	return found;
}

void Node::deleteNext(std::string firstNode, std::string secondNode) {
	int firstLoc;
	int secondLoc;
	bool exists;

	firstLoc = location(firstNode);
	secondLoc = location(secondNode);

	if (firstLoc != -1 && secondLoc != -1) {
		for (int i = 0; i < nodes.at(firstLoc)->next.size(); i++) {
			if (nodes.at(firstLoc)->next.at(i)->value.compare(secondNode) == 0) {
				removePrev(secondNode);
				nodes.at(firstLoc)->next.erase(nodes.at(firstLoc)->next.begin() + i);
			}
		}
		
	}
	else if (firstLoc == -1) {
		std::cout << firstNode << " not found" << std::endl;
	}
	else if (secondLoc == -1) {		
		std::cout << secondNode << " not found" << std::endl;
	}
}
