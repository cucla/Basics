public class TwoGeneric<T, U>
    {
        //fields
        private T _field1;
        private U _field2;

        //constructors
        private TwoGeneric() { }  //disable default constructor
        public TwoGeneric(T arg1, U arg2)
        {
            _field1 = arg1;
            _field2 = arg2;
        }

        //properties
        public T PropertyOne
        {
            get { return _field1; }
            set { _field1 = value; }
        }

        public U PropertyTwo
        {
            get { return _field2; }
            set { _field2 = value; }
        }

        public void PrettyPrint()
        {
            Console.WriteLine("T is a " + _field1.GetType().ToString() + " with value " + _field1);
            Console.WriteLine("U is a " + _field2.GetType().ToString() + " with value " + _field2);
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            TwoGeneric<string, int> myObj = new TwoGeneric<string, int>("Hello", 8);
            myObj.PropertyTwo = 365;
            myObj.PrettyPrint();

            Console.Read();
        }
    }
    
    
