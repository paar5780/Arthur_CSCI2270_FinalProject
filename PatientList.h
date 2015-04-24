#ifndef PATIENTLIST_H
#define PATIENTLIST_H

struct Donor{
  std::string name;
  std::string organ;
  std::string blood_type;
  std::string location;

};

struct Patient{
    std::string name;
    std::string organ;
    std::string blood_type;
    int survivability;
    std::string location;
    int time_left;
};

class PatientTree
{

    public:
        PatientTree();
        virtual ~PatientTree();
        void addPatient(std::string name, std::string organ, std::string blood_type, std:: string city, int time_left);
        void addDonor(std::string name, std::string organ, std::string blood_type, std:: string city);
        void deletePatient(std::string name);
        void deleteDonor(std::string name);
        int countPatients();
        int countDonors();
        void printDonors();
        void printPatients();
        void printMatches();
        void Operate();


    protected:

    private:
        void buildPatientList();
        void buildDonorList();
        void buildGraph();
        void findShortestPath();
        void findMatch();
        void chooseMatch();

};

#endif // MOVIETREE_H
