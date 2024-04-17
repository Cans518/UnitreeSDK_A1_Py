#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include <iostream>
int main()
{
    UNITREE_LEGGED_SDK::UDP udp_test(8020,"127.0.0.1",32000);
    char buffer[1024];
    int a = udp_test.Recv();
    while(udp_test.Recv() > 0)
        udp_test.GetRecv(buffer);
    std::cout<<buffer<<std::endl;
    return 0;
}