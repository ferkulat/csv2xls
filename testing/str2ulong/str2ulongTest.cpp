#include "../src/str2ulong.hpp"
#include "CppUTest/TestHarness.h"





TEST_GROUP(Group1)
{
   unsigned long num;

   void setup()
   {

      // Init stuff
   }

   void teardown()
   {
      // Uninit stuff
   }	
};

TEST(Group1,fails_on_negative_value)
{    
    CHECK ( !csv2xls::str2ulong("-1",num,10));
    CHECK ( !csv2xls::str2ulong("-1",num,0));
}

TEST(Group1,max_value)
{    
    CHECK ( !csv2xls::str2ulong("4294967296",num,4294967295U));
    CHECK ( !csv2xls::str2ulong("67296",     num,65536));
    CHECK (  csv2xls::str2ulong("67296",     num,67296));
    LONGS_EQUAL (67296, num);
}




