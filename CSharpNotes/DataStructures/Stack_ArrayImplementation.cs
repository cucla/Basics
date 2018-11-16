    // implemented as array of objects
    class MyStack
    {
        public MyStack() : this(INITIAL_SIZE) { }
        public MyStack(int size) { _stack_contents = new object[size]; }

        private const int INITIAL_SIZE = 3;
        private object[] _stack_contents;
        private int _top = -1;

        public bool IsEmpty { get { return _top == -1; } }

        public bool Push(object obj)
        {
            if (obj == null) return false;
            else
            {
                if ((++_top) >= _stack_contents.Length)
                    GrowStack();
                _stack_contents[_top] = obj;
                return true;
            }
        }

        public bool Pop()
        {
            if (IsEmpty) return false;
            else
            {
                _stack_contents[_top--] = null;
                return true;
            }
        }

        public object Top()
        {
            if (IsEmpty)
                throw new InvalidOperationException("The stack is empty!");
            return _stack_contents[_top];
        }

        private void GrowStack()
        {
            int new_size = this._stack_contents.Length * 2;

            object[] tmp = this._stack_contents;
            this._stack_contents = new object[new_size];
            tmp.CopyTo(_stack_contents, 0);
            tmp = null;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            MyStack stack1 = new MyStack();
            stack1.Push(1);
            stack1.Push(2);
            stack1.Push(3);
            stack1.Push(4);
            stack1.Push(5);
            stack1.Pop();

            Console.WriteLine(stack1.Top().ToString());


            Console.Read();
        }
    }
