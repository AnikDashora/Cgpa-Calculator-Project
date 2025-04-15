#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

struct coureses
{
    string courseCode;
    string grade;
    int credit;
    bool softSkillCourse;

    int attendancePercent, attendanceWeightAge, attendanceMarks, attendanceFinalMarks;

    int numberOfCaConducted, caWeightAge, caConductedMark, caTotalMarks, caFinalMarks;
    double *caMarks;

    bool midTermExam;
    int midTermMark, midTermConductedMark, midTermFinalMark, midTermWeightAge;

    char endTermType;
    int *endTermMark;
    int *endTermConductedMark;
    int *endTermFinalMark;
    int *endTermWeightAge;
};

void calculateAttendance(coureses *args)
{
    if (args->softSkillCourse)
    {
        args->attendanceWeightAge = 15;
    }
    else
    {
        args->attendanceWeightAge = 5;
    }

    if (args->attendancePercent >= 90)
    {
        args->attendanceMarks = 5;
    }
    else if (args->attendancePercent >= 85 && args->attendancePercent < 90)
    {
        args->attendanceMarks = 4;
    }
    else if (args->attendancePercent >= 80 && args->attendancePercent < 85)
    {
        args->attendanceMarks = 3;
    }
    else if (args->attendancePercent >= 75 && args->attendancePercent < 80)
    {
        args->attendanceMarks = 2;
    }
    else
    {
        args->attendanceMarks = 0;
    }

    double percentage = args->attendanceMarks / 5.0;
    args->attendanceFinalMarks = int(percentage * args->attendanceWeightAge);
}

void calculateCa(coureses *args)
{
    sort(args->caMarks, (args->caMarks) + args->numberOfCaConducted);

    double sum = 0.0;
    for (int i = 1; i < args->numberOfCaConducted; i++)
    {
        sum += args->caMarks[i];
    }

    args->caTotalMarks = round((int)sum * 100) / (args->caConductedMark * (args->numberOfCaConducted - 1));
    args->caFinalMarks = round((args->caTotalMarks * args->caWeightAge) / 100);
}

void calculateMidTerm(coureses *args)
{
    if (!(args->midTermExam))
    {
        return;
    }
    double percentage = args->midTermMark / double(args->midTermConductedMark);
    args->midTermFinalMark = round(percentage * args->midTermWeightAge);
}

void calculateEndTerm(coureses *args)
{
    if (args->endTermType == 'M' || args->endTermType == 'm')
    {
        double percent[2];
        percent[0] = args->endTermMark[0] / double(args->endTermConductedMark[0]);
        percent[1] = args->endTermMark[1] / double(args->endTermConductedMark[1]);

        args->endTermFinalMark[0] = round(percent[0] * double(args->endTermWeightAge[0]));
        args->endTermFinalMark[1] = round(percent[1] * double(args->endTermWeightAge[1]));
    }
    else
    {
        double percent = args->endTermMark[0] / double(args->endTermConductedMark[0]);
        args->endTermFinalMark[0] = round(percent * double(args->endTermWeightAge[0]));
    }
}

void calculateGrade(coureses *args)
{
    int total = 0;
    total += args->attendanceFinalMarks;
    total += args->caFinalMarks;

    if (args->midTermExam)
    {
        total += args->midTermFinalMark;
    }

    if (args->endTermType == 'M' || args->endTermType == 'm')
    {
        total += args->endTermFinalMark[0];
        total += args->endTermFinalMark[1];
    }
    else
    {
        total += args->endTermFinalMark[0];
    }

    if (total >= 90 && total <= 100)
    {
        args->grade = "O";
    }
    else if (total >= 80 && total < 90)
    {
        args->grade = "A+";
    }
    else if (total >= 70 && total < 80)
    {
        args->grade = "A";
    }
    else if (total >= 60 && total < 70)
    {
        args->grade = "B+";
    }
    else if (total >= 50 && total < 60)
    {
        args->grade = "B";
    }
    else if (total >= 40 && total < 50)
    {
        args->grade = "C+";
    }
    else
    {
        args->grade = "E";
    }
}

