 /* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * University project
 * Name: Lari Lantonen
 * Student number: 283531
 * UserID: lantonen
 * E-Mail: lari.lantonen@tuni.fi
 *
 * Notes about the program and it's implementation:
 * University program that helps students and teachers to singup,
 * compelete courses and check their signups.
 * Counting credits could have done with only reading credits from completed courses
 * but I decided to make account a new private information called all_credits.
 *
 * */

#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;


const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    /**
     * @brief Instance constructor
     * @param instance name
     * @param starting date
     * @param course that has this instance
     */
    Instance(const std::string& name, Date& date, Course* course);

    /**
     * @brief prints instance, starting date, and amount of students
     */
    void print();

    /**
     * @brief prints instance_students_ vectors all student
     */
    void print_students();

    /**
     * @brief compares instances name_ and name given
     * @param instances name example "K2020"
     * @return true if instance is named as param name
     */
    bool is_named(const std::string name);

    /**
     * @brief adds student to instance
     * @param Account that is searched
     * @return true if account is found
     * Note: cant be added if already signed up or signing up late
     * (if statements in university.cpp)
     */
    void add_student(Account* new_student);

    /**
     * @brief finds if account is signed to this instance
     * @param Account that is searched
     * @return true if account is found
     */
    bool is_account_signed(Account *new_student);

    /**
     * @brief gets instances date
     * @return starting date
     */
    Date get_date();


    /**
     * @brief gets instances name
     * @return name as string
     */
    std::string get_name();


    /**
     * @brief gets instances course
     * @return points to spesific course
     */
    Course* get_course();

private:
    std::string name_;
    Date date_;
    Course* course_;
    std::vector<Account*> instance_students_;
};

#endif // INSTANCE_HH
