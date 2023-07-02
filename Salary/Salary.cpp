// Salary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <list>
using namespace std;

class Date {
public:
    int day;
    int month;
    int year;


    Date(int day, int month, int year)
        : day(day), month(month), year(year)
    {
    }
};

class Employee {
protected:
    const int tax = 10;
    const int insuranse = 7;
    string firstName;
    string lastName;
    int personalNumber;
    int accountingNumber;
    int salaryPerHour;
    int workOfTheCurrentMonth;
    Date birthDate;
    Date startWork;
    Date startContract;
    Date finishContract;





public:
    // Construct
    Employee(const string& firstName, const string& lastName,
        int personalNumber, int accountingNumber, int salaryPerHour,int workOfTheCurrentMonth, const Date& birthDate,
        const Date& startWork, const Date& startContract, const Date& finishContract)
        : firstName(firstName), lastName(lastName), personalNumber(personalNumber),
        accountingNumber(accountingNumber), salaryPerHour(salaryPerHour),workOfTheCurrentMonth(workOfTheCurrentMonth),
        birthDate(birthDate), startWork(startWork),
        startContract(startContract), finishContract(finishContract)
    {

    }

    virtual int  netSalaryOfTheCurrentMonth() = 0;
    virtual int grossSalaryOfTheCurrentMonth() = 0;
    virtual int grossSalaryOfTheCurrentMonth(int workOfTheCurrentMonth) = 0;


    // Getter methods
    string getFirstName() const {
        return firstName;
    }

    string getLastName() const {
        return lastName;
    }

    int getPersonalNumber() const {
        return personalNumber;
    }

    int getAccountingNumber() const {
        return accountingNumber;
    }

    int getSalaryPerHour() const {
        return salaryPerHour;
    }

    int getWorkOfTheCurrentMonth() const {
        return workOfTheCurrentMonth;
    }


    Date getBirthDate() const {
        return birthDate;
    }

    Date getStartWork() const {
        return startWork;
    }

    // Setter methods
    void setFirstName(const string& firstName) {
        this->firstName = firstName;
    }

    void setLastName(const string& lastName) {
        this->lastName = lastName;
    }

    void setPersonalNumber(int personalNumber) {
        this->personalNumber = personalNumber;
    }

    void setAccountingNumber(int accountingNumber) {
        this->accountingNumber = accountingNumber;
    }

    void setSalaryPerHour(int salaryPerHour) {
        this->salaryPerHour = salaryPerHour;
    }

    void setWorkOfTheCurrentMonth(int workOfTheCurrentMonth) {
        this->workOfTheCurrentMonth = workOfTheCurrentMonth;
    }


    void setBirthDate(const Date& birthDate) {
        this->birthDate = birthDate;
    }

    void setStartWork(const Date& startWork) {
        this->startWork = startWork;
    }


};

class EmployeeSemiTime :public Employee {
public:
    EmployeeSemiTime(const string& firstName, const string& lastName,
        int personalNumber, int accountingNumber, int salaryPerHour,   int workOfTheCurrentMonth, const Date& birthDate,
        const Date& startWork, const Date& startContract, const Date& finishContract)
        :Employee(firstName, lastName, personalNumber, accountingNumber, salaryPerHour,workOfTheCurrentMonth, birthDate, startWork, startContract, finishContract) {
    }

    int netSalaryOfTheCurrentMonth() {

        return grossSalaryOfTheCurrentMonth() - (tax * grossSalaryOfTheCurrentMonth()/100) - (insuranse * grossSalaryOfTheCurrentMonth() / 100);

    };

    int grossSalaryOfTheCurrentMonth() {
        return salaryPerHour*workOfTheCurrentMonth;
    };

    int grossSalaryOfTheCurrentMonth(int workOfTheCurrentMonth) {
        this->workOfTheCurrentMonth = workOfTheCurrentMonth;
        return grossSalaryOfTheCurrentMonth();
    };

    

    string toString() {
        return Employee::getFirstName();
    };


};

class EmployeeTotalTime :public Employee {
private:

