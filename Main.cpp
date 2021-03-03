#include <iostream>
#include "Node.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void main() {
	
	ifstream file;
	Node node;

	int count = 0;
	char sChoice;
	string choice;
	bool play = true;
	

	string line;
	string firstWord;
	string secondWord;

	file.open("resource.txt");

	while (getline(file, line)) {

		istringstream iss(line);
		firstWord, secondWord;
		
		if (!(iss >> firstWord >> secondWord))
			break;

		node.setNext(firstWord, secondWord);

		/*node.setNext("Handgun", "Bullets");
		node.setNext("Handgun", "Metal");
		node.setNext("Metal", "Ore");
		node.setNext("Bullets", "Ore");

		node.showResources();*/
	}

	file.close();

	while (play == true) {
		cout << endl;
		cout << "Current graph:" << endl;
		node.showResources();
		cout << endl;

		if (node.getSize() == 0) {
			cout << "No more nodes left...Quiting" << endl;
			break;
		}

		cout << "Choose whether to create a new node, a new connection, delete a connection or delete a node (q to quit)" << endl;
		cout << "1. Create a new node" << endl;
		cout << "2. Create a new connection" << endl;
		cout << "3. Delete a node" << endl;
		cout << "4. Delete a connection" << endl;
		cout << "Choice: ";
		cin >> sChoice;

		switch (sChoice) {
		case '1':
			cout << "Enter the name of the node you would like to create: ";
			cin >> choice;
			if (node.searchNode(choice) == false)
				node.createNode(choice);
			else
				cout << "Node already exists" << endl;
			break;

		case '2':
			cout << "Enter the name of the first node: ";
			cin >> firstWord;
			cout << "Enter the name of the second node: ";
			cin >> secondWord;
			if (node.searchNode(firstWord) == true && node.searchNode(secondWord) == true)
				node.setNext(firstWord, secondWord);
			else if (node.searchNode(firstWord) == false)
				cout << firstWord << " not found" << endl;
			else if (node.searchNode(secondWord) == false)
				cout << secondWord << " not found" << endl;
			break;

		case '3': 
			cout << "Enter the name of a node you would like to delete: ";
			cin >> choice;
			node.removeNode(choice);
			break;

		case '4':
			cout << "Enter the name of the first node: ";
			cin >> firstWord;
			cout << "Enter the name of the second node: ";
			cin >> secondWord;
			node.deleteNext(firstWord, secondWord);
			break;

		case 'q':
		case 'Q':
			play = false;
			break;

		default:
			cout << endl << "Invalid option...try again" << endl;
			break;
		}
		
	}
		
	
}