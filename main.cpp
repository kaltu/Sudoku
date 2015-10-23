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
    cout << "0. exit player mode" << endl
         << ">>> " ;
    string opt ;
    cin >> opt ;
    if ( opt == "0" )
        return start( manager ) ;
    else return play( manager ) ;
    system( "pause" ) ;
    return play( manager ) ;
} // player interface

void manage( Manager &manager ) {
    manager.clear_screen() ;
    cout << "1. show all sudokus" << endl
         << "2. show current sudoku" << endl
         << "3. change sudoku" << endl
         << "4. add a new sudoku" << endl
         << "5. delete current sudoku" << endl
         << "0. exit managing mode" << endl
         << ">>> " ;
    string opt ;
    cin >> opt ;
    if ( opt == "1" )
        manager.print_sudokus() ;
    else if ( opt == "2" )
        manager.print_sudoku() ;
    else if ( opt == "3" ) {
        manager.print_sudokus() ;
        int index ;
        cout << "Whitch one do you wnat to switch to?" << endl << ">>> " ;
        cin >> index ;
        manager.switch_sudoku( index ) ;
    }
    else if ( opt == "4" )
        manager.create_sudoku() ;
    else if ( opt == "5" )
        manager.delete_sudoku() ;
    else if ( opt == "0" )
        return start( manager ) ;
    else return manage( manager ) ;
    system( "pause" ) ;
    return manage( manager ) ;
} // manager interface

void start( Manager &manager ) {
    manager.clear_screen() ;
    cout << "1. play" << endl
         << "2. manage" << endl
         << "0. exit" << endl
         << ">>> " ;
    string opt ;

    cin >> opt ;
    if ( opt == "1" )
        return play( manager ) ;
    else if ( opt == "2" )
        return manage( manager ) ;
    else if ( opt == "0" )
        return init() ;
    else
        return start( manager ) ;
} // starter

void init(void) {
    system( "cls" ) ;
    cout << "4. mini-sudoku" << endl
         << "9. standard-sudoku" << endl
         << "0. exit" << endl
         << ">>> " ;
    string i ;
    cin >> i ;
    if ( i == "4" ) {
        Manager manager(4) ;
        start( manager ) ;
    }
    else if ( i == "9" ) {
        Manager manager(9) ;
        start( manager ) ;
    }
    else if ( i != "0" )
        return init() ;
}

int main( int argc, char** argv ) {
    srand(time(NULL)) ;
    init() ;
    return 0 ;
} // main
