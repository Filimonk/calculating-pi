#include<iostream>
#include<vector>
#include<string>
#include<math.h>
#include<cstring>

class LNum {
public:

    LNum()
    {
        num.resize((accuracy_ + orderOfBase - 1) / orderOfBase + 1);
        countOfLNums = 1;
    }

    explicit LNum(double startVal)
    {
        sign_ = startVal >= 0? 1: -1;

        long long numberOfDec = (accuracy_ + orderOfBase - 1) /
                                   orderOfBase * orderOfBase;

        countOfLNums = 1;

        std::string strStartVal = std::to_string(startVal);
        std::string strIntPart = "";
        std::string strFractionalPart = "";

        int i = (strStartVal[0] == '-'? 1: 0);
        while (i < static_cast<int>(strStartVal.size()) &&
               strStartVal[i] != '.') {
            strIntPart += strStartVal[i];
            ++i;
        }
        ++i;
        while (i < static_cast<int>(strStartVal.size())) {
            strFractionalPart += strStartVal[i];
            ++i;
        }
        while (static_cast<int>(strFractionalPart.size()) < numberOfDec) {
            strFractionalPart += '0';
        }

        for (int i = numberOfDec - 1; i >= 0; i -= orderOfBase) {
            int iDigit = 0;
            for (int j = orderOfBase - 1; j >= 0; --j) {
                iDigit *= 10;
                iDigit += strFractionalPart[i - j] - '0';
            }
            num.push_back(iDigit);
        }

        int lenthIntOfDec = static_cast<int>(strIntPart.size());
        for (int i = lenthIntOfDec - 1; i >= 0; i -= orderOfBase) {
            int iDigit = 0;
            for (int j = orderOfBase - 1; j >= 0; --j) {
                if (i - j >= 0) {
                    iDigit *= 10;
                    iDigit += strIntPart[i - j] - '0';
                }
            }
            num.push_back(iDigit);
        }
    }

    explicit LNum(int startVal)
    {
        LNum support(static_cast<double>(startVal));
        (*this) = support;
        
        countOfLNums = 1;
    }
    
    LNum(const char* startVal)
    {
        long long numberOfDec = (accuracy_ + orderOfBase - 1) /
                                   orderOfBase * orderOfBase;

        countOfLNums = 1;

        std::string strStartVal = "";

        for (int i = 0; i < static_cast<int>(strlen(startVal)); ++i) {
            strStartVal += startVal[i];
        }

        std::string strIntPart = "";
        std::string strFractionalPart = "";

        sign_ = strStartVal[0] == '-'? -1: 1;
        int i = (strStartVal[0] == '-'? 1: 0);
        while (i < static_cast<int>(strStartVal.size()) &&
               strStartVal[i] != '.') {
            strIntPart += strStartVal[i];
            ++i;
        }
        ++i;
        while (i < static_cast<int>(strStartVal.size())) {
            strFractionalPart += strStartVal[i];
            ++i;
        }
        while (static_cast<int>(strFractionalPart.size()) < numberOfDec) {
            strFractionalPart += '0';
        }

        for (int i = numberOfDec - 1; i >= 0; i -= orderOfBase) {
            int iDigit = 0;
            for (int j = orderOfBase - 1; j >= 0; --j) {
                iDigit *= 10;
                iDigit += strFractionalPart[i - j] - '0';
            }
            num.push_back(iDigit);
        }

        int lenthIntOfDec = static_cast<int>(strIntPart.size());
        for (int i = lenthIntOfDec - 1; i >= 0; i -= orderOfBase) {
            int iDigit = 0;
            for (int j = orderOfBase - 1; j >= 0; --j) {
                if (i - j >= 0) {
                    iDigit *= 10;
                    iDigit += strIntPart[i - j] - '0';
                }
            }
            num.push_back(iDigit);
        }
    }

    static void setAccuracy(long long accuracy)
    {
        if (countOfLNums != 0) {
            return;
        }

        accuracy_ = accuracy;
    }

    LNum abs()
    {
        LNum absThis = *this;
        absThis.sign_ = 1;

        return absThis;
    }

