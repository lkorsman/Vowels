/*
 * Author: Luke Korsman
 * Name: vowels.cpp
 * Date: April 18, 2018
 * Version: 1
 */

/*
 * This program will create 20 pthreads based on 20 .txt files. It will prompt
 * the user to enter to enter a directory as to where the 20 files are located.
 * If there are no errors creating the pthreads then the program will display 
 * the total count of each vowel contained within all 20 files.
 */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
using namespace std;

// Array containing the .txt file names
string filenameArray[20] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", 
	"file5.txt", "file6.txt", "file7.txt", "file8.txt", "file9.txt", "file10.txt",
	"file11.txt", "file12.txt", "file13.txt", "file14.txt", "file15.txt",
	"file16.txt", "file17.txt", "file18.txt", "file19.txt", "file20.txt"};

int const FILE_ARRAY_SIZE = 20;		// Size of the array of .txt files
int countA = 0;						// Count of number of A's
int countE = 0;						// Count of number of E's
int countI = 0;						// Count of number of I's
int countO = 0;						// Count of number of O's
int countU = 0;						// Count of number of U's
pthread_mutex_t vowelALock;			// Lock for A counter
pthread_mutex_t vowelELock;			// Lock for E counter
pthread_mutex_t vowelILock;			// Lock for I counter
pthread_mutex_t vowelOLock;			// Lock for O counter
pthread_mutex_t vowelULock;			// Lock for U counter

// Introduces the program to the user
void welcome();

// Counts the number of vowels within a given text file
void* countVowels(void *filename);

// Prints the message 'Goodbye', signaling the program ended
void goodbye();

// Entry point into the program
int main()
{
	char input[200]; // Holds directory path of the .txt files
	pthread_t threadArray[FILE_ARRAY_SIZE]; // Array of thread ID's
	int threadReturnValue;					// Checks to see if error creating 
											// thread
	// Initialize all vowel locks
	pthread_mutex_init(&vowelALock, NULL);
	pthread_mutex_init(&vowelELock, NULL);
	pthread_mutex_init(&vowelILock, NULL);
	pthread_mutex_init(&vowelOLock, NULL);
	pthread_mutex_init(&vowelULock, NULL);
	
	welcome();
	
	// Prompt user for file directory
	cout << "Enter a file path directory containing the 20 .txt files, "
	"ending with the '/' \ncharacter. If the files are in the current "
	"directory, then simply hit \nenter: ";
	cin.getline(input,sizeof(input));
		
	// If .txt files not in current directory, concatenate filenames with
	// file location
	if (sizeof(input) > 0)
	{
		for (int i = 0; i < FILE_ARRAY_SIZE; i++)
		{
			filenameArray[i] = input + filenameArray[i];
		}
	}

	// Create 20 threads based on each file
	for (int j = 0; j < FILE_ARRAY_SIZE; j++)
	{
		threadReturnValue = pthread_create(&threadArray[j], NULL, 
										   countVowels, &filenameArray[j]);
		
		// End program if unable to create a thread
		if (threadReturnValue)
		{
			cout << "Error: unable to create thread." << endl;
			exit(-1);
		}
	}

	// Join all threads before ending program
	for (int k = 0; k < FILE_ARRAY_SIZE; k++)
	{
		pthread_join (threadArray[k], NULL);
	}
	
	// Display counts of each vowel
	cout << "Count of A's: " << countA << endl;
	cout << "Count of E's: " << countE << endl;
	cout << "Count of I's: " << countI << endl;
	cout << "Count of O's: " << countO << endl;
	cout << "Count of U's: " << countU << endl;
	
	goodbye();
	
	return 0;
}

// Counts the number of vowels of a given .txt file passed in as it's parameter
void *countVowels(void *parameters)
{
	string *fname = (string*)parameters; // Create local string variable with 
									     // based on parameter variable
	char ch;							 // Current character being read
	ifstream infile;					 // Input file to be read
	
	infile.open(*fname);	
	
	if (infile.is_open())
	{
		while (infile >> noskipws >> ch) 
		{
			// Increment vowel counts based on the character being read
			switch(ch)
			{
				case 'A':
					pthread_mutex_lock(&vowelALock);
					countA++;
					pthread_mutex_unlock(&vowelALock);
					break;
				case 'a':
					pthread_mutex_lock(&vowelALock);
					countA++;
					pthread_mutex_unlock(&vowelALock);
					break;
				case 'E':
					pthread_mutex_lock(&vowelELock);
					countE++;
					pthread_mutex_unlock(&vowelELock);
					break;
				case 'e':
					pthread_mutex_lock(&vowelELock);
					countE++;
					pthread_mutex_unlock(&vowelELock);
					break;
				case 'I':
					pthread_mutex_lock(&vowelILock);
					countI++;
					pthread_mutex_unlock(&vowelILock);
					break;
				case 'i':
					pthread_mutex_lock(&vowelILock);
					countI++;
					pthread_mutex_unlock(&vowelILock);
					break;
				case 'O':
					pthread_mutex_lock(&vowelOLock);
					countO++;
					pthread_mutex_unlock(&vowelOLock);
					break;
				case 'o':
					pthread_mutex_lock(&vowelOLock);
					countO++;
					pthread_mutex_unlock(&vowelOLock);
					break;
				case 'U':
					pthread_mutex_lock(&vowelULock);
					countU++;
					pthread_mutex_unlock(&vowelULock);
					break;
				case 'u':
					pthread_mutex_lock(&vowelULock);
					countU++;
					pthread_mutex_unlock(&vowelULock);
					break;
				default:
					break;
			}
		}
	}
	else
	{
		cout << "\nError reading files." << endl;
	}
	pthread_exit(NULL);
}

void welcome()
{
	cout << "\nThis program will ask you for a directory location of 20 .txt \n"
			"files named file1.txt through file20.txt. Then it will create 20 \n"
			"pthreads to count the total number of vowels in all the files. \n"
			"Once finished, if there are no errors, it will print the total \n"
			"counts of each vowel.\n" << endl;
}

void goodbye()
{
	cout << "\nGoodbye.\n" << endl;
}


