/**
 * File:   atekade1_phone_directory.cpp
 * Author: Aniruddha Tekade
 *
 * Created on February 11, 2017, 2:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <c++/5/istream>

using namespace std;

class PhoneDirectory {
public:
    string firstName;
    string lastName;
    string contactNumber;
};

void create(char *);
void sort_contact();
void delete_contact(char *);
void search(char *);
void insert(char *, char *);
void printVector();
int binarySearchOnRecords(vector<PhoneDirectory>, char *);
void randomizeRecords(vector<PhoneDirectory>);
int generateRandom(int low, int high);
void randomisedQuickSort(vector<PhoneDirectory>, int, int);
int makePartitions(vector<PhoneDirectory> &, int low, int high);

/**
 * Defining vector to hold the objects of the class 'PhoneDirectory'
 */
vector<PhoneDirectory> recordVector;

int main(int argc, char **argv) {
    string fileName = "test_input.txt";//argv[1];
    char *fp = new char[fileName.length()+1];
    strcpy(fp, fileName.c_str());
    create(fp);

    // infinite loop;

    while (1) {
        int choice = 0;
        cout << "\n1) sort_contact\n2) search\n3) delete\n4) insert\n5) Exit\nEnter the choice : ";
        cin >> choice;
        while (getchar() != '\n');
        switch (choice) {
            case 1:
            {
                sort_contact();
                break;
            }
            case 2:
            {
                string searchInput;
                cout << "\nEnter the Name -> ";
                std::getline(cin, searchInput);
                char *searchName = new char[searchInput.length() + 1];
                strcpy(searchName, searchInput.c_str());
                search(searchName);
                break;
            }
            case 3:
            {
                string deleteInput;
                cout << "\nEnter the Name -> ";
                getline(cin, deleteInput);
                char *deleteName = new char [deleteInput.length() + 1];
                strcpy(deleteName, deleteInput.c_str());
                delete_contact(deleteName);
                break;
            }
            case 4:
            {
                string insertInput;
                cout << "\nEnter the Name -> ";
                getline(cin, insertInput);
                char *insertName = new char[insertInput.length() + 1];
                char *phoneNumber = '\0';
                strcpy(insertName, insertInput.c_str());
                insert(insertName, phoneNumber);
                break;
            }
            case 5:
            {
                exit(0);
                break;
            }
            default:
            {
                cout << "\nInvalid choice!\n";
                break;
            }
        };
    }
    printf("\nI'm reading the file. . .\n");
    return 0;
}

void create(char *name) {
    string inputFile = name;
    cout << "This is create function!\n";

    ifstream reader;
    reader.open(inputFile);

    if (!reader) {
        cout << "File read failure!" << endl;
        return;
    }

    //    int counter = 0;
    string currentLine;
    while (reader.good()) {
        /**
         * Reading file untill EOF line by line
         * Tokenizing into three pieces
         * Setting fields of the class PhoneDirectory
         * Storing the objects into the Vector (Know nothing about how vector works!!!
         * N.B.: This logic is reading ONE EXTRA line which is undesirable. It shows -1 for all fields.
         */
        getline(reader, currentLine);

        if (currentLine.size() < 2)
            continue;
        int posOne = currentLine.find(" ");
        int posTwo = currentLine.find(",");
        int posThree = currentLine.find("\n");
        string fName = currentLine.substr(0, posOne);
        string lName = currentLine.substr(posOne + 1, posTwo - posOne - 1);
        string contactNumber = currentLine.substr(posTwo + 2);
        cout << "First Name : " << fName << "\n";
        cout << "Last Name : " << lName << "\n";
        cout << "Contact Number : " << contactNumber << "\n";

        /**
         * Creating object of the PhoneDirectory class as 'record'
         */
        PhoneDirectory record;

        /**
         * Setting fields of the 'record'
         */
        record.firstName = fName;
        record.lastName = lName;
        record.contactNumber = contactNumber;

        /**
         * Storing the objects into the Vector (Know nothing about how vector works!!!
         */
        recordVector.push_back(record);
    }
    //sort_contact();
    reader.close();
}

void sort_contact() {
    randomizeRecords(recordVector);
    randomisedQuickSort(recordVector, 0, recordVector.size()-1);
}

void randomizeRecords(std::vector<PhoneDirectory> recordVector)
{
    int length = recordVector.size();

    for (int i = 0; i < length-1; ++i)
    {
        //swap(recordVector, i, generateRandom(i+1, length-1));
        std::swap(recordVector[i], recordVector[generateRandom(i+1, length-1)]);
    }

    printVector();
}

int generateRandom(int low, int high)
{
    srand(low);
    int gen = 0;
    gen = rand() % (high - low + 1) + low;
    return gen;
}

