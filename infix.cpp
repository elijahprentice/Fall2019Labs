#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

/*
C++ program that takes a formula (in infix notation)
and converts it to either prefix or postfix notation
depending on the user's preference
*/

struct expressed{
  string oper;
  expressed *next;
};

void add_express(expressed *head, string new_op){
  expressed *next_part = new expressed;
  next_part->oper = new_op;
  next_part->next = NULL;

  expressed *prev_part;
  prev_part = head;

  while(prev_part->next != NULL){
    prev_part = prev_part->next;
  }

  prev_part->next = next_part;
}

void print_express(expressed *head, string pre_post){
  expressed *print_it = head;
  string new_express;
  if (pre_post == "postfix"){
    
    while (print_it != NULL){
      cout << print_it->oper;
      print_it = print_it->next;
    }
  } else {
    
    //reverse postfix before printing
    while(print_it != NULL){
      new_express = print_it->oper + new_express;
      print_it = print_it->next;
    }
    cout << new_express;
  }
}

bool higher_precedence(string current, string top){
  if (current == top)   { return false; }
  else if (top == "^")  { return false; }
  else if (top == "*")  { return true;  }
  else if (top == "/"){
    if(current == "*"){
      return false;
    } else {  return true;  }
  }
  else if (top == "+"){

    if(current == "*" || current == "/"){
      return false;
    } else {  return true;  }
  }
  else if (top == "-"){

    if(current == "^"){
      return true;
    } else {  return false; }
  }
  return false;
}

int main() {
  /*
  infix expression from user is converted to prefix/postfix form
  
  use Stack (Array implementation) for the manipulation of the operators in the infix expression

  linked list as the container for the final prefix/postfix string

  use the linked list to print/output the result of prefix/postfix
  */

  //ask for expression from user
  string expression;
  cout << "Enter your expression in infix form: ";
  cin >> expression;

  //stack to hold operators
  stack <string> opers;
  opers.push("");

  /*
  linked list as the container for the final prefix/postfix string
  */
  expressed nextOper;
  nextOper.next = NULL;

  string temp;    //hold next operand/operator
  bool is_higher; //precedence of top operator over current
  string option;  //prefix or postfix

  cout << "Do you want the [prefix] or [postfix]?: ";
  cin >> option;

  /*
  to find prefix:
  - reverse expression
  - find postfix
  - reverse postfix
  */
  if (option == "prefix"){
    //reverse expression
    reverse(expression.begin(), expression.end());
  }

  int i = 0;      //expression size counter

  /*
  infix to postfix using stack
  */

  while(i < expression.size()){
    
    //current operand/operator
    temp = expression.at(i);

    //flip brackets if prefix is wanted
    if(option == "prefix"){
      if (temp == "("){ temp = ")";}
      else if (temp == ")"){  temp = "("; }
      else if (temp == "["){  temp = "]"; }
      else if (temp == "]"){  temp = "["; }
    }

    if (temp == "["){ opers.push(temp); }
    else if (temp == "]"){

      while(opers.top() != "["){

        add_express(&nextOper, opers.top());
        opers.pop();
      }
      opers.pop();
    }
    else if (temp == "("){  opers.push(temp); }
    else if (temp == ")"){

      while(opers.top() != "("){

        add_express(&nextOper, opers.top());
        opers.pop();
      }
      opers.pop();
    }
    else if(temp != "*" && temp != "/" && temp != "+" && temp != "-" && temp != "^"){

      add_express(&nextOper, temp);
    }
    else if ((temp != "(" && temp != ")")){
      is_higher = higher_precedence(temp, opers.top());
      while (!opers.empty() && is_higher == true){
        add_express(&nextOper, opers.top());
        opers.pop();
        is_higher = higher_precedence(temp, opers.top());
      }
      opers.push(temp);
    }
    i++;
  }
  while (!opers.empty()){

    add_express(&nextOper, opers.top());
    opers.pop();
  }
  
  print_express(&nextOper, option);
  return 0;
}