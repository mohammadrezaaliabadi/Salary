// Salary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

    virtual int netSalaryOfTheCurrentMonth() = 0;
    virtual int grossSalaryOfTheCurrentMonth() = 0;
    virtual int grossSalaryOfTheCurrentMonth(int workOfTheCurrentMonth) = 0;
    virtual int getLessWorkMony() = 0;

    int getTaxMony() {
        return (tax * grossSalaryOfTheCurrentMonth()/100);
    }

    int getInsuranceMony() {
        return (insuranse * grossSalaryOfTheCurrentMonth()/100);
    }

  


    friend ostream& operator<<(std::ostream& strm,Employee& e) {
        return strm << "Employee:" <<endl
            <<"First Name:"<<e.firstName << endl
            <<"Last Name:"<<e.lastName << endl
            <<"Personal Number:"<<e.personalNumber << endl
            <<"Account Number:"<<e.accountingNumber << endl
            <<"Salary Per Hours:"<<e.salaryPerHour << endl
            <<"Work of the current month:"<<e.workOfTheCurrentMonth << endl
            <<"Gross Salary Of The Current Month:"<<e.grossSalaryOfTheCurrentMonth() << endl
            <<"Tax:"<<e.getTaxMony() << endl
            <<"Insurance:"<<e.getInsuranceMony() << endl
            <<"Less Work:"<<e.getLessWorkMony() << endl
            <<"Net Salary Of The Current Month:"<<e.netSalaryOfTheCurrentMonth() << endl
            ;
    }





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

    int getLessWorkMony() {
        return 0;
    }

    

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


    int getLessWorkMony() {
        int monyResetTime = 0;
        if (resetTime > 20) {
            monyResetTime = (resetTime - 20) * salaryPerHour * 1.2;
        }
        return monyResetTime;
    }

    int netSalaryOfTheCurrentMonth() {
        return grossSalaryOfTheCurrentMonth() - getLessWorkMony() - (tax * grossSalaryOfTheCurrentMonth() / 100) - (insuranse * grossSalaryOfTheCurrentMonth() / 100);

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
        :Employee(firstName, lastName, personalNumber, accountingNumber, convertMonthlySalarytoHoursPerSalary(monthlySalary), 176, birthDate, startWork, startContract, finishContract), score(score), resetTime(resetTime) ,overtime(overtime){
    }


    int convertMonthlySalarytoHoursPerSalary(int monthlySalary) {
        return monthlySalary / 176;
    }

    int getLessWorkMony() {
        int monyResetTime = 0;
        if (resetTime > 25) {
            monyResetTime = (resetTime - 25) * salaryPerHour * 1.2;
        }
        return monyResetTime;
    }

    int netSalaryOfTheCurrentMonth() {

        return grossSalaryOfTheCurrentMonth() - getLessWorkMony() - (tax * grossSalaryOfTheCurrentMonth() / 100) - (insuranse * grossSalaryOfTheCurrentMonth() / 100);

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

class Company {
private:
    const int totalInsurance = 30;
    string name;
    int numEmployee;
    vector<Employee*> employees;

public:


    Company(const string& name, int numEmployee)
        : name(name), numEmployee(numEmployee)
    {
    }

    void addEmployee(Employee *employee) {
        employees.push_back(employee);
    }

    vector<Employee*> getEmployees() {
        return employees;
    }

    Employee* getEmployeeByPersonalNumber(int personalNumber){
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i]->getPersonalNumber() == personalNumber) {
                return employees[i];
            }

        }
        return NULL;
    }

    int totalTaxMonyPeyment() {
        int t = 0;
        for (auto &e : employees) {
            t = e->getTaxMony() + t;
        }

        return t;

    }

    int totalInsuranecMonyPeyment() {
        int t = 0;
        for (auto& e : employees) {
            t = (e->grossSalaryOfTheCurrentMonth()* totalInsurance /100) + t;
        }

        return t;

    }

    int totalEmployeeSalaryPeyment() {
        int t = 0;
        for (auto& e : employees) {
            t = e->netSalaryOfTheCurrentMonth() + t;
        }

        return t;

    }

    void writeToCsv() {
        ofstream file(name+".csv");
        file << "FirstName"<< ",";
        file << "LastName" << ",";
        file << "PersonalNumber" << ",";
        file << "AccountingNumber" << ",";
        file << "SalaryPerHour" << ",";
        file << "WorkOfTheCurrentMonth" << ",";
        file << "grossSalaryOfTheCurrentMonth" << ",";
        file << "TaxMony" << ",";
        file << "InsuranceMony" << ",";
        file << "LessWorkMony" << ",";
        file << "NetSalaryOfTheCurrentMonth" << "," << endl;

        for (auto& e : employees) {
            file << e->getFirstName() << ",";
            file << e->getLastName() << ",";
            file << e->getPersonalNumber() << ",";
            file << e->getAccountingNumber() << ",";
            file << e->getSalaryPerHour() << ",";
            file << e->getWorkOfTheCurrentMonth() << ",";
            file << e->grossSalaryOfTheCurrentMonth() << ",";
            file << e->getTaxMony() << ",";
            file << e->getInsuranceMony() << ",";
            file << e->getLessWorkMony() << ",";
            file << e->netSalaryOfTheCurrentMonth() << ","<<endl;
        }

        file.close();
    }




};

