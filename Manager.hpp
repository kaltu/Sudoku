#ifndef MANAGER_HPP_INCLUDED
#define MANAGER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <list>
#include <algorithm>
#include "Sudoku.hpp"
using namespace std ;

class Manager {
    protected:
        Sudoku* s ;
        list<Sudoku*> sudoku_pointer_list ;
        list<string> file_list ;
        string list_file_name ;

        /* * * * * * * * * *sudoku_creater* * * * * * * * * * */

        void new_sudoku( int size = 9 ) {
            if ( size != 9 ) size = 4 ;                                          // no other size allowed
            Sudoku sudoku(size) ;
            sudoku.save() ;

            if ( !s ) s = new Sudoku( sudoku.size() ) ;                          // if s is NULL pointer
            *s = sudoku ;
            sudoku_pointer_list.push_back(s) ;
            file_list.push_back(sudoku.file_name()) ;
            add_to_file_list( sudoku.file_name() ) ;
        } // create a new sudoku

        void add_to_file_list( string file_name ) {
            ofstream file( list_file_name ) ;
            if ( file.is_open() )
                file << file_name << endl ;
        } // add_to_file_list()

        /* * * * * * * * * *sudoku_creater* * * * * * * * * * */
        /* * * * * * * * * * sudoku_pointer_list * * * * * * * * * * */

        void readin_sudoku( Sudoku &sudoku ) {
            Sudoku* temp = new Sudoku(sudoku.size()) ;
            *temp = sudoku ;
            sudoku_pointer_list.push_back(temp) ;
            file_list.push_back(sudoku.file_name()) ;
            if ( !s ) s = temp ;
        } // add_sudoku to Manager

        void create_sudoku_list(void) {
            cout << "creating file: " << list_file_name << endl ;
            // ************************ // may be buggy
            struct stat sb ;
            if ( ! ( stat( "sudoku\\", &sb ) == 0 && S_ISDIR( sb.st_mode ) ))
                system( "md sudoku" ) ;
            // ************************ // may be buggy
            ofstream file( list_file_name ) ;
            new_sudoku() ;
        } // create sudoku_list()

        void load_sudoku_list(void) {
            ifstream file( list_file_name ) ;
            if ( !file.is_open() ) return ;
            string sudoku_file_name ;
            while( file >> sudoku_file_name ) {
                ifstream sudoku_file(sudoku_file_name) ;
                if ( !sudoku_file.is_open() ) {
                    cout << "failed to open: " << sudoku_file_name << endl ;
                    return ;
                }
                string sudoku_str ;
                sudoku_file >> sudoku_str ;
                Sudoku sudoku(sudoku_str) ;
                readin_sudoku( sudoku ) ;
            }
        }

        /* * * * * * * * * * sudoku_list * * * * * * * * * * */


    // end protected
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    public:
        /* * * * * * * * * * constructors * * * * * * * * * * */
        /*  the constructor of Sudoku class
         */
        Manager() {
            s = NULL ;
            list_file_name = "sudoku\\sudokus.list" ;
            ifstream file( list_file_name ) ;
            if ( file.is_open() ) load_sudoku_list() ;
            else create_sudoku_list() ;
        } // constructor of Manager class

        void print_sudokus( void ) {
            for_each( sudoku_pointer_list.begin(), sudoku_pointer_list.end(),
                [](Sudoku* p){
                    p->print_sudoku() ;
                    cout << endl ;
                } ) ;
        } // print_sudokus()

    // end public
}; // class Manger

#endif // MANAGER_HPP_INCLUDED
