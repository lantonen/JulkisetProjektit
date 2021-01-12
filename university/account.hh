/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief add instance to current vector
     */
    void add_to_current(Instance *inst);

    /**
     * @brief remove instance from current_
     * @param instances name, so it can be found
     */
    void remove_current(std::string inst_name);

    /**
     * @brief add course to completed courses
     * @param course that is added to completed
     */
    void add_to_completed(Course *course);

    /**
     * @brief prints all copleted courses and students points
     */
    void print_completed();

    /**
     * @brief gives accounts credits from compeling courses
     */
    int get_all_credits();

    /**
     * @brief prints all current instances
     */
    void print_current();

    /**
     * @brief finds if searched instance is in current_
     * @param instances that we are searching
     * @return email linked to this account
     */
    bool is_in_current(Instance *searched_inst);

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
    // all_credits saved into a accounts helps to track credits
    int all_credits_;
};

#endif // ACCOUNT_HH
