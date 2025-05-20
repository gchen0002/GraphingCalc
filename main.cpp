#include <iostream>


#include <iomanip>
using namespace std;

#include "includes/animate/animate.h" 

int main(int argv, char** argc) {
    cout << "\n\n" << endl; 

    animate game; 
    game.run();   

    cout << "\n\n\n=====================" << endl;
    return 0;
}
