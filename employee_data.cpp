#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

const float tax = 20;   //tax rate
const int bonus = 10;   //bonus rate for parttime employees

//printing the total summary of parttime and fulltime employees
class summaryReport{
  public:
    float final_gross;
    float final_deduct;
    float final_netPay;
    float final_dedYTD;
    float final_netYTD;

    //prints out total summary
    friend void operator << (ostream &output, summaryReport &x){
      output << setw(21) << "Total Summary";
      output << setw(47) << x.final_gross;
      output << setw(14) << x.final_deduct;
      output << setw(12) << x.final_netPay;
      output << setw(10) << x.final_dedYTD;
      output << setw(11) << x.final_netYTD;
    }
};

//store data on every employee
class EmployeeData{
  //only accessible within base and derived class(es)
  protected:
    float gross;
    float deductions;
    float netPay;
    float netYTD;
    float DedYTD;
  
  //accessible anywhere
  public:
    int idNum;
    char fName[15];
    char lName[15];
    char contract;

    //constructor
    EmployeeData(){}

    /*
    find employee gross pay

    'virtual' allows the derived classes to call
    their own forms of the CalculateGross function
    */
    virtual void CalculateGross(){}
};

//data for fulltime employees
class FullTime : public EmployeeData, public summaryReport
/*
EmployeeData public members are public in FullTime
EmployeeData protected members are protected in FullTime
*/
{
  protected:
    float earnings;

  public:

    //default constructor
    FullTime(int ivar=0, string fvar=" ", string lvar=" ", char cvar=' ', float dyvar=0, float nyvar=0)
    {
        idNum = ivar;
        strcpy(fName, fvar.c_str());
        strcpy(lName, lvar.c_str());
        contract = cvar;
        earnings = 0;
        gross = 0;
        deductions = 0;
        netPay = 0;
        DedYTD = dyvar;
        netYTD = nyvar;
    }

    //FullTime operator '>>' allows user to enter employees' earnings
    friend void operator >> (istream &input, FullTime &employed){
      cout << "Enter "<< employed.fName << "'s earnings: ";
      input >> employed.earnings;
      cout << endl;
    }

    //FullTime operator '-=' allows tax to be deducted from gross pay and added to net pay
    friend void operator -= (FullTime &employed, float const &deducted){
      employed.deductions = employed.gross * (deducted*0.01);
      employed.netPay = employed.gross - employed.deductions;
    }

    //FullTime prefix operator '++' adds net pay onto netYTD
    friend void operator ++ (FullTime &employed){
      employed.netYTD += employed.netPay;
    }

    //FullTime postfix operator '++' adds deductions onto DedYTD
    friend void operator ++ (FullTime &employed, int){
      employed.DedYTD = employed.gross + employed.deductions;
    }

    //FullTime operator '+' summarizes data for fulltime employees
    friend FullTime operator + (FullTime employee_a, FullTime employee_b){
      FullTime total;
      total.gross = employee_a.gross + employee_b.gross;
      total.deductions = employee_a.deductions + employee_b.deductions;
      total.netPay = employee_a.netPay + employee_b.netPay;
      total.DedYTD = employee_a.DedYTD + employee_b.DedYTD;
      total.netYTD = employee_a.netYTD + employee_b.netYTD;
      total.idNum = 0;
      return total;
    }

    //FullTime operator '<<' prints out employee data
    friend ostream& operator << (ostream &output, FullTime &employed){
      if(employed.idNum > 0){
        output << employed.idNum;
        output << setw(6) << employed.contract;
        output << setw(17) << employed.fName;
        output << setw(11) << employed.lName;
        output << setw(31) << employed.gross;
        output << setw(14) << employed.deductions;
        output << setw(12) << employed.netPay;
        output << setw(10) << employed.DedYTD;
        output << setw(11) << employed.netYTD;
      } else {
        output << setw(27) << "Full-Time Sub-Total";
        output << setw(41) << employed.gross;
        output << setw(14) << employed.deductions;
        output << setw(12) << employed.netPay;
        output << setw(10) << employed.DedYTD;
        output << setw(11) << employed.netYTD;
      }
      return output;
    }

    //FullTime operator '+=' adds data from the fulltime sub-total to the final report
    friend void operator += (summaryReport &a, FullTime &x){
      a.final_gross += x.gross;
      a.final_deduct += x.deductions;
      a.final_netPay += x.netPay;
      a.final_dedYTD += x.DedYTD;
      a.final_netYTD += x.netYTD;
    }

    //gross pay is equal to regular earnings for fulltime employees
    void CalculateGross(){
      gross = earnings;
    }
};

