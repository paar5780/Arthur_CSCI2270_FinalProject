#include <iostream>
#include <fstream>
#include <sstream> #include <iostream>
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
    myTree.buildGraph();//builds our city graph
    myTree.buildDonorList();//builds our donor table and fills it with placeholders
    myTree.buildPatientList();//builds our patient table and fills it with placeholders
	bool running = true;//initialize bool to keep program running. Will = false when 'Quit' is selected

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
			myTree.addPatient(name, organ, blood_type, city, time, successRate);//adds each patient from the txt file to the patient table, replacing the placeholders
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
    cout    <<"10. Print quantity requested of organ"<<endl;
    cout    <<"11. Operate"<< endl;
    cout	<<"12. Quit"<<	endl;

  //takes user input
  int answer;
  cin >> answer;
  cin.ignore();

  if (answer == 1){
    cout << "Enter patient name (First or Last): " << endl;//ex: Johnson (We entered last names, but any name can identify a patient)
    string name;
    getline(cin, name);

    cout << "Enter organ needed:\n(Heart, Lungs, Liver, Pancreas, Kidney, Intestines, Head)" << endl;//ex: heart
    string organ;
    getline(cin, organ);

    cout << "Enter blood type:\n(A, B, AB, O)" << endl;//ex: AB
    string blood_type;
    getline(cin, blood_type);

    cout << "Enter survivabilty rate (0% - 100%):\n%";//ex: 87
    int survivability;
    string str_rate;
    getline(cin, str_rate);
    survivability = atoi(str_rate.c_str());

    cout << "Enter time left (in hrs): " << endl;//ex: 3 (this is measured in hours)
    int time_left;
    string str_time_left;
    getline(cin, str_time_left);
    time_left = atoi(str_time_left.c_str());

    cout << "Choose closest location:\n";
    cout << "(Atlanta, Boise, Boston, Chicago, Cleveland, Dallas, Denver, Detroit, Honolulu, Houston,\n";
    cout << "Los Angeles, Memphis, Miami, New York City, Philadelphia, Phoenix, San Francisco, Seattle)" << endl;//ex: Cleveland
    string location;
    getline(cin, location);

	//here we add the input information into the patient table, and then check if there is a donor
	//already available to be matched with the patient. If there is, a Pair is created and the patient
	//is removed from the table.
    Patient* newPatient = myTree.addPatient(name, organ, blood_type, location, time_left, survivability);//adds patient to the patient table
    Donor* donorMatch = NULL;
    if(newPatient != NULL){
		Donor* donorMatch = myTree.findDonorMatch(newPatient);//searches donor table for a match for the patient, assigns it to donorMatch if found
	}
    if (donorMatch != NULL){
      bool full = myTree.queueIsFull();
      if (full == true){
        cout << "Must operate before adding another match." << endl;
      }
      else{
        Pair newPair;//initializes the patient-donor match struct
        newPair.patient = newPatient->name;//assigns patient to pair
        newPair.donor = donorMatch->name;//assigns donor to pair
        newPair.success_rate = newPatient->survivability;
        myTree.enqueue(newPair);//adds the pair to the surgery waiting list
        myTree.deleteDonor(donorMatch->name);//deletes donor from table because the organ has been allocated
        myTree.deletePatient(newPatient->name);//deletes patient from table because they no longer need an organ
      }


  }
}

  if (answer == 2){
    cout << "Enter donor name (First or Last):" << endl;//ex: Smith
    string name;
    getline(cin, name);

    cout << "Enter donated organ:\n(Heart, Lungs, Liver, Pancreas, Kidney, Intestines, Head)" << endl;//ex: lungs
    string organ;
    getline(cin, organ);

    cout << "Enter blood type:\n(A, B, AB, O)" << endl;//ex: O
    string blood_type;
    getline(cin, blood_type);

    cout << "Choose closest location:\n";
    cout << "(Atlanta, Boise, Boston, Chicago, Cleveland, Dallas, Denver, Detroit, Honolulu, Houston,\n";
    cout << "Los Angeles, Memphis, Miami, New York City, Philadelphia, Phoenix, San Francisco, Seattle)" << endl;//ex: Honolulu
    string location;
    getline(cin, location);

	//here we add the input information into the donor table and check for a suitable match in the patient table.
	//If a candidate is found, a Pair is made and the donor is removed from the table.
    Donor* newDonor = myTree.addDonor(name, organ, blood_type, location);//Adds the donor to the donor table
    Patient* patientMatch = NULL;//initializes the matched patient struct
    if(newDonor != NULL){
		patientMatch = myTree.findPatientMatch(newDonor);//searches patient tree for a match to the donor, assigns it to patientMatch if found
	}
    if (patientMatch != NULL){
      bool full = myTree.queueIsFull();
      if (full == true){
        cout << "Must operate before adding another match." << endl;
      }
      else{
        Pair newPair;//initializes struct for matched donor and patient
        newPair.patient = patientMatch->name;//assigns patient to pair
        newPair.donor = newDonor->name;//assigns donor to pair
        newPair.success_rate = patientMatch->survivability;//assigns chance of surgery success to pair
        myTree.enqueue(newPair);//places the donor-patient pair into a waiting list for surgery
        myTree.deletePatient(patientMatch->name);//removes the patient from the patient table (since they no longer need a donor)
        myTree.deleteDonor(newDonor->name);//removes the donor from the donor table (since the organ has been allocated)
      }
    }

  }

  if (answer == 3){
    cout << "Enter patient name:" << endl;//ex: Jamison
    string name;
    getline(cin, name);
    myTree.deletePatient(name);//deletes patient from patient table
  }

  if (answer == 4){
    cout << "Enter donor name:" << endl;//ex: Chen
    string name;
    getline(cin, name);
    myTree.deleteDonor(name);//deletes donor from donor table
  }

  if (answer == 5){
    int count = myTree.countPatients();//counts the number of patients in the table and assigns it to a variable
    cout << "There are " << count << " patients waiting."<<endl;//outputs the number of patients in the patient table
  }

  if (answer == 6){
    int count = myTree.countDonors();//counts the number of donors in the table and assigns it to a variable
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
    string organ;
    int organInt;
    cout<<"Enter organ type"<<endl;
    getline(cin,organ);
    int numRequested = myTree.printOrganQuantity(organ);//prints the list of matches made (that have not undergone sugery)
    if (numRequested != -1) {
    cout<<"There are "<<numRequested<<" requests for "<<organ<<"."<<endl;
    }
    else { cout<<"No such organ found"<<endl; }
  }

  if (answer == 11){
    myTree.Operate();//Performs a surgery on the first Pair in the queue
  }

  if (answer == 12){
	running = false;//ends while loop, thus ending program
    cout << "Goodbye!" << endl;
    return 0;
  }
}
}
