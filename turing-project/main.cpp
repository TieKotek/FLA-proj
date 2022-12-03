#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    if(argc == 1){
        cerr << "something went wrong!" << endl;
        return 1;
    }
    cout<<"This is for testing" << endl;
    return 0;
}