//data for parttime employees
class PartTime : public EmployeeData
/*
EmployeeData public members are public in PartTime
EmployeeData protected members are protected in PartTime
*/
{
  protected:
    float payRate;
    int hours;
    int workDays;
  
  public:
    
    //default PartTime constructor
    PartTime(int ivar=0, string fvar=" ", string lvar=" ", char cvar=' ', float dyvar=0, float nyvar=0){
      idNum = ivar;
      strcpy(fName, fvar.c_str());
      strcpy(lName, lvar.c_str());
      contract = cvar;
      payRate = 0;
      hours = 0;
      workDays = 0;
      gross = 0;
      deductions = 0;
      netPay = 0;
      DedYTD = dyvar;
      netYTD = nyvar;
    }

    //PartTime operator '>>' allows user to enter employees' earnings
    friend void operator >> (istream &input, PartTime &employed){

      cout << "Enter "<< employed.fName << "'s pay rate: ";
      input >> employed.payRate;

      cout << "Enter "<< employed.fName << "'s daily hours: ";
      input >> employed.hours;

      cout << "Enter the number of days "<< employed.fName << " has worked: ";
      input >> employed.workDays;

      cout << endl;
    }

    //PartTime operator '-=' allows tax to be deducted from gross pay and added to net pay
    friend void operator -= (PartTime &employed, float const &deducted){
      employed.deductions = employed.gross * (deducted*0.01);
      employed.netPay = employed.gross - employed.deductions;
    }

    //PartTime prefix operator '++' adds net pay onto netYTD
    friend void operator ++ (PartTime &employed){
      employed.netYTD += employed.netPay;
    }

    //PartTime postfix operator '++' adds deductions onto DedYTD
    friend void operator ++ (PartTime &employed, int){
      employed.DedYTD += employed.deductions;
    }

    //PartTime relational operator '>' determines the employee with the highest worked hours
    friend bool operator > (PartTime &employee_a, PartTime &employee_b){
      static bool compared = true;
      if ((employee_a.workDays*employee_a.hours) > (employee_b.workDays*employee_b.hours)){
        compared = true;
      }else{
        compared = false;
      }
      return compared;
    }

    //PartTime function call operator '()' adds the 10% bonus onto net pay
    void operator() (const int &added){
      netPay += gross*(added*0.01);
      netYTD += netPay*(added*0.01);
    }

    //PartTime operator '+' summarizes data for parttime employees
    friend PartTime operator + (PartTime &employee_a, PartTime &employee_b){
      static PartTime total;
      total.gross = employee_a.gross + employee_b.gross;
      total.deductions = employee_a.deductions + employee_b.deductions;
      total.netPay = employee_a.netPay + employee_b.netPay;
      total.DedYTD = employee_a.DedYTD + employee_b.DedYTD;
      total.netYTD = employee_a.netYTD + employee_b.netYTD;
      total.idNum = 0;
      return total;
    }

    //PartTime operator '<<' prints out employee data
    friend ostream& operator << (ostream &output, PartTime &employed){
      if (employed.idNum > 0){
        output << employed.idNum;
        output << setw(6) << employed.contract;
        output << setw(17) << employed.fName;
        output << setw(11) << employed.lName;
        output << setw(8) << employed.payRate;
        output << setw(10) << employed.workDays*employed.hours;
        output << setw(13) << employed.gross;
        output << setw(14) << employed.deductions;
        output << setw(12) << employed.netPay;
        output << setw(10) << employed.DedYTD;
        output << setw(11) << employed.netYTD;
      } else {
        output << setw(27) << "Part-Time Sub-Total";
        output << setw(41) << employed.gross;
        output << setw(14) << employed.deductions;
        output << setw(12) << employed.netPay;
        output << setw(10) << employed.DedYTD;
        output << setw(11) << employed.netYTD;
      }
      return output;
    }

    //PartTime operator '+=' adds data from the parttime sub-total to the final report
    friend void operator += (summaryReport &a, PartTime &y){
      a.final_gross += y.gross;
      a.final_deduct += y.deductions;
      a.final_netPay += y.netPay;
      a.final_dedYTD += y.DedYTD;
      a.final_netYTD += y.netYTD;
    }

    //gross for parttime employees equals (payRate * hours * workDays)
    void CalculateGross(){
      gross = payRate * hours * workDays;
    }
};

