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


	//Here we initialize our data structures
    PatientTree myTree;
    myTree.buildGraph();
    myTree.buildDonorList();
    myTree.buildPatientList();
	bool running = true;

	//The following block of code reads in the patient list (.txt file) and adds them all to the patient table
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
    cout	<<"======Main Menu====="<<	endl;
    cout	<<"1. Add a patient"<<	endl;
    cout	<<"2. Add a donor"<<	endl;
    cout    <<"3. Delete a patient"<< endl;
    cout    <<"4. Delete a donor"<< endl;
    cout    <<"5. Count patients"<< endl;
    cout    <<"6. Count donors"<< endl;
    cout    <<"7. Print patients"<< endl;
    cout    <<"8. Print donors"<< endl;
    cout    <<"9. Print matches"<< endl;
    cout    <<"10. Operate"<< endl;
    cout	<<"11. Quit"<<	endl;

  //takes user input
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

	//here we add the input information into the patient table, and then check if there is a donor
	//already available to be matched with the patient. If there is, a Pair is created and the patient
	//is removed from the table.
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

	//here we add the input information into the donor table and check for a suitable match in the patient table.
	//If a candidate is found, a Pair is made and the donor is removed from the table.
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
    myTree.deletePatient(name);//deletes patient from patient table
  }

  if (answer == 4){
    cout << "Enter donor name:" << endl;
    string name;
    getline(cin, name);
    myTree.deleteDonor(name);//deletes donor from donor table
  }

  if (answer == 5){
    int count = myTree.countPatients();
    cout << "There are " << count << " patients waiting."<<endl;//outputs the number of patients in the patient table
  }

  if (answer == 6){
    int count = myTree.countDonors();
    cout << "There are " << count << " donors availible."<<endl;//outputs the number of donors in the donor table
  }

  if (answer == 7){
    myTree.printPatients();//prints the list of patients and all their attributes
  }

  if (answer == 8){
    myTree.printDonors();//prints the list of donors and all their attributes
  }

  if (answer == 9){
    myTree.printMatches();//prints the list of matches made (that have not undergone sugery)
  }

  if (answer == 10){
    myTree.Operate();//Performs a surgery on the first Pair in the queue
  }

  if (answer == 11){
	running = false;//ends while loop, thus ending program
    cout << "Goodbye!" << endl;
    return 0;
  }
  //fixing an issue found by a4nacation - this issue is about putting in a number for the menu that isn't an option
  //(i.e. anything > 11) does nothing and should maybe provide an error message to the user
  if (answer > 11){
    cout<<"Not a valid selection. Pick a valid number."<<endl;
  }
}
}
