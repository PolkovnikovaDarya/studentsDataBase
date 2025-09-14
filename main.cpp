#include <iostream>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
    // Функция для сравнения студентов по всем полям
    bool isEqual(const Student& other) const {
        return name == other.name && 
               age == other.age && 
               major == other.major && 
               gpa == other.gpa;
    }
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    // Проверка, пуста ли база данных или нет
    if (database.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }

    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Функция для сравнения двух студентов
void compareStudents(const std::vector<Student>& database) {
    if (database.size() < 2) {
        std::cout << "Для сравнения нужно как минимум 2 студента в базе.\n";
        return;
    }

    int index1, index2;
    std::cout << "Введите номер первого студента (1-" << database.size() << "): ";
    std::cin >> index1;
    std::cout << "Введите номер второго студента (1-" << database.size() << "): ";
    std::cin >> index2;

    if (index1 < 1 || index1 > database.size() || index2 < 1 || index2 > database.size()) {
        std::cout << "Неверный номер студента.\n";
        return;
    }

    const Student& student1 = database[index1 - 1];
    const Student& student2 = database[index2 - 1];

    std::cout << "\nСравнение студентов:\n";
    std::cout << "Студент #" << index1 << " и Студент #" << index2 << "\n\n";

    if (student1.isEqual(student2)) {
        std::cout << "Результат: Студенты идентичны по всем полям!\n";
    } else {
        std::cout << "Результат: Студенты отличаются.\n";
        
        // Показываем различия
        std::cout << "Различия:\n";
        if (student1.name != student2.name) {
            std::cout << "- Имя: '" << student1.name << "' vs '" << student2.name << "'\n";
        }
        if (student1.age != student2.age) {
            std::cout << "- Возраст: " << student1.age << " vs " << student2.age << "\n";
        }
        if (student1.major != student2.major) {
            std::cout << "- Специальность: '" << student1.major << "' vs '" << student2.major << "'\n";
        }
        if (student1.gpa != student2.gpa) {
            std::cout << "- Средний балл: " << std::fixed << std::setprecision(2) 
                      << student1.gpa << " vs " << student2.gpa << "\n";
        }
    }
}

// Функция для поиска дубликатов в базе
void findDuplicates(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }

    std::cout << "Поиск дубликатов студентов:\n";
    bool foundDuplicates = false;

    for (size_t i = 0; i < database.size(); ++i) {
        for (size_t j = i + 1; j < database.size(); ++j) {
            if (database[i].isEqual(database[j])) {
                if (!foundDuplicates) {
                    foundDuplicates = true;
                    std::cout << "Найдены дубликаты:\n";
                }
                std::cout << "Студент #" << i + 1 << " и Студент #" << j + 1 << " идентичны\n";
                std::cout << "Имя: " << database[i].name << "\n";
                std::cout << "Возраст: " << database[i].age << "\n";
                std::cout << "Специальность: " << database[i].major << "\n";
                std::cout << "Средний балл: " << std::fixed << std::setprecision(2) << database[i].gpa << "\n\n";
            }
        }
    }

    if (!foundDuplicates) {
        std::cout << "Дубликаты не найдены.\n";
    }
}

int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
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
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}