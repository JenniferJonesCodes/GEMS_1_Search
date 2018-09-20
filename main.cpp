/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    string box;
    string location;
};

ifstream fileIn,fileIn1;
ofstream fileOut;

int getInput(ifstream& infile);
int printArray(bacteria a[], int size, ofstream& name);
int searchLocation (string strain, bacteria a[], int size, ofstream& stream);
bacteria inital = {"0", "0", "0", "0"};
bacteria current;
const int SIZE = 30000;
string etec, check;
bacteria repository[SIZE];
bacteria list[200];


int main() {
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

    //initialize all values in repository to 0
    for (int i = 0; i < SIZE; i++){
        repository[i] = inital;
        list[i] = inital;
    }

    //take in values for repository array
    int i=0;
    int count = 0;
    do{
        getInput(fileIn);
        repository[i]= current;
        i++;
       count++;
    } while (!fileIn.eof());

    fileIn.close();

    //ETEC list
    fileIn1.open("ETEC_List.txt");
    if (fileIn1.fail()){
        cout <<"File in 1 Failure" <<endl;
        exit (1);
    }
    
    //fill search repo
  
    do{
        getInput(fileIn);
        list[i]= current;
    } while (!fileIn.eof());

    //search for location and output file
    do {
        fileIn1 >> etec;
        searchLocation(repository, list, SIZE, fileOut);
    } while (!fileIn1.eof());

    //printArray(repository, SIZE, fileOut);

    fileIn1.close();
    fileOut.close();
    
    return 0;
}

int getInput(ifstream& infile){
    infile >> current.ID >> current.isolate>> current.note >> current.box >> current.location;
    return 0;
}

int printArray(bacteria a[], int size, ofstream& name){
    for (int i=0; i < size; i++)
        name << a[i].ID <<" " <<a[i].isolate <<" "<<a[i].note <<","<< a[i].box<<" "<< a[i].location <<endl;
    return 0;
}

int searchLocation(bacteria a[], bacteria b[], int size, ofstream& stream){
    for (int i=0; i < size; i++){
        string sID = a[i].ID;
        string sIsolate = a[i].ID;
        if (b[i].ID == sID && b[i].isolate == sIsolate);
            stream << a[i].ID <<","<< a[i].isolate <<","<< a[i].note <<","<< a[i].box <<","<< a[i].location <<endl;
    }
    return 0;
}