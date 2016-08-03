#include <iostream> 
#include <string>
#include <sstream>

using namespace std; 
int main()
{ 
   string str = "3   J     JD,K";
   stringstream ss(str);

   string token;

while (getline(ss,token, ','))
{
    cout<< token <<endl; 
}

 
   return 0;
}
 