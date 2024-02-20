#include<iostream>
#include<vector>
#include<math.h>
#include<time.h>

#include "LNum.h"

int main() {
    int accuracy;
    
    std::cout << "Задайте точность" << std::endl;
    std::cin >> accuracy;
    std::cout << std::endl;
    
    LNum::setAccuracy(accuracy);
    
    clock_t start = clock();
    
    LNum PI;
    LNum four = LNum(4);
    for (int k = 1, i = 1; ; k += 2, ++i) {
        LNum term;
        
        LNum divider = LNum(k);
        term = four / divider;
        
        if (term == LNum(0)) {
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
