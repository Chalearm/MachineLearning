/********************************************************************/
/*
      FILE        :   w1.cpp
      Name        :   Chalearm Saelim
      Date        :   21 September 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to make a simple design to check the wording correctness. 


      Description :   This is made up of a simple class for checking wording.
      Dependency  :   We use the included library as below 
                                                #include <iostream>
      How to compile: g++ w1.cpp -o  main
      How to run        : ./main
      
      revision-history
      version   date          author     Description
      1.        21-09-2017    csaelim    First draft
      
      */


/*******************************************************************/

#include <iostream>
#include <cstring>
/*
 Example 
int core#
  int a <- 0#
  int b <- 0#
  int result <- 0#
  
  result <- a + b*5#
  
  if result is not 4
  <
  >#
  
  
end core : result#
Lexical term

VT "int"
VT "uint"
EL "#"
EQ "<-"
PS "+"
MS "-"
MY "*"
DR "/"
IF "if"
SE "is"
NQ "is not"
OF "<"
CF ">"
ED "end"
RT ":"



  
   

*/
class tokens
{
    std::string m_name;
    const 
};

int main(int argc,char **argv)
{
    std::string str1 = "We think in generalities, but we live in details.";
    std::string str2 = str1.substr(3,5);
    std::size_t pos = str1.find("live");
    std::string str3 = str1.substr(pos);
    char str[] = "- This, a sample string.";
    char *pch = NULL;
    std::cout<<"Splitting string \""<<str<<"\" into tokens:\n";
    pch = strtok(str," ,.-");
    while(pch != NULL)
    {
        std::cout<<pch<<std::endl;
        pch = strtok(NULL," ,.-");
    }
    std::cout<<str2<<' '<<str3<<'\n';
    return 0;
}