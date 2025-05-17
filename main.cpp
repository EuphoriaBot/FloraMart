#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    time_t timestamp = time(NULL);
    tm datetime = *localtime(&timestamp);

    char output[50];
    strftime(output, 50, "%d-%m-%y %H:%M", &datetime);
    // time_t stringtotime = 

    cout << ctime(&timestamp) << endl;
    cout << output << endl;
    return 0;
}
