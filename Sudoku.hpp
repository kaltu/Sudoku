#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

class Sudoku {
    protected:
        int build_times, sudoku_size, cell_size ;
        int** sudoku ;
        string sudoku_str ;
        std::size_t sudoku_hash ;                                                // (size_t) means (unsigned long long int)

        /* * * * * * * * * * builders * * * * * * * * * * */

        /*   check if numbers were used in same cell
         */
        void check_cell( int x, int y, bool* used ) {
            int x_start = ( x / cell_size ) * cell_size ;                        // perform floor division then production.
            int y_start = ( y / cell_size ) * cell_size ;
            for ( int i = x_start ; i < x_start + cell_size ; ++i )
                for ( int j = y_start; j < y_start + cell_size ; ++j )
                    if ( sudoku[i][j] ) used[ sudoku[i][j] ] = true ;
        } // check_cell()

        /*   check if numbers were used in same column and same row
         */
        void check_cross( int x, int y, bool* used ) {
            for ( int i = 1 ; i < sudoku_size+1 ; ++i ) {
                if ( sudoku[x][i-1] )
                    used[ sudoku[x][i-1] ] = true ;
                if ( sudoku[i-1][y] )
                    used[ sudoku[i-1][y] ] = true ;
            } // for() 1 ~ sudoku_size
        } // check_cross()

        /*    generate and retrun an array of useage data
         */
        bool* check_useage( int x, int y ) {
            bool* used = new bool[ sudoku_size+1 ] ;
            for ( int i = 0 ; i < sudoku_size+1 ; ++i ) used[i] = false ;        // initialize used[]
            check_cross( x, y, used ) ;
            check_cell( x, y, used ) ;
            return used ;
        } // check_useage()

        /*    generate and retrun an array of useage data
         */
        bool* check_column( int x, int y ) {
            bool* used = new bool[ sudoku_size+1 ] ;
            for ( int i = 0 ; i < sudoku_size+1 ; ++i ) used[i] = false ;        // initialize used[]
            for ( int i = 1 ; i < sudoku_size+1 ; ++i )
                if ( sudoku[i-1][y] )
                    used[ sudoku[i-1][y] ] = true ;
            check_cell( x, y, used ) ;
            return used ;
        } // check_useage()

        /*  generate and return a random number witch must be valid
         */
        int random_valid( int x, int y ) {
            bool* used = check_useage( x, y ) ;
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
            bool *used = check_column( x, y ) ;                                  // check useage data at ( x, y )
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
                    if ( !insert_number( x, y ) )
                        if ( !replace( x, y ) )
                            if ( !re_build( x, y, retry_count) )
                                return false ;
            return true ;
        } // build_sudoku()

        /* * * * * * * * * * builders * * * * * * * * * * */
        /* * * * * * * * * * * commands * * * * * * * * * * * */

        /*   clear or initialize the sudoku
         */
        void clear(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    sudoku[x][y] = 0 ;
        } // clear()

        void set_hash(void) {
            std::hash<std::string> hasher ;
            sudoku_hash = hasher( sudoku_str ) ;
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

        /* * * * * * * * * * * commands * * * * * * * * * * * */

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
        } // constructor of Sudoku class

        /* * * * * * * * * * constructors * * * * * * * * * * */
        /* * * * * * * * * * * commands * * * * * * * * * * * */

        bool self_check(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x )
                for ( int y = 0 ; y < sudoku_size ; ++ y )
                    if ( !sudoku[x][y] ) return false ;
            return true ;
        } // self_check()

        /*   print out whole sudoku
         */
        void print_sudoku(void) {
            for ( int x = 0 ; x < sudoku_size ; ++x ) {
                for ( int y = 0 ; y < sudoku_size ; ++y )
                    cout << sudoku[x][y] << " " ;
                cout << endl ;
            } // for()
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

        void save(void) {
            stringstream ss ;
            ss << "sudoku\\" << sudoku_hash << ".sudoku" ;
            string name = "" ;
            ss >> name ;
            try {
                fstream file ;
                file.open( name.c_str(), ios::out | ios::trunc ) ;
                if ( !file ) {
                    cout << "error: failed to open '" << name << "'" << endl ;
                    return ;
                }
                string str = sudoku_str ;
                file.write( str.c_str(), str.size() ) ;
                file.close() ;
            } // try
            catch ( exception e ) {
                cout << "error: " << e.what() << endl ;
            } // catch()
        } // save sodoku

        /* * * * * * * * * * * commands * * * * * * * * * * * */
        /* * * * * * * * * * * getters * * * * * * * * * * * */

        std::size_t hash(void) {
            return sudoku_hash ;
        } // hash getter

        /*  get how many times retried to build this sudoku
         */
        int times(void) {
            return build_times ;
        } // build_times getter

        string str(void) {
            return sudoku_str ;
        } // str getter

        /* * * * * * * * * * * getters * * * * * * * * * * * */

    // end public
}; // class Sudoku

#endif // SUDOKU_HPP_INCLUDED
