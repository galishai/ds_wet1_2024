#include "Olympicsa1.h"
#include <iostream>

int main(){
    Olympics olympus;

    std::cout << (int)olympus.add_country(100,2) << '\n'; // usa
    std::cout << (int)olympus.add_team(1, 100, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(1,100,Sport::SWIMMING,2) << '\n';
    std::cout << (int)olympus.add_contestant(2,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(3,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(4,100,Sport::SWIMMING,2) << '\n';
    std::cout << (int)olympus.add_contestant(5,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(6,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(7,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(8,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(9,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(10,100,Sport::SWIMMING,2) << '\n';
    std::cout << (int)olympus.add_contestant(11,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant(12,100,Sport::SWIMMING,1) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,3) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,2) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,1) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,1) << "*1" << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,1) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,2) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,1) << '\n';
    std::cout << (int)olympus.remove_team(1) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,3) << '\n';
    std::cout << (int)olympus.remove_team(1) << '\n';
    std::cout << (int)olympus.add_team(1, 100, Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.add_team(2, 100, Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.unite_teams(1,2) << "*2" << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,1) << '\n';
    std::cout << (int)olympus.unite_teams(1,2) << '\n';
    std::cout << (int)olympus.add_team(2, 100, Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.unite_teams(1,2) << '\n';
    std::cout << (int)olympus.add_team(2, 100, Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,1) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,1) << "*3" << '\n';
    std::cout << (int)olympus.unite_teams(2,1) << '\n';
    std::cout << (int)olympus.add_team(1,100,Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,1) << '\n';
    std::cout << (int)olympus.unite_teams(1,2) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,8) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,5) << '\n';
    std::cout << (int)olympus.get_team_strength(1).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,12) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,12) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,7) << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,7) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,4) << '\n';
    std::cout << (int)olympus.update_contestant_strength(4,5) << '\n';
    std::cout << (int)olympus.update_contestant_strength(4,-4) << "*4" << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,9) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,7) << '\n';
    std::cout << (int)olympus.update_contestant_strength(1,16)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(4,10)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(5,10)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(7,12)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(8,11)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(9,13)  << '\n';
    std::cout << (int)olympus.austerity_measures(1).ans() << '\n';
    std::cout << (int)olympus.add_team(2,100,Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.add_team(3,100,Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.add_team(4,100,Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.add_team(5,100,Sport::SWIMMING) << '\n';
    std::cout << (int)olympus.add_contestant(13,100,Sport::SWIMMING, 9) << '\n';
    std::cout << (int)olympus.add_contestant(14,100,Sport::SWIMMING, 8) << '\n';
    std::cout << (int)olympus.add_contestant(15,100,Sport::SWIMMING, 7) << '\n';
    std::cout << (int)olympus.add_contestant(16,100,Sport::SWIMMING, 6) << '\n';
    std::cout << (int)olympus.add_contestant(17,100,Sport::SWIMMING, 5) << '\n';
    std::cout << (int)olympus.add_contestant(18,100,Sport::SWIMMING, 4) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(3,1) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(4,1) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(5,1) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,13) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,14) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,15) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,16) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,17) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,18) << '\n';
    std::cout << (int)olympus.austerity_measures(2).ans() << '\n';
    std::cout << (int)olympus.unite_teams(1,3) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(5,1)  << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(5,1)  << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(1,1)  << '\n';
    std::cout << (int)olympus.remove_contestant_from_team(4,1)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(1,1)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(2,1)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(4,1)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(5,1)  << '\n';
    std::cout << (int)olympus.add_team(7,100,Sport::SWIMMING)  << '\n';
    std::cout << (int)olympus.add_contestant(19,100,Sport::SWIMMING,1)  << '\n';
    std::cout << (int)olympus.add_contestant(20,100,Sport::SWIMMING,1)  << '\n';
    std::cout << (int)olympus.add_contestant(21,100,Sport::SWIMMING,1)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(7,19)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(7,20)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(7,21)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(19,1)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(20,1)  << '\n';
    std::cout << (int)olympus.update_contestant_strength(21,1)  << '\n';
    std::cout << (int)olympus.get_team_strength(7).ans()  << '\n';
    std::cout << (int)olympus.add_country(2,1)  << '\n';
    std::cout << (int)olympus.add_team(8,2,Sport::BOULDERING)  << '\n';
    std::cout << (int)olympus.play_match(8,7)  << '\n';
    std::cout << (int)olympus.add_team(9,2,Sport::SWIMMING)  << '\n';
    std::cout << (int)olympus.play_match(7,9)  << '\n';
    std::cout << (int)olympus.get_medals(100).ans()  << '\n';
    std::cout << (int)olympus.add_contestant(22,2,Sport::SWIMMING,100)  << '\n';
    std::cout << (int)olympus.add_contestant(23,2,Sport::SWIMMING,100)  << '\n';
    std::cout << (int)olympus.add_contestant(24,2,Sport::SWIMMING,100)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(9,22)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(9,23)  << '\n';
    std::cout << (int)olympus.add_contestant_to_team(9,24)  << '\n';
    std::cout << (int)olympus.play_match(7,9)  << '\n';
    std::cout << (int)olympus.get_medals(2).ans()  << '\n';
    std::cout << (int)olympus.add_country(3,1)  << '\n';
    std::cout << (int)olympus.add_country(4,1)  << '\n';
    std::cout << (int)olympus.add_team(17,3,Sport::SWIMMING)  << '\n';
    std::cout << (int)olympus.add_team(18,4,Sport::SWIMMING)  << '\n';
    std::cout << (int)olympus.play_match(17,18)  << '\n';
    std::cout << (int)olympus.get_medals(3).ans()  << '\n';
    std::cout << (int)olympus.get_medals(4).ans()  << '\n';
    std::cout << (int)olympus.unite_teams(1,2)  << '\n';



    /*
    std::cout << (int)olympus.add_country(100,2) << '\n'; // usa
    std::cout << (int)olympus.add_country(200,3) << '\n'; // usa
    std::cout << (int)olympus.add_team(11, 100, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.add_team(12, 100, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.add_team(13, 100, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.add_team(21, 100, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(1,100,Sport::SWIMMING,24) << '\n';
    std::cout << (int)olympus.add_contestant(2,100,Sport::SWIMMING,22) << '\n';
    std::cout << (int)olympus.add_contestant(3,100,Sport::SWIMMING,21) << '\n';
    std::cout << (int)olympus.add_contestant(4,100,Sport::SWIMMING,23) << '\n';
    std::cout << (int)olympus.add_contestant(5,100,Sport::SWIMMING,20) << '\n';
    std::cout << (int)olympus.add_contestant(6,100,Sport::SWIMMING,24) << '\n';
    std::cout << (int)olympus.add_contestant(7,100,Sport::SWIMMING,25) << '\n';
    std::cout << (int)olympus.add_contestant(8,100,Sport::SWIMMING,26) << '\n';
    std::cout << (int)olympus.add_contestant(9,100,Sport::SWIMMING,27) << '\n';
    std::cout << (int)olympus.add_contestant(10,100,Sport::SWIMMING,28) << '\n';
    std::cout << (int)olympus.add_contestant(11,100,Sport::SWIMMING,29) << '\n';
    std::cout << (int)olympus.add_contestant(12,100,Sport::SWIMMING,30) << '\n';
    std::cout << (int)olympus.add_contestant(13,100,Sport::SWIMMING,22) << '\n';
    std::cout << (int)olympus.add_contestant(14,100,Sport::SWIMMING,27) << '\n';
    std::cout << (int)olympus.add_contestant(15,100,Sport::SWIMMING,23) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,9) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(13,9) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(21,9) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(11,9) << "*" << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,2) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,6) << '\n';
    std::cout << (int)olympus.get_team_strength(12).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,7) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,10) << '\n';
    std::cout << (int)olympus.get_team_strength(12).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,8) << '\n';
    std::cout << (int)olympus.get_team_strength(12).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,11) << '\n';
    std::cout << (int)olympus.get_team_strength(12).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,1) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,3) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,5) << '\n';
    std::cout << (int)olympus.get_team_strength(12).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,4) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(12,12) << '\n';
    std::cout << (int)olympus.play_match(12,21) << '\n';
    std::cout << (int)olympus.get_medals(100).ans() << "*" << '\n';
    std::cout << (int)olympus.update_contestant_strength(9,3) << '\n';
    std::cout << (int)olympus.update_contestant_strength(1,-5) << '\n';
    std::cout << (int)olympus.get_team_strength(12).ans() << '\n';
    std::cout << (int)olympus.austerity_measures(12).ans() << '\n';
    std::cout << (int)olympus.add_contestant_to_team(13,13) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(13,14) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(13,15)<< "*" << '\n';
    std::cout << (int)olympus.unite_teams(12,13) << '\n';
    std::cout << (int)olympus.add_contestant_to_team(11,9) << '\n';
    std::cout << (int)olympus.austerity_measures(12).ans() << '\n';
    std::cout << (int)olympus.add_team(13, 100, Sport::SWIMMING) << '\n'; // usa
    std::cout << (int)olympus.unite_teams(13,12) << '\n';
    std::cout << (int)olympus.unite_teams(13,21) << '\n';
    int a = 0;
     */









    /*std::cout << (int)olympus.add_contestant(1, 700, Sport::SWIMMING, 2) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(2, 700, Sport::SWIMMING, 4) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(3, 700, Sport::SWIMMING, 7) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(4, 700, Sport::SWIMMING, 15) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(5, 700, Sport::SWIMMING, 6) << '\n'; // usa
    std::cout << (int)olympus.add_contestant(6, 700, Sport::SWIMMING, 10) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 1) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 5) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(300, 3) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(200, 6) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(200, 4) << '\n'; // usa
    std::cout << (int)olympus.add_contestant_to_team(200, 2) << '\n'; // usa
    std::cout << (int)olympus.unite_teams(300,200);
    int a = 0;
*/
    /*
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
     */

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