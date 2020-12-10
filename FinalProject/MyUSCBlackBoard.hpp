//
//  MyUSCBlackBoard.hpp
//  BlackBoardExtension
//
//  Created by Justin Bai on 12/9/20.
//

#ifndef MyUSCBlackBoard_hpp
#define MyUSCBlackBoard_hpp

#include <stdio.h>

#endif /* MyUSCBlackBoard_hpp */

#include <string>
#include <vector>

using namespace std;

struct assignmentType
{
    string typeName;
    double typeWeight;
    double numPoints;
    double totalPoints;
    double typeGradePercentage;
};

struct letterGradePercentage
{
    string letterGrade;
    double percentage;
};

class MyUSCClass
{
public:
    MyUSCClass(string name);
    string calculateLetterGrade();
    double needOnFinal(string letterGrade, double weight);
    void addAssignmentType(string gradeName, double weight);  //take weight as whole number
    int addAssignment(string gradeName, double pointsEarned, double pointsTotal);
    double calculateNumberGrade(); //return 0 if gradeType doesn't exist
    int addLetterGradeCutOff(string letter, double cutoff); //return 0 if letter not found
    //void removeAssignmentType(string gradeName);
private:
    string className;
    vector<assignmentType> classGrades;
    vector<letterGradePercentage> gradeDistribution;
};
