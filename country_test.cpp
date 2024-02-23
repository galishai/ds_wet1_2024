#include "Olympicsa1.h"
#include <iostream>

int main(){
    Olympics olympus;

    std::cout << (int)olympus.add_country(700,11) << '\n'; // usa
    std::cout << (int)olympus.add_team(300, 700, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(1, 700, Sport::SWIMMING, 2) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(102, 700, Sport::SWIMMING, 4) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(100, 700, Sport::SWIMMING, 7) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(20, 700, Sport::SWIMMING, 15) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(101, 700, Sport::SWIMMING, 6) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(10, 700, Sport::SWIMMING, 10) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(4, 700, Sport::SWIMMING, 5) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(16, 700, Sport::SWIMMING, 11) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(6, 700, Sport::SWIMMING, 3) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 1) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 100) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 101) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 6) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 4) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 102) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 20) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 10) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 16) << '\n'; // usa
    std::cout << (int)olympus.austerity_measures(300).ans() << '\n'; // usa

    //TODO

/*
    // trying successful things.
    std::cout << (int)olympus.add_country(1,1) << '\n'; // usa
    std::cout << (int)olympus.add_country(40,2) << '\n'; // romania
    std::cout << (int)olympus.add_country(972,3) << '\n'; // israel
    std::cout << (int)olympus.add_country(44,4) << '\n'; // uk
    std::cout << (int)olympus.add_country(46,5) << '\n'; // sweden
    std::cout << (int)olympus.add_country(7,6) << '\n'; // russia
    std::cout << (int)olympus.add_country(39,0) << "\n\n"; // italy
    // trying invalid input.
    std::cout << (int)olympus.add_country(-2,0) << "\n"; // negative country id
    std::cout << (int)olympus.add_country(39,-1) << "\n"; // neative medals
    std::cout << (int)olympus.add_country(0,0) << "\n\n"; // null_id
    // trying failure
    std::cout << (int)olympus.add_country(39,0) << "\n\n"; // italy again

    // trying to get medal count successfully
    output_t<int> value = olympus.get_medals(1);
    std::cout << '(' << (int)value.status() << ',' << value.ans() << ')' << "\n";
    output_t<int> value2 = olympus.get_medals(972);
    std::cout << '(' << (int)value2.status() << ',' << value2.ans() << ')' << "\n\n";
    // trying invalid input
    output_t<int> value3 = olympus.get_medals(0); // null id
    std::cout << '(' << (int)value3.status() << ',' << value3.ans() << ')' << "\n\n";
    // trying failure
    output_t<int> value4 = olympus.get_medals(54); // argentina
    std::cout << '(' << (int)value4.status() << ',' << value4.ans() << ')' << "\n\n";

    // trying to remove successfully
    std::cout << (int)olympus.remove_country(7) << '\n'; // russia
    std::cout << (int)olympus.remove_country(39) << '\n'; // italy
    std::cout << (int)olympus.remove_country(40) << "\n\n"; // romania
    // trying invalid input
    std::cout << (int)olympus.remove_country(-7) << '\n'; // negative country id
    std::cout << (int)olympus.remove_country(0) << "\n\n"; // null id
    // trying failure
    std::cout << (int)olympus.remove_country(7) << '\n'; // russia again (supposed to be removed already)
    std::cout << (int)olympus.remove_country(254) << '\n'; // kenya
    std::cout << (int)olympus.remove_country(359) << "\n\n"; // bulgaria
    return 0;
    */
}