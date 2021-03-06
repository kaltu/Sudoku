#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
using namespace std ;

enum Hardness { simple = 2, medium = 4, hard = 6 };
class Sudoku {
    protected:
    	Hardness sudoku_hardness ;
        int build_times, sudoku_size, cell_size ;
        int** sudoku ;
        bool* used ;
        string dirname, sudoku_str, sudoku_hash_str, sudoku_name ;
        size_t sudoku_hash ;                                                     // (size_t) means (unsigned long long int)

        /* * * * * * * * * * builders * * * * * * * * * * */

        /*   check if numbers were used in same cell
         */
        void check_cell( int x, int y ) {
            int x_start = ( x / cell_size ) * cell_size ;                        // perform floor division then production.
            int y_start = ( y / cell_size ) * cell_size ;
            for ( int i = x_start ; i < x_start + cell_size ; ++i )
                for ( int j = y_start; j < y_start + cell_size ; ++j )
                    if ( sudoku[i][j] ) used[ sudoku[i][j] ] = true ;
        } // check_cell()

        /*   check if numbers were used in same column and same row
         */
        void check_cross( int x, int y ) {
            for ( int i = 1 ; i < sudoku_size+1 ; ++i ) {
                if ( sudoku[x][i-1] )
                    used[ sudoku[x][i-1] ] = true ;
                if ( sudoku[i-1][y] )
                    used[ sudoku[i-1][y] ] = true ;
            } // for() 1 ~ sudoku_size
        } // check_cross()

        /*    generate and retrun an array of useage data
         */
        void check_useage( int x, int y ) {
            for ( int i = 0 ; i < sudoku_size+1 ; ++i ) used[i] = false ;        // initialize used[]
            check_cross( x, y ) ;
            check_cell( x, y ) ;
        } // check_useage()

        /*    generate and retrun an array of useage data
         */
        void check_column( int x, int y ) {
            for ( int i = 0 ; i < sudoku_size+1 ; ++i ) used[i] = false ;        // initialize used[]
            for ( int i = 1 ; i < sudoku_size+1 ; ++i )
                if ( sudoku[i-1][y] )
                    used[ sudoku[i-1][y] ] = true ;
            check_cell( x, y ) ;
        } // check_useage()

        /*  generate and return a random number witch must be valid
         */
        int random_valid( int x, int y ) {
            check_useage( x, y ) ;
            vector<int> v ;
            for ( int i = 1 ; i < sudoku_size+1 ; ++i )
                if ( !used[i] ) v.push_back( i ) ;
            return v.size() ? v[ rand() % v.size() ] : 0 ;
            // if there is no such number meets the rule, return -1.
        } // random_valid()

        /*   insert a valid number at specified (x, y)
         */
        bool insert_number( int x, int y ) {
            int num = random_valid( x, y ) ;                                     // get a random number witch is available to ( x, y )
            if ( num ) {                                                         // if number found ( num != 0 )
                sudoku[x][y] = num ;                                             // set it to sudoku[x][y]
                return true ;                                                    // return success
            }
            else                                                                 // else no such number ( num == 0 )
                return false ;                                                   // return failure
        } // insert_number()

        /*   bool( random_valid() )
         */
        bool changeable( int x, int y ) {
            return random_valid( x, y ) ;
        } // changeable()

        /*   should replace one number in x axi
         *   so that (x, y) can insert new number
         */
        bool replace( int x, int y ) {
            check_column( x, y ) ;                                               // check useage data at ( x, y )
            for ( int i = 0 ; i < y ; i++ )                                      // for numbers in range ( x, 0 ) ~ ( x, y-1 )
                if ( ! used[ sudoku[x][i] ] && changeable( x, i ) ) {            // if number at ( x, i ) is available at ( x, y ) and is changeable
//                    cout << "swap ( " << x << ", " << i << " ) with ( "
//                         << x << ", " << y << " )" << endl ;
                    sudoku[x][y] = sudoku[x][i] ;                                // the number at ( x, i ) is now the number of ( x, y )
                    insert_number( x, i ) ;                                      // give ( x, i ) new number
                    return true ;                                                // return successfally find a number for ( x, y )
                } // if()
            return false ;                                                       // failed to find a number for ( x, y )
        } // replace() uncompelet

        bool re_build( int x, int &y, int &retry_count ) {
            if ( retry_count < 5 ) {
                ++retry_count ;
                y = -1 ; // so that after ++y it's 0
                for ( int i = 0 ; i < sudoku_size ; ++i )
                    sudoku[x][i] = 0 ;
                return true ;
            } // re-build current x-axi untill retry limit.
            else return false ; // we failed this time.
        }

