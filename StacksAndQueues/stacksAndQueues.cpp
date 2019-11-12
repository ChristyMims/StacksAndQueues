/////////////////////////////////////////////////////////////////////////////////////////////////
//  This program allows the user to enter a file name. The data in the file is then moved into
//  the queue if 0 through 49 and into the stack if 50 to 99.  It will also exclude bad or 
//  invalid data. The data will then be written to separate data files, Queue.txt and Stack.txt,
//  and be popped off respectively. The data in each will also be averaged and outputted to the
//  file as well.
//
//  Christy Mims
//
//  6/30/2019
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<string>
#include<fstream>
#include<stack>
#include<queue>

using namespace std;

// function headers
string getFileName(string);
void readData(string, stack<int>*, queue<int>*);
int popQueue(queue<int>*);
int popStack(stack<int>*);

int main()
{
	// defines the stack to be used and so other functions can access it
	stack<int> MyStack;	

	// defines the queue to be used
	queue<int> MyQueue;	

	// create variable to hold file name
	string fileName;		
	
	// call getfileName function and catch the file name
	fileName = getFileName(fileName);	

	// call the read data function
	readData(fileName, &MyStack, &MyQueue);		

	// calls function to write queue to file and pop off queue
	popQueue(&MyQueue); 

	// calls function to write stack to file and pop off stack
	popStack(&MyStack); 


	// pauses output
	//system("PAUSE");
	return(0);

}

string getFileName(string fileName)
{

	// prompt user for name of file
	cout << "Enter name of text file." << endl;

	// take in file name from the user
	cin >> fileName;

	// formatting
	cout << endl << endl;


	// returns file name
	return (fileName);
}

void readData(string fileName, stack<int> *MyStack, queue<int> *MyQueue)
{
	// variable to catch data
	int fileData = -1;


	// create stream reader
	ifstream readData;

	// point to the stream reader and open the file provided by the user
	readData.open(fileName);

	// check to see if there was problem opening the file loops until 
	// user provides vaild file name
	while (!readData)
	{
		cout << "File could not be opened for reading." << endl << endl;

		// calls the function getFileName
		fileName = getFileName(fileName);
		// try to open file 
		readData.open(fileName);
	}


	// look for end of file to see if all data has been read in 
	while (readData)
	{

		// read in data from file
		readData >> fileData;

		// check to see if end of file has been reached
		if (readData.eof()) break;

		// check for invalid data and clear if is invalid
		if (readData.fail() || fileData < 0 || fileData > 99)
		{
			

			readData.clear();
			readData.ignore();
			
			fileData = -1;

			cout << endl;
		}

		// check to see if the number is between 0 and 49
		if ((fileData >= 0) && (fileData <= 49))
		{
			// push to queue if number is valid and within range
			MyQueue->push(fileData);
			//cout << MyQueue->back() << " ";
		}

		// check to see if the number is between 50 and 99
		if ((fileData >= 50) && (fileData <= 99))
		{
			// push to stack if valid and within range
			MyStack->push(fileData);
			//cout << MyStack->top() << " ";
		}



	}

	// close the file 
	readData.close();

}

int popQueue(queue<int> *MyQueue)
{
	// create the stream writer
	ofstream writeQueue;

	// opens the file Queue.txt or creates it
	writeQueue.open("Queue.txt");

	// check to see if file was opened or created for writing
	if (!writeQueue)
	{
		cout << "Could not open or create the text file for writing" << endl;
		return(1);	
	}

	// variable to store total of data
	int total = 0;

	// variable to keep track of how many are in queue
	int counter = 0;

	// output for user
	cout << "My Queue has: " << endl;

	// checks to see if list is empty
	while (!MyQueue->empty())
	{
		// output to console for user
		cout << ' ' << MyQueue->front();

		// output to file
		writeQueue << MyQueue->front();

		// keeps running total of data in queue
		total += MyQueue->front();

		// pops them out of the queue
		MyQueue->pop();

		// increments counter to keep track of total data in queue
		counter = counter + 1;
		
		// formatting
		writeQueue << endl;
		cout << endl;
		
	}
	
	// average of queue
	int average = total / counter;

	// writes the average to the console and the file
	cout << "Average of Queue is: " << average << endl;
	writeQueue << "Average of Queue is: " << average << endl;
	
	// formatting 
	cout << endl << endl;

	// closes the file
	writeQueue.close();
}

int popStack(stack<int> *MyStack)
{
	// creates stream writer
	ofstream writeStack;

	// opens the file Stack.txt or creates it
	writeStack.open("Stack.txt");

	// check to see if file was opened or created for writing
	if (!writeStack)
	{
		cout << "Could not open or create the text file for writing" << endl;
		return(1);
	}

	// variable to store total of data
	int total = 0;

	// variable to keep track of how many are in stack
	int counter = 0;

	// output for user
	cout << "My Stack has: " << endl;

	// checks to see if list is empty
	while (!MyStack->empty())
	{
		// output to console for user
		cout << ' ' << MyStack->top();

		// output to file
		writeStack << MyStack->top();

		// keeps running total of data in queue
		total += MyStack->top();

		// pops them off stack
		MyStack->pop();

		// increments counter to keep track of total data in stack
		counter = counter + 1;

		// formatting
		writeStack << endl;
		cout << endl;
	}

	// average of queue
	int average = total / counter;

	// writes the average to the console and the file
	cout << "Average of Stack is: " << average << endl;
	writeStack << "Average of Stack is: " << average << endl;

	// formatting 
	cout << endl << endl;

	// close the file
	writeStack.close();
}