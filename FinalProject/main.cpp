//
//  main.cpp
//  BlackBoardExtension
//
//  Created by Justin Bai on 12/9/20.
//
#include "MyUSCBlackBoard.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, const char * argv[])
{
    ifstream ifile ("./input.txt");
    
    if (ifile.fail())
    {
        cout << "Failed to open file" << endl;
        return 1;
    }
    
    string name;
    ifile >> name;
    ifile >> name;
    
    MyUSCClass myClass(name);
    
    string myLetterGrade;
    double letterCutOff;
    
    ifile >> myLetterGrade;
    ifile >> myLetterGrade;
    
    while (myLetterGrade != "CATAGORIES:")
    {
        ifile >> letterCutOff;
        myClass.addLetterGradeCutOff(myLetterGrade, letterCutOff);
        ifile >> myLetterGrade;
    }
    
    string type;
    double weight;
    ifile >> type;
    while (type != "ASSIGNMENTS:")
    {
        ifile >> weight;
        myClass.addAssignmentType(type, weight);
        ifile >> type;
    }
    
    double myPoints;
    double allPoints;
    ifile >> type;
    
    while (type != "end")
    {
        ifile >> myPoints >> allPoints;
        myClass.addAssignment(type, myPoints, allPoints);
        ifile >> type;
    }
    
    double myGrade = myClass.calculateNumberGrade();
    //cout << myGrade << endl;
    string myFinalLetterGrade = myClass.calculateLetterGrade();
    //cout << myFinalLetterGrade << endl;
    double gradeIWant = myClass.needOnFinal("A+", 30);
    //cout << gradeIWant << endl;
    
    ofstream ofile("./output.txt");
    if (ofile.fail())
    {
        cout << "Couldn't open output file" << endl;
        return 0;
    }
    
    ofile << myFinalLetterGrade << endl;
    ofile << myGrade << endl;
    ofile << gradeIWant << endl;
    
    return 0;
}
