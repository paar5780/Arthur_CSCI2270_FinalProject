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
    arrayQueue = new Pair*[10];

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
  addEdge("Honolulu", "San Fransisco", 5);
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

int PatientTree::Dijkstra(int count, std::string starting, std::string destination){

    int minDistance;
    vertex* minVertex;
    vector <vertex *> solved;

    //set visted to false, except on starting vertex
    for(int i=0; i<vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;
        if(vertices[i].name == starting){
            vertices[i].visited = true;
            vertices[i].distance = 0;
            solved.push_back(&vertices[i]);
        }
    }

    //find destination vertex
    vertex *d = NULL;
    for (int i=0; i<vertices.size(); i++){
        if(vertices[i].name == destination){
            d = &vertices[i];
            break;
        }
    }

    while (d->visited == false){
        minDistance = INT_MAX; //arbitary large number
        for (int i = 0; i < solved.size(); i++){ //for every solved vertex
             for (int j = 0; j < solved[i]->adj.size(); j++){ //for every adjacent vertex
                 if (solved[i]->adj[j].v->visited == false){ //if that adjacent vertex hasn't already been solved (visited)
                    //calculate distance using u.distance and edge weight
                    if (solved[i]->distance + solved[i]->adj[j].weight < solved[i]->adj[j].v->distance){
						//calculate distance to orgin and replace if smaller than existing distance
                        solved[i]->adj[j].v->distance = solved[i]->distance + solved[i]->adj[j].weight;
                        solved[i]->adj[j].v->previous = solved[i];
                    }
                    //find minimum distance and store vertex information
                    if (solved[i]->adj[j].v->distance < minDistance){
                        minDistance = solved[i]->adj[j].v->distance;
                        minVertex = solved[i]->adj[j].v;

                    }
                 }
             }
        }
        //update solved, adding minimum vertex
        solved.push_back(minVertex);
        minVertex->visited = true;

    }
    //find the path using previous pointer, put into a vector
    vertex *vert = minVertex;
    vector <string> path;
    while (vert) {
        path.push_back(vert->name);
        vert = vert->previous;
    }

    cout << minDistance << ","; //print minimum distance
    //return minDistance;

	//print path by going through vector in reverse
	//since the path was added to the vector in reverse in the first place
    for (int i = path.size()-1; i >= 0; i--){
        cout << path[i];
        if (i != 0){
            cout << ",";
        }
    }
    return minDistance;
}


int PatientTree::findShortestDistance(int count, string city1, string city2){
  //check the two cities
  /*bool cont = checkCities(count, city1, city2);
  if (cont == false){
  	return;
  }*/
  //use Dijkstra traverse to find and print the shortest distance
  int distance = Dijkstra(count, city1, city2);
  return distance;
  cout << endl;
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

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (PatientList[i][j] != NULL){
        x = PatientList[i][j]; //head of linked list
        cout << x->name << " : " << organ << " - Blood type " << blood_type << " - " << x->location << " - " << x->survivability << " chance of survival - " << x->time_left << " hours left" << endl;
        //iterate through patients
        while (x->next != NULL){
          x = x->next;
          cout << x->name << " : " << organ << " - Blood type " << blood_type << " - " << x->location << " - " << x->survivability << " chance of survival - " << x->time_left << " hours left" << endl;
        }
    }

  }

}
}

void PatientTree::printDonors(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  Donor* x;
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

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (DonorList[i][j] != NULL){
        x = DonorList[i][j]; //head of linked list
        cout << x->name << " : " << organ << " - Blood type " << blood_type << " - " << x->location << endl;
        //iterate through patients
        while (x->next != NULL){
          x = x->next;
          cout << x->name << " : " << organ << " - Blood type " << blood_type << " - " << x->location << endl;
        }
    }

  }

}
}

