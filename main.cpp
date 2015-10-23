#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std ;

#include "Manager.hpp"
#include "Player.hpp"

void play( Manager &manager ) ;
void manage( Manager &manager ) ;
void start( Manager &manager ) ;
void init(void) ;

void play( Manager &manager ) {
    manager.clear_screen() ;
    Player player( manager.request_quesion() ) ;
    manager.clear_screen() ;
    cout << "1. P)ractice" << endl
         << "2. A)dvanture" << endl
         << "3. Show R)anking" << endl
         << "0. E)xit player mode" << endl
         << ">>> " ;
    string opt ;
    cin >> opt ;
    if ( opt == "0" || opt == "E" || opt == "e" )
        return start( manager ) ;
    else if ( opt == "1" || opt == "P" || opt == "p" )
        player.exerciseMode() ;
    else if ( opt == "2" || opt == "A" || opt == "a" )
        player.stageMode( manager ) ;
    else if ( opt == "3" || opt == "R" || opt == "r" )
        manager.print_rank() ;
    else return play( manager ) ;
    system( "pause" ) ;
    return play( manager ) ;
} // player interface

void manage( Manager &manager ) {
    manager.clear_screen() ;
    cout << "1. show A)ll sudokus" << endl
         << "2. show C)urrent sudoku" << endl
         << "3. S)witch sudoku" << endl
         << "4. add a N)ew sudoku" << endl
         << "5. D)elete current sudoku" << endl
         << "0. E)xit managing mode" << endl
         << ">>> " ;
    string opt ;
    cin >> opt ;
    manager.clear_screen() ;
    if ( opt == "1" || opt == "A" || opt == "a" )
        manager.print_sudokus() ;
    else if ( opt == "2" || opt == "C" || opt == "c" )
        manager.print_sudoku() ;
    else if ( opt == "3" || opt == "S" || opt == "s" ) {
        manager.print_sudokus() ;
        int index ;
        cout << "Whitch one do you wnat to switch to?" << endl << ">>> " ;
        cin >> index ;
        manager.switch_sudoku( index ) ;
    }
    else if ( opt == "4" || opt == "N" || opt == "n" )
        manager.create_sudoku() ;
    else if ( opt == "5" || opt == "D" || opt == "d" )
        manager.delete_sudoku() ;
    else if ( opt == "0" || opt == "E" || opt == "e" )
        return start( manager ) ;
    else return manage( manager ) ;
    system( "pause" ) ;
    return manage( manager ) ;
} // manager interface

void start( Manager &manager ) {
    manager.clear_screen() ;
    cout << "1. P)lay" << endl
         << "2. M)anage" << endl
         << "0. E)xit" << endl
         << ">>> " ;
    string opt ;

    cin >> opt ;
    if ( opt == "1" || opt == "P" || opt == "p" )
        return play( manager ) ;
    else if ( opt == "2" || opt == "M" || opt == "m" )
        return manage( manager ) ;
    else if ( opt == "0" || opt == "E" || opt == "e" )
        return init() ;
    else
        return start( manager ) ;
} // starter

void init(void) {
    system( "cls" ) ;
    cout << "4. M)ini-sudoku" << endl
         << "9. S)tandard-sudoku" << endl
         << "0. E)xit" << endl
         << ">>> " ;
    string i ;
    cin >> i ;
    if ( i == "4" || i == "M" || i == "m" ) {
        Manager manager(4) ;
        start( manager ) ;
    }
    else if ( i == "9" || i == "S" || i == "s" ) {
        Manager manager(9) ;
        start( manager ) ;
    }
    else if ( i != "0" && i != "E" && i != "e" )
        return init() ;
}

int main( int argc, char** argv ) {
    srand(time(NULL)) ;
    init() ;
    return 0 ;
} // main