void randomisedQuickSort(vector<PhoneDirectory> recordVector,int low, int high)
{
    if (low >= high) return;

    int p = makePartitions(recordVector, low, high);

    randomisedQuickSort(recordVector, low, p-1);
    randomisedQuickSort(recordVector, p+1, high);
}


int makePartitions(std::vector<PhoneDirectory> & refRecordVector, int low, int high)
{
    int partitionNumber = low;
    for (int i = partitionNumber+1; i <= high; ++i)
    {
        if (refRecordVector[i].firstName < refRecordVector[partitionNumber].firstName)
        {
            std::swap(refRecordVector[i], refRecordVector[partitionNumber]);
            partitionNumber = partitionNumber + 1;
        }
    }
    return partitionNumber;
}

void search(char *name) {
    sort_contact();
    binarySearchOnRecords(recordVector, name);
}

int binarySearchOnRecords(std::vector<PhoneDirectory> recordVector, char *name) {
    //use strcmp option
    int mid=0;
    int left = 0;
    int right = recordVector.size()-1;
    string inputString = name;
    int posOne = inputString.find(" ");
    int posTwo = inputString.find("\n");
    string firstPartOfString = inputString.substr(0, posOne);
    string secondPartOfString = inputString.substr(posOne+1);
    int status = 0;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        int firstNameComparison, lastNameComparison, contactNumberComparison;
        firstNameComparison = firstPartOfString.compare(recordVector[mid].firstName);
        lastNameComparison = secondPartOfString.compare(recordVector[mid].lastName);
        if (firstNameComparison > 0)
        {
            left = mid + 1;
        }
        else if (firstNameComparison < 0)
        {
            right = mid - 1;
        }
        else
        {
            if (firstNameComparison == 0)
            {
                /*First name found...*/
                if (lastNameComparison == 0)
                {
                    /*Second name found...*/
                    //auto iter = recordVector.begin() + mid;
                    cout << "\n" << recordVector[mid].firstName<<" "<<recordVector[mid].lastName<<", "<<recordVector[mid].contactNumber<<"\n";
                    status = 1;
                    break;
                } else {
                    cout << "\nName not found";
                    status = 0;
                    break;
                }
            }
        }
    }
    return status;
}

/**
 *
 * You can NOT have delete(char* name); function in C++, as "delete" is a keyword.
 * Hence using the function name as "delete_record();"
 */

void insert(char *name, char *phoneNumber) {
    string inputString = name;
    int posOne = inputString.find(" ");
    int posTwo = inputString.find(",");
    int posThree = inputString.find("\n");
    string fName = inputString.substr(0, posOne);
    string lName = inputString.substr(posOne + 1, posTwo - posOne - 1);
    string contactNumber = inputString.substr(posTwo + 2);
    cout << "In BS : " << fName <<" " <<lName;
    cout << "First Name : " << fName << "\n";
    cout << "Last Name : " << lName << "\n";
    cout << "Contact Number : " << contactNumber << "\n";
    /**
     * Creating object of the PhoneDirectory class as 'record'
     */
    PhoneDirectory record;

    /**
     * Setting fields of the 'record'
     */
    record.firstName = fName;
    record.lastName = lName;
    record.contactNumber = contactNumber;

    /**
     * Storing the objects into the Vector (Know nothing about how vector works!!!
     */
    recordVector.push_back(record);
}

void delete_contact(char *name) {
    string inputString = name;
    int posOne = inputString.find(" ");
    int posTwo = inputString.find(",");
    int posThree = inputString.find("\n");
    string fName = inputString.substr(0, posOne);
    string lName = inputString.substr(posOne + 1, posTwo - posOne - 1);
    string contactNumber = inputString.substr(posTwo + 2);
    cout << "First Name : " << fName << "\n";
    cout << "Last Name : " << lName << "\n";
    cout << "Contact Number : " << contactNumber << "\n";

    bool deleteStatus = false;
    for (int i = 0; i < recordVector.size(); i++) {
        if (recordVector[i].firstName == fName) {
            if (recordVector[i].lastName == lName) {
                auto iter = recordVector.begin() + i;
                recordVector.erase(iter);
                deleteStatus = true;
            }
        }
    }
    if (deleteStatus) {
        for (int i = 0; i < recordVector.size(); i++) {
            cout << "\n" << recordVector[i].firstName << " " << recordVector[i].lastName << ", " << recordVector[i].contactNumber;
        }
        cout << "\n";
    } else {
        cout << "\nName not found\n";
    }


}

void printVector()
{
    auto iter = recordVector.begin();
    for (; iter != recordVector.end(); ++iter)
    {
        cout << "\n" << iter->firstName << " " << iter->lastName << ", " << iter->contactNumber;
    }

    if (recordVector.size() > 0)
    {
        cout << endl;
    }
}
