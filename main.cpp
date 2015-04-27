#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Patient_Donor_Database.h"


using namespace std;

int main(){



  PatientTree myTree;
  myTree.buildGraph();
  myTree.buildDonorList();
  myTree.buildPatientList();
	bool running = true;

  ifstream textFile;
	textFile.open("patientList.txt");
	string line;
	string tempLine;
	string name;
	string organ;
	string blood_type;
	string city;
	int successRate;
	int time;
	while(!textFile.eof()){

		getline(textFile, line, ',');
		name = line;

		getline(textFile, line, ',');
		organ = line;

		getline(textFile, line, ',');
		blood_type = line;

		getline(textFile, line, ',');
		city = line;

		getline(textFile, line, ',');
		successRate = atoi(line.c_str());

		getline(textFile, line);
		time = atoi(line.c_str());

		if(!textFile.eof()){
			myTree.addPatient(name, organ, blood_type, city, time, successRate);
		}
	}

  while(running == true){
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
    int survivability;
    string str_rate;
    getline(cin, str_rate);
    survivability = atoi(str_rate.c_str());

    cout << "Enter time left:" << endl;
    int time_left;
    string str_time_left;
    getline(cin, str_time_left);
    time_left = atoi(str_time_left.c_str());

    cout << "Enter location:" << endl;
    string location;
    getline(cin, location);

    Patient* newPatient = myTree.addPatient(name, organ, blood_type, location, time_left, survivability);
    Donor* donorMatch = NULL;
    if(newPatient != NULL){
		Donor* donorMatch = myTree.findDonorMatch(newPatient);
	}
    if (donorMatch != NULL){
      bool full = myTree.queueIsFull();
      if (full == true){
        cout << "Must operate before adding another match." << endl;
      }
      else{
        Pair newPair;
        newPair.patient = newPatient->name;
        newPair.donor = donorMatch->name;
        newPair.success_rate = newPatient->survivability;
        myTree.enqueue(newPair);
        myTree.deleteDonor(donorMatch->name);
        myTree.deletePatient(newPatient->name);
      }


  }
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

    Donor* newDonor = myTree.addDonor(name, organ, blood_type, location);
    Patient* patientMatch = NULL;
    if(newDonor != NULL){
		patientMatch = myTree.findPatientMatch(newDonor);
	}
    if (patientMatch != NULL){
      bool full = myTree.queueIsFull();
      if (full == true){
        cout << "Must operate before adding another match." << endl;
      }
      else{
        Pair newPair;
        newPair.patient = patientMatch->name;
        newPair.donor = newDonor->name;
        newPair.success_rate = patientMatch->survivability;
        myTree.enqueue(newPair);
        myTree.deletePatient(patientMatch->name);
        myTree.deleteDonor(newDonor->name);
      }
    }

  }

  if (answer == 3){
    cout << "Enter patient name:" << endl;
    string name;
    getline(cin, name);
    myTree.deletePatient(name);
  }

  if (answer == 4){
    cout << "Enter donor name:" << endl;
    string name;
    getline(cin, name);
    myTree.deleteDonor(name);
  }

  if (answer == 5){
    int count = myTree.countPatients();
    cout << "There are " << count << " patients waiting."<<endl;
  }

  if (answer == 6){
    int count = myTree.countDonors();
    cout << "There are " << count << " donors availible."<<endl;
  }

  if (answer == 7){
    myTree.printPatients();
  }

  if (answer == 8){
    myTree.printDonors();
  }

  if (answer == 9){
    myTree.printMatches();
  }

  if (answer == 10){
    myTree.Operate();
  }

  if (answer == 11){
	running = false;
    cout << "Goodbye!" << endl;
    return 0;
  }
}
}