Date* createDate(string title) {
    int day;
    int month;
    int year;
    cout << title << endl;
    cout << "Day:";
    cin >> day;
    cout << "Month:";
    cin >> month;
    cout << "Year:";
    cin >> year;

    return new Date(day, month, year);

}
Employee * createEmployee() {

    string firstName;
    string lastName;
    int personalNumber;
    int accountingNumber;
    cout << "Create Employee." << endl;
    cout << "First name:";
    cin >> firstName;
    cout << "Last name:";
    cin >> lastName;
    cout << "Personal Number:";
    cin >> personalNumber;
    cout << "Accounting Number:";
    cin >> accountingNumber;



    int choice;

        cout << "Choice type of employee?  1.Total Time employee   2.Agreement employee  etc.Semi time employee" << endl << "Choice:";
        cin >> choice;
        if (choice == 1) {
            int monthlySalary;
            int overtime;
            int score;
            int resetTime;
            cout << "Monthly Salary:";
            cin >> monthlySalary;
            cout << "Overtime:";
            cin >> overtime;

            cout << "Reset Time:";
            cin >> resetTime;

            return new EmployeeTotalTime(firstName, lastName, personalNumber, accountingNumber, monthlySalary, resetTime, overtime, *createDate("Birth day:"), *createDate("Start work:"), *createDate("Start Contract:"), *createDate("Finish Contract:"));


        }
        else if (choice == 2) {
            int monthlySalary;
            int overtime;
            int score;
            int resetTime;
            cout << "Monthly Salary:";
            cin >> monthlySalary;
            cout << "Overtime:";
            cin >> overtime;
            cout << "Score:";
            cin >> score;
            cout << "Reset Time:";
            cin >> resetTime;

            return new EmployeeAgreement(firstName, lastName, personalNumber, accountingNumber, monthlySalary, resetTime, overtime,score, *createDate("Birth day:"), *createDate("Start work:"), *createDate("Start Contract:"), *createDate("Finish Contract:"));


        }
        else {

            int salaryPerHour;
            int workOfTheCurrentMonth;
            cout << "Salary Per Hour:";
            cin >> salaryPerHour;
            cout << "Work Of The Current Month:";
            cin >> workOfTheCurrentMonth;
            return new EmployeeSemiTime(firstName, lastName, personalNumber, accountingNumber, salaryPerHour, workOfTheCurrentMonth, *createDate("Birth day:"), *createDate("Start work:"), *createDate("Start Contract:"), *createDate("Finish Contract:"));

        }



}
int main()
{
    Date d = Date(34, 5, 6);
    vector<Employee*> employees;

    string companyName;

    int employeeCount;
    cout << "Company name:";

    cin >> companyName;

    cout << "Employee count:";

    cin >> employeeCount;




   

    Company* company = new Company(companyName, employeeCount);
    EmployeeAgreement *e = new EmployeeAgreement("mohammad", "Reza", 33, 22, 45000, 77, 5, 44, d, d, d, d);
    EmployeeAgreement *e2 = new EmployeeAgreement("mohammad", "Reza", 33, 22, 45000, 77, 5, 44, d, d, d, d);
    company->addEmployee(e);
    company->addEmployee(e2);

     while (true) {
        int select;
        cout << "1.Add employee.   2.Get Employee by personal number    3.Total Peyment company     4.Save to Csv   etc:Exit   Select?:";
        cin >> select;
        switch (select)
        {
        case 1: {
            company->addEmployee(createEmployee());

            break;
        }
        case 2: {
            int personalNumber;

            cout << "Personal number:";
            cin >> personalNumber;
            Employee* e = company ->getEmployeeByPersonalNumber(personalNumber);

            int choice;
            cout << "1. Gross salary by Work Of The Current Month. 2.Nat salary  etc:Pay slip Choice?";
            cin >> choice;
            if (choice == 1) {
                int workOfTheCurrentMonth;
                cout << "Work Of The Current Month:";
                cin >> workOfTheCurrentMonth;
                cout<<"Mony gross salary:" << e->grossSalaryOfTheCurrentMonth(workOfTheCurrentMonth)<<endl;
            }
            else if (choice == 2) {
                cout << "Mony nat salary:" << e->netSalaryOfTheCurrentMonth() << endl;

            }
            else {
                cout << *e;
            }
            break;
        }
        case 3: {

            cout << "Total Tax peyment:" << company->totalTaxMonyPeyment() << endl;
            cout << "Total Insurance peyment:" << company->totalInsuranecMonyPeyment() << endl;
            cout << "Total Employee peyment:" << company->totalEmployeeSalaryPeyment() << endl;

            break;
        }
        case 4: {
            company->writeToCsv();
            break;
        }

        default:
            return 0;
            break;
        };
    }




    




    

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


