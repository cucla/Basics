    public class BalancedSymbolChecker
    {
        private const char OPEN_PAREN = '(';
        private const char CLOSE_PAREN = ')';
        private const char OPEN_BRACKET = '[';
        private const char CLOSE_BRACKET = ']';
        private const char OPEN_BRACE = '{';
        private const char CLOSE_BRACE = '}';

        public void Parse(string s)
        {
            Stack<char> myStack = new Stack<char>();

            foreach(char ch in s)
            {
                if (ch == OPEN_PAREN || ch == OPEN_BRACKET || ch == OPEN_BRACE)
                    myStack.Push(ch);
                else
                {
                    if (ch == CLOSE_PAREN || ch == CLOSE_BRACKET || ch == CLOSE_BRACE)
                    {
                        if (myStack.Count == 0)
                        {
                            Console.WriteLine("Error: Closing symbol not matched");
                            return;
                        }
                        else
                        {
                            char tmp = myStack.Pop();
                            if (!CheckMatch(tmp, ch)) return;
                        }
                    }
                }
            }

            if (myStack.Count != 0)
                Console.WriteLine("Error: Opening symbol not matched");
            else
                Console.WriteLine("All symbols matched!");
        }

        private bool CheckMatch(char open_symbol, char close_symbol)
        {
            if ((open_symbol == OPEN_PAREN) && (close_symbol != CLOSE_PAREN) ||
                (open_symbol == OPEN_BRACKET) && (close_symbol != CLOSE_BRACKET) ||
                (open_symbol == OPEN_BRACE) && (close_symbol != CLOSE_BRACE))
            {
                Console.WriteLine($"Error: {open_symbol} and {close_symbol} not matched");
                return false;
            }
            return true;
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            BalancedSymbolChecker scheck = new BalancedSymbolChecker();
            scheck.Parse("((a + b) - c)");
            scheck.Parse("({a + b) - c * k))");
            scheck.Parse("v * (((a + b) - c)");


            Console.Read();
        }
    }