    int monthlySalary;
    int resetTime;
    int overtime;

public:

    EmployeeTotalTime(const string& firstName, const string& lastName,
        int personalNumber, int accountingNumber, int monthlySalary, int resetTime,int overtime, const Date& birthDate,
        const Date& startWork, const Date& startContract, const Date& finishContract)
        :Employee(firstName, lastName, personalNumber, accountingNumber, convertMonthlySalarytoHoursPerSalary(monthlySalary), 176, birthDate, startWork, startContract, finishContract), 
       monthlySalary(monthlySalary), resetTime(resetTime),overtime(overtime) {
    }

    int convertMonthlySalarytoHoursPerSalary(int monthlySalary) {
        return monthlySalary / 176;
    }

    int netSalaryOfTheCurrentMonth() {
        int monyResetTime = 0;
        if (resetTime > 20) {
            monyResetTime = (resetTime - 20) * salaryPerHour * 1.2;
        }
        return grossSalaryOfTheCurrentMonth() - monyResetTime - (tax * grossSalaryOfTheCurrentMonth() / 100) - (insuranse * grossSalaryOfTheCurrentMonth() / 100);

    };

    int grossSalaryOfTheCurrentMonth() {
        int monyOvertime = overtime * 1.2 * salaryPerHour;

        return salaryPerHour*workOfTheCurrentMonth + monyOvertime;
    };
    int grossSalaryOfTheCurrentMonth(int workOfTheCurrentMonth) {
        this->workOfTheCurrentMonth = workOfTheCurrentMonth;
        return grossSalaryOfTheCurrentMonth();
    };



};

class EmployeeAgreement : public Employee {
private:
    int monthlySalary;
    int overtime;
    int score;
    int resetTime;

public:
    EmployeeAgreement(const string& firstName, const string& lastName,
        int personalNumber, int accountingNumber, int monthlySalary, int resetTime, int overtime, int score, const Date& birthDate,
        const Date& startWork, const Date& startContract, const Date& finishContract)
        :Employee(firstName, lastName, personalNumber, accountingNumber, convertMonthlySalarytoHoursPerSalary(monthlySalary), 176, birthDate, startWork, startContract, finishContract), score(score), resetTime(resetTime) {
    }


    int convertMonthlySalarytoHoursPerSalary(int monthlySalary) {
        return monthlySalary / 176;
    }

    int netSalaryOfTheCurrentMonth() {
        int monyResetTime = 0;
        if (resetTime > 25) {
            monyResetTime = (resetTime - 25) * salaryPerHour * 1.2;
        }
        return grossSalaryOfTheCurrentMonth() - monyResetTime - (tax * grossSalaryOfTheCurrentMonth() / 100) - (insuranse * grossSalaryOfTheCurrentMonth() / 100);

    };

    int grossSalaryOfTheCurrentMonth() {
        int monyOvertime = overtime * 1.2 * salaryPerHour;
      

        int temp = salaryPerHour * workOfTheCurrentMonth + monyOvertime;

        return temp + (temp*10/100);

    };

    int grossSalaryOfTheCurrentMonth(int workOfTheCurrentMonth) {
        this->workOfTheCurrentMonth = workOfTheCurrentMonth;
        return grossSalaryOfTheCurrentMonth();
    };

};

int main()
{
    Date d = Date(34, 5, 6);
    vector<Employee*> employees;

    employees.push_back(
        new EmployeeSemiTime("mohammad", "Reza", 33, 65, 22, 44, d, d, d, d));

    employees.push_back(
        new EmployeeTotalTime("mohammad", "Reza", 33, 22, 45000, 77, 44, d, d, d, d));

    employees.push_back(
        new EmployeeAgreement("mohammad", "Reza", 33, 22, 45000, 77,34, 44, d, d, d, d));




    std::cout << employees[0]->netSalaryOfTheCurrentMonth()<< endl;
    std::cout << employees[1]->netSalaryOfTheCurrentMonth() << endl;
    std::cout << employees[2]->netSalaryOfTheCurrentMonth() << endl;

    

}




        

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


