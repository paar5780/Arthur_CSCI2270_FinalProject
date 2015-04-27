#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "PatientList.h"


using namespace std;

PatientTree::PatientTree(){
    //constructor
	successCount = 0;
	failureCount = 0;
	queueHead = 0;
	queueTail = 0;
    for(int i = 0; i < 7; i++){
      for(int j = 0; j < 4; j++){
        PatientList[i][j] = NULL;
        DonorList[i][j] = NULL;
      }
    }
}

PatientTree::~PatientTree(){
}
void PatientTree::addVertex(std::string n){
	//make sure it's not already in the graph
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<"found"<<endl;
        }
    }
    //add it to the vector of vertices
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);
    }
}

void PatientTree::addEdge(std::string v1, std::string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);

                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}


void PatientTree::buildGraph(){
  //Graph g;
  addVertex("Boston");
	addVertex("New York City");
	addVertex("Philadelphia");
	addVertex("Atlanta");
	addVertex("Denver");
	addVertex("San Francisco");
	addVertex("Dallas");
	addVertex("Phoenix");
  addVertex("Seattle");
  addVertex("Honolulu");
  addVertex("Chicago");
  addVertex("Detroit");
  addVertex("Los Angeles");
  addVertex("Houston");
  addVertex("Miami");
  addVertex("Memphis");
  addVertex("Cleveland");
  addVertex("Boise");
  //edge written to be undirected
  addEdge("Seattle", "San Francisco", 2);
  addEdge("Seattle", "Phoenix", 3);
  addEdge("Seattle", "New York City", 6);
  addEdge("San Francisco", "New York City", 6);
  addEdge("San Francisco", "Phoenix", 2);
  addEdge("San Francisco", "Boston", 6);
  addEdge("San Francisco", "Denver", 3);
  addEdge("Boise", "Seattle", 1);
  addEdge("Boise", "Denver", 2);
  addEdge("Los Angeles", "San Francisco", 1);
  addEdge("Los Angeles", "Denver", 2);
  addEdge("Los Angeles", "Dallas", 3);
  addEdge("Los Angeles", "Miami", 5);
  addEdge("Los Angeles", "New York", 6);
  addEdge("Los Angeles", "Boston", 6);
  addEdge("Denver", "Phoenix", 2);
  addEdge("Denver", "Dallas", 2);
  addEdge("Denver", "New York", 4);
  addEdge("Honolulu", "San Francisco", 5);
  addEdge("Dallas", "Memphis", 1);
  addEdge("Dallas", "Houston", 1);
  addEdge("Dallas", "Atlanta", 2);
  addEdge("Houston", "Miami", 3);
  addEdge("Houston", "Philadelphia", 3);
  addEdge("Houston", "Chicago", 3);
  addEdge("Memphis", "Atlanta", 1);
  addEdge("Memphis", "Cleveland", 4);
  addEdge("Cleveland", "Detroit", 1);
  addEdge("Cleveland", "Chicago", 1);
  addEdge("Detroit", "Chicago", 1);
  addEdge("Detroit", "New York City", 2);
  addEdge("Detroit", "Philadelphia", 2);
  addEdge("Detroit", "Denver", 3);
  addEdge("Miami", "Los Angeles", 5);
  addEdge("Miami", "Atlanta", 2);
  addEdge("Atlanta", "Philadelphia", 2);
  addEdge("Philadelpha", "Boston", 1);
  addEdge("Boston", "New York City", 1);
}

int PatientTree::Dijkstra(string starting, string destination) {
    
    vector<vertex*> solved;
    vertex *start, *dest;
    for(int i=0; i < vertices.size();i++){
		vertices[i].visited = false;
		vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;
        if (starting == vertices[i].name) {
            start = &vertices[i];
        }
        if (destination == vertices[i].name) {
            dest = &vertices[i];
        }
    }
    start->visited = true;
    start->distance = 0;
    solved.push_back(start);
    
    while (!dest->visited) {
        int minDistance = INT_MAX;
        vertex *minVertex, *prevVertex;
        for(int i = 0; i<solved.size(); i++){
			vertex *u = solved[i];
			for(int j=0; j < u->adj.size(); j++) {
				if (!u->adj[j].v->visited){
					int distance = u->distance + u->adj[j].weight;
					if(minDistance > distance ){
						minDistance = distance;
                        minVertex = u->adj[j].v;
                        prevVertex = u;
                    }
                }
            }
        }
        solved.push_back(minVertex);
        minVertex->distance = minDistance;
        minVertex->previous = prevVertex;
        minVertex->visited = true;
    }
    vector <string> path;
    vertex *temp = dest;
    while(temp!= NULL){
		path.push_back(temp->name);
        temp = temp->previous;
    }
    return dest->distance;
}


