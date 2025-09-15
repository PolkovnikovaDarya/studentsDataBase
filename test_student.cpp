#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "gtest/gtest.h"

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;

    bool operator==(const Student& other) const {
        return name == other.name && 
               age == other.age && 
               major == other.major && 
               std::abs(gpa - other.gpa) < 1e-6;
    }
};

// Функция для сравнения студентов
bool compareStudents(const Student& s1, const Student& s2) {
    return s1 == s2;
}

// Функция для поиска дубликатов
std::vector<std::pair<size_t, size_t>> findDuplicates(const std::vector<Student>& database) {
    std::vector<std::pair<size_t, size_t>> duplicates;
    
    for (size_t i = 0; i < database.size(); ++i) {
        for (size_t j = i + 1; j < database.size(); ++j) {
            if (database[i] == database[j]) {
                duplicates.emplace_back(i, j);
            }
        }
    }
    
    return duplicates;
}

// Юнит-тесты
TEST(StudentTest, EqualityOperator) {
    Student s1{"Ivan", 20, "CS", 4.5};
    Student s2{"Ivan", 20, "CS", 4.5};
    Student s3{"Ivan", 21, "CS", 4.5};
    Student s4{"Petr", 20, "CS", 4.5};
    Student s5{"Ivan", 20, "Math", 4.5};
    Student s6{"Ivan", 20, "CS", 4.0};
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);  // Different age
    EXPECT_FALSE(s1 == s4);  // Different name
    EXPECT_FALSE(s1 == s5);  // Different major
    EXPECT_FALSE(s1 == s6);  // Different GPA
}

TEST(StudentTest, CompareStudentsFunction) {
    Student s1{"Anna", 19, "Physics", 4.8};
    Student s2{"Anna", 19, "Physics", 4.8};
    Student s3{"Anna", 19, "Chemistry", 4.8};
    
    EXPECT_TRUE(compareStudents(s1, s2));
    EXPECT_FALSE(compareStudents(s1, s3));
}

TEST(StudentTest, FindDuplicatesEmpty) {
    std::vector<Student> empty_db;
    auto duplicates = findDuplicates(empty_db);
    EXPECT_TRUE(duplicates.empty());
}

TEST(StudentTest, FindDuplicatesNoDuplicates) {
    std::vector<Student> db{
        {"Ivan", 20, "CS", 4.5},
        {"Anna", 19, "Physics", 4.8},
        {"Petr", 21, "Math", 4.2}
    };
    
    auto duplicates = findDuplicates(db);
    EXPECT_TRUE(duplicates.empty());
}

TEST(StudentTest, FindDuplicatesWithDuplicates) {
    std::vector<Student> db{
        {"Ivan", 20, "CS", 4.5},      // 0
        {"Anna", 19, "Physics", 4.8}, // 1
        {"Ivan", 20, "CS", 4.5},      // 2 - duplicate of 0
        {"Petr", 21, "Math", 4.2},    // 3
        {"Anna", 19, "Physics", 4.8}  // 4 - duplicate of 1
    };
    
    auto duplicates = findDuplicates(db);
    
    EXPECT_EQ(duplicates.size(), 2);
    EXPECT_EQ(duplicates[0].first, 0);
    EXPECT_EQ(duplicates[0].second, 2);
    EXPECT_EQ(duplicates[1].first, 1);
    EXPECT_EQ(duplicates[1].second, 4);
}

TEST(StudentTest, FindDuplicatesPartialMatch) {
    std::vector<Student> db{
        {"Ivan", 20, "CS", 4.5},
        {"Ivan", 20, "CS", 4.0},  // Different GPA
        {"Ivan", 21, "CS", 4.5},  // Different age
        {"Anna", 20, "CS", 4.5}   // Different name
    };
    
    auto duplicates = findDuplicates(db);
    EXPECT_TRUE(duplicates.empty());
}

TEST(StudentTest, FloatingPointPrecision) {
    Student s1{"Ivan", 20, "CS", 4.5000001};
    Student s2{"Ivan", 20, "CS", 4.5000002};
    
    // Should be considered equal due to floating point tolerance
    EXPECT_TRUE(s1 == s2);
}

// Интеграционные тесты
TEST(IntegrationTest, FullWorkflow) {
    std::vector<Student> database;
    
    // Add students
    database.push_back({"Ivan", 20, "CS", 4.5});
    database.push_back({"Anna", 19, "Physics", 4.8});
    database.push_back({"Ivan", 20, "CS", 4.5}); // Duplicate
    
    // Test duplicates
    auto duplicates = findDuplicates(database);
    EXPECT_EQ(duplicates.size(), 1);
    EXPECT_EQ(duplicates[0].first, 0);
    EXPECT_EQ(duplicates[0].second, 2);
    
    // Test comparison
    EXPECT_TRUE(compareStudents(database[0], database[2]));
    EXPECT_FALSE(compareStudents(database[0], database[1]));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
