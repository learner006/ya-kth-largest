/***********************************
00-61-ya-kth-largest-source-code.cpp
***********************************/

//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <exception>
#include <vector>
//---------------------------------------------------------------------------
using std::string;
using std::vector;
//---------------------------------------------------------------------------
const char* E_BAD_INDEX = "Array index must be >= 0!";
const char* E_COUNT_FOR_CHAR_IS_ZERO = "Count for key (%c) is equal or less than zero!";

// Easy indexing using 1 byte numeric characters codes
int& arr_item(int *p_arr, char p_charIndex, char p_charBase = '0');
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   const char* TEST_SUITE1_DATA[][3] = {
      {"812675429038","917608128",
       "988776429238"},
      {"812675429038","17608128",
       "888776429238"},
      {"124","1",
       "124"},
      {"124","9",
       "924"},
      {"6295323672435","5386210",
       "8695533672435"},
      {"6295323602430","5386210",
       "8695533622431"}
   };

   const int inputIndex = 0;
   
   string A = TEST_SUITE1_DATA[inputIndex][0];
   const string B = TEST_SUITE1_DATA[inputIndex][1];
   const string A_backup = A;

   std::cout << "B: " << A << std::endl;

   int B_digitCountersArray[] = {0,0,0,0,0,0,0,0,0,0};

   // count number of occurencies for each character from B string
   for(unsigned n = 0; n < B.length(); ++n)
      ++arr_item(B_digitCountersArray,B[n]);

   char charIndexToSubstitute = '9';

   // search for non-zero counter for 'highest' digit 9,8,7,6 etc
   // out: charIndexToSubstitute
   charIndexToSubstitute++;
   while (charIndexToSubstitute > '0' && arr_item(B_digitCountersArray,--charIndexToSubstitute) == 0)
      ;

   for(unsigned n = 0; n < A.length() && charIndexToSubstitute > '0'; ++n)
   {
      if (A[n] < charIndexToSubstitute)
      {
         if (arr_item(B_digitCountersArray,charIndexToSubstitute) <= 0)
            throw new std::runtime_error(E_COUNT_FOR_CHAR_IS_ZERO);

         A[n] = charIndexToSubstitute;
         if (--arr_item(B_digitCountersArray,charIndexToSubstitute) <= 0)
         {
             // search for non-zero counter for 'highest' digit 9,8,7,6 etc
             // out: charIndexToSubstitute
            charIndexToSubstitute++;
            while (charIndexToSubstitute > '0' && arr_item(B_digitCountersArray,--charIndexToSubstitute) == 0)
               ;
         }
      }
   }

   std::cout << "old A: " << A_backup << std::endl;
   std::cout << "new A: " << A << std::endl;

   std::cin.get();
}
//---------------------------------------------------------------------------
int& arr_item(int *p_arr, char p_charIndex, char p_charBase)
{
   int index = p_charIndex - p_charBase;
   if (index < 0)
      throw new std::runtime_error(E_BAD_INDEX);

   return p_arr[index];
}
//---------------------------------------------------------------------------