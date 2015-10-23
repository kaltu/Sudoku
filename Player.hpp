#include <string>
#include <iostream>
#include <windows.h>
#include "Sudoku.hpp"
#include "Manager.hpp"
#include <ctime>
using namespace std ;
class Player{
  protected:
    string name ;
    int spendtime, size, s_score ;
    int cell_size ;
    Hardness hardness ;
    Sudoku *now_sudoku;
    bool **uncorrect ;

    void build_bool() {
      uncorrect = new bool*[size] ;
      for ( int i = 0 ; i < size ; i++ )
        uncorrect[i] = new bool[size] ;
      for ( int x = 0 ; x < size ; x++ )
        for ( int y = 0 ; y < size ; y++ )
          uncorrect[x][y] = true ;
    } // build_bool()

    void exercise( int int_hardness = 1 ) {
      int x, y, num ;
      size = now_sudoku->size() ;
      if ( size == 9 ) cell_size = 3 ;
      else cell_size = 2 ;
      if ( int_hardness == 1 ) hardness = simple ;
      else if ( int_hardness == 2 ) hardness = medium ;
      else if ( int_hardness == 3 ) hardness = hard ;

      now_sudoku->set_hardness( hardness ) ;
      clock_t s_star, s_end ;
      s_star = clock() ;
      for ( init_sudoku() ; ! clearstage() ; printNow( num ) )
        enter_sudoku( x, y, num ) ;
      s_end = clock() ;
      s_score = score( ( double( s_end - s_star ) / CLOCKS_PER_SEC ) / 60.0 ) ;
      system( "cls" ) ;
      cout << "You passed it, Exercise end! You get " << s_score << " score!\n";
    } // exercise()

    bool clearstage() {
      for ( int x = 0 ; x < size ; x++ )
        for ( int y = 0 ; y < size ; y++ )
          if ( ! now_sudoku->rtn_sudoku( x, y ) ) return false ;
      return true ;
    } // clearstage()

    int score( double spendtime ) {
      return spendtime = ( 1.0 / spendtime ) * hardness * 1000 ;
    } // score()

    /*
    check enter coordinate
    */
    void enter_coordinate( int & x, int & y ) {
      cout << "Enter coordinate to fill sudoku EX : 1 1\n3\nor 2 2 3\n" ;
      cin >> x >> y ;
      if ( ! ( ( 0 <= x && x < size ) && ( 0 <= y && y < size ) ) ) {
        cout << "Error coordinate Please try again!\n" ;
        return enter_coordinate( x, y ) ;
      } // if()
    } // enter_coordinate()
    /*
    check coordinate and number to sukoku is ok?
    */
    void enter_sudoku( int x, int y, int num ) {
      build_bool() ;
      enter_coordinate( x, y ) ;
      cin >> num ;
      if ( ! ( 0 < num && num < size + 1 ) ) return enter_sudoku( x, y, num ) ;
      cout << "not num problemQQ!\n" ;
      if ( ! now_sudoku->rtn_sudoku( x, y ) )
        if ( ! now_sudoku->correct( x, y, num ) ) now_sudoku->set_array( x, y, num ) ;
        else uncorrect[x][y] = false ;
      else return enter_sudoku( x, y, num ) ;
    } // enter_sudoku()

    void update_sudoku( Sudoku * sudoku ) {
      now_sudoku = sudoku ;
    } // update_sudoku()
  // end protected
  public:

    Player() {
      now_sudoku = new Sudoku(9) ;
    } // Player()

    Player( Sudoku *readlist ) {
      now_sudoku = readlist ;
      cout << "Enter your name..." << endl ;
      cin >> name ;
    } // Player()

    void SetColor( int ForeColor = 7, int BackGroundColor = 0 ){
        HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( hCon,ForeColor|BackGroundColor );
    } // SetColor()

    void exerciseMode() {
      system( "cls" ) ;
      exercise() ;
    } // exerciseMode()

    void stageMode( Manager & manager ) {
      exercise() ;
      cout << "Stage 1 clear!! do next!" << endl ;
      update_sudoku( manager.request_quesion() ) ;
      exercise(2) ;
      cout << "Stage 2 clear!! do next!" << endl ;
      update_sudoku( manager.request_quesion() ) ;
      exercise(3) ;
      cout << "All stage clear!!" << endl ;
    } // stageMode()

    void printNow( int num ) {
        system( "cls" ) ;
        Print_xcoordinate() ;
        Print_ycoordinate(0) ;
        for ( int x = 0 ; x < size ; cout << endl, ++x, Print_ycoordinate(x) ) {
            for ( int y = 0 ; y < size ; ++y ) {
                int c_x = ( x / cell_size ) * cell_size ;
                int c_y = ( y / cell_size ) * cell_size ;
                if ( !uncorrect[x][y] ) {
                    SetColor( 7, 70 ) ;
                    cout << " " ;
                    SetColor() ;
                    cout << " " ;
                } // if()
                else if ( now_sudoku->rtn_sudoku( x, y ) )
                  set_color( c_x, c_y, now_sudoku->rtn_sudoku( x, y ) ) ;
                else cout << "  " ;
            } // for
            Print_ycoordinate(x) ;
        } // for
        Print_xcoordinate() ;
    } // printNow()

    void init_sudoku(void) {
      Print_xcoordinate() ;
      Print_ycoordinate(0) ;
      for ( int x = 0 ; x < size ; cout << endl, ++x, Print_ycoordinate(x) ) {
        for ( int y = 0 ; y < size ; ++y ) {
          int c_x = ( x / cell_size ) * cell_size ;
          int c_y = ( y / cell_size ) * cell_size ;
          if ( now_sudoku->rtn_sudoku( x, y ) )
            set_color( c_x, c_y, now_sudoku->rtn_sudoku( x, y ) ) ;
          else cout << "  " ;
        } // for
        Print_ycoordinate(x) ;
      } // for
      Print_xcoordinate() ;
    } // print_sudoku()

    void set_color( int x, int y, int sudoku ) {
      if ( ( x % 2 == 0 && y % 2 != 0 ) || ( x % 2 != 0 && y % 2 == 0 ) ) {
        SetColor( 7, 90 ) ;
        cout << sudoku << " " ;
        SetColor() ;
      }
      else
        cout << sudoku << " " ;
    } // set_color()

    void Print_xcoordinate() {
      SetColor( 7, 50 ) ;
      cout << "  " ;
      for ( int i = 0 ; i < size ; cout << i << " ", i++ ) ;
      cout << " " << endl ;
      SetColor() ;
    } // Print_xcoordinate()

    void Print_ycoordinate( int i ) {
      if( i < size ) {
        SetColor( 7, 50 ) ;
        cout << i ;
        SetColor() ;
        cout << " " ;
      } // if
    } // Print_ycoordinate()

  // end public
}; // Player
