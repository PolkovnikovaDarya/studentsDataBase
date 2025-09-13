#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;

    // Оператор сравнения для студентов
    bool operator==(const Student& other) const {
        return name == other.name && 
               age == other.age && 
               major == other.major && 
               gpa == other.gpa;
    }

    // Оператор вывода для студента
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Имя: " << student.name << "\n"
           << "Возраст: " << student.age << "\n"
           << "Специальность: " << student.major << "\n"
           << "Средний балл: " << std::fixed << std::setprecision(2) << student.gpa << "\n";
        return os;
    }
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin.ignore();
    std::getline(std::cin, student.name);
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin.ignore();
    std::getline(std::cin, student.major);
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }

    std::cout << "\nСписок студентов:\n";
    std::cout << "================\n";
    for (size_t i = 0; i < database.size(); ++i) {
        std::cout << "Студент #" << i + 1 << ":\n";
        std::cout << database[i];
        std::cout << "----------------\n";
    }
}

// Функция для поиска дубликатов студентов
void findDuplicates(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }

    std::cout << "\nПоиск дубликатов студентов:\n";
    std::cout << "===========================\n";

    bool foundDuplicates = false;
    
    for (size_t i = 0; i < database.size(); ++i) {
        for (size_t j = i + 1; j < database.size(); ++j) {
            if (database[i] == database[j]) {
                if (!foundDuplicates) {
                    foundDuplicates = true;
                }
                std::cout << "Найден дубликат:\n";
                std::cout << "Студент #" << i + 1 << " и Студент #" << j + 1 << " идентичны\n";
                std::cout << database[i];
                std::cout << "----------------\n";
            }
        }
    }

    if (!foundDuplicates) {
        std::cout << "Дубликаты не найдены.\n";
    }
}

// Функция для сравнения двух студентов
void compareStudents(const std::vector<Student>& database) {
    if (database.size() < 2) {
        std::cout << "Для сравнения необходимо как минимум 2 студента в базе.\n";
        return;
    }

    int index1, index2;
    std::cout << "\nВведите номер первого студента для сравнения (1-" << database.size() << "): ";
    std::cin >> index1;
    std::cout << "Введите номер второго студента для сравнения (1-" << database.size() << "): ";
    std::cin >> index2;

    if (index1 < 1 || index1 > static_cast<int>(database.size()) || 
        index2 < 1 || index2 > static_cast<int>(database.size())) {
        std::cout << "Неверный номер студента.\n";
        return;
    }

    index1--; index2--; // Convert to 0-based index

    std::cout << "\nСравнение студентов:\n";
    std::cout << "===================\n";
    std::cout << "Студент #" << index1 + 1 << ":\n" << database[index1];
    std::cout << "Студент #" << index2 + 1 << ":\n" << database[index2];
    std::cout << "-------------------\n";

    if (database[index1] == database[index2]) {
        std::cout << "Результат: Студенты идентичны!\n";
    } else {
        std::cout << "Результат: Студенты различны.\n";
        
        // Показать различия
        std::cout << "Различия:\n";
        if (database[index1].name != database[index2].name) {
            std::cout << "- Имена разные: '" << database[index1].name << "' vs '" << database[index2].name << "'\n";
        }
        if (database[index1].age != database[index2].age) {
            std::cout << "- Возраст разный: " << database[index1].age << " vs " << database[index2].age << "\n";
        }
        if (database[index1].major != database[index2].major) {
            std::cout << "- Специальности разные: '" << database[index1].major << "' vs '" << database[index2].major << "'\n";
        }
        if (database[index1].gpa != database[index2].gpa) {
            std::cout << "- Средний балл разный: " << std::fixed << std::setprecision(2) 
                      << database[index1].gpa << " vs " << database[index2].gpa << "\n";
        }
    }
}

int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "\n=== Система управления студентами ===\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Найти дубликаты студентов\n";
        std::cout << "4. Сравнить двух студентов\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                findDuplicates(database);
                break;
            case 4:
                compareStudents(database);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
        }
    } while (choice != 0);

    return 0;
}
