#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std ;

#include "Sudoku.hpp"

int main( int argc, char** argv ) {
    srand(time(NULL));
    int times[10000] = {} ;
    unsigned long long sum = 0 ;
    int max = 0, min = 900 ;
    for ( int i = 0 ; i < 10000 ; ++i ) {
        Sudoku sudoku(9) ;
        times[i] = sudoku.times() ;
        sum += times[i] ;
        if ( times[i] > max ) max = times[i] ;
        if ( times[i] < min ) min = times[i] ;
        if ( ! ( i % 1000 ) )
            cout << i << ": " << times[i] << endl ;
    }
    double t = 10000.00 ;
    double ave = sum / t ;
    double sig = 0, e = 0 ;
    for ( int i = 0 ; i < 10000 ; i++ )
        e += (times[i] - ave) * (times[i] - ave) ;
    sig = sqrt(e / 10000 ) ;
    cout << "===========================" << endl
         << "statistic of 10,000 times: " << endl
         << "max: " << max << endl 
         << "min: " << min << endl
         << "ave: " << ave << endl
         << "sig: " << sig << endl ;
        
    return 0 ;
} // main

