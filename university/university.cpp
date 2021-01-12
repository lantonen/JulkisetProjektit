#include "university.hh"

University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin();
         iter != accounts_.end(); ++iter ) {

        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;

    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter =
            accounts_.find(std::stoi(params.at(0)));

    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

void University::add_instance(Params params)
{

    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if (courses_.at(params.at(0))->has_instance(params.at(1))){
        std:: cout << INSTANCE_EXISTS << std::endl;
        return;
    }
    else{
        Instance* n_instance = new Instance (params.at(1), utils::today,
                                             courses_.at(params.at(0)));

        courses_.at(params.at(0))->new_instance(n_instance);
    }
}

void University::sign_up_on_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if (not courses_.at(params.at(0))->has_instance(params.at(1)) ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(2))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
    }
    Account *new_student = accounts_.at(std::stoi(params.at(2)));

    // if account has already singned up
    Instance *inst = courses_.at(params.at(0))->get_instance(params.at(1));
    if(not inst->is_account_signed(new_student)){

        // checks is signing up late
        if( utils::today < inst->get_date()  or
                inst->get_date() == utils::today){

            courses_.at(params.at(0))->get_instance(params.at(1))
                    ->add_student(new_student);

            new_student->add_to_current(inst);
        }
        else{
            std::cout << LATE << std::endl;
            return;
        }
    }
    else{
        std::cout << ALREADY_REGISTERED << std::endl;
        return;
    }

}

void University::complete_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if (not courses_.at(params.at(0))->has_instance(params.at(1)) ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(2))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
    }

    Account *student = accounts_.at(std::stoi(params.at(2)));
    Course *course = courses_.at(params.at(0));
    Instance *searched_inst = course->get_instance(params.at(1));

    if(student->is_in_current(searched_inst)){
        student->add_to_completed(course);
        student->remove_current(params.at(1));
        std::cout << COMPLETED << std::endl;
    }
    else{
        std::cout << NO_SIGNUPS << std::endl;
    }



}
void University::print_signups(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_signups();
}

void University::print_study_state(Params params)
{
    std::map<int, Account*>::iterator iter =
            accounts_.find(std::stoi(params.at(0)));

    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    print_current(params.at(0));
    std::cout << "Completed: " << std::endl;
    print_completed(params);
}

void University::print_current(std::string account_number){
    std::cout << "Current: " << std::endl;
    Account *student = accounts_.at(std::stoi(account_number));
    student->print_current();
}

void University::print_completed(Params params)
{
    Account *student = accounts_.at(std::stoi(params.at(0)));
    student->print_completed();
    std::cout << "Total credits: " << student->get_all_credits() <<std::endl;
}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)),
                        std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
