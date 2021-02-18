#include "instance.hh"
#include "course.hh"

Instance::Instance(const std::string& name, Date& date, Course* course):
    name_ (name), date_ (date), course_ (course){
}

void Instance::print(){
    std::cout << name_ << std::endl << INDENT << "Starting date: ";
    date_.print();
    std::cout << std::endl;

    std::cout << INDENT << "Amount of students: "
              << instance_students_.size() << std::endl;
}

void Instance::print_students(){
    for(auto student : instance_students_){
        student->print();
    }
}

bool Instance::is_named(const std::string name){
    if(name_ == name){
        return true;
    }
    return false;
}

void Instance::add_student(Account *new_student){
    instance_students_.push_back(new_student);
    std::cout  << "Signed up on the course instance. " << std::endl;

}

bool Instance::is_account_signed(Account *new_student){
    for(auto student : instance_students_){
        if(student->get_email() == new_student->get_email()){
            return true;
        }
    }
    return false;
}

Date Instance::get_date(){
    return date_;
}

std::string Instance::get_name() {
    return name_;
}

Course* Instance::get_course() {
    return course_;
}
