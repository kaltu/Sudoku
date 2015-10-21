#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std ;

#include "Manager.hpp"
#include "Player.hpp"

void play() ;
void manage() ;
void start() ;

void play(void) {

} // player interface

void manage(void) {
    cout << "�Ѧa������" << endl << ">>> \n" ;
    string answer ;
    cin >> answer ;
    if ( answer != "���M���y��" ) return start() ;

} // manager interface

void start(void) {
    cout << "�Ӫ̦��H�I" << endl << ">>> \n" ;
    short opt ;
    cin >> opt ;
    if ( opt == 1 )
        return play() ;
    else if ( opt == 2 )
        return manage() ;
    else
        return start() ;
} // starter

int main( int argc, char** argv ) {
    srand(time(NULL)) ;
    Manager manager ;
    manager.print_sudokus() ;
    Sudoku a( 9 ) ;
    manager.set_hardness( 1, a );
    //Player play ;
    //play.doexercise( a ) ;
    /*
    Sudoku sudoku(9) ;
    sudoku.print_sudoku() ;
    cout << "build in " << sudoku.times() << " times." << endl ;
    cout << "self check: " << ( sudoku.self_check() ? "success" : "failed" ) << endl ;
    cout << "string: " << endl << sudoku.str() << endl ;
    cout << "HASH: " << sudoku.hash() << endl ;
    sudoku.save() ;
    //cout << "self check: " << ( sudoku.self_check() ? "success" : "failed" ) << "\n" ;
    //sudoku.copy2() ;
    //sudoku.print_copy() ;
    */
    start() ;
    return 0 ;
} // main