    LNum operator-()
    {
        LNum support;
        
        support.num = num;
        support.sign_ = -sign_;
        
        return support;
    }

    LNum & operator=(const LNum other)
    {
        num = other.num;
        sign_ = other.sign_;

        return (*this);
    }
    
    void clearLeadingZeros()
    {
        int lenth = static_cast<int>(num.size());
        for (int i = lenth-1; 
                    i > (accuracy_ + orderOfBase - 1) / orderOfBase; --i) {
            
            if (num[i] == 0) {
                num.pop_back();
            }
            else {
                return;
            }
        }
    }

    bool operator==(const LNum &other)
    {
        //std::cout << "Сравнения ==\n";
        return (sign_ == other.sign_) && (num == other.num);
    }

    bool operator!=(const LNum &other) 
    {
        //std::cout << "Сравнение !=\n";
        return !((*this) == other);
    }

    bool operator>(const LNum &other)
    {

        //std::cout << "Сравнение >\n";
        if (sign_ != other.sign_) {
            return sign_ > other.sign_;
        }

        int lenthThis = static_cast<int>(num.size());
        int lenthOther = static_cast<int>(other.num.size());

        if (lenthThis != lenthOther) {
            if (sign_ == 1) {
                return lenthThis > lenthOther;
            }
            else {
                return lenthThis < lenthOther;
            }
        }

        for (int i = lenthThis - 1; i >= 0; --i) {
            if (num[i] > other.num[i]) {
                if (sign_ == 1) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else if (num[i] < other.num[i]) {
                if (sign_ == 1) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
        }

        return 0;
    }

    bool operator<(const LNum &other)
    {
        //std::cout << "Сравнении <\n";
        return !(((*this) == other) || ((*this) > other));
    }
    
    LNum sumWithDifferentSigns(LNum &other)
    {
        //std::cout << "Сумма чисел разных знаков\n";
        LNum result;
        int base = pow(10, orderOfBase);

        LNum leftTerm;
        LNum rightTerm;

        if (!((*this).abs() < other.abs())) {
            leftTerm = *this;
            rightTerm = other;

            result.sign_ = sign_;
        }
        else {
            leftTerm = other;
            rightTerm = *this;

            result.sign_ = other.sign_;
        }

        leftTerm.sign_ = 1;
        rightTerm.sign_ = 1;

        for (int i = 0; i < static_cast<int>(leftTerm.num.size()); ++i) {
            int subtrahend = 0;
            if (i < static_cast<int>(rightTerm.num.size())) {
                subtrahend = rightTerm.num[i];
            }

            if (i == static_cast<int>(leftTerm.num.size()) - 1 && 
                                              leftTerm.num[i] == 0) {
                break; 
            }

            if (i < result.num.size()) {
                result.num[i] = leftTerm.num[i] - subtrahend;
            }
            else {
                result.num.push_back(leftTerm.num[i] - subtrahend);
            }

            if (result.num[i] < 0) {
                result.num[i] += base;
                --leftTerm.num[i+1];
            }
        }

        return result;
    }

    LNum operator+(LNum other)
    {
        if (sign_ != other.sign_) {
            return sumWithDifferentSigns(other);
        }
        
        //std::cout << "Сумма чисел с одинаковым знаком\n";
        LNum result;
        int base = pow(10, orderOfBase);

        int lenth = std::max(static_cast<int>(num.size()),
                        static_cast<int>(other.num.size()));

        result.sign_ = sign_;
        
        int additionalFactor = 0;
        for (int i = 0; i < lenth; ++i) {
            int firstDigit = 0;
            if (static_cast<int>(num.size()) > i) {
                firstDigit = num[i];
            }

            int secondDigit = 0;
            if (static_cast<int>(other.num.size()) > i) {
                secondDigit = other.num[i];
            }

            additionalFactor += firstDigit + secondDigit;
            int sum = additionalFactor % base;
            additionalFactor /= base;

            if (i < static_cast<int>(result.num.size())) {
                result.num[i] = sum;
            }
            else {
                result.num.push_back(sum);
            }
        }

        if (additionalFactor) {
            result.num.push_back(additionalFactor);
        }

        return result;
    }

    LNum operator-(LNum &other)
    {
        //std::cout << "Разность\n";
        LNum result = (*this) + (-other);
        
        return result;
    }

    LNum operator*(const LNum &other) const
    {
        //std::cout << "Умножение\n";
        LNum result;

        int lenthThis = static_cast<int>(num.size());
        int lenthOther = static_cast<int>(other.num.size());

        result.sign_ = sign_ * other.sign_;

        long long base = pow(10, orderOfBase);

        std::vector <int> resNum;
        for (int i = 0; i < lenthThis; ++i) {
            for (int j = 0; j < lenthOther; ++j) {
                if (i + j == static_cast<int>(resNum.size())) {
                    resNum.push_back(0);
                }

                long long term = static_cast<long long>(num[i]) * other.num[j] 
                                                                + resNum[i + j];
                resNum[i + j] = term % base;

                if (term / base) {
                    if (i + j + 1 == static_cast<int>(resNum.size())) {
                        resNum.push_back(0);
                    }
                    resNum[i + j + 1] = term / base;
                }
            }
        }

        long long numberOfDigits = (accuracy_ + orderOfBase - 1) /
                                   orderOfBase;
        for (int i = 0, j = numberOfDigits; j < static_cast<int>(resNum.size());
                                                                    ++i, ++j) {
            if (i == static_cast<int>(result.num.size())) {
                result.num.push_back(0);
            }
            result.num[i] = resNum[j];
        }
        
        result.clearLeadingZeros();

        if (result.abs() == LNum(0)) {
            result.sign_ = 1;
        }
        return result;
    }
    
    bool isInt() {
        for (int i = 0; i < (accuracy_ + orderOfBase - 1) / orderOfBase; ++i) {
            if (num[i]) {
                return 0;
            }
        }
        
        return 1;
    }

    LNum operator/(LNum & other)
    {
        //std::cout << "Деление\n";
        if (other.abs() == LNum(0)) {
            std::cout << "ОШИБКА! Произошло деление на 0.\n";
        }

        LNum result;
        
        result.sign_ = sign_ * other.sign_;

        LNum dividend = (*this).abs();
        LNum divider = other.abs();
        LNum ten(10);
        LNum base(pow(10, orderOfBase));

        while (divider.isInt() == 0) {
            dividend = dividend * ten;
            divider = divider * ten;
        }

        int lenth = static_cast<int>(dividend.num.size());
        result.num.resize(lenth);
        
        LNum minuend;
        
        for (int i = lenth-1; i >= 0; --i) {
            minuend = minuend * base;
            LNum term = LNum(dividend.num[i]);
            minuend = minuend + term;
            minuend.clearLeadingZeros();
            
            if (!(minuend < divider)) {
                int l = 0;
                int r = pow(10, orderOfBase);
                while (r - l > 1) {
                    int m = (l + r) / 2;
                    
                    if ((divider * LNum(m)) > minuend) {
                        r = m;
                    }
                    else {
                        l = m;
                    }
                }
                
                result.num[i] = l;
                LNum intermediate = divider * LNum(l);
                minuend = minuend - intermediate;
            }
        }

        result.clearLeadingZeros();
        
        if (result.abs() == LNum(0)) {
            result.sign_ = 1;
        }
        
        return result;
    }

    std::string to_string() const
    {
        std::string result = "";
        for (int i = static_cast<int>(num.size()) - 1; i >= 0; --i) {
            std::string digitals = std::to_string(num[i]);

            if (i != static_cast<int>(num.size()) - 1) {
                for (int j = 0; 
                       j < orderOfBase - static_cast<int>(digitals.size()); ++j) {
                    result += '0';
                }
            }

            result += digitals;
        }

        return result;
    }

    void print() const
    {
        std::string strNum = to_string();
        int sizeStrNum = static_cast<int>(strNum.size());
        long long numberOfFractional = (accuracy_ + orderOfBase - 1) /
                                   orderOfBase * orderOfBase;

        if (sign_ == -1) {
            std::cout << '-';
        }

        int i = 0;
        while (i < sizeStrNum - numberOfFractional) {
            std::cout << strNum[i];
            ++i;
        }
        std::cout << '.';
        while (i < sizeStrNum - numberOfFractional + accuracy_) {
            std::cout << strNum[i];
            ++i;
        }
        std::cout << "\n";
    }

private:

    std::vector <int> num;
    char sign_ = 1;

    static long long accuracy_;
    static int countOfLNums;

    const int orderOfBase = 9;
};

int LNum::countOfLNums = 0;
long long LNum::accuracy_ = 20;

LNum operator"" _LN(const char* startVal)
{
    return LNum(startVal);
}

int main() {
    {
        LNum A = -123_LN; 
        LNum B(934.);
        
        LNum C = A + B;
        A.print(); std::cout << '+'; B.print(); std::cout << '='; C.print();
        C = A - B;
        A.print(); std::cout << '-'; B.print(); std::cout << '='; C.print();
        C = A * B;
        A.print(); std::cout << '*'; B.print(); std::cout << '='; C.print();
        C = A / B;
        A.print(); std::cout << '/'; B.print(); std::cout << '='; C.print();
        std::cout << "\n";
    }
    
    {
        LNum A = 0.99999999999_LN; 
        LNum B = 0.0000000001_LN;
        
        LNum C = A + B;
        A.print(); std::cout << '+'; B.print(); std::cout << '='; C.print();
        C = A - B;
        A.print(); std::cout << '-'; B.print(); std::cout << '='; C.print();
        C = A * B;
        A.print(); std::cout << '*'; B.print(); std::cout << '='; C.print();
        C = A / B;
        A.print(); std::cout << '/'; B.print(); std::cout << '='; C.print();
        std::cout << "\n";
    }
    
    {
        LNum A = 100000000000_LN; 
        LNum B = 0.0000000001_LN;
        
        LNum C = A + B;
        A.print(); std::cout << '+'; B.print(); std::cout << '='; C.print();
        C = A - B;
        A.print(); std::cout << '-'; B.print(); std::cout << '='; C.print();
        C = A * B;
        A.print(); std::cout << '*'; B.print(); std::cout << '='; C.print();
        C = A / B;
        A.print(); std::cout << '/'; B.print(); std::cout << '='; C.print();
        std::cout << "\n";
    }
    
    {
        LNum A(13); 
        LNum B(-.2);
        
        LNum C = A + B;
        A.print(); std::cout << '+'; B.print(); std::cout << '='; C.print();
        C = A - B;
        A.print(); std::cout << '-'; B.print(); std::cout << '='; C.print();
        C = A * B;
        A.print(); std::cout << '*'; B.print(); std::cout << '='; C.print();
        C = A / B;
        A.print(); std::cout << '/'; B.print(); std::cout << '='; C.print();
        std::cout << "\n";
    }
    
    {
        LNum A(-0); 
        LNum B(-1);
        
        LNum C = A + B;
        A.print(); std::cout << '+'; B.print(); std::cout << '='; C.print();
        C = A - B;
        A.print(); std::cout << '-'; B.print(); std::cout << '='; C.print();
        C = A * B;
        A.print(); std::cout << '*'; B.print(); std::cout << '='; C.print();
        C = A / B;
        A.print(); std::cout << '/'; B.print(); std::cout << '='; C.print();
        std::cout << "\n";
    }
    
    {
        LNum A = 14.000000000009_LN; 
        LNum B = -0.00000000001_LN;
        
        LNum C = A + B;
        A.print(); std::cout << '+'; B.print(); std::cout << '='; C.print();
        C = A - B;
        A.print(); std::cout << '-'; B.print(); std::cout << '='; C.print();
        C = A * B;
        A.print(); std::cout << '*'; B.print(); std::cout << '='; C.print();
        C = A / B;
        A.print(); std::cout << '/'; B.print(); std::cout << '='; C.print();
        std::cout << "\n";
    }
    
    return 0;
}
