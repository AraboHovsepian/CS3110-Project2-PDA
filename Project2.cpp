#include <iostream>
#include <string>
#include <stack>

using namespace std;

float stringToFloatVerificationConversion(string s)
{
	int state = 0, power = -1;
	int exponent = 0;
	float floatNum = 0.0;
	bool exponentNegativeFlag = false;

	for (int i = 0; i <= s.length(); i++)
	{
		switch (state)
		{
		case 0:
			if (isdigit(s[i]))
			{
				state = 1;
				floatNum += (s[i] - 48);
			}
			else if (s[i] == '.')
			{
				state = 3;
			}
			else
			{
				state = 9;
			}
			break;

		case 1:
			if (isdigit(s[i]))
			{
				state = 1;
				floatNum = ((floatNum * 10) + (s[i] - 48));
			}
			else if (s[i] == '_')
			{
				state = 2;
			}
			else if (s[i] == '.')
			{
				state = 3;
			}
			else if (s[i] == 'e' || s[i] == 'E')
			{
				state = 6;
			}
			else if (s[i] == 'f' || s[i] == 'F' || s[i] == 'd' || s[i] == 'D')
			{
				state = 8;
			}
			else
			{
				state = 9;
			}
			break;

		case 2:
			if (s[i] == '_')
			{
				state = 2;
			}
			else if (isdigit(s[i]))
			{
				state = 1;
				floatNum = ((floatNum * 10) + (s[i] - 48));
			}
			else
			{
				state = 9;
			}
			break;

		case 3:
			if (isdigit(s[i]))
			{
				state = 4;
				floatNum += ((s[i] - 48) * pow(10, power));
				power--;
			}
			else if (s[i] == 'e' || s[i] == 'E')
			{
				state = 6;
			}
			else if (s[i] == 'f' || s[i] == 'F' || s[i] == 'd' || s[i] == 'D')
			{
				state = 8;
			}
			else if (s[i] == NULL)
			{
				state = 8;
			}
			else
			{
				state = 9;
			}
			break;

		case 4:
			if (isdigit(s[i]))
			{
				state = 4;
				floatNum += ((s[i] - 48) * pow(10, power));
				power--;
			}
			else if (s[i] == '_')
			{
				state = 5;
			}
			else if (s[i] == 'e' || s[i] == 'E')
			{
				state = 6;
			}
			else if (s[i] == 'f' || s[i] == 'F' || s[i] == 'd' || s[i] == 'D')
			{
				state = 8;
			}
			else if (s[i] == NULL)
			{
				state = 8;
			}
			else
			{
				state = 9;
			}
			break;

		case 5:
			if (s[i] == '_')
			{
				state = 5;
			}
			else if (isdigit(s[i]))
			{
				state = 4;
				floatNum += ((s[i] - 48) * pow(10, power));
				power--;
			}
			else
			{
				state = 9;
			}
			break;

		case 6:
			if (isdigit(s[i]))
			{
				state = 7;
				exponent += (s[i] - 48);
			}
			else if (s[i] == '-')
			{
				exponentNegativeFlag = true;
			}
			else
			{
				state = 9;
			}
			break;

		case 7:
			if (isdigit(s[i]))
			{
				state = 7;
				exponent = ((exponent * 10) + (s[i] - 48));
			}
			else if (s[i] == 'f' || s[i] == 'F' || s[i] == 'd' || s[i] == 'D')
			{
				state = 8;
			}
			else if (s[i] == NULL)
			{
				state = 8;
			}
			else
			{
				state = 9;
			}
			break;

		case 8:
			if (s[i] == 'f' || s[i] == 'F' || s[i] == 'd' || s[i] == 'D')
			{
				state = 9;
			}
			break;
		}
	}

	if (state == 8)
	{
		if (exponentNegativeFlag)
		{
			exponent = exponent * -1;
		}
		return (floatNum * pow(10, exponent));
	}
	else if (state == 9)
	{
		return -1;
	}
}

float evaluate(float num1, float num2, char op)
{
	switch (op)
	{
	case '*':
		return num1 * num2;
		break;

	case '/':
		return num1 / num2;
		break;

	case '+':
		return num1 + num2;
		break;

	case '-':
		return num1 - num2;
		break;
	}
}

