# Arthur_CSCI2270_FinalProject
Data Structures project

Project Summary:
Our project matches organ donors to patients who need transplants. The program starts with a list of 100 patients and 0 donors. Each patient has the following attributes: organ needed, blood type, survivability (how likely it is they will survive the operation), time left (how many hours they have to get the organ before they pass away), and location (what city in the US they're in). The donor has the same attributes, minus the suvivability and time left. The user can input and delete a patient or donor. The program searches through all possible matches with the same organ and blood type. It calculates a score for each patient based on the time the patient has been waiting (aka their location in the list) and the patient's survivability. However, it will only look at patients who live close enough to the donor such that the organ can be transplanted to the patient before the patient passes away. A graph of US cities is used to determine this and a searching algoritm determines the shorest path between the donor's city and the patient's city. If a match is found when a donor or patient is added, the pair will be added to a queue. The user can then select "Operate", which will operate on the first pair in the queue and determine if the operation was a success depending on the patient's liklihood of survivability. The user can print the matches waiting to be operated on. They can also print the patients and donors waiting for a match. The user can also count the patients and the donors waiting for a match. 

How to Run:
There are 11 options the user can select.

1. Add a patient: When prompted, the user will enter the patient's name, organ needed, blood type, chance of survivability, time left, and location. The name should be the patient's last name. The organ needed can be heart, lungs, liver, pancreas, kidney, intestines, or head, and must not be capitalized. The blood type can be O, A, B, or AB, and must be capitalized. Chance of survivability should be between 0 and 100. Time left should be in hours. The location can be one of the following citites: New York City, Philadelphia, Atlanta, Denver, San Francisco, Dallas, Phoenix, Seattle, Honolulu, Chicago, Detroit, Los Angeles, Houston, Miami, Memphis, Cleveland, or Boise, and must be captialized. For example: "Smith", "heart", "O", "50", "Denver".

2. Add a donor: Same as adding a patient, but the user will not be promted for survivability or time left since those attributes do not apply to donors. For example: "Jackson", "liver", "AB", "Boston".

3. Delete a patient: User will be promted for the patient's name. It should be their last name. For example: "Johnson".

4. Delete a donor: Same as delete patient. For example: "Benson".

5. Count patients: This will count the number of patients waiting and output the number. It does not require any input arguments. 

6. Count donors: This will count the number of donors waiting and output the number. It does not require any input arguments. 

7. Print patients: This will print all of the patients in the waiting list and all of their attributes. It does not require any input arguments. 

8. Print donors: This will print all of the donors waiting for a patient match and all of their attributes. It does not require any input arguments. 

9. Print matches: This will print all of the patient - donor matches that have been paired but not yet operated on, and the liklihood that the operation will be a success. It does not require any input arguments.

10. Operate: This will "operate" on a donor - patient match and will determine whether or not the operation was a sucess using a random function and the patient's liklihood of survivability. It does not require any input arguments. 

Dependencies: 
The text file containing the patients must be including in the appropriate folder so that the program can access it.

System Requirements:
None.

Group Members:
Paige Arthur
Evan Sidrow
Michael Feller

Contributors:
Andrew Dudney

Open Issues / Bugs:
Features we would like:
1. Make it so the user can add cities (with edges!) to the graph.
2. Allow the organs, locations, and blood types to not be case sensitive
3. Make it so that as time passes (aka as operations are done), time passes and the patients' "time left" runs out.

Bugs:
1. Sometimes the print matches function doesn't work and we're not sure why. It works most of the time but sometimes it won't print anything.