int PatientTree::findShortestDistance(string city1, string city2){
  //check the two cities
  if (city1 == city2){
  	return 0;
  }
  //use Dijkstra traverse to find and print the shortest distance
  int distance = Dijkstra(city1, city2);
  return distance;
}

int PatientTree::countPatients(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  Patient* x;
  int count = 0;

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (PatientList[i][j] != NULL){
        count ++;
        x = PatientList[i][j]; //head of linked list
        //iterate through patients
        while (x->next != NULL){
          count++;
          x = x->next;
        }
    }

  }

}
return count;
}

int PatientTree::countDonors(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  Donor* x;
  int count = 0;

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (DonorList[i][j] != NULL){
        count ++;
        x = DonorList[i][j]; //head of linked list
        //iterate through patients
        while (x->next != NULL){
          count++;
          x = x->next;
        }
    }

  }

}
return count;
}

void PatientTree::printPatients(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  string organ;
  string blood_type;
  Patient* x;

  

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (PatientList[i][j] != NULL){
        x = PatientList[i][j]; //head of linked list
        //iterate through patients
        while (x != NULL){
		  if (x->organ == 1){
			organ = "Heart";
		  }
		  else if (x->organ == 2){
			organ = "Lungs";
		  }
		  else if (x->organ == 3){
			organ = "Liver";
		  }
		  else if (x->organ == 4){
			organ = "Pancreas";
		  }
		  else if (x->organ == 5){
			organ = "Kidney";
		  }
		  else if (x->organ == 6){
			organ = "Intestines";
		  }
		  else if (x->organ == 7){
			organ = "Head";
		  }

		  if (x->blood_type == 1){
			blood_type = "A";
		  }
		  else if (x->blood_type == 2){
			blood_type = "B";
		  }
		  else if (x->blood_type == 3){
			blood_type = "AB";
		  }
		  else if (x->blood_type == 4){
			blood_type = "O";
		  }
          cout << x->name << " : " << organ << " - Blood type " << blood_type << " - " << x->location << " - " << x->survivability << " chance of survival - " << x->time_left << " hours left" << endl;
          x = x->next;
        }
    }

  }

}
}

void PatientTree::printDonors(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  Donor* x;
  string organ;
  string blood_type;

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (DonorList[i][j] != NULL){
        x = DonorList[i][j]; //head of linked list
        //iterate through patients
        while (x != NULL){
          if (x->organ == 1){
			organ = "Heart";
		  }
		  else if (x->organ == 2){
			organ = "Lungs";
		  }
		  else if (x->organ == 3){
			organ = "Liver";
		  }
		  else if (x->organ == 4){
			organ = "Pancreas";
		  }
		  else if (x->organ == 5){
			organ = "Kidney";
		  }
		  else if (x->organ == 6){
			organ = "Intestines";
		  }
		  else if (x->organ == 7){
			organ = "Head";
		  }

		  if (x->blood_type == 1){
			blood_type = "A";
		  }
		  else if (x->blood_type == 2){
			blood_type = "B";
		  }
		  else if (x->blood_type == 3){
			blood_type = "AB";
		  }
		  else if (x->blood_type == 4){
			blood_type = "O";
		  }
          cout << x->name << " : " << organ << " - Blood type " << blood_type << " - " << x->location << endl;
          x = x->next;
        }
    }

  }

}
}

