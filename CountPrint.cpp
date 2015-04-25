#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <string>
#include "PatientList.h"


using namespace std;

//MovieTree::MovieTree(char *filename)
PatientList::PatientList()
{
    //constructor
    for(int i = 0; i < 7; i++){
      for(int j = 0; j < 4; j++){
        PatientList[i][j] = NULL;
        DonorList[i][j] = NULL;
      }
    }
}


void addVertex(std::string n){
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

void addEdge(std::string v1, std::string v2, int weight){

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


void PatientList::buildGraph(){
  Graph g;
  g.addVertex("Boston");
	g.addVertex("New York City");
	g.addVertex("Philadelphia");
	g.addVertex("Atlanta");
	g.addVertex("Denver");
	g.addVertex("San Francisco");
	g.addVertex("Dallas");
	g.addVertex("Phoenix");
  g.addVertex("Seattle");
  g.addVertex("Honolulu");
  g.addVertex("Chicago");
  g.addVertex("Detroit");
  g.addVertex("Los Angeles");
  g.addVertex("Houston");
  g.addVertex("Miami");
  g.addVertex("Memphis");
  g.addVertex("Cleveland");
  g.addVertex("Boise");
  //edge written to be undirected
  g.addEdge("Seattle", "San Francisco", 2);
  g.addEdge("Seattle", "Phoenix", 3);
  g.addEdge("Seattle", "New York City", 6);
  g.addEdge("San Francisco", "New York City", 6);
  g.addEdge("San Francisco", "Phoenix", 2);
  g.addEdge("San Francisco", "Boston", 6);
  g.addEdge("San Francisco", "Denver", 3);
  g.addEdge("Boise", "Seattle", 1);
  g.addEdge("Boise", "Denver", 2);
  g.addEdge("Los Angeles", "San Francisco", 1);
  g.addEdge("Los Angeles", "Denver", 2);
  g.addEdge("Los Angeles", "Dallas", 3);
  g.addEdge("Los Angeles", "Miami", 5);
  g.addEdge("Los Angeles", "New York", 6);
  g.addEdge("Los Angeles", "Boston", 6);
  g.addEdge("Denver", "Phoenix", 2);
  g.addEdge("Denver", "Dallas", 2);
  g.addEdge("Denver", "New York", 4);
  g.addEdge("Honolulu", "San Fransisco", 5);
  g.addEdge("Dallas", "Memphis", 1);
  g.addEdge("Dallas", "Houston", 1);
  g.addEdge("Dallas", "Atlanta", 2);
  g.addEdge("Houston", "Miami", 3);
  g.addEdge("Houston", "Philadelphia", 3);
  g.addEdge("Houston", "Chicago", 3);
  g.addEdge("Memphis", "Atlanta", 1);
  g.addEdge("Memphis", "Cleveland", 4);
  g.addEdge("Cleveland", "Detroit", 1);
  g.addEdge("Cleveland", "Chicago", 1);
  g.addEdge("Detroit", "Chicago", 1);
  g.addEdge("Detroit", "New York City", 2);
  g.addEdge("Detroit", "Philadelphia", 2);
  g.addEdge("Detroit", "Denver", 3);
  g.addEdge("Miami", "Los Angeles", 5);
  g.addEdge("Miami", "Atlanta", 2);
  g.addEdge("Atlanta", "Philadelphia", 2);
  g.addEdge("Philadelpha", "Boston", 1);
  g.addEdge("Boston", "New York City", 1);
}

int Dijkstra(int count, std::string starting, std::string destination){

    int minDistance;
    vertex* minVertex;
    vertex* minVertexPrev;
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
                        minVertexPrev = solved[i];
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
    return minDistance;

	//print path by going through vector in reverse
	//since the path was added to the vector in reverse in the first place
    for (int i = path.size()-1; i >= 0; i--){
        cout << path[i];
        if (i != 0){
            cout << ",";
        }
    }
}


int findShortestDistance(int count, string city1, string city2){
  //check the two cities
  bool cont = checkCities(count, city1, city2);
  if (cont == false){
  	return;
  }
  //use Dijkstra traverse to find and print the shortest distance
  int distance = Dijkstra(count, city1, city2);
  return distance;
  cout << endl;
}

int countPatients(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  node* x;
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

int countDonors(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  node* x;
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

void printPatients(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  node* x;

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (PatientList[i][j] != NULL){
        x = PatientList[i][j]; //head of linked list
        cout << x->name << " : " << x->organ << " - Blood type " << x->blood_type << " - " << x->location << " - " << x->surviability << " chance of survival - " << x->time_left << " hours left" << endl;
        //iterate through patients
        while (x->next != NULL){
          x = x->next;
          cout << x->name << " : " << x->organ << " - Blood type " << x->blood_type << " - " << x->location << " - " << x->surviability << " chance of survival - " << x->time_left << " hours left" << endl;
        }
    }

  }

}

void printDonors(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB
  node* x;

  //iterate through organs
  for (int i = 0; i < 7; i++){
    //iterate through blood types
    for (int j = 0; j < 4; j++){
      if (DonorList[i][j] != NULL){
        x = DonorList[i][j]; //head of linked list
        cout << x->name << " : " << x->organ << " - Blood type " << x->blood_type << " - " << x->location << endl;
        //iterate through patients
        while (x->next != NULL){
          x = x->next;
          cout << x->name << " : " << x->organ << " - Blood type " << x->blood_type << " - " << x->location << endl;
        }
    }

  }

}

Patient* findPatientMatch(Donor* d){
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
  node* best = NULL;
  int count = 0;
  int score;
  int time_taken;

  int m = 0;
  while (int js[m] != 0){
    Patient* p = PatientList[d->organ][js[m]];
    while (p->next != NULL){
      count++; //relative time on waiting list
      time_taken = findShortestDistance(p->location, d->location);
      if (p->time_left >= time_taken){
        score = survivability - count;
        if (score > best_score){
          best_score = score;
          best = p;
        }
      }
    }
  }

  void PatientTree::addPatient(string name, string organ, string blood_type, string city, int time_left, int survivability){
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
  }

  void PatientTree::addDonor(string name, string organ, string blood_type, string city){
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

}
