#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdint>
using namespace std;
int main() {
    //int pid = 6594;
    int pid;
    cin>>pid;
    int value_before,value_after;
    //string address;
    //cin>>address;
    string addressString;
    cin >> addressString;
    unsigned long address = stoul(addressString, nullptr, 16);
    stringstream mem_path;
    mem_path << "/proc/" << pid << "/mem";
    ifstream mem(mem_path.str().c_str(), ios::in | ios::binary);
    if (!mem) {
        cerr << "Failed to open memory file" << endl;
        return 1;
    }
   while(1){
    mem.seekg(address);
    mem.read(reinterpret_cast<char*>(&value_before), sizeof(value_before));
    if(value_before!=value_after) cout << "Read value from memory: " << value_before << endl;
    value_after=value_before;
   }
   mem.close();
}
