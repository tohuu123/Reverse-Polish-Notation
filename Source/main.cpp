#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using std::cin;
using std::cout;

using std::string;
using std::stack;

// function to find precedence of operators.
int precedence(char op)
{
    // if op is + or - (same precedence)
    if (op == '+' || op == '-') return 1;
    // if op is * or / (same precedence) higher than + and -
    if (op == '*' || op == '/') return 2;
    // remaining cases
    return 0;
}

// function to perform arithmetic operations.
double applyOp(double a, double b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0; // return 0 if operator is invalid
}

// Function to convert infix expression to postfix.
string convertToPostfix(string infix) {
    // size of infix.
    int n = infix.length();
    // stack to store non-negative integer values (base string for postfix).
    stack<string> vals;
    // stack to store operators.
    stack<char> ops;

    // convert infix to postfix.
    for (int i = 0; i < n; i++)
    {
        // if brace, push to 'ops'.
        if (infix[i] == '(')
        {
            ops.push(infix[i]);
        }
        else if (isdigit(infix[i]))
        {
            string val = "";
            // find the value.
            while (i < n && isdigit(infix[i]))
            {
                val += infix[i];
                i++;
            }
            // push value to 'vals'.
            vals.push(val);
            // go back one digit because now we are at the next digit after value.
            i--;
        }
        // if closing brace.
        else if (infix[i] == ')')
        {
            // handle operations in parentheses
            while (!ops.empty() && ops.top() != '(')
            {
                // take two values from top of stack.
                // first top is value2 because it comes after value1.
                string val_2 = vals.top();
                vals.pop();

                string val_1 = vals.top();
                vals.pop();

                // take operator.
                char op = ops.top();
                ops.pop();

                // convert from infix to postfix.
                string convert = val_1 + " " + val_2 + " " + op;
                // push back to 'vals'.
                vals.push(convert);
            }
            // remove opening brace.
            ops.pop();
        }
        else
        {
            // while top of 'ops' has same or greater precedence, apply operator on top of 'ops' to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top()) >= precedence(infix[i]))
            {
                // treat data as if it were in parentheses
                string val_2 = vals.top();
                vals.pop();

                string val_1 = vals.top();
                vals.pop();

                char op = ops.top();
                ops.pop();

                string convert = val_1 + " " + val_2 + " " + op;
                vals.push(convert);
            }
            // push new op to 'ops'.
            ops.push(infix[i]);
        }
    }

    // process remaining data in stack
    while (!ops.empty())
    {
        // treat data as if it were in parentheses
        string val_2 = vals.top();
        vals.pop();

        string val_1 = vals.top();
        vals.pop();

        char op = ops.top();
        ops.pop();

        string convert = val_1 + " " + val_2 + " " + op;
        vals.push(convert);
    }

    // the final value in 'vals' is the postfix expression
    return vals.top();
}

// Function to evaluate the postfix expression.
double evaluatePostfix(string postfix) {
    // size of postfix (different from infix because postfix has spaces to recognize numbers together)
    int m = postfix.length();
    // stack to store numbers (using double because division may produce non-integer values)
    stack<double> numbers;

    // evaluate the postfix expression
    for (int i = 0; i < m; i++) {
        if (postfix[i] == ' ')
        {
            // skip spaces
            continue;
        }
        else if (isdigit(postfix[i]))
        {
            double number = 0;
            // extract the number
            while (i < m && isdigit(postfix[i]))
            {
                number = (number * 10) + (postfix[i] - '0');
                i++;
            }
            // push the number to 'numbers'
            numbers.push(number);
            // go back one digit because now we are at the next digit after number.
            i--;
        }
        else
        {
            // take two numbers from top of stack.
            // first top is number2 because it comes after number1.
            double number_2 = numbers.top();
            numbers.pop();

            double number_1 = numbers.top();
            numbers.pop();

            // push the result of applying the operator to the two numbers.
            numbers.push(applyOp(number_1, number_2, postfix[i]));
        }
    }

    // the final number is the result of the expression.
    return numbers.top();
}

int main()
{
    // input INFIX arithmetic expression.
    string infix;
    cin >> infix;

    // Convert infix to postfix.
    string postfix = convertToPostfix(infix);
    // print postfix to screen (uncomment the line below if you want to display the postfix expression)
    // cout << postfix << "\n";

    // Evaluate the postfix expression.
    double result = evaluatePostfix(postfix);

    // print the result
    cout << result << '\n';

    return 0;
}

/*
Some examples:
10+2*6
= 22
100*2+12
= 212
100*(2+12)
= 1400
100*(2+12)/14
= 100
*/