        /*   main method to build the sudoku
         */
        bool build_sudoku(void) {
            int retry_count = 0 ;
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0, retry_count = 0 ; y < sudoku_size ; ++y )
                    if ( !insert_number( x, y ) )                                // if insert failed
                        if ( !replace( x, y ) )                                  // try replace previous number with current location
                            if ( !re_build( x, y, retry_count) )                 // replace failed, abort current line and retry
                                return false ;                                   // even rebuild also failed, return false, we did our best
            return true ; // build success
        } // build_sudoku()

        /* * * * * * * * * * * builders * * * * * * * * * * */
        /* * * * * * * * * * * methods * * * * * * * * * * * */

        /*   clear or initialize the sudoku
         */
        void clear(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    sudoku[x][y] = 0 ;
        } // clear()

        /*
        隨機產生座標後
        判斷若可以挖洞
        就挖掉填成0
        若不行就重來
        */
        void dig(void) {
          int hole = sudoku_size > 4 ? (2+sudoku_hardness) * sudoku_size : sudoku_hardness * cell_size ;
          for( int i = 0 ; i < hole ; i++ ) {
            int x = ( rand() % sudoku_size ) ;
            int y = ( rand() % sudoku_size ) ;
            int r = sudoku[x][y] ;
            sudoku[x][y] = 0 ;
            if ( not diggable( x, y) ) {
              sudoku[x][y] = r ;
              i-- ;
            } // if
          } // for()
        } // dig()
        /*
        判斷此座標是否可以挖洞
        如果挖洞的座標有小於難度的解挖
        不行就不給挖
        */
        bool diggable( int x, int y ) {
            for ( int i = 0 ; i < sudoku_size+1 ; ++i ) used[i] = false ;
            check_cell( x, y ) ;
            check_cross( x, y ) ;
            int solution = 0 ;
            for ( int i = 1 ; i < sudoku_size+1 ; i++ )
                if ( ! used[i] ) solution++ ;
            if ( 0 < solution && solution <= sudoku_hardness ) return true ;
            return false ;
        } // diggable()

        void set_hash(void) {
            std::hash<string> hasher ;
            sudoku_hash = hasher( sudoku_str ) ;
            stringstream ss ; // using stringstream convert hash into string
            ss << sudoku_hash ;
            ss >> sudoku_hash_str ;
        } // set_hast()

        void set_str(void) {
            string str = "" ;
            stringstream ss ;
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    ss << sudoku[x][y] ;
            ss >> str ;
            sudoku_str = str ;
        } // set_str()

        void set_name(void) {
            stringstream ss ;
            ss << "sudoku" << sudoku_size << "\\" << sudoku_hash_str << ".sudoku" ;
            sudoku_name = ss.str() ;
        } // set_name()

        void set_num( int x, int y, int num ) {
          sudoku[x][y] = num ;
        } // set_num()

        /* * * * * * * * * * * methods * * * * * * * * * * * */

    // end protected
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    public:
        /* * * * * * * * * * constructors * * * * * * * * * * */
        /*  the constructor of Sudoku class
         */
        Sudoku( int size = 4 ) {
            if ( size != 9 ) size = 4 ;                                          // only 4*4 or 9*9 sudoku is allowed
            sudoku_size = size ;
            cell_size = size % 3 ? 2 : 3 ;
            used = new bool[ size ] ;
            sudoku = new int*[ size ] ;                                          // sudoku is a pointer of integer pointer (int**)
            for ( int i = 0 ; i < size ; ++i )
                sudoku[i] = new int[ size ] ;
            int times = 0 ;
            do {
                ++times ;
                clear() ;
            } while( !build_sudoku() ) ; // rebuild until success
            build_times = times ;
            set_str() ;
            set_hash() ;
            set_name() ;
            sudoku_hardness = simple ;
            stringstream ss ;
            ss << "sudoku" << sudoku_size << "\\" ;
            dirname = ss.str() ;
        } // constructor by specified size

        Sudoku( string str ) {
            if ( str.size() == 16 ) sudoku_size = 4 ;
            else sudoku_size = 9 ;
            cell_size = sudoku_size % 3 ? 2 : 3 ;
            used = new bool[ sudoku_size ] ;
            sudoku = new int*[ sudoku_size ] ;                                   // sudoku is a pointer of integer pointer (int**)
            for ( int i = 0 ; i < sudoku_size ; ++i )
                sudoku[i] = new int[ sudoku_size ] ;
            build_times = 0 ;
            stringstream ss(str);
            char current ;
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y ) {
                    ss >> current ;
                    sudoku[x][y] = current - '0' ;                               // ascii - '0' = integer
                }
            set_str() ;
            set_hash() ;
            set_name() ;
            sudoku_hardness = simple ;
            ss.clear() ;
            ss << "sudoku" << sudoku_size << "\\" ;
            dirname = ss.str() ;
        } // constructor by string representation of other Sudoku object

        Sudoku( const Sudoku& other ) {
            *this = other ;
        } // constuctor by other Sudoku object

        ~Sudoku() {
            for ( int i = 0 ; i < sudoku_size ; ++i )
                delete sudoku[i] ;
            delete sudoku ;
            delete used ;
        } // destructor of Sudoku class

        /* * * * * * * * * * constructors * * * * * * * * * * */
        /* * * * * * * * * * * operators * * * * * * * * * * * */

        Sudoku& operator=( const Sudoku& Other ) {
            build_times = Other.build_times ;
            sudoku_size = Other.sudoku_size ;
            cell_size = Other.cell_size ;

            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++ y )
                    sudoku[x][y] = Other.sudoku[x][y] ;

            dirname = Other.dirname ;
            sudoku_str = Other.sudoku_str ;
            sudoku_hash_str = Other.sudoku_hash_str ;
            sudoku_name = Other.sudoku_name ;
            sudoku_hash = Other.sudoku_hash ;
            sudoku_hardness = Other.sudoku_hardness ;

            return *this ;
        } // operator overloading =

        /* * * * * * * * * * * operators * * * * * * * * * * * */
        /* * * * * * * * * * * methods * * * * * * * * * * * */

        /*   check if the sudoku is fully filled
         */
        bool self_check(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++ y )
                    if ( !sudoku[x][y] ) return false ;
            return true ;
        } // self_check()

        /*   print out whole sudoku
         */
        void print_sudoku(void) {
            for ( int x = 0 ; x < sudoku_size ; cout << endl, ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y )
                	if ( sudoku[x][y] ) cout << sudoku[x][y] << " " ;
                    else cout << "  " ;
        } // print_sudoku()

        /*   print out the cell witch specified (x, y) located.
         */
        void print_cell( int x, int y ) {
            int x_start = ( x / cell_size ) * cell_size ;                        // perform floor division then production.
            int y_start = ( y / cell_size ) * cell_size ;
            for ( int i = x_start ; i < x_start + cell_size ; ++i ) {
                for ( int j = y_start; j < y_start + cell_size ; ++j )
                    cout << sudoku[i][j] << " " ;
                cout << endl ;
            } // for()
        } // print_cell()

        /*   save this sudoku into file
         */
        void save( string filename = "" ) {
            if ( filename == "" ) filename = hash_str() ;
            // ************************ // may be buggy
            struct stat sb ;
            if ( ! ( stat( dirname.c_str(), &sb ) == 0 && S_ISDIR( sb.st_mode ) )) {
                stringstream ss ;
                ss << "md sudoku" << sudoku_size ;
                system( ss.str().c_str() ) ;
            }
            // ************************ // may be buggy
            try {
                ofstream file( sudoku_name ) ;
                if ( !file ) {
                    cout << "error: failed to open '" << sudoku_name << "'" << endl ;
                    return ;
                }
                file << sudoku_str ;
                file.close() ;
            } // try
            catch ( exception e ) {
                cout << "error: " << e.what() << endl ;
            } // catch()
        } // save sodoku

        /*   delete saved sudoku file
         */
        void delete_sudoku(void) {
            string filename = dirname + hash_str() + ".sudoku" ;
            std::remove( filename.c_str() ) ;
        } // delete_sudoku()

        /*   set hardness to this sudoku
         */
        void set_hardness( Hardness hardness ) {
        	  this->sudoku_hardness = hardness ;
              dig() ;
        } // set_hardness()

        bool correct( int x, int y, int number ) {
            for ( int i = 0 ; i < sudoku_size+1 ; i++ ) used[i] = false ;
            check_cell( x, y ) ;
            check_cross( x, y ) ;
            return used[number] ;
        } // correct()

        void set_array( int x, int y, int num ) {
          set_num( x, y, num ) ;
        } // set_array()

        int rtn_sudoku( int x, int y ) {
          return sudoku[x][y] ;
        } // rtn_sudoku()

        /* * * * * * * * * * * methods * * * * * * * * * * * */
        /* * * * * * * * * * * getters * * * * * * * * * * * */

        size_t hash(void) {
            return sudoku_hash ;
        } // hash getter

        string hash_str(void) {
            return sudoku_hash_str ;
        } // hash_str getter

        /*  get how many times retried to build this sudoku
         */
        int times(void) {
            return build_times ;
        } // build_times getter

        string str(void) {
            return sudoku_str ;
        } // str getter

        string file_name(void) {
            return sudoku_name ;
        } // file_name getter

        int size(void) {
            return sudoku_size ;
        } // size getter

        /* * * * * * * * * * * getters * * * * * * * * * * * */
    // end public
}; // class Sudoku

#endif // SUDOKU_HPP_INCLUDED