Patient* PatientTree::findPatientMatch(Donor* d){
  int js[5];
  for (int k = 0; k < 5; k++){
	js[k] = 0;
  }

  if(d->blood_type==1){
	js[0] = 1;
	js[1] = 3;
  }
  if(d->blood_type==2){
	js[0] = 2;
	js[1] = 3;
  }
  if(d->blood_type==3){
	js[0] = 3;
  }
  if(d->blood_type==4){
	js[0] = 1;
	js[1] = 2;
	js[2] = 3;
	js[3] = 4;
  }

  int best_score = INT_MIN;
  Patient* best = NULL;
  Patient *p = NULL;
  int count = 0;
  int score;
  int time_taken;

  int m = 0;
  while (js[m] != 0){
	  count = 0;
	p = PatientList[d->organ-1][js[m]-1];
	while (p != NULL){
	  count++; //relative time on waiting list
	  time_taken = findShortestDistance(p->location, d->location);
	  if (p->time_left >= time_taken){
		score = (p->survivability) - count;
		if (score > best_score){
		  best_score = score;
		  best = p;
		}
	  }
	  p = p->next;
	}
	m++;
  }
  if (best == NULL){
    cout << "No suitable patient was found" << endl;
  }
  else{
    cout << "Match found!" << endl;
  }
  return best;
}

Donor* PatientTree::findDonorMatch(Patient *p){
  int js[4];
  for (int k = 0; k < 4; k++){
	js[k] = 0;
  }

  if(p->blood_type==1){
	js[0] = 1;
	js[1] = 4;
  }
  if(p->blood_type==2){
	js[0] = 2;
	js[1] = 4;
  }
  if(p->blood_type==3){
	js[0] = 1;
	js[1] = 2;
	js[2] = 3;
	js[3] = 4;
  }
  if(p->blood_type==4){
	js[0] = 4;
  }

  int best_score = INT_MIN;
  Donor* best = NULL;
  int score;
  int time_taken;
  int count;

  int m = 0;
  while (js[m] != 0){
	count = 0;
	Donor* d = DonorList[p->organ-1][js[m]-1];
	while (d != NULL){
	  time_taken = findShortestDistance(p->location, d->location);
	  if (p->time_left >= time_taken){
		return d;
        cout << "A suitable donor was found!" << endl;
	  }
	  d = d->next;
	}
	m++;
  }
  cout << "No suitable donor was found." << endl;
  return NULL;
}

Patient* PatientTree::addPatient(string name, string organ, string blood_type, string city, int time_left, int survivability){
	bool cityfound = false;
      int i = 1*(organ == "heart") + 2*(organ == "lungs") + 3*(organ == "liver") + 4*(organ == "pancreas")
      + 5*(organ == "kidney") + 6*(organ == "intestines") + 7*(organ == "head");
      if(i == 0){
          cout << "Organ not found" << endl;
          // new
          return NULL;
      }
      int j = 1*(blood_type == "A") + 2*(blood_type == "B") + 3*(blood_type == "AB") + 4*(blood_type == "O");
      if(j == 0){
          cout << "Blood type not found" << endl;
          // new
          return NULL;
      }
      
      for(int k = 0; k < vertices.size(); k++){
		if(vertices[k].name == city){
			cityfound = true;
        }
	   }
	   
	   if(cityfound == false){
		   cout << "City not found" << endl;
		   return NULL;
	   }
	   
      

      Patient *n = new Patient;
      n->name = name;
      n->survivability = survivability;
      n->time_left = time_left;
      n->organ = i;
      n->blood_type = j;
      n->location = city;
      n->next = NULL;
      n->prev = NULL;
      Patient *x = PatientList[i-1][j-1];
      if(x == NULL){
          PatientList[i-1][j-1] = n;
          return n;
      }
      while(x->next != NULL){
          x = x->next;
      }
      n->prev = x;
      x->next = n;
		
      return n;
  }

Donor* PatientTree::addDonor(string name, string organ, string blood_type, string city){
	bool cityfound = false;
      int i = 1*(organ == "heart") + 2*(organ == "lungs") + 3*(organ == "liver") + 4*(organ == "pancreas")
      + 5*(organ == "kidney") + 6*(organ == "intestines") + 7*(organ == "head");
      if(i == 0){
          cout << "Organ not found" << endl;
          return NULL;
      }
      int j = 1*(blood_type == "A") + 2*(blood_type == "B") + 3*(blood_type == "AB") + 4*(blood_type == "O");
      if(j == 0){
          cout << "Blood type not found" << endl;
          return NULL;
      }

	 for(int k = 0; k < vertices.size(); k++){
		if(vertices[k].name == city){
			cityfound = true;
        }
	   }
	   
	   if(cityfound == false){
		   cout << "City not found" << endl;
		   return NULL;
	   }
	
      Donor *n = new Donor;
      n->name = name;
      n->organ = i;
      n->blood_type = j;
      n->location = city;
      n->next = NULL;
      n->prev = NULL;
      Donor *x = DonorList[i-1][j-1];
      if(x == NULL){
          DonorList[i-1][j-1] = n;
          cout << "Added " << n->name << " to spot " << i-1 << "," << j-1 << endl;
          return n;
      }
      while(x->next != NULL){
          x = x->next;
      }
      n->prev = x;
      x->next = n;

		cout << n->name << endl;
      return n;
  }

