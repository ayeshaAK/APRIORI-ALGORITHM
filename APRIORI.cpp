#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <time.h> 
#include <cstdlib>
using namespace std;

class itemset1st
{
public:
	string item;
	int item_freq;
	itemset1st()
	{
		item = "" ;
		item_freq = 0;
	}
};
class itemset2nd
{
public:
	string item1;
	string item2;
	int item_freq;
	itemset2nd()
	{
		item1= "";
		item2 = "";
		item_freq = 0;
	}
};
class itemset3rd
{
public:
	string item1;
	string item2;
	string item3;
	int item_freq;
	itemset3rd()
	{
		item1 = "";
		item2 = "";
		item3 = "";
		item_freq = 0;
	}
};

int main()
{

//STEP1:

	int transactionno = 0;
	double supthreshold = 0.0, threshold = 0.0;


	ifstream myfile("GroceryStore.txt");
	if (myfile.is_open())
	{
		myfile >> supthreshold;
		myfile >> transactionno;
	}
	else cout << "Unable to open file." << endl;
	myfile.close();
	threshold = transactionno * supthreshold;

	cout << "SUPPORT THRESHOLD  =   " << supthreshold << endl;
	cout << "TRANSACTION NUMBER =   " << transactionno << endl;
	cout << "THRESHOLD          =   " << threshold << endl;

	//Initializing memory of myarray
	int nChars = 10; // assuming a max length of 10 char per string
	int nRows = transactionno;
	int nCols = transactionno;
	char*** myarray =(char***) malloc(nRows * sizeof(char**));
	int i;
	int j;
	int k;
	for (i = 0; i < nCols; ++i)
	{
		myarray[i] =(char**) malloc(nCols * sizeof(char*));
	}
	for (i = 0; i < nRows; ++i)
	{
		for (j = 0; j < nCols; ++j)
		{
			myarray[i][j] =(char*) malloc(nChars * sizeof(char));
		}
	}

	for (i = 0; i < nRows; ++i)
	{
		for (j = 0; j < nCols; ++j)
		{
			for (k = 0; k < nChars; k++)
			{
				myarray[i][j][k] = ' ';
			}

		}
	}
	
	//Storing data in 2D;
	char word=' ';
	ifstream myfile1("GroceryStore.txt");
	if (myfile1.is_open())
	{
		myfile1.seekg(9);

		for (i = 0; i < nRows; ++i)
		{
			for (j = 0; j < nCols; ++j)
			{
				for (k = 0; k < nChars; ++k)
				{
					myfile1.get(word);
					if (myfile1.eof())
					{
						break;
					}
					if  (word == '\n' || word == ',')
					{
						goto l;
					}
					myarray[i][j][k] = word;
				}

			l:
				if (word =='\n')
				{
					goto m;
				}
				continue;
			}
		m:
			continue;
		}
	}
	else cout << "Unable to open file." << endl;
	myfile1.close();

/*
	for (i = 0; i < nRows; ++i)
	{
		for (j = 0; j < nCols; ++j)
		{
			for (k = 0; k < nChars; k++)
			{
				cout << myarray[i][j][k];
			}
		}
		cout << endl;
	}
*/

//STEP2:
//	In the given file the number of different elements bought is 11. So, the array is made accordinly.

	int a = 0;
	const int element_no = 11;
	string allelements[element_no] = { "" };
	string temp = "";
	for (i = 0; i < nRows; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			for (k = 0; k < nChars; k++)
			{
				temp = temp + myarray[i][j][k];
			}
			if (temp != "          ")
			{
				for (int n = 0; n < element_no; n++)
				{
					if (temp == allelements[n])
					{
						goto next;
					}
				}
				allelements[a] = temp;
				a++;
			}
			next:
			temp = "";
		}
	}

/*	In the given file the number of different elements bought is 11. So, the frequency is counted accordinly.
	Keys index for all the elements is given below:
	MILK = 0
	BREAD = 1
	BISCUIT = 2
	TEA = 3
	BOURNVITA = 4
	JAM = 5
	MAGGI = 6
	CORNFLAKES = 7
	COFFEE = 8
	COCK = 9
	SUGAR = 10
*/
	int freq[11] = { 0 };
	temp = "";
	for (i = 0; i < nRows; ++i)
	{
		for (j = 0; j < nCols; ++j)
		{
			for (k = 0; k < nChars; k++)
			{
				temp = temp + myarray[i][j][k];
			}
			if (temp == allelements[0])
			{
				freq[0]++;
			}
			else if (temp == allelements[1])
			{
				freq[1]++;
			}
			else if (temp == allelements[2])
			{
				freq[2]++;
			}
			else if (temp == allelements[3])
			{
				freq[3]++;
			}
			else if (temp == allelements[4])
			{
				freq[4]++;
			}
			else if (temp == allelements[5])
			{
				freq[5]++;
			}
			else if (temp == allelements[6])
			{
				freq[6]++;
			}
			else if (temp == allelements[7])
			{
				freq[7]++;
			}
			else if (temp == allelements[8])
			{
				freq[8]++;
			}
			else if (temp == allelements[9])
			{
				freq[9]++;
			}
			else if (temp == allelements[10])
			{
				freq[10]++;
			}
			else
			{
			}	
			temp = "";
		}
	}

/*	for (i = 0; i < element_no; i++)
	{
		cout <<  allelements[i] << "   =  " << freq[i] << endl;
	}
	cout << endl;*/


//STEP3:
//VALIDATING ITEMS FOR 1ST ITEMSET

	itemset1st* set1;
	int size1 = 0;
	for (i = 0; i < element_no; i++)
	{
		if (freq[i] >= threshold)
		{
			size1++;
		}
	}
	set1 = new itemset1st[size1];

	j = 0;
	for (i = 0; i < element_no; i++)
	{
		if (threshold <= freq[i])
		{
			set1[j].item = allelements[i];
			set1[j].item_freq = freq[i];
			j++;
		}
	}

//SORTING 1ST ITEMSET
	itemset1st tempset;
	for (i = 0; i < size1; i++)
	{
		for (j = i + 1; j < size1; j++)
		{
			if (set1[i].item_freq < set1[j].item_freq)
			{
				tempset = set1[i];
				set1[i] = set1[j];
				set1[j] = tempset;
			}
		}
	}

	cout << "FIRST ITEM SET " << endl;
	for (i = 0; i < size1; i++)
	{
		cout << set1[i].item << " ****** " << set1[i].item_freq << endl;
	}

//STEP4:


	return 0;

}