float calculator(string oldString)
{
	stack<char> operatorStack;
	stack<float> floatStack;
	stack<float> tempFloatStack;
	int state = 0, floatStackSize = 0;
	float tempFloat1 = 0.0, tempFloat2 = 0.0;
	string s = "", tempString = "";

	for (int i = 0; i < oldString.length(); i++)
	{
		if (oldString[i] != ' ')
		{
			s += oldString[i];
		}
	}

	for (int i = 0; i <= s.length(); i++)
	{
		switch (state)
		{
		case 0:
			if (s[i] == '(')
			{
				state = 1;
				operatorStack.push(s[i]);
			}
			else if (s[i] == NULL)
			{
				state = 5;
			}
			else
			{
				state = 3;
				tempString += s[i];
			}
			break;

		case 1:
			if (s[i] == '(')
			{
				state = 1;
				operatorStack.push(s[i]);
			}
			else if (s[i] == ')')
			{
				state = 2;
				if (stringToFloatVerificationConversion(tempString) > -1)
				{
					floatStack.push(stringToFloatVerificationConversion(tempString));
					tempString = "";
				}
				else if (stringToFloatVerificationConversion(tempString) == -1)
				{
					state = 5;
				}
				while (!operatorStack.empty() && operatorStack.top() != '(')
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
				operatorStack.pop();
				while (!operatorStack.empty() && (operatorStack.top() == '*' || operatorStack.top() == '/') && floatStack.size() > 1)
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
			}
			else
			{
				state = 3;
				tempString += s[i];
			}
			break;

		case 2:
			if (s[i] == ')')
			{
				state = 2;
				while (!operatorStack.empty() && operatorStack.top() != '(')
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
				operatorStack.pop();
				while (!operatorStack.empty() && (operatorStack.top() == '*' || operatorStack.top() == '/') && floatStack.size() > 1)
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
			}
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			{
				state = 1;
				operatorStack.push(s[i]);
			}
			else if (s[i] == NULL)
			{
				state = 4;
				floatStackSize = floatStack.size();
				for (int i = 0; i < floatStackSize; i++)
				{
					tempFloatStack.push(floatStack.top());
					floatStack.pop();
				}
				while (!operatorStack.empty() && tempFloatStack.size() > 1)
				{
					tempFloat1 = tempFloatStack.top();
					tempFloatStack.pop();
					tempFloat2 = tempFloatStack.top();
					tempFloatStack.pop();
					tempFloatStack.push(evaluate(tempFloat1, tempFloat2, operatorStack.top()));
					operatorStack.pop();
				}
			}
			else
			{
				state = 5;
			}
			break;

		case 3:
			if ((s[i] == '+' || s[i] == '-') && tempString[tempString.size() - 1] != 'e')
			{
				state = 1;
				if (stringToFloatVerificationConversion(tempString) > -1)
				{
					floatStack.push(stringToFloatVerificationConversion(tempString));
					tempString = "";
				}
				else if (stringToFloatVerificationConversion(tempString) == -1)
				{
					state = 5;
				}
				while (!operatorStack.empty() && (operatorStack.top() == '*' || operatorStack.top() == '/') && floatStack.size() > 1)
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
				operatorStack.push(s[i]);
			}
			else if (s[i] == '*' || s[i] == '/')
			{
				state = 1;
				if (stringToFloatVerificationConversion(tempString) > -1)
				{
					floatStack.push(stringToFloatVerificationConversion(tempString));
					tempString = "";
				}
				else if (stringToFloatVerificationConversion(tempString) == -1)
				{
					state = 5;
				}
				operatorStack.push(s[i]);
			}
			else if (s[i] == ')')
			{
				state = 2;
				if (stringToFloatVerificationConversion(tempString) > -1)
				{
					floatStack.push(stringToFloatVerificationConversion(tempString));
					tempString = "";
				}
				else if (stringToFloatVerificationConversion(tempString) == -1)
				{
					state = 5;
				}
				while (!operatorStack.empty() && operatorStack.top() != '(' && floatStack.size() > 1)
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
				operatorStack.pop();
				while (!operatorStack.empty() && (operatorStack.top() == '*' || operatorStack.top() == '/') && floatStack.size() > 1)
				{
					tempFloat1 = floatStack.top();
					floatStack.pop();
					tempFloat2 = floatStack.top();
					floatStack.pop();
					floatStack.push(evaluate(tempFloat2, tempFloat1, operatorStack.top()));
					operatorStack.pop();
				}
			}
			else if (s[i] == NULL)
			{
				state = 4;
				if (stringToFloatVerificationConversion(tempString) > -1)
				{
					floatStack.push(stringToFloatVerificationConversion(tempString));
					tempString = "";
				}
				else if (stringToFloatVerificationConversion(tempString) == -1)
				{
					state = 5;
				}
				floatStackSize = floatStack.size();
				for (int i = 0; i < floatStackSize; i++)
				{
					tempFloatStack.push(floatStack.top());
					floatStack.pop();
				}
				while (!operatorStack.empty() && state != 5 && tempFloatStack.size() > 1)
				{
					tempFloat1 = tempFloatStack.top();
					tempFloatStack.pop();
					tempFloat2 = tempFloatStack.top();
					tempFloatStack.pop();
					tempFloatStack.push(evaluate(tempFloat1, tempFloat2, operatorStack.top()));
					operatorStack.pop();
				}
			}
			else
			{
				state = 3;
				tempString += s[i];
			}
			break;
		}
	}

	if (state == 4)
	{
		return tempFloatStack.top();
	}
	else if (state == 5 && s.empty())
	{
		return -1;
	}
	else if (state == 5)
	{
		return -2;
	}
}

int main()
{
	string s = "";

	cout << "String to Float Calculator\nThis program can take any string which consists of valid float numbers and operators ( +, -, *, /, (, ) ) and also whitespaces and then calculate the result." << endl;

	while (true)
	{
		cout << "Please enter a string: ";
		getline(cin, s);

		float convertedFloat = calculator(s);

		if (convertedFloat > -1)
		{
			cout << "Calculation Result: " << convertedFloat << endl;
		}
		else if (convertedFloat == -1)
		{
			cout << "Empty strings don't need calculation :)" << endl;
		}
		else if (convertedFloat == -2)
		{
			cout << "Invalid Input" << endl;
		}
	}

	return 0;
}