void PatientTree::deletePatient(string name){
      for(int i = 0; i < 7; i++){
          for(int j = 0; j < 4; j++){
              Patient *x = PatientList[i][j];
              while(x != NULL){
                  if(x->name == name){
					  if(x->next == NULL and x->prev == NULL){
						  DonorList[i][j] = NULL;
						  delete x;
						  return;
					  }
                      if(x->next == NULL){
                          x->prev->next = NULL;
                          delete x;
                          return;
                      }
                      if(x->prev == NULL){
                          x->next->prev = NULL;
                          PatientList[i][j] = x->next;
                          delete x;
                          return;
                      }
                      else{
                          x->prev->next = x->next;
                          x->next->prev = x->prev;
                          delete x;
                          return;
                      }
                  }
                  x = x->next;
              }
          }
      }
      cout << "patient not found." << endl;
  }

void PatientTree::deleteDonor(string name){
      for(int i = 0; i < 7; i++){
          for(int j = 0; j < 4; j++){
              Donor *x = DonorList[i][j];
              while(x != NULL){
                  if(x->name == name){
					  if(x->next == NULL and x->prev == NULL){
						  DonorList[i][j] = NULL;
						  delete x;
						  return;
					  }
                      if(x->next == NULL){
						  x->prev->next = NULL;
                          delete x;
                          return;
                      }
                      if(x->prev == NULL){
                          x->next->prev = NULL;
                          DonorList[i][j] = x->next;
                          delete x;
                          return;
                      }
                      else{
                          x->prev->next = x->next;
                          x->next->prev = x->prev;
                          delete x;
                          return;
                      }
                  }
                  x = x->next;
              }
          }
      }
      cout << "patient not found." << endl;
  }

void PatientTree::buildPatientList(){
      for(int i = 0; i < 7; i++){
          for(int j = 0; j < 4; j++){
              PatientList[i][j] = 0;
          }
      }
  }

void PatientTree::buildDonorList(){
      for(int i = 0; i < 7; i++){
          for(int j = 0; j < 4; j++){
              DonorList[i][j] = 0;
          }
      }
}

void PatientTree::enqueue(Pair match){ //we can do this bc we've declared push in header
	arrayQueue[queueTail] = match;
	queueTail++;
	queueTail = queueTail % 10;

}

Pair PatientTree::dequeue(){
  Pair match = arrayQueue[queueHead];
  queueHead++;
  queueHead = queueHead % 10;
  return match;
}

bool PatientTree::queueIsFull(){
    if ((queueTail+1)%10 == queueHead){
        return true;
    }
    else{
        return false;
    }
}

bool PatientTree::queueIsEmpty(){
    if (queueHead == queueTail){
        return true;
    }
    else{
        return false;
    }
}

void PatientTree::printMatches(){
    for(int i = queueHead; i < queueTail; i++){
        cout << "Patient: " << arrayQueue[i].patient << " - Donor: " << arrayQueue[i].donor << " - Chance of sucessfull operation: "<< arrayQueue[i].success_rate<< endl;
    }
}


void PatientTree::Operate(){
  Pair operatedPair;
	int successChance = arrayQueue[queueHead].success_rate;
	bool success = (rand() % 100) < successChance;
	if(success == true){
		cout<<arrayQueue[queueHead].patient<<"'s surgery was a success."<<endl;
		operatedPair = dequeue();
    successCount++;
	}
	else{
		cout<<arrayQueue[queueHead].patient<<"'s surgery was a failure."<<endl;
		operatedPair = dequeue();
    failureCount++;
	}
}



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
