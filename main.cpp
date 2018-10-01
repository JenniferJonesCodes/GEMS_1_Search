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
    string box;
    string location;
};

ifstream fileIn,fileIn1;
ofstream fileOut;

int getInput(ifstream& infile);
int printArray(bacteria a[], int size, ofstream& name);
int searchLocation (bacteria a[], bacteria b[], int size,  int smallSize, ofstream& stream);
bacteria getInputSearchList(ifstream& fileIn);
bacteria current;
const int SIZE = 30000;
const int SEARCHLIST = 150;
string etec, check;
bacteria repository[SIZE];
bacteria list[SEARCHLIST];


int main() {
    bacteria initial = {"0", "0", "0", "0"};
    //repository file
    fileIn.open("GEMS_1_Isolates.txt");

    //output file
    fileOut.open("GEMS_Locations.csv");

    //file success
    if (fileIn.fail()){
        cout << "File in Failure."<< endl;
        exit(1);
    }

    if (fileOut.fail()){
        cout << "File out Failure."<< endl;
        exit(1);
    }

    //initialize all values in repo and list array to 0
    for (int i = 0; i < SIZE; i++){
        repository[i] = initial;
    }
    for (int j = 0; j < SEARCHLIST; j++){
        list[j] = initial;
    }
    
    //take in values for repository array
    int i=0;
    do{
        getInput(fileIn);
        repository[i]= current;
        i++;
    } while (!fileIn.eof());
    fileIn.close();

    //ETEC list we need locations for
    fileIn1.open("ETEC_ST_List.txt");
    if (fileIn1.fail()){
        cout <<"File in 1 Failure" <<endl;
        exit (1);
    }
    
    //set current back to zero so nothing carries over
    current = initial;
    //fill search list
    int t=0;
    do{
        getInputSearchList(fileIn1);
        list[t] = current;
        t++;
    } while (!fileIn.eof());
    
    fileIn.close();

    //searchLocation(repository, list, SIZE, SEARCHLIST, fileOut);
 
    //printArray(list, SIZE, fileOut);

    fileOut.close();
    
    return 0;
}

int getInput(ifstream& infile){
    infile >> current.ID >> current.isolate>> current.box >> current.location;
    return 0;
}

bacteria getInputSearchList(ifstream& fileIn){
    fileIn >> current.ID >> current.isolate;
    cout << current.isolate << endl;
    current.box =" "; 
    current.location= " ";
    return current;
}

int printArray(bacteria a[], int size, ofstream& name){
    for (int i=0; i < size; i++)
        name << a[i].ID <<" " <<a[i].isolate  <<","<< a[i].box<<" "<< a[i].location <<endl;
    return 0;
}

int searchLocation(bacteria repo[], bacteria searchList[], int size, int smallSize, ofstream& stream){
    for (int i=0; i < smallSize; i++){
        for (int j=0; j< size; j++){
            if ((searchList[i].ID == repo[j].ID) && (searchList[i].isolate == repo[j].isolate)){
                stream << repo[j].ID <<","<< repo[j].isolate <<","<< repo[j].box <<","<< repo[j].location <<endl;
            }    
        }
    }
    return 0;
}