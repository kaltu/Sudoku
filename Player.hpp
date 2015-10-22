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
      cout << "bool table finished" << endl ;
    } // build_bool()

    void stage(){
      exercise() ;
      exercise(2) ;
      exercise(3) ;
    } // stage()

    void exercise( int int_hardness = 1 ) {
      int x, y, num ;
      cout << "select sudoku size\n" ;
      cin >> size ;
      if ( int_hardness == 1 ) hardness = simple ;
      else if ( int_hardness == 2 ) hardness = medium ;
      else if ( int_hardness == 3 ) hardness = hard ;

      now_sudoku->set_hardness( hardness ) ;
      clock_t s_star, s_end ;
      s_star = clock() ;
      for ( now_sudoku->print_sudoku() ; ! clearstage() ; printNow( num ) )
        enter_sudoku( x, y, num ) ;
      s_end = clock() ;
      s_score = score( ( double( s_end - s_star ) / CLOCKS_PER_SEC ) / 60.0 ) ;
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
      if ( ! ( ( 0 <= x && x < 9 ) && ( 0 <= y && y < 9 ) ) ) {
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
      if ( ! ( 0 < num && num < 10 ) ) return enter_sudoku( x, y, num ) ;
      cout << "not num problemQQ!\n" ;
      if ( ! now_sudoku->rtn_sudoku( x, y ) )
        if ( ! now_sudoku->correct( x, y, num ) ) now_sudoku->set_array( x, y, num ) ;
        else uncorrect[x][y] = false ;
      else return enter_sudoku( x, y, num ) ;
    } // enter_sudoku()
  // end protected
  public:

    Player() {
      now_sudoku = new Sudoku(9) ;
    } // Player()

    void SetColor( int ForeColor = 7, int BackGroundColor = 0 ){
        HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( hCon,ForeColor|BackGroundColor );
    } // SetColor()

    void doexercise() {
      stage() ;
    } // doexercise()

    void printNow( int num ) {
        for ( int x = 0 ; x < size ; cout << endl, ++x )
            for ( int y = 0 ; y < size ; ++y )
                if ( !uncorrect[x][y] ) {
                    SetColor( 7, 70 ) ;
                    cout << num ;
                    SetColor() ;
                    cout << " " ;
                } // if()
                else if ( now_sudoku->rtn_sudoku( x, y ) ) cout << now_sudoku->rtn_sudoku( x, y ) << " " ;
                else cout << "  " ;
    } // printNow()
  // end public
}; // Player
