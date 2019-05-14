/* 
 * File:   main.cpp
 * Author: jjones3
 *
 * Created on September 20, 2018, 11:41 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <valarray>
#include <regex>

using namespace std;

struct bacteria
{
    string ID;
    string isolate;
    string note;
    string date;
    string box;
    string location;
};

bacteria initial = {"0", "0", "0","0", "0", "0"};
bacteria current;
const int SIZE = 12000;
const int SEARCHLIST = 474;
bacteria repository[SIZE];
bacteria list[SEARCHLIST];

//dataset input
bacteria getInput(ifstream& infile){
    infile >> current.ID >> current.isolate>> current.note >> current.date >>current.box >> current.location;
    return current;
}

//take in information id and isolate of specimens to find
bacteria getInputSearchList(ifstream& fileIn){
    fileIn >> current.ID >> current.isolate;
    current.note = " ";
    current.date = " ";
    current.box = " ";
    current.location = " ";
    return current;
}

int printArray(bacteria a[], int size, ofstream& name){
    for (int i=0; i < size; i++)
        name << a[i].ID <<" " <<a[i].isolate  <<","<< a[i].box<<" "<< a[i].location <<endl;
    return 0;
}

int searchLocation(bacteria repo[], bacteria searchList[], int size, int smallSize, ofstream& stream){
    for (int i =0; i <smallSize; i++)
    {
        for (int j =0; j <size; j++)
        {
            if ((searchList[i].ID == repo[j].ID) && (searchList[i].isolate == repo[j].isolate))
            {
                stream << repo[j].ID <<","<< repo[j].isolate <<","<< repo[j].box <<","<< repo[j].location <<endl;
                cout<< "running" <<endl;
                break;
            }    
        }
    }
    cout<< "end" <<endl;
    return 0;
}

int main() {
    ifstream fileIn,fileIn1;
    ofstream fileOut;
    //repository file
    fileIn.open("GEMS_1_Isolates.txt");

    //output file
    fileOut.open("GEMS_Locations.txt");

    //file success
    if (fileIn.fail())
    {
        cout << "File in Failure."<< endl;
        exit(1);
    }

    if (fileOut.fail())
    {
        cout << "File out Failure."<< endl;
        exit(1);
    }

    //initialize all values in repo and list array to 0
    for (int i = 0; i < SIZE; i++)
    {
        repository[i] = initial;
    }
    
    for (int j = 0; j < SEARCHLIST; j++)
    {
        list[j] = initial;
    }
    
    //take in values for repository array
    
    for (int i=0; i <SIZE; i++)
    {
        getInput(fileIn);
        repository[i]= current;
    }

    fileIn.close();

    //ETEC list we need locations for
    fileIn1.open("ETEC_LTST_List.txt");
    if (fileIn1.fail())
    {
        cout <<"File in 1 Failure" <<endl;
        exit (1);
    }
    
    //set current back to zero so nothing carries over
    current = initial;
    //fill search list
    for (int i =0; i <SEARCHLIST; i++)
    {
        getInputSearchList(fileIn1);
        list[i] = current;
    }
    
    fileIn.close();

    searchLocation(repository, list, SIZE, SEARCHLIST, fileOut);

    fileOut.close();
    
    return 0;
}