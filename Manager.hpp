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
    	int manager_size, sudoku_index ;
        Sudoku* s ;                                                              // current sudoku
        list<Sudoku*> sudoku_pointer_list ;
        list<string> file_list ;
        string list_file_name ;

        /* * * * * * * * * *sudoku_creater* * * * * * * * * * */

        void new_sudoku( void ) {
            Sudoku* temp = new Sudoku( manager_size ) ;
            temp->save() ;
            write_to_file( temp ) ;
            add_to_list( temp ) ;
        } // create a new sudoku

        void write_to_file( Sudoku* sptr ) {
            ofstream file( list_file_name ) ;
            if ( file.is_open() ) file << sptr->file_name() << endl ;
        }

        void add_to_list( Sudoku* sptr ) {
            sudoku_pointer_list.push_back(sptr) ;
            sudoku_index = sudoku_pointer_list.size() - 1 ;                      // update sudoku_inex by the index of newest sudoku object
            file_list.push_back( sptr->file_name() ) ;
            s = sptr ;                                                           // update s to pointing newest sudoku object
        } // add_to_list()

        /* * * * * * * * * *sudoku_creater* * * * * * * * * * */
        /* * * * * * * * * * sudoku_pointer_list * * * * * * * * * * */

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
                cout << "reading " << sudoku_file_name << endl ;
                ifstream sudoku_file(sudoku_file_name) ;
                if ( !sudoku_file.is_open() ) {
                    cout << "failed to open: " << sudoku_file_name << endl ;
                    return ;
                }
                string sudoku_str ;
                sudoku_file >> sudoku_str ;
                add_to_list( new Sudoku( sudoku_str ) ) ;
            }
        }

        /* * * * * * * * * * sudoku_list * * * * * * * * * * */

        void init() {
            int size = manager_size ;
            destructor() ;
            constructor( size ) ;
        }

        void destructor() {
            if ( s != nullptr ) {
                delete s ;
                s = nullptr ;
            }
            for_each( sudoku_pointer_list.begin(), sudoku_pointer_list.end(), [](Sudoku* p){
                if ( p != nullptr ) {
                    delete p ;
                    p = nullptr ;
                }
            }) ; // for ( p : sudoku_pointer_list )
            sudoku_pointer_list.clear() ;
            file_list.clear() ;
        } // destructor()

        void constructor( int size = 9 ) {
        	manager_size = size == 9 ? 9 : 4 ;
            s = nullptr ;
            list_file_name = "sudoku\\sudokus.list" ;
            ifstream file( list_file_name ) ;
            if ( file.is_open() ) load_sudoku_list() ;
            else create_sudoku_list() ;
        } // initializer()


    // end protected
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    public:
        /* * * * * * * * * * constructors * * * * * * * * * * */

        /*  the constructor of Sudoku class
         */
        Manager() {
            constructor() ;
        } // constructor of Manager class

        Manager( int size ) {
            constructor( size ) ;
        } // constructor of Manager class

        ~Manager() {
            destructor() ;
        } // destructor of Manager class

        /* * * * * * * * * * constructors * * * * * * * * * * */
        /* * * * * * * * * * * methods * * * * * * * * * * * */

        void delete_sudoku( void ) {

        } // delete_sudoku()

        void create_sudoku( void ) {

        } // new_sudoku()

        void print_sudokus( void ) {
            int index = 0, size = 2 * manager_size ;
            for_each( sudoku_pointer_list.begin(), sudoku_pointer_list.end(),
                [&index, size](Sudoku* p){
                    cout << index++ << endl ;
                    for ( int i = 1 ; i < size ; ++i )
                        cout << '=' ;
                    cout << endl ;
                    p->print_sudoku() ;
                    for ( int i = 1 ; i < size ; ++i )
                        cout << '=' ;
                    cout << endl ;
                } ) ;
        } // print_sudokus()

        void set_hardness( ) {
            Sudoku new_sudoku( manager_size ) ;
            new_sudoku = *s ;
            Hardness hardness ;
            cout << "Input hardness:" << endl << ">>> " ;
            int int_hardness ;
            cin >> int_hardness ;
            if ( int_hardness == 1 )
                hardness = simple ;
            else if ( int_hardness == 2 )
                hardness = medium ;
            else if ( int_hardness == 3 )
                hardness = hard ;
            else {
            	cout << "error: " << int_hardness << endl ;
            	return ;
			}
            new_sudoku.set_hardness( hardness ) ;
            new_sudoku.print_sudoku() ;
        } // set_hardness to current sudoku object

        /* * * * * * * * * * * methods * * * * * * * * * * * */
    // end public
}; // class Manger

#endif // MANAGER_HPP_INCLUDED
