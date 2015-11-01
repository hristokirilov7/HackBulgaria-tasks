#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main ()
{
	ifstream file("input.txt",ios::in);
	vector <string> table;
	int counterRows = 0;
	string wordToFind;
	file >> wordToFind;
	while ( !file.eof() )
	{
		counterRows++;
		string tmp;
		file >> tmp;
		table.push_back( tmp);
	}
	file.close ();
	
	int counterColumns = table[0].size(), counterWord = 0, wordSize = wordToFind.size (); 
	for ( int i = 0; i < counterRows; i++ )
		for ( int j = 0; j < counterColumns; j++ )
			if ( table[i][j] == wordToFind[0] )
			{
				if ( wordSize <= i + 1 ) 
				{
					bool flag = 1;
					for ( int x = i - 1, l = 1; l < wordSize && flag; l++, x-- )
						if ( table[x][j] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				}
				
				if ( wordSize <= counterRows- i ) 
				{
					bool flag = 1;
					for ( int x = i + 1, l = 1; l < wordSize && flag; l++, x++ )
						if ( table[x][j] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				}
				
				if ( wordSize <= j + 1 ) 
				{
					bool flag = 1;
					for ( int y = j - 1, l = 1; l < wordSize && flag; l++, y-- )
						if ( table[i][y] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				}
				
				if ( wordSize <= counterColumns - j ) 
				{
					bool flag = 1;
					for ( int y = j + 1, l = 1; l < wordSize && flag; l++, y++ )
						if ( table[i][y] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
					
				}
				
				if ( wordSize <= i+1 &&  wordSize <= j + 1 ) 
				{
					bool flag = 1;
					for ( int x = i - 1, y = j - 1, l = 1; l < wordSize && flag; l++, x--, y-- )
						if ( table[x][y] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				}
				
				if ( wordSize <= counterRows - i && wordSize <= counterColumns - j ) 
				{
					bool flag = 1;
					for ( int x = i + 1, y = j + 1, l = 1; l < wordSize && flag; l++, x++, y++ )
						if ( table[x][y] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				}
				
				if ( wordSize <= i + 1 && wordSize <= counterColumns - j ) 
				{
					bool flag = 1;
					for ( int x = i - 1, y = j + 1, l = 1; l < wordSize && flag; l++, x--, y++ )
						if ( table[x][y] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				}
				
				if ( wordSize <= counterRows - i && wordSize <= j + 1 ) 
				{
					bool flag = 1;
					for ( int x = i + 1, y = j - 1, l = 1; l < wordSize && flag; l++, x++, y-- )
						if ( table[x][y] != wordToFind[l] ) 
							flag = 0;
					if ( flag )
						counterWord++;
				} 
			}
	cout << counterWord;
	
	return 0;
}