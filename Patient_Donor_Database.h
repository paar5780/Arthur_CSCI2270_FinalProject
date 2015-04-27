#ifndef PATIENTLIST_H
#define PATIENTLIST_H


//heart = 1
//lungs = 2
//liver = 3
//pancreas = 4
//kindey = 5
//intestines = 6
//head = 7

//A = 1
//B = 2
//AB = 3
//O = 4

struct Donor{
    std::string name;
    int organ;
    int blood_type;
    std::string location;
    Donor* next;
    Donor* prev;
};

struct Patient{
    std::string name;
    int organ;
    int blood_type;
    int survivability;
    std::string location;
    int time_left;
    Patient* next;
    Patient* prev;
};

struct Pair{
  std::string patient;
  std::string donor;
  int success_rate;
};

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct queueVertex{
	int edges;
	int distance;
	std::vector<vertex> path;
};

struct vertex{
	vertex* previous;
	bool visited; //has the vertex been visited?
	int ID; //what district does the vertex belong to?
	int numEdge; //how many edges separate the vertex from the starting vertex?
	int distance; //how far  is the vertec from the starting vertex?
	std::string path[100]; //what is the path between the vertex and the starting vertex?
  std::string name; //what is the name of the vertex?
  std::vector<adjVertex> adj; //what are the adjacent vertices to the vertex?
  std::vector<queueVertex> que; //what are the edges, distance, and path to start vertex?
};


class PatientTree
{

    public:
        PatientTree();
        virtual ~PatientTree();
        Patient *PatientList[7][4];
        Donor *DonorList[7][4];
        Patient* addPatient(std::string name, std::string organ, std::string blood_type, std:: string city, int time_left, int survivability);
        Donor* addDonor(std::string name, std::string organ, std::string blood_type, std:: string city);
        void deletePatient(std::string name);
        void deleteDonor(std::string name);
        int countPatients();
        int countDonors();
        void printDonors();
        void printPatients();
        void printMatches(); //prints all of the matches with patients and donors that have been made
        void Operate(); //operates and outputs results
		void buildGraph(); //builds graph with cities
		void buildPatientList(); //builds empty patient list
        void buildDonorList(); //builds empty donor list
        void enqueue(Pair);
        Pair dequeue();
        bool queueIsFull();
        bool queueIsEmpty();

        int queueSize;
        int queueHead;
        int queueTail;
        int successCount;
      	int failureCount;
      	Pair arrayQueue[10];
		Patient* findPatientMatch(Donor*); //finds all possible patient donor matches
        Donor* findDonorMatch(Patient*);

    protected:

    private:
        std::vector<vertex> vertices;

        void addVertex(std::string city);
        void addEdge(std::string starting_city, std::string ending_city, int weight);


        int findShortestDistance(std::string starting_city, std::string ending_city); //finds shortest path between two cities

        void chooseMatch(); //chooses best patient doner match
        int Dijkstra(std::string starting, std::string destination);



};
#endif // MOVIETREE_H
