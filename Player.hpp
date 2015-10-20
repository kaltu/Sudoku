#include <string>
#include <iostream>
#include <windows.h>
#include "Sudoku.hpp"
using namespace std ;
class Player{
  protected:
    string name ;
    int spendtime = 0
    Sudoku *now_sudoku ;
    bool *uncorrect ;

    void stage(){

    } // stage()

    void exercise() {

    } // exercise()

    int score() {

    } // score()

    void set_now( Sudoku sudoku ) {
      now_sudoku = sudoku ;
    } // set_now()
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
      // set boolean
      uncorrect = new bool[9][9] ;
      for ( int i = 0 ; i < now_sudoku.sudoku_size ; i++ )
        for ( int j = 0 ; j < now_sudoku.sudoku_size ; j++ )
          uncorrect[i][j] = true ;
      // set boolean
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

    void printNow( int num ) {
        for ( int x = 0 ; x < sudoku_size ; cout << endl, ++x )
            for ( int y = 0 ; y < sudoku_size ; ++y )
                if ( !uncorrect[x][y] ) {
                    SetColor( 7, 70 ) ;
                    cout << num << " " ;
                    SetColor() ;
                } // if()
                else if ( sudoku[x][y] ) cout << sudoku[x][y] << " " ;
                else cout << "  " ;
    } // printNow()
  // end public
}; // Player
