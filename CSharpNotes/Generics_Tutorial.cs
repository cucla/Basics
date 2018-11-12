/*  1. Two generic parameters
 *  2. Constructor constraint
 */

// 1. Two generic parameters--------------------------------------------------
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
    
// 2. Constructor constraint--------------------------------------------------
// to indicate that the generic code can create new objects of the type
// represented by the type parameter. The type's argument class must provide
// a public parameterless or default constructor
//----------------------------------------------------------------------------
    public class MyClass
    {
        public MyClass(): this("Hello world!") { }
        public MyClass(string s) { _filed1 = s; }

        private string _filed1;
        public string PropertyOne
        {
            get { return _filed1; }
            set { _filed1 = value; }
        }
    }

// GenericFactory<T> implemets both factory and singleton design patterns.
// It is used to create instances of MyClass
    public class GenericFactory<T> where T : new()
    {
        private static GenericFactory<T> factory;
        public static GenericFactory<T> Factory
        {
            get
            {
                if (factory != null) return factory;
                else
                {
                    factory = new GenericFactory<T>();
                    return factory;
                }
            }
        }
        public T NewObj() { return new T(); }
    }

    class Program
    {
        static void Main(string[] args)
        {
            MyClass myClassOne = GenericFactory<MyClass>.Factory.NewObj();
            MyClass myClassTwo = GenericFactory<MyClass>.Factory.NewObj();
            myClassTwo.PropertyOne = "Bye bye!";
            Console.WriteLine(myClassOne.PropertyOne);
            Console.WriteLine(myClassTwo.PropertyOne);

            Console.Read();
        }
    }
//----------------------------------------------------------------------------
