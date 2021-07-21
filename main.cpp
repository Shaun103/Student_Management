#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;


class Student {
    friend std::ostream &operator<<(std::ostream &os, const Student &p);  // can place anywhere - always overload
    friend std::istream &operator>> (std::istream &in, Student &rhs);
private:
    std::string first_name;
    std::string last_name;
    std::string major;
    double section_number;
public:
    Student() = default;
    Student(std::string first_name, std::string last_name, std::string major, double section_number) 
        : first_name{first_name}, last_name{last_name}, major{major}, section_number{section_number} 
        {};

    bool operator<<(const Student &rhs) const {          // always overload
        return this->section_number < rhs.section_number;
    }

    bool operator==(const Student &rhs) const {
        return (this->first_name == rhs.first_name);    // always overload
    }

    void set_first_name(std::string first_name) {
        this->first_name = first_name; 
    }

    std::string get_first_name() { 
        return first_name; 
    }

    void set_last_name(std::string last_name) {
        this->last_name = last_name; 
    }

    std::string get_last_name(std::string last_name) {
        return last_name; 
    }

    void set_major(std::string major) {
        this->major = major; 
    }

    std::string get_major(std::string major) { 
        return major; 
    }

    void set_section_number(int section_number) { 
        this->section_number; 
    }

    int get_section_number(int section_number) { 
        return section_number; 
    }
};

std::ostream &operator<<(std::ostream &os, const Student &p) {
    os << " First Name: " << p.first_name << " : " 
        << " Last Name: " << p.last_name << " : " 
        << " Major: " << p.major << " : " 
        << " Section number: " << p.section_number;
    return os;
}

// std::istream &operator >> (std::istream &in, Student &rhs){
//     int *buff = new int;
//     in >> buff;

//     rhs = Mystring {buff};
//     delete [] buff;
//     return in;
// }

int menu(){

    int menuChoice{0}; 
    std::cout << "\nPlease select a number from the menu: " << std::endl;
    std::cout << "1: Add Records" << std::endl;
    std::cout << "2: List Records" << std::endl;
    std::cout << "3: Modify Records" << std::endl;
    std::cout << "4: Delete Records" << std::endl;
    std::cout << "5: Print Records" << std::endl;
    std::cout << "6: Exit Program" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "Select Your Choice :=>" << std::endl;
    std::cin >> menuChoice;

    return menuChoice;
}

void addRecords(std::vector<Student> &vec){

    std::string first_name{}, last_name, major;
    double section_number{};

    cin.clear();
    cin.sync();

    std::cout << "\nPlease enter students first name: " << std::endl;
    std::getline(std::cin, first_name);
    std::cout << "Please enter students last name: " << std::endl;
    std::getline(std::cin, last_name);
    std::cout << "Please enter students major: " << std::endl;
    std::getline(std::cin, major);
    std::cout << "Please enter students section number: " << std::endl;
    std::cin >> section_number;

    Student temp {first_name, last_name, major, section_number};    // making a temp to add to vector

    vec.push_back(temp); // adding to vector 
}

// template function to display any vector
template <typename T>
void displayAllRecords(const std::vector<T> &lem) {
    std::cout << "\n[ ";
    for (const auto &elem: lem)
        std::cout << "\n " << elem << " ";
    std::cout <<  "\n ]"<< std::endl;
}

// Creates file with student records
template <typename T>
void printAllRecords(const std::vector<T> &lem) {

    ofstream MyFile("Student_Records_Data.txt");

    MyFile << "=== Students Data ===" << endl;

    MyFile << "[ ";
    for (const auto &elem: lem)
        MyFile << "\n" << elem << " ";
    MyFile <<  "\n]" << std::endl;

    std::cout << "\n === RECORDS PRINTED === \n";
    std::cout << "\n";

    MyFile.close();  // Close the file
}

