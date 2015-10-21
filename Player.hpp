#include <string>
#include <iostream>
#include <windows.h>
#include "Sudoku.hpp"
using namespace std ;
class Player{
  protected:
    string name ;
    int spendtime, size ;
    Sudoku *now_sudoku ;
    bool **uncorrect ;

    void build_bool() {
      uncorrect = new bool*[9] ;
      for ( int i = 0 ; i < 9 ; i++ )
        uncorrect[i] = new bool[9] ;
      for ( int x = 0 ; x < size ; x++ )
        for ( int y = 0 ; y < size ; y++ )
          uncorrect[x][y] = true ;
    } // build_bool()

    void stage(){

    } // stage()

    void exercise() {
      int x, y, num ;
      int size, int_hardness ;
      cin >> size >> int_hardness ;
      now_sudoku = new Sudoku( size ) ;

      for ( printNow( num ) ; ! clearstage() ; printNow( num ) )
        enter_sudoku( x, y, num ) ;
      cout << "You passed it, Exercise end!" ;
    } // exercise()

    bool clearstage() {
      for ( int x = 0 ; x < size ; x++ )
        for ( int y = 0 ; y < size ; y++ )
          if ( ! now_sudoku[x][y] ) return false ;
      return true ;
    } // clearstage()

    int score( Hardness hardness, int spendtime ) {
      return spendtime = ( 1 / spendtime ) * hardness * 1000 ;
    } // score()

    /*
    check enter coordinate
    */
    void enter_coordinate( int x, int y ) {
      cout << "Enter coordinate to fill sudoku EX : 1 1 、 2 2\n" ;
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
      if ( ! now_sudoku[x][y] )
        if ( now_sudoku.correct( x, y, num,) ) now_sudoku[x][y] = num ;
        else uncorrect[x][y] = false ;
      else return enter_sudoku( x, y, num ) ;
    } // enter_sudoku()
  // end protected
  public:
    void SetColor( int ForeColor = 7, int BackGroundColor = 0 ){
        HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( hCon,ForeColor|BackGroundColor );
    } // SetColor()

    void doexercise() {
      exercise() ;
    } // doexercise()

    void printNow( int num ) {
        for ( int x = 0 ; x < size ; cout << endl, ++x )
            for ( int y = 0 ; y < size ; ++y )
                if ( !uncorrect[x][y] ) {
                    SetColor( 7, 70 ) ;
                    cout << num << " " ;
                    SetColor() ;
                } // if()
                else if ( now_sudoku[x][y] ) cout << now_sudoku[x][y] << " " ;
                else cout << "  " ;
    } // printNow()
  // end public
}; // Player
