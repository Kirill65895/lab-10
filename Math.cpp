#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string summNumbers(string number1, string number2) {
    string result;
    int carry = 0;
    int i = number1.size() - 1;
    int j = number2.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? number1[i] - '0' : 0;
        int digit2 = (j >= 0) ? number2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');

        --i;
        --j;
    }
    reverse(result.begin(), result.end());
    return result;
}

string differNumbers(string number1, string number2) {
    string result;
    int borrow = 0;
    int diff;

    while (number1.size() != number2.size()) {
        number2.insert(number2.begin(), '0');
    }

    for (int i = number1.size() - 1; i >= 0; --i) {
        int digit1 = number1[i] - '0';
        int digit2 = number2[i] - '0';
        digit1 -= borrow;
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        diff = digit1 - digit2;
        result.insert(result.begin(), diff + '0');
    }
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty()) {
        return "0";
    }
    return result;
}

string multNumbers(string number1, string number2) {
    string result = "0";
    string currentValue = "0";

    for (int i = number2.size() - 1; i >= 0; --i) {
        int digit = number2[i] - '0';
        for (int j = 0; j < digit; ++j) {
            currentValue = summNumbers(currentValue, number1);
        }
        for (int k = 0; k < (number2.size() - 1 - i); ++k) {
            currentValue += "0";
        }
        result = summNumbers(currentValue, result); 
        currentValue = "0";
    }
    return result;
}


string largeNumbers(string number1, string number2) {
    string result;
    if (number1 == number2) {
        return "Числа равны";
    }

    if (number1.size() == number2.size()) {
        int i = 0;

        do {
            int digit1 = number1[i] - '0';
            int digit2 = number2[i] - '0';
            if (digit1 != digit2) {
                if (digit1 > digit2) {
                    result = number1;
                    break;
                }
                else {
                    result = number2;
                    break;
                }
            }
            else {
                ++i;
                continue;
            }
        } while (i < number1.size());
    }
    else {
        if (number1.size() > number2.size()) {
            result = number1;
        }
        else {
            result = number2;
        }
    }
    return result;
}

bool doWhileDiv(string currentValue, string number2) {
    if (largeNumbers(currentValue, number2) == number2) {
        return false;
    }
    else {
        return true;
    }
}

string divNumbers(string number1, string number2) {
    if (largeNumbers(number1, number2) == number2 || number1 == "0") {
        return "0";
    }
    if (number1 == number2) {
        return "1";
    }
    if (number2 == "0") {
        return "На ноль делить нельзя";
    }
    string result = "0";
    string currentValue = number1;
    while (doWhileDiv(currentValue, number2)) {
        currentValue = differNumbers(currentValue, number2);
        result = summNumbers(result, "1");
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "ru");

    int choice;

    string number1, number2;
    while (true) {
        cout << "1.Сложение (1+1=2)\n2.Вычитание (1-1=0)\n3.Умножение (2*2=4)\n4.Деление(целочисленное) (3/2=1)\n5.Сравнение (2=2 Числа равны!)\n6.Выход (Программа останавливается)\n\nВаш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            cout << "Введите первое число: ";
            cin >> number1;
            cout << "Введите второе число: ";
            cin >> number2;

            string result = summNumbers(number1, number2);
            cout << result << endl;
            break;
        }

        case 2:
        {
            cout << "Введите первое число: ";
            cin >> number1;
            cout << "Введите второе число: ";
            cin >> number2;

            if (largeNumbers(number1, number2) == number2) {
                cout << "Первое число должно быть больше второго" << endl;
                break;
            }

            string result = differNumbers(number1, number2);
            cout << result << endl;
            break;
        }

        case 3:
        {
            cout << "Введите первое число: ";
            cin >> number1;
            cout << "Введите второе число: ";
            cin >> number2;

            string result = multNumbers(number1, number2);
            cout << result << endl;
            break;
        }

        case 4:
        {
            cout << "Введите первое число: ";
            cin >> number1;
            cout << "Введите второе число: ";
            cin >> number2;
            string result = divNumbers(number1, number2);
            cout << result << endl;
            break;
        }

        case 5:
        {
            cout << "Введите первое число: ";
            cin >> number1;
            cout << "Введите второе число: ";
            cin >> number2;

            if (number1 == number2) {
                cout << "Числа равны" << endl;
                break;
            }

            string result = largeNumbers(number1, number2);
            cout << "Большее число: " << result << endl;
            break;
        }

        case 6:
        {
            return 0;
        }

        default:
        {
            cout << "Введите число от 1 до 6" << endl;
            break;
        }
        }
    }
}