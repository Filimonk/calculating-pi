#include<iostream>
#include<vector>
#include<math.h>
#include<time.h>

#include "LNum.cpp"

int main() {
    int accuracy;
    
    std::cout << "Задайте точность" << std::endl;
    std::cin >> accuracy;
    std::cout << std::endl;
    
    LNums::LNum::setAccuracy(accuracy);
    
    clock_t start = clock();
    
    LNums::LNum PI;
    LNums::LNum four = LNums::LNum(4);
    for (int k = 1, i = 1; ; k += 2, ++i) {
        LNums::LNum term;
        
        LNums::LNum divider = LNums::LNum(k);
        term = four / divider;
        
        if (term == LNums::LNum(0)) {
            break;
        }
        
        if (k / 2 % 2) {
            term = -term;
        }
        
        PI = PI + term;
        if (i % 1000 == 0) {
            PI.print();
        }
    }
    
    clock_t finish = clock();
    
    PI.print();
    std::cout << std::endl;
    std::cout << static_cast<double>(finish - start) / CLOCKS_PER_SEC << "сек\n";

    return 0;
}
