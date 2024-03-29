#include <iostream>
#include "load_frame.hpp"
using namespace std;
int main(){
    const char *filename = "/home/masoud/Programming/Looking For Love - Pornhub.com.mp4";

    if (!load_frame(filename))
    {
        cout<<"something bad happened"<<endl;
    }
    
    cout<<"hello masoud"<<endl;
    return 0;
}