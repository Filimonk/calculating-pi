#include<iostream>
#include<vector>
#include<math.h>

#include<LNum.h>

int main() {
    int accuracy;
    std::cout << "Задайте точность" << std::endl;
    std::cin >> accuracy;
    LNum::setAccuracy(accuracy);
    std::cout << "\n";
    
    

    return 0;
}
