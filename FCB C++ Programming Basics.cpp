#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Define classes for students, subjects, streams, etc.
class Student {
public:
    std::string name;
    double marks[3]; // Assuming 3 subjects
    double totalMarks;
    int schoolRank;
    int classRank;

    // Constructor
    Student(const std::string& n, double m1, double m2, double m3)
        : name(n), totalMarks(0), schoolRank(0), classRank(0) {
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        calculateTotalMarks();
    }

    // Calculate total marks
    void calculateTotalMarks() {
        totalMarks = marks[0] + marks[1] + marks[2];
    }
};

class Stream {
public:
    std::vector<Student> students;
};

// Function to rank students
void rankStudents(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return a.totalMarks > b.totalMarks;
              });

    for (size_t i = 0; i < students.size(); ++i) {
        students[i].schoolRank = i + 1;
    }
}

// Function to read marks from file and create students
void readMarksFromFile(const std::string& filename, Stream& stream) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string name;
    double marks[3];
    while (inFile >> name >> marks[0] >> marks[1] >> marks[2]) {
        stream.students.emplace_back(name, marks[0], marks[1], marks[2]);
    }

    inFile.close();
}

// Function to print and write ranks to file
void printAndWriteRanks(const Stream& stream, const std::string& outputFilename) {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << outputFilename << std::endl;
        return;
    }

    for (const Student& student : stream.students) {
        outFile << "Student: " << student.name << "\n"
                << "Total Marks: " << student.totalMarks << "\n"
                << "School Rank: " << student.schoolRank << "\n"
                << "Class Rank: " << student.classRank << "\n\n";

        std::cout << "Student: " << student.name << "\n"
                  << "Total Marks: " << student.totalMarks << "\n"
                  << "School Rank: " << student.schoolRank << "\n"
                  << "Class Rank: " << student.classRank << "\n\n";
    }

    outFile.close();
}

int main() {
    // Create streams for Bio and Math
    Stream bioStream;
    Stream mathStream;

    // Read marks from files and create students
    readMarksFromFile("bio_marks.txt", bioStream);
    readMarksFromFile("math_marks.txt", mathStream);

    // Rank students
    rankStudents(bioStream.students);
    rankStudents(mathStream.students);

    // Print and write ranks to files
    printAndWriteRanks(bioStream, "bio_ranks.txt");
    printAndWriteRanks(mathStream, "math_ranks.txt");

    return 0;
}
