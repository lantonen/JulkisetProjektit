#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
    all_credits_ = 0;
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::add_to_current(Instance *inst){
    current_.push_back(inst);
}

void Account::remove_current(std::string inst_name){
    int index = 0;
    for( auto inst : current_ ){
        if(inst->is_named(inst_name)){
            break;
        }
        else{
            index++;
        }
    }
    current_.erase(current_.begin() + index);
}

void Account::add_to_completed(Course *course){
    completed_.push_back(course);
    all_credits_ += course->get_credits();
}

void Account::print_completed(){
    for(auto course : completed_){
        course->print_info(true);
    }
}

void Account::print_current(){
    for(auto inst : current_){
        inst->get_course()->print_info(false);
        std::cout << " " + inst->get_name() << std::endl;
    }
}

//
int Account::get_all_credits(){
    return all_credits_;
}

bool Account::is_in_current(Instance* searched_inst){
    for(auto inst : current_){
        if(inst==searched_inst){
            return true;
        }
    }
    return false;
}