void modifyRecords(std::vector<Student> &vec) {
    // finds and deletes object to modify
    std::string myName;
    
    std::cout << "\nName of record to delete: " << std::endl;
    std::cin >> myName;

    auto iter = find_if(vec.begin(), vec.end(), [&](Student &s){ 
        return s.get_first_name() == myName; 
    }); 
    
    if (iter != vec.end()) { 
        vec.erase(iter); 
    } 

    // Recreates the object
    std::string first_name{}, last_name, major;
    double section_number{};

    std::cout << "\nPlease enter students first name: " << std::endl;
    std::cin >> first_name;
    std::cout << "Please enter students last name: " << std::endl;
    std::cin >> last_name;
    std::cout << "Please enter students major: " << std::endl;
    std::cin >> major;
    std::cout << "Please enter students section number: " << std::endl;
    std::cin >> section_number;

    Student temp {first_name, last_name, major, section_number};    // making a temp to add to vector

    vec.push_back(temp); // adding to vector
}

/*************************************************************************************************************/
// // StackOverFlow Question - multiple answers

// int delete_record(std::vector<Student> &vec){
//     std::string myName;
//     std::cout << "\nName of record to delete: " << std::endl;
//     std::cin >> myName;

//     auto iter = find_if(vec.begin(), vec.end(), [&](Student &s){ return s.get_first_name() == myName; }); 

//      if (iter != vec.end()){
//          vec.erase(iter); 
//      } else 
//          std::cout << "Student not found.." << std::endl;
            

//         if (s.get_first_name() != myName){
//             std::cout << "Student not found.." << std::endl;
//         } else
//             return s.get_first_name() == myName;
//         });

//         if (iter != vec.end())
//             vec.erase(iter);     
// }

void delete_record(std::vector<Student> &vec){
    std::string myName;
    std::cout << "\nName of record to delete: " << std::endl;
    std::cin >> myName;

    auto iter = std::remove_if(vec.begin(), vec.end(), [&](Student &s) { return s.get_first_name() == myName; }); 
        // vec.erase(iter, vec.end()); // does the same as the bottom code
    
    if (iter != vec.end()){
        std::cout << " DELETED..."<< *iter << std::endl;
        vec.erase(iter); 
    } else {
        std::cout << "Student not found.." << std::endl;
    }
}

/*Or, in C++20:*/  
// void delete_record(std::vector<Student> &vec){

//   auto iter = std::remove_if(vec.begin(), vec.end(), [&](Student &s) { return s.get_first_name() == myName; });
//
//     erase_if(vec, [&](Student &s){ 
//         return s.get_first_name() == myName; 
//     }); 
// }
/*************************************************************************************************************/

int main () {
    
    bool toContinue = true;
    std::vector<Student> vec; // vector to hold students

    std::cout << "Ruler" << std::endl;
    std::cout << "123456789123456789123456789123456789123456789" << std::endl;  

    do {
        system("cls");
        std::cout << "=== View the Records in the Database ===";
        std::cout << "\n";

        switch (menu()) {
            case 1:
                system("cls");
                std::cout << "MENU: Add Records";
                addRecords(vec);
                break;
            case 2:
                system("cls");
                std::cout << "MENU: List Records";
                displayAllRecords(vec);
                system("pause");
                break;
            case 3:
                system("cls");
                std::cout << "MENU: Modify Records";
                modifyRecords(vec);
                break;
            case 4:
                system("cls");
                std::cout << "MENU: Delete Records";
                delete_record(vec);
                system("pause");
                break;
            case 5:
                system("cls");
                std::cout << "MENU: Print Records ";
                printAllRecords(vec);
                system("pause");
                break;
            case 6:
                system("cls");
                cout << "\n === THANK YOU FOR USING THIS SOFTWARE ===";
                cout << "\n ..Terminating program" << endl;
                toContinue = false;
                break;
            default: 
                std::cout << "You did not select an option from the menu..." << std::endl;
            }
    } while (toContinue != false); 

    system("pause");
    return 0; 
} 