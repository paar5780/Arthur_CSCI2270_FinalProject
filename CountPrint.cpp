#include <iostream>
#include <fstream>
#include <sstream>
#include "PatientList.h"


using namespace std;

//MovieTree::MovieTree(char *filename)
PatientList::PatientList()
{
    //constructor

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
  g.addVertex("Honolulu")
  //edge written to be undirected
  g.addEdge("Boston", "New York City", 2);
	g.addEdge("Boston", "Philadelphia", 5);
	g.addEdge("New York City", "Philadelpha", 1);
	g.addEdge("New York City", "Atlanta", 10);
	g.addEdge("Denver", "Atlanta", 11);
	g.addEdge("Boston", "San Francisco", 20);
	g.addEdge("Dallas", "Denver", 7);
	g.addEdge("Denver", "Phoenix", 5);
	g.addEdge("San Francisco", "Seattle", 4);
	g.addEdge("New York City", "Seattle", 18);
	g.addEdge("Boston", "Seattle", 19);
	g.addEdge("Honolulu", "San Francisco", 25);
	g.addEdge("Dallas", "Phoenix", 7);
	g.addEdge("Seattle", "Denver", 9);
}

void Dijkstra(int count, std::string starting, std::string destination){

    int minDistance;
    vertex* minVertex;
    vertex* minVertexPrev;
    vector <vertex *> solved;

    //set visted to false, except on starting vertex
    for(int i=0; i<vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance = 999999999;
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
        minDistance = 99999999; //arbitary large number
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

	//print path by going through vector in reverse
	//since the path was added to the vector in reverse in the first place
    for (int i = path.size()-1; i >= 0; i--){
        cout << path[i];
        if (i != 0){
            cout << ",";
        }
    }
}


void findShortestDistance(int count, string city1, string city2){
  //check the two cities
  bool cont = checkCities(count, city1, city2);
  if (cont == false){
  	return;
  }
  //use Dijkstra traverse to find and print the shortest distance
  Dijkstra(count, city1, city2);
  cout << endl;
}

int countPatients(){
  //organs: heart, kidney, liver, lungs, pancreas, intestines, head
  //blood tyes: O, A, B, AB

  Patient* patientList[4] //array of pointers to head nodes of linked list



  for (int o = 0; o < 6; o++){

  }

}

int countDonors(){

}

void printPatients(){

}

void printDonors(){

}
