//============================================================================
// Name        : VectorSorting.cpp
// Author      : Jhon Smith
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;
    string strAmount

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');  //Method call that changes string to a double

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

/**
 * I tested the code with the larger file and it failed to sort regardless of case.  iPhone
 * was placed at the end of the list instead of with the I's.  This function converts
 * the title to lower case for a more accurate comparison.
 */
std::string toLower(std::string str) {

	for( char& c : str ) c = std::tolower(c) ;
		return str ;

}

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	int low = 0;
	int high = 0;
	int mid = 0;
	string pivot = "";
	Bid temp;
	bool done = false;

	//Find the midpoint and assign to pivot
	mid = begin + (end - begin) / 2;
	pivot = toLower(bids.at(mid).title);

	low = begin;
	high = end;

	while (!done) {

		//Increment low while bid.at(low) is < pivot
		while (toLower(bids.at(low).title).compare(pivot) < 0) {
			++low;

		}

		//Decrement high while pivot < bid.at(high)
		while (pivot.compare(toLower(bids.at(high).title)) < 0) {
			--high;

		}

		//If there are 0 or 1 elements left, return high
		if (low >= high) {
			done = true;

		//Swap low and high values, adjust low and high
		} else {
			temp = bids.at(low);
			bids.at(low) = bids.at(high);
			bids.at(high) = temp;

			++low;
			--high;
		}


	}

	return high;

}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
	int mid = 0;

	//If there are 0 or 1 elements, return
	if (begin >= end) {
		return;
	}

	//Call partitition to set the mid
	mid = partition(bids, begin, end);

	//Recursively call quickSort for the lower part
	quickSort(bids, begin, mid);

	//Recursively call quickSort for the upper part using mid + 1
	quickSort(bids, mid + 1, end);

	return;

}

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
	unsigned int min;
	Bid temp;

	//Assign min value to current position
	for (unsigned pos = 0; pos < bids.size(); ++pos) {
		min = pos;

		//Compare each value with current min
		for (unsigned j = pos + 1; j < bids.size(); ++j) {
			//If value is lower, reassign min
			if (toLower(bids.at(j).title).compare(toLower(bids.at(min).title)) < 0) {
				min = j;

			}
		}

		//If the current min is not equal to the current element, swap them
		if (min != pos) {
			temp = bids.at(pos);
			bids.at(pos) = bids.at(min);
			bids.at(min) = temp;

		}

	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (unsigned int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        case 3:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to selection sort
            selectionSort(bids);

            cout << bids.size() << " bids sorted" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to quick sort
            quickSort(bids, 0, bids.size() -1);

            cout << bids.size() << " bids sorted" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