int main() {
  EmployeeData *objptr;

  //list of employees
  FullTime ftobj1(101, "Michael", "Smith", 'F', 10000, 40000);
  PartTime ptobj1(102, "Maria", "Rodriguez", 'P', 7000, 28000);
  FullTime ftobj2(105, "Kyndra", "Hernandez", 'F', 8000, 32000);
  PartTime ptobj2(103, "James", "Robert", 'P', 4800, 19200);
  PartTime ptobj3(104, "Kenny", "Mercedes", 'P', 7200, 32000);


  //use the input operator to enter hours and earnings
  cin >> ftobj1;
  cin >> ftobj2;

  cin >> ptobj1;
  cin >> ptobj2;
  cin >> ptobj3;

  //Calculate gross income using member function and the EmployeeData pointer (objptr);
  objptr = &ftobj1;
  objptr->CalculateGross();
  objptr = &ftobj2;
  objptr->CalculateGross();

  objptr = &ptobj1;
  objptr->CalculateGross();
  objptr = &ptobj2;
  objptr->CalculateGross();
  objptr = &ptobj3;
  objptr->CalculateGross();
  

  //calculate deduction and netPay using substraction assignment operator overloading
  ftobj1 -= tax;
  ftobj2 -= tax;

  ptobj1 -= tax;
  ptobj2 -= tax;
  ptobj3 -= tax;

  //use (++) prefix operator to update netYTP with netPay to reflect YTD-netPay
  ++ftobj1;
  ++ftobj2;

  ++ptobj1;
  ++ptobj2;
  ++ptobj3;

  //use postfix (++) operator to update dedYTP with deductions to reflect total deductions to date in the financial year
  ftobj1++;
  ftobj2++;

  ptobj1++;
  ptobj2++;
  ptobj3++;

  /*Use the relational operator overloading to find Part-time staff with the highest worked hours (workday*hours) and use function call () operator to add bonus (10% of gross) to the netPay */
  if (ptobj1 > ptobj2){
    if(ptobj1 > ptobj3){
      ptobj1(bonus);
    }
    else{
      /* had to add this else statement to account for when ptobj1 is less than ptobj3 */
      ptobj3(bonus);
    }

  }else{
    if (ptobj2 > ptobj3){
      ptobj2(bonus);
    }else{
      ptobj3(bonus);
    }
  }

  //declared for data summary manipulations
  FullTime totalftobj;
  PartTime totalptobj;
  PartTime totalptobj1;
  PartTime totalptobj2;

  //First use assignment operator to assign ptobj1 to totalptobj1 because you can pass more than two arguments
  totalptobj1 = ptobj1;

  //use the '+' operator to sum the deductions, netPay, DedYTD, and netYTD for each group
  totalptobj2 = ptobj2 + ptobj3;
  totalptobj = totalptobj1 + totalptobj2;

  totalftobj = ftobj1 + ftobj2;

  summaryReport printReport;

  //adds parttime/fulltime sub-totals to the final report
  printReport += totalftobj;
  printReport += totalptobj;

  //use output operator to display/print
  cout << "ID. #	C/Type	First Name  Last Name 	 Rate	  Hours	    Earnings	Deductions   	NetPay  Ded. YTD	Net YTD" << endl;
  cout << ftobj1 << endl;
  cout << ftobj2 << endl;
  cout << totalftobj << endl;

  cout << endl;

  cout << ptobj1 << endl;
  cout << ptobj2 << endl;
  cout << ptobj3 << endl;
  cout << totalptobj << endl;

  cout << endl;

  cout << printReport;
  return 0;
}
