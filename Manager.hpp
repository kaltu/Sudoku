#ifndef MANAGER_HPP_INCLUDED
#define MANAGER_HPP_INCLUDED

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include "Sudoku.hpp"
using namespace std ;

class Manager {
    protected:
    	int manager_size, sudoku_index ;
        Sudoku* s ;                                                              // current sudoku
        vector<Sudoku*> sudoku_pointer_list ;
        vector<string> file_list ;
        set<pair<int, string>> rank_list ;
        string list_file_name, rank_file_name ;

        /* * * * * * * * * *sudoku_creater* * * * * * * * * * */

        void new_sudoku( void ) {
            Sudoku* temp = new Sudoku( manager_size ) ;
            temp->save() ;
            add_to_list( temp ) ;
            write_to_file( temp ) ;
        } // create a new sudoku

        void write_to_file( Sudoku* sptr ) {
            ofstream file( list_file_name, std::ios_base::app ) ;
            if ( file.is_open() ) file << sptr->file_name() << endl ;
        }

        void rebuild_file_system(void) {
            ofstream file( list_file_name ) ;
            file << "" ;
            file.close() ;
            for ( int i = 0 ; i < sudoku_pointer_list.size() ; ++i )
                write_to_file( sudoku_pointer_list.at( i ) ) ;
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

        void load_rank_file(void) {
            ifstream file( rank_file_name ) ;
            if ( !file.is_open() ) return ;
            int score ;
            string player_name ;
            while( file >> score >> player_name ) {
                rank_list.insert( make_pair( score, player_name ) ) ;
            }
        }

        void save_rank_file(void) {
            ofstream file( rank_file_name ) ;
            auto ite = rank_list.rbegin() ;
            auto end = rank_list.rend() ;
            int count = 0 ;
            for ( ; ite != end && count < 10 ; ++ite, ++count )
                file << (*ite).first << " " << (*ite).second << endl ;
        }

        /* * * * * * * * * * sudoku_list * * * * * * * * * * */

        void print_line() {
            for ( int i = 1 ; i < 2 * manager_size ; ++i )
                cout << '=' ;
            cout << endl ;
        }

        void init() {
            int size = manager_size ;
            destructor() ;
            constructor( size ) ;
        }

        void destructor() {
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
            rank_file_name = "sudoku\\rank.rank" ;
            ifstream file( list_file_name ) ;
            if ( file.is_open() ) load_sudoku_list() ;
            else create_sudoku_list() ;
            load_rank_file() ;
        } // initializer()


    // end protected
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    public:
        /* * * * * * * * * * constructors * * * * * * * * * * */

        /*  the constructor of Sudoku class
         */
        Manager( int size = 9 ) {
            constructor( size ) ;
        } // constructor of Manager class

        ~Manager() {
            destructor() ;
        } // destructor of Manager class

        /* * * * * * * * * * constructors * * * * * * * * * * */
        /* * * * * * * * * * * methods * * * * * * * * * * * */

        void delete_sudoku( void ) {
             if ( sudoku_pointer_list.size() <= 1 ) {
                cout << "Error! You can not delete the only one sudoku." << endl ;
                return ;
            }
            print_sudoku() ;
            cout << "Do you want to delete this(as above) sudoku? (y/N)" << endl << ">>> " ;
            string ans ;
            cin >> ans ;
            if ( !( ans == "Y" || ans == "y" ) ) return ;
            s->delete_sudoku() ;
            delete s ;
            s = nullptr ;
            sudoku_pointer_list.erase( sudoku_pointer_list.begin() + sudoku_index ) ;
            if ( sudoku_pointer_list.size() ) {
                sudoku_index = sudoku_pointer_list.size() - 1 ;
                s = sudoku_pointer_list.at( sudoku_index ) ;
            }
            rebuild_file_system() ;
            print_sudoku() ;
        } // delete_sudoku()

        void create_sudoku( void ) {
            new_sudoku() ;
            print_sudoku() ;
        } // new_sudoku()

        void print_sudoku(void) {
            clear_screen() ;
            cout << sudoku_index << endl ;
            print_line() ;
            sudoku_pointer_list.at( sudoku_index )->print_sudoku() ;
        }

        void switch_sudoku( int index ) {
            if ( index >= sudoku_pointer_list.size() ) {
                cout << "Error! change to " << index << " while there is only "
                     << sudoku_pointer_list.size() << " sudokus." << endl ;
                return ;
            }
            sudoku_index = index ;
            s = sudoku_pointer_list.at(index) ;
        }

        void print_sudokus( void ) {
            int index = 0, size = 2 * manager_size ;
            for_each( sudoku_pointer_list.begin(), sudoku_pointer_list.end(),
                [&index, &size](Sudoku* p){
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

        void set_hardness( int int_hardness, Sudoku & new_sudoku ) {
            new_sudoku = *s ;
            Hardness hardness ;
            cout << "Input hardness:" << endl << ">>> " ;
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

        void clear_screen(void) {
            system( "cls" ) ;
        } // clear_screen()

        Sudoku* request_quesion(void) {
          return sudoku_pointer_list.at( rand() % sudoku_pointer_list.size() ) ;
        } // request_quesion()

        void add_to_rank( int score = 0, string name = "unnamed" ) {
            rank_list.insert( make_pair( score, name ) ) ;
            save_rank_file() ;
        } // add_to_rank()

        void print_rank(void) {
            auto ite = rank_list.rbegin() ;
            auto end = rank_list.rend() ;
            int count = 0 ;
            for ( ; ite != end && count < 10 ; ++ite, ++count )
                cout << (*ite).first << " : " << (*ite).second << endl ;
        } // print_rank()
        /* * * * * * * * * * * methods * * * * * * * * * * * */
    // end public
}; // class Manger

#endif // MANAGER_HPP_INCLUDED
