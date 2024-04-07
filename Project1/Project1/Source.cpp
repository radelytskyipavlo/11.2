#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>
using namespace std;

enum Specialnist { KN, ME, IN, FI, TN };
string specialnistList[] = { "KN", "ME", "IN", "FI", "TN" };
struct Student
{
    string surname;
    int course;
    Specialnist spec;
    int fiz;
    int mat;
    union
    {
        int prog;
        int chis_metod;
        int pedagog;
    };
};

void Create(Student* p, const int N, ofstream& file); 
void Print(Student* p, const int N);
int CountProgrammingGrades(Student* p, const int N, int grade);
double percentagePhysicsMath(Student* p, const int N);

int main()
{
    int N;
    cout << "Type the number of students: "; cin >> N;
    Student* p = new Student[N];


    ofstream file("students.bin", ios::binary); 

    Create(p, N, file); 
    Print(p, N);
    cout << "The percentage of students who have 4 or 5 in both physics and math: " << percentagePhysicsMath(p, N) << "%" << endl;
    cout << "Number of students with grade 5 in programming: " << CountProgrammingGrades(p, N, 5) << endl;
    cout << "Number of students with grade 4 in programming: " << CountProgrammingGrades(p, N, 4) << endl;
    cout << "Number of students with grade 3 in programming: " << CountProgrammingGrades(p, N, 3) << endl;

    delete[] p;

    file.close();
    return 0;
}

void Create(Student* p, const int N, ofstream& file)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Student # " << i + 1 << ":" << endl;
        file.write(reinterpret_cast<char*>(&i), sizeof(int)); 

        cin.get();
        cin.sync();
        cout << "Surname: "; getline(cin, p[i].surname);
        file.write(p[i].surname.c_str(), p[i].surname.size() + 1); 
        cout << "Course: "; cin >> p[i].course;
        file.write(reinterpret_cast<char*>(&p[i].course), sizeof(int)); 

        cout << "Grades in physics: "; cin >> p[i].fiz;
        file.write(reinterpret_cast<char*>(&p[i].fiz), sizeof(int)); 
        cout << "Grades in math: "; cin >> p[i].mat;
        file.write(reinterpret_cast<char*>(&p[i].mat), sizeof(int)); 
        cout << "A specialty (0 - KN, 1 - ME, 2 - IN, 3 - FI, 4 - TN): ";  cin >> spec;
        if (spec > 4) {
            cout << "Wrong value, selected 2 (IN)" << endl;
            spec = 2;
        }
        p[i].spec = (Specialnist)spec;
        file.write(reinterpret_cast<char*>(&p[i].spec), sizeof(int)); 

        switch (p[i].spec)
        {
        case KN:
            cout << "Grades in programming: "; cin >> p[i].prog;
            file.write(reinterpret_cast<char*>(&p[i].prog), sizeof(int)); 
            break;
        case ME:
            cout << "Grades in pedagogy: "; cin >> p[i].pedagog;
            file.write(reinterpret_cast<char*>(&p[i].pedagog), sizeof(int)); 
            break;
        case IN:
            cout << "Grades in num.methods: "; cin >> p[i].chis_metod;
            file.write(reinterpret_cast<char*>(&p[i].chis_metod), sizeof(int)); 
            break;
        case FI:
            cout << "Grades in pedagogy: "; cin >> p[i].pedagog;
            file.write(reinterpret_cast<char*>(&p[i].pedagog), sizeof(int)); 
            break;
        case TN:
            cout << "Grades in pedagogy: "; cin >> p[i].pedagog;
            file.write(reinterpret_cast<char*>(&p[i].pedagog), sizeof(int)); 
            break;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "==========================================================================================================="
        << endl;
    cout << "| # | Surname | Course | Specilization | Physic | Mathematic | Programming | Numerical Methods | Pedagogy |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(8) << left << p[i].surname
            << "| " << setw(4) << right << p[i].course << "  "
            << " | " << setw(14) << left << specialnistList[p[i].spec]
            << setw(4) << "| " << setw(3) << left << p[i].fiz << "  "
            << setw(6) << "| " << setw(6) << left << p[i].mat << " ";
        switch (p[i].spec)
        {
        case KN:
            cout << setw(8) << "| " << setw(5) << left << p[i].prog << setw(21)
                << " | " << setw(10) << left
                << "| " << left << " |" << endl;
            break;
        case ME:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| "
                << setw(6) << "| " << setw(4) << left << p[i].pedagog << " |" << endl;
            break;
        case IN:
            cout << "" << setw(13) << "| " << setw(10) << " |" << " "
                << setw(9) << p[i].chis_metod << " |" << " "
                << setw(8) << "" << " |" << endl;
            break;
        case FI:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| "
                << setw(6) << "| " << setw(4) << left << p[i].pedagog << " |" << endl;
            break;
        case TN:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| "
                << setw(6) << "| " << setw(4) << left << p[i].pedagog << " |" << endl;
            break;
        }
    }
    cout << "==========================================================================================================="
        << endl;
    cout << endl;
}

int CountProgrammingGrades(Student* p, const int N, int grade)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].spec == KN && p[i].prog == grade)
            count++;
    }
    return count;
}

double percentagePhysicsMath(Student* p, const int N)
{
    double count = 0;
    for (int i = 0; i < N; i++)
    {
        if ((p[i].fiz == 4 || p[i].fiz == 5) && (p[i].mat == 4 || p[i].mat == 5))
            count++;
    }
    return (count / N) * 100;
}
