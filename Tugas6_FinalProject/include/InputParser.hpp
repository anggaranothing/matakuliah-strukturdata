#pragma once

#ifndef AN_INPTPRSR_H
#define AN_INPTPRSR_H

#include <iostream>
#include <string>

namespace AN
{

    const char ASCII_LF = 10;
    const char ASCII_CR = 13;


    void getInput( std::string& output )
    {
        output.clear();

        char input;
        while( true )
        {
            input = std::cin.get();
            if( input == ASCII_LF || input == ASCII_CR ) break;
            output += input;
        }
    }


    void getInput( double& output )
    {
        char* pEnd = NULL;
        double temp;

        std::string buffer;
        getInput( buffer );
        temp = strtod( buffer.c_str() , &pEnd );
        if( buffer.empty() || !( pEnd != 0 && *pEnd == 0 ) ) return;
        output = temp;
    }


    void getInput( int& output )
    {
        double buffer = output;
        getInput( buffer );
        output = buffer;
    }


    void getInput( float& output )
    {
        double buffer = output;
        getInput( buffer );
        output = buffer;
    }

}
#endif
