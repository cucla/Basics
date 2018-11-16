using System;
using System.Collections.Generic;


namespace AppForInterview
{
    public class PostfixExprEvaluator
    {
        private const char ADD = '+';
        private const char SUB = '-';
        private const char MULT = '*';
        private const char DIV = '/';

        public int Evaluate(string s)
        {
            Stack<int> myStack = new Stack<int>();

            foreach(char ch in s)
            {
                if (!IsOperator(ch))
                    myStack.Push((int)ch - '0');
                else
                {
                    int operand1 = myStack.Pop();
                    int operand2 = myStack.Pop();
                    int result;
                    switch(ch)
                    {
                        case ADD:
                            result = operand1 + operand2;
                            myStack.Push(result);
                            break;
                        case SUB:
                            result = operand1 - operand2;
                            myStack.Push(result);
                            break;
                        case MULT:
                            result = operand1 * operand2;
                            myStack.Push(result);
                            break;
                        case DIV:
                            result = operand1 / operand2;
                            myStack.Push(result);
                            break;
                    }
                }
            }
            return myStack.Pop();
        }

        private bool IsOperator(char ch)
        {
            if (ch == ADD ||
                ch == SUB ||
                ch == MULT ||
                ch == DIV)
                return true;
            return false;
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            PostfixExprEvaluator evv = new PostfixExprEvaluator();
            int result = evv.Evaluate("246+*");
            Console.WriteLine(result);


            Console.Read();
        }
    }
}
