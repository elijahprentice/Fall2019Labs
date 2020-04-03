#include <iostream>
#include <string>
using namespace std;

struct deqNode{
  int appStartTime;
  int appEndtime;
  string custName;
  deqNode *prevNode;
  deqNode *nextNode;
};

//function to add appointment
//add comments later
void addAppointment(deqNode *head, int addStart, int addEnd, string addName){
  deqNode *add_app = new deqNode;
  add_app->appStartTime = addStart;
  add_app->appEndtime = addEnd;
  add_app->custName = addName;
  add_app->prevNode = NULL;
  add_app->nextNode = NULL;

  //start from the earliest appointment
  deqNode *last_app;
  last_app = head;

  //check if an appointment was added
  bool added = false;

  //if the schedule is clear
  if (last_app->nextNode == NULL){
    add_app->prevNode = last_app;
    last_app->nextNode = add_app;
  } else {
    while (last_app->nextNode != NULL){
      last_app = last_app->nextNode;
      if (add_app->appStartTime == last_app->appStartTime){
        break;
      } else if (add_app->appStartTime <= 3){
        if (last_app->appStartTime >= 9){
          if (last_app->nextNode == NULL){
            add_app->prevNode = last_app;
            last_app->nextNode = add_app;
            added = true;
            break;
          } else if (((add_app->appStartTime) < (last_app->nextNode->appStartTime)) && last_app->nextNode->appStartTime <= 3){
            add_app->prevNode = last_app;
            add_app->nextNode = last_app->nextNode;
            last_app->nextNode->prevNode = add_app;
            last_app->nextNode = add_app;
            added = true;
            break;
          }
        } else if ((add_app->appStartTime) < (last_app->appStartTime)){
          add_app->prevNode = last_app->prevNode;
          add_app->nextNode = last_app;
          last_app->prevNode->nextNode = add_app;
          last_app->prevNode = add_app;
          added = true;
          break;
        } else if ((add_app->appStartTime) > (last_app->appStartTime)){
          if (last_app->nextNode == NULL){
            add_app->prevNode = last_app;
            last_app->nextNode = add_app;
            added = true;
            break;
          }
        }
      } else if ((add_app->appStartTime) < (last_app->appStartTime)){
        add_app->prevNode = last_app->prevNode;
        add_app->nextNode = last_app;
        last_app->prevNode->nextNode = add_app;
        last_app->prevNode = add_app;
        added = true;
        break;
      } else if ((add_app->appStartTime) > (last_app->appStartTime)){
        if (last_app->nextNode == NULL){
          add_app->prevNode = last_app;
          last_app->nextNode = add_app;
          added = true;
          break;
        } else if ((add_app->appStartTime) < (last_app->prevNode->appStartTime)){
          add_app->prevNode = last_app->prevNode;
          add_app->nextNode = last_app;
          last_app->prevNode->nextNode = add_app;
          last_app->prevNode = add_app;
          added = true;
          break;
        }
      }
    }
    
    //cout error is appointment could not be added
    if (added == false){
      cout << "This time is not available." << endl << endl;
    }
  }
}

//function to remove appointment
//add comments later
void cancelAppointment(deqNode *head, int rmStart, string rmName){

  //start from the earliest appointment
  deqNode *last_app;
  last_app = head;

  bool removed = false;

  if (last_app->nextNode != NULL){
    while (last_app->nextNode != NULL){
      last_app = last_app->nextNode;
      if (last_app->appStartTime == rmStart && last_app->custName == rmName){
        if(last_app->nextNode == NULL){
          last_app->prevNode->nextNode = NULL;
          removed = true;
          break;
        } else {
          last_app->nextNode->prevNode = last_app->prevNode;
          last_app->prevNode->nextNode = last_app->nextNode;
          removed = true;
          break;
        }
      }
    }
    if (removed == false){
      cout << "There is no appointment for " + rmName + " at " << rmStart << "."
      << endl << endl;
    }
  } else {
    cout << "There are no appointments to cancel." << endl << endl;
  }
}

//function to print all the bookings
//add comments
void printBookings(deqNode *head){
  
  deqNode *printThis = head->nextNode;
  if (printThis == NULL){
    cout << "There are no appointments." << endl << endl;
  } else {
    while (printThis != NULL){
      cout << printThis->appStartTime << ":00 to "
      << printThis->appEndtime << ":00, Name: "
      + printThis->custName << endl << endl;
      printThis = printThis->nextNode;
    }
  }
}

//function to count and return total number of bookings
//add comments
int findNum(deqNode *head){

  deqNode *countIt = head->nextNode;
  int count = 0;

  if (countIt == NULL){
    return 0;
  } else {
    while (countIt != NULL){
      count++;
      countIt = countIt->nextNode;
    }
    return count;
  }
}

//function to print whether or not the salon is fully booked
//add comments
void full(deqNode *head){
  
  int count = findNum(head);
  if (count == 7){
    cout << "The schedule is full." << endl << endl;
  } else {
    cout << "There is space available." << endl << endl;
  }
}

int main() {
  
  //create front node (empty beginning of the list)
  deqNode front;
  front.custName = "front";
  front.prevNode = NULL;
  front.nextNode = NULL;

  char option;
  int tempStart;
  int tempEnd;
  string tempName;
  int bookings;
  while (option != 'Q'){
    tempStart = 0;
    tempEnd = 0;

    cout <<
    "[A]dd appointment"       << endl <<
    "[C]ancel appointment"    << endl <<
    "[V]iew all bookings"     << endl <<
    "[N]umber of bookings"    << endl << 
    "[I]s it fully booked?"   << endl <<
    "[Q]uit"                  << endl <<
    "What would you like to do?: ";

    cin >> option;
    
    if (option == 'A' || option == 'C'){
      cout << "What time is the appointment?: ";
      cin >> tempStart;

      if ((tempStart <= 0) || ((tempStart > 3) && (tempStart < 9))){
        cout << "This time is outside hours of operation." << endl << endl;
      } else {
        cout << "What is the name for the appointment?: ";
        cin >> tempName;

        if (option == 'A'){
          if (tempStart == 12) {
            tempEnd = 1;
          } else {
            tempEnd = tempStart + 1;
          }
          addAppointment(&front, tempStart, tempEnd, tempName);
        } else {
          cancelAppointment(&front, tempStart, tempName);
        }
      }
    }
    else if (option == 'V'){  printBookings(&front);  }
    else if (option == 'N'){
      
      bookings = findNum(&front);
      if (bookings == 0){
        cout << "The schedule is empty." << endl << endl;
      } else if (bookings == 1) {
        cout << "There is 1 appointment." << endl << endl;
      } else {
        cout << "There are " << bookings << " appointments." << endl << endl;
      }
    }
    else if (option == 'I'){  full(&front); }
    else if (option == 'Q'){  cout << "Goodbye!"; }
    else {  cout << "Invalid option"; }
  }
  return 0;
}
