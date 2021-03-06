//=================================================================
//
//        strncpy1.c
//
//        Testcase for C library strncpy()
//
//=================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002, 2006 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//=================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     ctarpy, jlarmour
// Contributors:  
// Date:          2000-04-30
// Description:   Contains testcode for C library strncpy() function
//
//
//####DESCRIPTIONEND####

// INCLUDES

#include <pkgconf/isoinfra.h>
#include <string.h>
#include <cyg/infra/testcase.h>


// FUNCTIONS

// Functions to avoid having to use libc strings

static int my_strlen(const char *s)
{
    const char *ptr;

    ptr = s;
    for ( ptr=s ; *ptr != '\0' ; ptr++ )
        ;

    return (int)(ptr-s);
} // my_strlen()


static int my_strncmp(const char *s1, const char *s2, size_t n)
{
    if (n==0)
        return 0;
    
    while (n-- != 0 && *s1 == *s2)
    {
        if (n == 0 || *s1 == '\0' || *s2 == '\0')
            break;
        s1++;
        s2++;
    }
    
    return (*s1 - *s2);
} // my_strncmp()


static int my_strcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2 ; s1++,s2++ )
    {
        if ( *s1 == '\0' )
            break;
    } // for

    return (*s1 - *s2);
} // my_strcmp()


static char *my_strcpy(char *s1, const char *s2)
{
    while (*s2 != '\0') {
        *(s1++) = *(s2++);
    }
    *s1 = '\0';

    return s1; 
} // my_strcpy()


#if CYGINT_ISO_MAIN_STARTUP
int
main( int argc, char *argv[] )
#else
void cyg_user_start(void)
#endif
{
    char x[300];
    char y[300];
    char *ret;

    CYG_TEST_INIT();

    CYG_TEST_INFO("Starting tests from testcase " __FILE__ " for C library "
                  "strncpy() function");
    CYG_TEST_INFO("This testcase provides simple basic tests");

    // Check 1
    my_strcpy(x, "Nine rings for men doomed to die");
    ret = strncpy(y, "Nine rings for men doomed to die", my_strlen(x));
    CYG_TEST_PASS_FAIL( (my_strncmp(x, y, my_strlen(x)) == 0),
                        "Simple copy" );
    // Check return value
    CYG_TEST_PASS_FAIL( (y == ret), "Simple copy return value" );


    // Check 2
    my_strcpy(x, "");
    my_strcpy(y, "Seven rings for the dwarves in their halls of stone");
    ret = strncpy(y, x, 1);
    CYG_TEST_PASS_FAIL( (my_strcmp(y, "") == 0), "Copy empty string" );
    // Check return value
    CYG_TEST_PASS_FAIL( (y == ret), "Copy empty string return value" );

    // Check 3
    my_strcpy(x, "");
    my_strcpy(y, "Seven rings for the dwarves in their halls of stone");
    ret = strncpy(y, x, 0);
    if (my_strcmp(y, "Seven rings for the dwarves "
                     "in their halls of stone") == 0)
        CYG_TEST_PASS("Copy 0 characters");
    else
        CYG_TEST_FAIL("Copy 0 characters");
    // Check return value
    CYG_TEST_PASS_FAIL( (y == ret), "Copy empty string return value" );

//    CYG_TEST_NA("Testing is not applicable to this configuration");

    CYG_TEST_FINISH("Finished tests from testcase " __FILE__ " for C library "
                    "strncpy() function");

} // main()

// EOF strncpy1.c
