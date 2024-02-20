#ifndef CPP_LNum_H
#define CPP_LNum_H

namespace LNums {
    LNum();
    explicit LNum(double startVal);
    explicit LNum(int startVal);
    LNum(const char* startVal);
    static void setAccuracy(long long accuracy);
    LNum abs();
    LNum operator-();
    LNum & operator=(const LNum other);
    void clearLeadingZeros();
    bool operator==(const LNum &other);
    bool operator!=(const LNum &other);
    bool operator>(const LNum &other);
    bool operator<(const LNum &other);
    LNum sumWithDifferentSigns(LNum &other);
    LNum operator+(LNum other);
    LNum operator-(LNum &other);
    LNum operator*(const LNum &other) const;
    bool isInt();
    LNum operator/(LNum & other);
    std::string to_string() const;
    void print() const;
    LNum operator"" _LN(const char* startVal);
}

#endif //CPP_LNum_H
