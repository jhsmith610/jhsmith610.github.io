//============================================================================
// Name        : delete.cpp
// Author      : Jhon Smith
// Date  	   : 11/15/2020
// Course	   : CS 499
// University  : Southern New Hampshire University
//============================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//***************************************************************
//    	Delete a Business using the ID
//***************************************************************


void main()
   {
    int no;

    system("cls");
    cout<<"\n\n\n\tDelete Record";
    // Get ID of record to be deleted
    cout<<"\n\nPlease Enter The ID Number of the Record You Want To Delete";
    cin>>no;
    // Open Inspections database
    fp.open("Inspections.dat",ios::in|ios::out);
    fstream fp2;
    // Create a temporary database using a copy
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&serv,sizeof(Service)))
	{
	 if(serv.retsno()!=no)
		{
		 // If entry does not match ID write to Temp database
		 fp2.write((char*)&serv,sizeof(Service));
		 }
	 }
    fp2.close();
    fp.close();
    // Delete the original database
    remove("Inspections.dat");
    // Rename the Temp database with original name
    rename("Temp.dat","Inspections.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

