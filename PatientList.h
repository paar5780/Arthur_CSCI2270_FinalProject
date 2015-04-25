#ifndef PATIENTLIST_H
#define PATIENTLIST_H

struct Donor{
    std::string name;
    std::string organ;
    std::string blood_type;
    std::string location;
    *Donor next;
    *Donor prev;
};

struct Patient{
    std::string name;
    std::string organ;
    std::string blood_type;
    int survivability;
    std::string location;
    int time_left;
    *Patient next;
    *Patient prev;
};


class PatientTree
{

    public:
        PatientTree();
        virtual ~PatientTree();
        Patient *PatientList[7][4];
        Donor *DonorList[7][4];
        void addPatient(std::string name, std::string organ, std::string blood_type, std:: string city, int time_left);
        void addDonor(std::string name, std::string organ, std::string blood_type, std:: string city);
        void deletePatient(std::string name);
        void deleteDonor(std::string name);
        int countPatients();
        int countDonors();
        void printDonors();
        void printPatients();
        void printMatches(); //prints all of the matches with patients and donors that have been made
        void Operate(); //operates and outputs results


    protected:

    private:
        void addVertex(std::string city);
        void addEdge(std::string starting_city, std::string ending_city, int weight);
        void buildPatientList(); //builds empty patient list
        void buildDonorList(); //builds empty donor list
        void buildGraph(); //builds graph with cities
        void findShortestDistance(std::string starting_city, std::string ending_city); //finds shortest path between two cities
        void findMatch(); //finds all possible patient donor matches
        void chooseMatch(); //chooses best patient doner match
        void Dijkstra(int count, std::string starting, std::string destination){

};
#endif // MOVIETREE_H
