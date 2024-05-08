/*
FILE NAME : CS112_A2_T3_S19_20230419_S19_20230144_S20_20230166.cpp
PURPOSE : It is a fractional calculator it can do addition , subtraction , multiplication and division. It also accepts integer inputs.
AUTHORS :
(1) Malak Nour-Elhussien Samir , ID: 20230419 , S19 , part taken : Addition , multiplication & validation ,E-mail :nourrm218@gmail.com

(2) Reem Abdou Mohamed , ID : 20230144 , S19 , part taken : Addition & multiplication ,E-mail :reem64404@gmail.com

(3) Sara Ibrahim Mohamed , ID: 20230166 , S20 , part taken : algorithm ,E-mail :si6357141@gmail.com

Date : 15 March 2024

ALGORITHM LINK : https://drive.google.com/file/d/1FgrLT28Gq8vkzPhnTVbnoo3nuGmpbD5U/view?usp=sharing
*/

#include <iostream>
#include <regex>
using namespace std;

bool expression_validation(const string &expression) {
    // Check if the expression matches the pattern
    regex expression_regex("[+-]?[0-9]+(/[+-]?[0-9]+)?\\s*[+\\-*/]\\s+[+-]?[0-9]+(/[+-]?[0-9]+)?");
    if (!regex_match(expression, expression_regex)) {
        cout << "Invalid input! Please enter a valid expression." << endl;
        return false;
    }

    // Splitting the expression by the operator
    int div1 = expression.find('/');  //from the left
    int div2 = expression.rfind('/'); //from the right
    int space = expression.find(" ");
    int denominator_1 = 1; // Default denominator for integers
    int denominator_2 = 1; // Default denominator for integers

    //If no / is found in the first operand, it means that the input is an integer. In this case, the default denominator is set to 1.

    // Extract numerator and denominator from the first operand
    if (div1 != string::npos) {
        denominator_1 = stoi(expression.substr(div1 + 1, space));
    }

    // Extract numerator and denominator from the second operand
    if (div2 != string::npos) {
        denominator_2 = stoi(expression.substr(div2 + 1));
    }

    // Check if any denominator is zero
    if (denominator_1 == 0 || denominator_2 == 0) {
        cout << "Error: Division by zero in the expression! Please enter a valid expression." << endl;
        return false;
    }

    return true;
}


int gcd(long long a, long long b) {    // dividing both the numerator and denominator by their greatest common divisor.
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void simplify_Fraction(long long &numerator, long long &denominator) {
    int common_divisor = gcd(numerator, denominator);
    numerator /= common_divisor;
    denominator /= common_divisor;
}

void print_Fraction(long long numerator, long long denominator) {   //print the simplified output
    if (denominator == 1)
        cout << numerator << endl;
    else
        cout << numerator << "/" << denominator << endl;
}

void main_calculator() {
    string expression;
    do {
        cout << "Enter your operation (for example ==>\"1/2 + 3/4\"):" << endl << "Enter \"exit\" if u want to stop." << endl << "==>";
        getline(cin, expression);

        if (expression == "exit") {
            cout << "Exiting the calculator . Goodbye!" << endl;
            break;
        }

        if (expression_validation(expression)) {

            int space1 = expression.find(" ");
            int space2 = expression.rfind(" "); //from the right

            string left_fraction = expression.substr(0, space1);
            string right_fraction = expression.substr(space2);

            string operation = expression.substr(space1 + 1, space2);
            int i;
            for(i = 0 ; i < operation.length() ; i++){  //excluding operator form users spaces
                if(operation[i] == ' '){
                    continue;
                }
                else{
                    break;
                }
            }
            char op = operation[i];

            // Extract numerator and denominator from the input strings

            long long left_int = stoll(left_fraction);
            long long right_int = stoll(right_fraction);
            int div_n1 = left_fraction.find('/');
            int div_n2 = right_fraction.find('/');

            //If no / is found in the first operand, it means that the input is an integer. In this case, the default denominator is set to 1.
            //and set the nomenator to itself

            long long denominator_1 = (div_n1 != string::npos) ? stoi(left_fraction.substr(div_n1 + 1)) : 1;
            long long denominator_2 = (div_n2 != string::npos) ? stoi(right_fraction.substr(div_n2 + 1)) : 1;
            long long numerator_1 = (div_n1 != string::npos) ? stoi(left_fraction.substr(0, div_n1)) : left_int * denominator_1;
            long long numerator_2 = (div_n2 != string::npos) ? stoi(right_fraction.substr(0, div_n2)) : right_int * denominator_2;

            // Call appropriate operation based on operator
            if (op == '+') {
                long long numerator_result = numerator_1 * denominator_2 + numerator_2 * denominator_1;
                long long denominator_result = denominator_1 * denominator_2;

                // Compute the sum of fractions
                simplify_Fraction(numerator_result, denominator_result);
                print_Fraction(numerator_result, denominator_result);
            }

            else if (op == '*') {

                long long numerator_result = numerator_1 * numerator_2;
                long long denominator_result = denominator_1 * denominator_2;

                // Compute the multiplication of fractions
                simplify_Fraction(numerator_result, denominator_result);
                print_Fraction(numerator_result, denominator_result);
            }

            else if (op == '/') {

                // Check if both operands are integers
                if (numerator_2 == 0) {
                    cout << "Error: Division by zero!" << endl;
                    main_calculator();
                }

                long long numerator_result = numerator_1 * denominator_2;
                long long denominator_result = denominator_1 * numerator_2;

                // Compute the division of fractions
                simplify_Fraction(numerator_result, denominator_result);
                print_Fraction(numerator_result, denominator_result);
            }

            else if (op == '-') {

                long long numerator_result = numerator_1 * denominator_2 - numerator_2 * denominator_1;
                long long denominator_result = denominator_1 * denominator_2;

                // Compute the subtraction of fractions
                simplify_Fraction(numerator_result, denominator_result);
                print_Fraction(numerator_result, denominator_result);
            }

            else {
                cout << "Unsupported operation!" << endl;
            }
        }
    } while (true);

}

int main(){
    cout << "WELCOME TO THE FRACTIONAL CALCULATOR !" << endl;
    main_calculator();
}