int gradeIntoMark(coureses *args)
{
    if (args->grade == "O")
    {
        return 10;
    }
    else if (args->grade == "A+")
    {
        return 9;
    }
    else if (args->grade == "A")
    {
        return 8;
    }
    else if (args->grade == "B+")
    {
        return 7;
    }
    else if (args->grade == "B")
    {
        return 6;
    }
    else if (args->grade == "C+")
    {
        return 5;
    }
    else
    {
        return 0;
    }
}

double calculateCGPA(coureses *args, int size)
{
    int gradeSum = 0;
    int sumOfCredit = 0;
    int gradeMark;
    for (int i = 0; i < size; i++)
    {
        gradeMark = gradeIntoMark(&args[i]);
        gradeSum += (gradeMark * args[i].credit);
        sumOfCredit += args[i].credit;
    }
    return gradeSum / sumOfCredit;
}

int main()
{
    char sem;
    int totalCourses;
    double CGPA;
    cout << "Which Semester:- ";
    cin >> sem;
    string fileName = "Semester" + string(1, sem) + ".txt";

    cout << "How many courses are there in this semester:-";
    cin >> totalCourses;
    cin.ignore();

    coureses *newCourses = new coureses[totalCourses];
    for (int i = 0; i < totalCourses; i++)
    {
        // course name
        cout << "What the " << i + 1 << "th course in this sem:- ";
        getline(cin, newCourses[i].courseCode);

        // course credit
        cout << "What is the credit of this course:- ";
        cin >> newCourses[i].credit;
        cin.ignore();

        // course type
        char softSkillCheck;
        cout << "Is the course related to soft skill (Y/y for yes or N/n for no):-";
        cin >> softSkillCheck;
        if (softSkillCheck == 'Y' || softSkillCheck == 'y')
        {
            newCourses[i].softSkillCourse = true;
        }
        else
        {
            newCourses[i].softSkillCourse = false;
        }
        cin.ignore();

        // attendance for course

        cout << "What is your attendance for this course in percentage:- ";
        cin >> newCourses[i].attendancePercent;
        cin.ignore();

        // ca for this course
        cout << "How many CA does this course has:- ";
        cin >> newCourses[i].numberOfCaConducted;
        newCourses[i].caMarks = new double[newCourses[i].numberOfCaConducted];
        cout << "CA is conducted for how much marks:- ";
        cin >> newCourses[i].caConductedMark;
        for (int j = 0; j < newCourses[i].numberOfCaConducted; j++)
        {
            cout << "Enter the marks you scored in CA" << j + 1 << " ";
            cin >> newCourses[i].caMarks[j];
        }
        cout << "Weightage for CA of this course is:- ";
        cin >> newCourses[i].caWeightAge;
        cin.ignore();

        // Midterm for this course
        char midterm;
        cout << "Is the course contain midterm (Y/y for yes or N/n for no):-";
        cin >> midterm;
        if (midterm == 'Y' || midterm == 'y')
        {
            newCourses[i].midTermExam = true;
        }
        else
        {
            newCourses[i].midTermExam = false;
        }
        cin.ignore();
        if (newCourses[i].midTermExam)
        {
            cout << "Enter the the total marks for Midterm can be scored by someone:- ";
            cin >> newCourses[i].midTermConductedMark;
            cout << "Enter the marks you have scored in Midterm:- ";
            cin >> newCourses[i].midTermMark;
            cout << "Enter the weightage for midterm:- ";
            cin >> newCourses[i].midTermWeightAge;
            cin.ignore();
        }

        // EndTerm for this course
        cout << "Enter the type of Endterm (S/s) for Subjective, (M/m) for Mixed and (C/c) for MCQ:- ";
        cin >> newCourses[i].endTermType;
        if (newCourses[i].endTermType == 'M' || newCourses[i].endTermType == 'm')
        {
            // 0 for the MCQ and 1 for the Subjective
            newCourses[i].endTermMark = new int[2];
            newCourses[i].endTermConductedMark = new int[2];
            newCourses[i].endTermFinalMark = new int[2];
            newCourses[i].endTermWeightAge = new int[2];

            cout << "Enter the total marks someone can score in endterm MCQ:- ";
            cin >> newCourses[i].endTermConductedMark[0];
            cout << "Enter the marks you have scored in endterm MCQ:- ";
            cin >> newCourses[i].endTermMark[0];
            cout << "Enter the weightage for MCQ in endterm:- ";
            cin >> newCourses[i].endTermWeightAge[0];

            cout << "Enter the total marks someone can score in endterm Subjective:- ";
            cin >> newCourses[i].endTermConductedMark[1];
            cout << "Enter the marks you have scored in endterm Subjective:- ";
            cin >> newCourses[i].endTermMark[1];
            cout << "Enter the weightage for Subjective in endterm:- ";
            cin >> newCourses[i].endTermWeightAge[1];
        }
        else
        {
            newCourses[i].endTermMark = new int[1];
            newCourses[i].endTermConductedMark = new int[1];
            newCourses[i].endTermFinalMark = new int[1];
            newCourses[i].endTermWeightAge = new int[1];

            cout << "Enter the total marks someone can score in endterm MCQ:- ";
            cin >> newCourses[i].endTermConductedMark[0];
            cout << "Enter the marks you have scored in endterm MCQ:- ";
            cin >> newCourses[i].endTermMark[0];
            cout << "Enter the weightage for MCQ in endterm:- ";
            cin >> newCourses[i].endTermWeightAge[0];
        }

        cin.ignore();
        system("cls");
    }

    for (int i = 0; i < totalCourses; i++)
    {
        calculateAttendance(&newCourses[i]);
        calculateCa(&newCourses[i]);
        calculateMidTerm(&newCourses[i]);
        calculateEndTerm(&newCourses[i]);
        calculateGrade(&newCourses[i]);
    }

    CGPA = calculateCGPA(newCourses, totalCourses);

    ofstream fin(fileName);
    fin << "THIS IS SEMESTER " + string(1, sem) + "\n";
    fin << "---------------------------------------------------------------------\n\n";
    fin.close();

    for (int i = 0; i < totalCourses; i++)
    {
        fstream file(fileName, ios::in | ios::out | ios::ate);
        if (!(file.is_open()))
        {
            cout << "THERE IS A ERROR IN OPENING THE FILE " << fileName << endl;
            break;
        }
        // PUSH COURSE CODE
        file << newCourses[i].courseCode << " -> \n\n";

        // PUSH ATTTENDANCE
        file << "Attendance Marks(" << newCourses[i].attendancePercent << "%)     " << newCourses[i].attendanceMarks << "\\5(Scored)     " << newCourses[i].attendanceFinalMarks << "\\" << newCourses[i].attendanceWeightAge << "(Final)\n";

        // PUSH CA

        file << "Continuous Assessment     " << newCourses[i].caTotalMarks << "\\100(Scored)     " << newCourses[i].caFinalMarks << "\\" << newCourses[i].caWeightAge << "(Final)\n";

        // PUSH MIDTERM
        if (newCourses[i].midTermExam)
        {
            file << "MidTerm               " << newCourses[i].midTermMark << "\\" << newCourses[i].midTermConductedMark << "(Scored)    " << newCourses[i].midTermFinalMark << "\\" << newCourses[i].midTermWeightAge << "(Final)\n";
        }

        // PUSH ENDTERM
        if (newCourses[i].endTermType == 'M' || newCourses[i].endTermType == 'm')
        {
            file << "Theory Endterm        " << newCourses[i].endTermMark[1] << "\\" << newCourses[i].endTermConductedMark[1] << "(Scored)     " << newCourses[i].endTermFinalMark[1] << "\\" << newCourses[i].endTermWeightAge[1] << "(Final)\n";
            file << "Endterm               " << newCourses[i].endTermMark[0] << "\\" << newCourses[i].endTermConductedMark[0] << "(Scored)     " << newCourses[i].endTermFinalMark[0] << "\\" << newCourses[i].endTermWeightAge[0] << "(Final)\n";
        }
        else
        {
            file << "Endterm               " << newCourses[i].endTermMark[0] << "\\" << newCourses[i].endTermConductedMark[0] << "(Scored)     " << newCourses[i].endTermFinalMark[0] << "\\" << newCourses[i].endTermWeightAge[0] << "(Final)\n";
        }

        file << "----------------------------------------------------------------------------\n";
        file.close();
    }
    fstream newWrite(fileName, ios::in | ios::out | ios::ate);
    newWrite << "\nTotal CGPA = " << CGPA << "\n";
    newWrite << "THIS IS THE END OF THE SEMESTER " << sem << "\n";
    return 0;
}