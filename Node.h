#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>

#ifndef NODE_H
#define NODE_H

class Node {

public:
	Node();
	virtual ~Node();

	
	//Node* getNext();
	void createNode(std::string);
	void removeNode(std::string);
	bool searchNode(std::string);
	bool searchDel(std::string);
	int	 location(std::string);
	int	 delLocation(std::string);
	void setNext(std::string, std::string);
	std::string getValue();
	void setValue(std::string);
	void showResources();
	int getSize();
	bool hasNext();
	bool hasPrev();
	void setFalse(std::string);
	void setTrue(std::string);
	void removePrev(std::string);
	bool checkNextList();
	void deleteNext(std::string, std::string);

private:
	int maxVal = 5;
	std::vector <Node*> next;
	std::vector <Node*> prev;
	std::vector <Node*> nodes;
	std::vector <Node*> del;
	std::string value;
	int numNodes = 0;
	bool usable;
	bool unDel = false;
};

#endif
