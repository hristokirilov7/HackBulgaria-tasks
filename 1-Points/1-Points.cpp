#include <iostream>
using namespace std;
int main ()
{
	int x, y, arr[4];
	cout << "Starting point: ";
	cin >> x >> y;
	string arrows;
	cout << "Type string: ";
	cin >> arrows;
	int arrowsSize = arrows.size();
	arr[0] = 1;
	arr[1] = -1;
	arr[2] = 1;
	arr[3] = -1;
	bool flag = 1;
	for (int i = 0; i < arrowsSize && flag; i++)
	{
		switch (arrows[i])
		{
			case '>' : x += arr[0]; break;
			case '<' : x += arr[1]; break;
			case 'v' : y += arr[2]; break;
			case '^' : y += arr[3]; break;
			case '~' : 
			{
				arr[0] *= -1;
				arr[1] *= -1;
				arr[2] *= -1;
				arr[3] *= -1;
			}break;
			default: flag = 0;
		}
	}
	if (flag)
		cout << '(' << x << ", " << y << ')' << endl;
	else
		cout << "Incorrect data" << endl;
	return 0;
}