Patient* PatientTree::findPatientMatch(Donor* d){
  int js[4];
  for (int k = 0; k < 4; k++){
	js[k] = 0;
  }

  if(d->blood_type==1){
	js[0] = 1;
	js[1] = 3;
  }
  if(d->blood_type==1){
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
  int count = 0;
  int score;
  int time_taken;

  int m = 0;
  while (js[m] != 0){
	Patient* p = PatientList[d->organ][js[m]];
	while (p->next != NULL){
	  count++; //relative time on waiting list
	  time_taken = findShortestDistance(18, p->location, d->location);
	  if (p->time_left >= time_taken){
		score = p->survivability - count;
		if (score > best_score){
		  best_score = score;
		  best = p;
		}
	  }
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

Patient* PatientTree::findDonorMatch(Patient *p){
  int js[4];
  for (int k = 0; k < 4; k++){
	js[k] = 0;
  }

  if(p->blood_type==1){
	js[0] = 1;
	js[1] = 4;
  }
  if(p->blood_type==1){
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

  int m = 0;
  while (js[m] != 0){
	Donor* d = DonorList[p->organ][js[m]];
	while (d->next != NULL){
	  time_taken = findShortestDistance(18, p->location, d->location);
	  if (p->time_left >= time_taken){
		    return d;
        cout << "A suitable donor was found!"
	  }
	}
	m++;
  }
  cout << "No suitable donor was found." << endl;
  return NULL;
}

Patient* PatientTree::addPatient(string name, string organ, string blood_type, string city, int time_left, int survivability){
      int i = 1*(organ == "heart") + 2*(organ == "lungs") + 3*(organ == "liver") + 4*(organ == "pancreas")
      + 5*(organ == "kidney") + 6*(organ == "intestines") + 7*(organ == "head");
      if(i == 0){
          cout << "Organ not found" << endl;
          return;
      }
      int j = 1*(blood_type == "A") + 2*(blood_type == "B") + 3*(blood_type == "AB") + 4*(blood_type == "O");
      if(j == 0){
          cout << "Blood type not found" << endl;
          return;
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
      Patient *x = PatientList[i][j];
      if(x == NULL){
          PatientList[i][j] = n;
          return;
      }
      while(x->next != NULL){
          x = x->next;
      }
      n->prev = x;
      x->next = n;

      return n;
  }

Donor* PatientTree::addDonor(string name, string organ, string blood_type, string city){
      int i = 1*(organ == "heart") + 2*(organ == "lungs") + 3*(organ == "liver") + 4*(organ == "pancreas")
      + 5*(organ == "kidney") + 6*(organ == "intestines") + 7*(organ == "head");
      if(i == 0){
          cout << "Organ not found" << endl;
          return;
      }
      int j = 1*(blood_type == "A") + 2*(blood_type == "B") + 3*(blood_type == "AB") + 4*(blood_type == "O");
      if(j == 0){
          cout << "Blood type not found" << endl;
          return;
      }

      Donor *n = new Donor;
      n->name = name;
      n->organ = i;
      n->blood_type = j;
      n->location = city;
      n->next = NULL;
      n->prev = NULL;
      Donor *x = DonorList[i][j];
      if(x == NULL){
          DonorList[i][j] = n;
          cout << "Added " << n->name << " to spot " << i << "," << j << endl;
          return;
      }
      while(x->next != NULL){
          x = x->next;
      }
      n->prev = x;
      x->next = n;

      return n;
  }

void PatientTree::deletePatient(string name){
      for(int i = 0; i < 7; i++){
          for(int j = 0; j < 4; j++){
              Patient *x = PatientList[i][j];
              while(x != NULL){
                  if(x->name == name){
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

void PatientTree::enqueue(Pair* match){ //we can do this bc we've declared push in header
	arrayQueue[queueTail] = word;
	queueTail++;
	queueTail = queueTail % 10;

}

Pair* PatientTree::dequeue(){
  Pair* match = arrayQueue[queueHead];
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

void PatientList::printMatches(){
    for(int i = queueHead; i < queueTail; i++){
        cout << "Patient: " << arrayQueue[i]->patient << " - Donor: " << arrayQueue[i]->donor << " - Chance of sucessfull operation: "<< arrayQueue[i]->survivability << endl;
    }
}


void PatientTree::Operate(){
  Pair* operatedPair;
	int successChance = arrayQueue[queueHead]->survivability;
	bool success = (rand() % 100) < successChance;
	if(success == true){
		cout<<arrayQueue[queueHead]->name<<"'s surgery was a success."<<endl;
		operatedPair = dequeue();
    successCount++;
	}
	else{
		cout<<arrayQueue[queueHead]->name<<"'s surgery was a failure."<<endl;
		operatedPair = dequeue();
    failureCount++;
	}
}



int main(){

  successCount = 0;
	failureCount = 0;

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

		myTree.addPatient(name, organ, blood_type, city, time, successRate);

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
    int rate;
    string str_rate;
    getline(cin, str_rate);
    rate = atoi(str_rate.c_str());

    cout << "Enter time left:" << endl;
    int time_left;
    string str_time_left;
    getline(cin, str_time_left);
    time_left = atoi(str_time_left.c_str());

    cout << "Enter location:" << endl;
    string location;
    getline(cin, location);

    myTree.addPatient(name, organ, blood_type, location, time_left, rate);


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

    myTree.addDonor(name, organ, blood_type, location);

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
    //printMatches();
  }

  if (answer == 10){
    //Operate();
  }

  if (answer == 11){
	running = false;
    cout << "Goodbye!" << endl;
    return 0;
  }
}
}
