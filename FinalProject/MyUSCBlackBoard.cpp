//
//  MyUSCBlackBoard.cpp
//  BlackBoardExtension
//
//  Created by Justin Bai on 12/9/20.
//

#include "MyUSCBlackBoard.hpp"
#include <stdio.h>
#include <iostream>

 
using namespace std;

MyUSCClass::MyUSCClass(string name)
{
    className = name;
    for (int i = 65; i <= 68; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            letterGradePercentage newGrade;
            newGrade.letterGrade = " ";
            newGrade.letterGrade[0] = i;
            if (j % 3 == 0)
                newGrade.letterGrade += "+";
            else if (j%3 == 2)
                newGrade.letterGrade += "-";
            newGrade.percentage = -1;
            gradeDistribution.push_back(newGrade);
        }
    }
    letterGradePercentage fail;
    fail.letterGrade = "F";
    fail.percentage = -1;
    gradeDistribution.push_back(fail);
}

//MyClass::~MyClass()
//{
//}

void MyUSCClass::addAssignmentType(string gradeName, double weight)
{
    assignmentType type;
    type.typeName = gradeName;
    type.typeWeight = weight;
    type.numPoints = 0;
    type.totalPoints = 0;
    type.typeGradePercentage = -1;
    classGrades.push_back(type);
}

int MyUSCClass::addAssignment(string gradeName, double pointsEarned, double pointsTotal)
{
    int index = -1;
    for (unsigned int i = 0; i < classGrades.size(); i++)
    {
        if (classGrades[i].typeName == gradeName)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
        return 0;
    classGrades[index].numPoints += pointsEarned;
    classGrades[index].totalPoints += pointsTotal;
    if (classGrades[index].totalPoints == 0)
        return 0;
    classGrades[index].typeGradePercentage = classGrades[index].numPoints / classGrades[index].totalPoints;
    return 1;
}

double MyUSCClass::calculateNumberGrade()
{
    double totalWeight = 0;
    double totalPercentage = 0;
    for (unsigned int i = 0; i < classGrades.size(); i++)
    {
        if (classGrades[i].typeGradePercentage==-1)
            continue;
        totalPercentage += (classGrades[i].typeGradePercentage * classGrades[i].typeWeight);
        totalWeight += classGrades[i].typeWeight;
    }
    totalWeight /= 100;
    
    return (totalPercentage / totalWeight);
}

int MyUSCClass::addLetterGradeCutOff(string letter, double cutoff)
{
    int index = -1;
    for (unsigned int i = 0; i < gradeDistribution.size(); i++)
    {
        if (gradeDistribution[i].letterGrade == letter)
        {
            index = i;
            break;
        }
    }
    
    if (index == -1)
        return 0;
    
    gradeDistribution[index].percentage = cutoff;
    
    return 1;
}

string MyUSCClass::calculateLetterGrade()
{
    double myGrade = calculateNumberGrade();
    
    for (unsigned int i = 0; i < gradeDistribution.size(); i++)
    {
        if (gradeDistribution[i].percentage == -1)
            continue;
        if (i == 0)
        {
            if (gradeDistribution[0].percentage < myGrade)
                return gradeDistribution[0].letterGrade;
        }
        else if (gradeDistribution[i].percentage < myGrade && gradeDistribution[i-1].percentage > myGrade)
            return gradeDistribution[i].letterGrade;
    }
    
    return "F";
}

double MyUSCClass::needOnFinal(string letterGrade, double weight)
{
    int index = -99999;
    for (unsigned int i = 0; i < gradeDistribution.size(); i++)
    {
        if (gradeDistribution[i].letterGrade == letterGrade)
        {
            if (gradeDistribution[i].percentage != -1)
            {
                index = i;
                break;
            }
        }
    }
    
    if (index == -99999)
        return -99999;
    
    double gradeIWant = gradeDistribution[index].percentage;
    
    double totalWeight = 0;
    double totalPercentage = 0;
    for (unsigned int i = 0; i < classGrades.size(); i++)
    {
        if (classGrades[i].typeGradePercentage==-1)
            continue;
        totalPercentage += (classGrades[i].typeGradePercentage * classGrades[i].typeWeight);
        totalWeight += classGrades[i].typeWeight;
    }
    
    if (totalWeight >= 100)
        return 0;
    totalWeight += weight;
    totalWeight /= 100;
    gradeIWant *= totalWeight;
    gradeIWant -= totalPercentage;
    gradeIWant /= weight;
    gradeIWant *= 100;
    return gradeIWant;
}


