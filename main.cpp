#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include "PatientList.h"

int main(){
  buildGraph();
  buildDonorList();
  buildPatientList();

  while(1){
    //build main menu
    cout	<<	"======Main Menu====="	<<	endl;
    cout	<<	"1. Add a patient"	<<	endl;
    cout	<<	"2. Add a donor"	<<	endl;
    cout  <<  "3. Delete a patient"   << endl;
    cout  <<  "4. Delete a donor"  << endl;
    cout  <<  "5. Count patients" << endl;
    cout  <<  "6. Count donors" << endl;
    cout  <<  "7. Print patients" << endl;
    cout  <<  "8. Print donors" << endl;
    cout  <<  "9. Print matches" << endl;
    cout  <<  "10. Operate" << endl;
    cout	<<	"11. Quit"	<<	endl;
  }

  int answer;
  cin >> answer;
  cin.ignore();

  if (answer == 1){
    cout << "Enter patient name:" << endl;
    string name;
    getline(cin, name);

    cout << "Enter organ needed:" << endl;
    string organ;
    getline(cin, organ);

    cout << "Enter blood type:" << endl;
    string blood_type;
    getline(cin, blood_type);

    cout << "Enter survivabilty rate:" << endl;
    int rate;
    string str_rate;
    getline(cin, str_rate);
    rate = atoi(str_rate);

    cout << "Enter time left:" << endl;
    int time_left;
    string str_time_left;
    getline(cin, str_time_left);
    time_left = atoi(str_time_left);

    cout << "Enter location:" << endl;
    string location;
    getline(cin, location);

    addPatient(name, organ, blood_type, city, time_left, suvivability);


  }

  if (answer == 2){
    cout << "Enter donor name:" << endl;
    string name;
    getline(cin, name);

    cout << "Enter donated organ:" << endl;
    string organ;
    getline(cin, organ);

    cout << "Enter blood type:" << endl;
    string blood_type;
    getline(cin, blood_type);

    cout << "Enter location:" << endl;
    string location;
    getline(cin, location);

    addDonor(name, organ, blood_type, city);

  }

  if (answer == 3){
    cout << "Enter patient name:" << endl;
    string name;
    getline(cin, name);
    deletePatient(name);
  }

  if (answer == 4){
    cout << "Enter donor name:" << endl;
    string name;
    getline(cin, name);
    deleteDonor(name);
  }

  if (answer == 5){
    int count = countPatients();
    cout << "There are " << count << " patients waiting."
  }

  if (answer == 6){
    int count = countDonors();
    cout << "There are " << count << " donors availible."
  }

  if (answer == 7){
    printPatients();
  }

  if (answer == 8){
    printDonors();
  }

  if (answer == 9){
    printMatches();
  }

  if (answer == 10){
    Operate();
  }

  if (answer == 11){
    cout << "Goodbye!" << endl;
    return 0;
  }

}
