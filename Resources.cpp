// Resources - Constructor and Destructor
// resources.cpp

#include <iostream>
using namespace std;

class Student {
    int no;         // Student number.
    float* grade;   // Pointer.
    int ng;         // Number of grades.
public:
    Student();                          // Default constructor.
    Student(int sn);                       // 1 arg constructor.
    Student(int sn, const float* g, int ng_);    // 3 arg constructor.
    ~Student();                         // Destructor
    void display() const;
};

// Default constructor:
// The no - argument constructor places the object in a safe empty state.

Student::Student() {
    no = 0;
    ng = 0;
    grade = nullptr;
}


// 1 arg constructor:

Student::Student(int sn) {
    float g[] = { 0.0f };       // Default setting.
    grade = nullptr;            // Ensure set to nullptr.
    *this = Student(sn, g, 0);  // Set.
}


// 3 arg constructor
// The three - argument constructor allocates dynamic memory for the resource only if the data received is valid.

Student::Student(int sn, const float* g, int ng_) {
    bool valid = sn > 0 && g != nullptr && ng_ >= 0;
    
    // Check if incoming grades are valid:
    if (valid)
        for (int i = 0; i < ng_ && valid; i++)
            valid = g[i] >= 0.0f && g[i] <= 100.0f;

    // If incoming grades are valid, accept:
    if (valid) {
        // accept the client's data
        no = sn;
        ng = ng_;
        // allocate dynamic memory
        if (ng > 0) {
            grade = new float[ng];
            for (int i = 0; i < ng; i++)
                grade[i] = g[i];
        }
        else {
            grade = nullptr;
        }
    }
    else {
        // If incoming grades are not valid, set to default state:
        grade = nullptr;
        *this = Student();
    }
}


// Destructor:
// The destructor deallocates any memory that the constructor allocated.
// Deallocating memory at the nullptr address has no effect.
Student::~Student() {
    delete[] grade;
}

void Student::display() const {
    if (no > 0) {
        cout << no << ":\n";
        cout.setf(ios::fixed);
        cout.precision(2);
        for (int i = 0; i < ng; i++) {
            cout.width(6);
            cout << grade[i] << endl;
        }
        cout.unsetf(ios::fixed);
        cout.precision(6);
    }
    else {
        cout << "no data available" << endl;
    }
}

int main() {
    float gh[] = { 89.4f, 67.8f, 45.5f };
    Student harry(1234, gh, 3);
    harry.display();
}