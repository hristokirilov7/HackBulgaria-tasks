#include <iostream>
#include <fstream>
#include <windows.h>
#include <io.h>
#include <vector>
using namespace std;

bool installPackages ( string name )
{
    string installedModules = "installed_modules";
    if ( access ( (installedModules + '\\' + name).c_str(), 0 ) == 0)
    {
        cout << name << " is already installed.\n";
        return 1;
    }
    ifstream packages ( "all_packages.json", ios::in );
    string row;
    bool flag;
    do
    {
        getline ( packages, row );
        flag = !packages.eof();
        if ( row.find ( name ) != string::npos )
        {
            int firstQuotes = 0;
            for ( int j = row.size(); firstQuotes != j; firstQuotes++ )
                if(row[firstQuotes] == '"')
                    break;
            if ( row.find ( name ) == firstQuotes + 1 )
                break;
        }
    }while( flag );
    packages.close();
    if(!flag)
    {
        cout << "Error! " << name << " is not found.\n";
        return 0;
    }
    cout << "Installing " << name << ".\n";
    vector <string> arrPackages;
    for ( int i = row.find ( name ) + name.size() + 1; row[i] !=  ']'; i++ )
        if( row[i] == '"' )
        {
            string tmp;
            for ( i++; row[i] != '"'; i++ )
                tmp.push_back( row[i] );
            arrPackages.push_back( tmp );
        }
    if ( arrPackages.size() != 0 )
    {
        cout << "In order to install " << name << ", we need ";
        for ( int i = 0, j = arrPackages.size(); i < j; i++ )
        {
            if ( i == 0 )
                cout << arrPackages[i];
            else if ( i == j - 1 )
                cout << " and " << arrPackages[i];
            else
                cout << ", " << arrPackages[i];
        }
        cout << ".\n";
        flag = 1;
        for ( int i = 0, j = arrPackages.size(); i < j && flag; i++ )
            flag = installPackages(arrPackages[i]);
    }
    if ( flag )
    {
        CreateDirectory ( ( installedModules + '\\' + name ).c_str(), NULL );
        return 1;
    }
    cout << "Error! Install of " << name << " is not possible.\n";
    return 0;
}

int main ()
{
	string installedModules = "installed_modules";
	if ( access ( installedModules.c_str(), 0 ) != 0 )
		CreateDirectory ( installedModules.c_str(), NULL );
	ifstream dependencies ( "dependencies.json", ios::in);
	string allDependencies;
	bool flag;
	do
	{
		getline( dependencies, allDependencies );
		flag = !dependencies.eof();

		if ( allDependencies.find ( "dependencies" ) != string::npos )
        {
            int firstQuotes = 0;
            for ( int j = allDependencies.size(); firstQuotes != j; firstQuotes++ )
                if(allDependencies[firstQuotes] == '"')
                    break;
            if ( allDependencies.find ( "dependencies" ) == firstQuotes + 1 )
                break;
        }
	}while ( flag );
	dependencies.close();
	if(!flag)
    {
        cout << "Error! Dependencies is not found.\n";
        return 0;
    }
	vector <string> arrDependencies;
    for( int i = allDependencies.find( "dependencies" ) + 13; allDependencies[i] != ']'; i++)
    {
        if ( allDependencies[i] == '"' )
        {
            string tmp;
            for ( i++; allDependencies[i] != '"'; i++ )
                tmp.push_back(allDependencies[i]);
            arrDependencies.push_back(tmp);
        }
    }
    flag = 1;
    for (int i = 0, j = arrDependencies.size () && flag; i < j; i++)
        flag = installPackages(arrDependencies[i]);
    if (flag)
        cout << "All done.\n";
    else
        cout << "Error!\n";
	return 0;
}
