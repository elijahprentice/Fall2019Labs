#include <iostream>
#include <string>
using namespace std;

struct CurrencyPairNode{
  string lcurrName;
  string fcurrName;
  float sellRate;
  float buyRate;
  CurrencyPairNode *next;
};

void addPair(CurrencyPairNode *head, string lcurr, string new_fcurr, float new_sell, float new_buy){
  CurrencyPairNode *curr_pair = new CurrencyPairNode;
  curr_pair->lcurrName = lcurr;
  curr_pair->fcurrName = new_fcurr;
  curr_pair->sellRate = new_sell;
  curr_pair->buyRate = new_buy;
  curr_pair->next = NULL;

  CurrencyPairNode *last_pair;
  last_pair = head;

  while (last_pair->next != NULL){
    last_pair = last_pair->next;
  }  
  last_pair->next = curr_pair;
}

void print_it(CurrencyPairNode *head){
  CurrencyPairNode *print = head;
  while(print != NULL){
    cout << print->lcurrName + "/" + print->fcurrName + "/" << print->sellRate <<"/"<<print->buyRate<<" ";
    print = print->next;
  }
  cout << endl;
}

int main(){
  //---------------------------------------
  /*
  -Data entry interface for user to declare the array size
  -Use array size to create the array
  -User enters local currencies for head pointers
  */
  int arrSize;
  string local;
  string forgn;
  float next_sell;
  float next_buy;

  cout << "How many local currencies are there?: ";

  cin >> arrSize;

  CurrencyPairNode pairs [arrSize];

  cout << "Enter the local currencies" << endl;

  for (int i = 0; i < arrSize; i++){
    cout << (i + 1) << ": ";
    cin >> pairs[i].lcurrName;
    pairs[i].fcurrName = pairs[i].lcurrName;
    pairs[i].sellRate = 1;
    pairs[i].buyRate = 1;
    pairs[i].next = NULL;
  }
  cout << endl;

  //---------------------------------------

  //---------------------------------------

  /*
  Input interface for the user to enter
  currency pair nodes to create the linked
  lists that connect to the local heads
  */
  char option;
  int valid_count;

  while (option != 'Q'){
    cout << "Would you like to add another pair? (Y/N): ";
    cin >> option;
    if(option == 'Y'){
      cout << "To what local currency would you like to add a pair to?: ";
      cin >> local;
      for(int j = 0; j < arrSize; j++){
        if (local == pairs[j].lcurrName){
          cout << "What is the new foreign currency?: ";
          cin >> forgn;
          
          cout << "Give the sell rate: ";
          cin >> next_sell;
          
          cout << "Give the buy rate: ";
          cin >> next_buy;
          
          addPair(&pairs[j], local, forgn, next_sell, next_buy);
          break;
        }
        valid_count++;
      }
      if (valid_count == 5){
        cout << "Not a valid local currency.";
      }
      valid_count = 0;
    }
    else if(option == 'N'){
      option = 'Q';
      cout << endl;
    } else {
      cout << "Invalid Option" << endl;
      cout << endl;
    }
  }

  //---------------------------------------

  //---------------------------------------
  /*
  print the data structure
  */
  cout << "Local/Foreign/Sell Rate/Buy Rate" << endl;
  cout << endl;
  for(int k = 0; k < arrSize; k++){
    print_it(&pairs[k]);
    cout << endl;
  }

  return 0;
}
