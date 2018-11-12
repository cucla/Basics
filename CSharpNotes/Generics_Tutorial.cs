/*  1. Two generic parameters
 *  2. Constructor constraint
 *  3. Reference/value type constraints
 *  4. Interface constraint
 */

// 1. Two generic parameters--------------------------------------------------
//----------------------------------------------------------------------------
public class TwoGeneric<T, U>
    {
        private T _field1;
        private U _field2;

        private TwoGeneric() { }  //disable default constructor
        public TwoGeneric(T arg1, U arg2)
        {
            _field1 = arg1;
            _field2 = arg2;
        }
 
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
        }
    }
//----------------------------------------------------------------------------

// 3. Reference/value type constraints----------------------------------------
// Use either of these if generic code needs to know if it's dealing with 
// reference (class) or value (struct) types.
// Difference exists in comparison or equality semantics: by default Object.Equals() 
// compares two references with same values but distinct memory locations as
// different.
// BUT: Object.Equals() can be overriden in derived classes, like in string class
//----------------------------------------------------------------------------
public class MyClass
    {
        public MyClass(): this(0) { }
        public MyClass(int num) { _filed1 = num; }

        private int _filed1;
        public int PropertyOne
        {
            get { return _filed1; }
            set { _filed1 = value; }
        }
    }

    public class EqualityCheker<T> where T : class
    {
        public bool CheckEquality(T a, T b)
        {
            bool result = a.Equals(b);
            Console.WriteLine(result + ": {0} is " + (result ? "" : "not ") + "equal to {1}", a, b);
            return result;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            EqualityCheker<string> eq1 = new EqualityCheker<string>();
            eq1.CheckEquality("hello", "hello");        // true
            eq1.CheckEquality("hi", "bye");             // false

            EqualityCheker<MyClass> eq2 = new EqualityCheker<MyClass>();
            eq2.CheckEquality(new MyClass(5), new MyClass(5));      // false
        }
    }
//----------------------------------------------------------------------------
public struct MyStruct
    {   // explicit default constructors are not allowed in structs
        public MyStruct(int num) { _filed1 = num; }

        private int _filed1;
        public int PropertyOne
        {
            get { return _filed1; }
            set { _filed1 = value; }
        }
    }

    public class EqualityCheker<T> where T : struct
    {
        public bool CheckEquality(T a, T b)
        {
            bool result = a.Equals(b);
            Console.WriteLine(result + ": {0} is " + (result ? "" : "not ") + "equal to {1}", a, b);
            return result;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            EqualityCheker<int> eq1 = new EqualityCheker<int>();
            eq1.CheckEquality(2, 2);        // true
            eq1.CheckEquality(10, 20);      // false

            EqualityCheker<MyStruct> eq2 = new EqualityCheker<MyStruct>();
            eq2.CheckEquality(new MyStruct(5), new MyStruct(5));        // true
        }
    }
//----------------------------------------------------------------------------

// 4. Interface constraint----------------------------------------------------
//----------------------------------------------------------------------------
   public class EqualityCheker<T> where T : IComparable, IComparable<T>
    {
        public bool CheckEquality(T a, T b)
        {
            bool result = false;
            int tmp = a.CompareTo(b);
            if (tmp == 0)
                result = true;
            Console.WriteLine(result + ": {0} is " + (result ? "" : "not ") + "equal to {1}", a, b);
            return result;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            EqualityCheker<int> eq1 = new EqualityCheker<int>();
            eq1.CheckEquality(2, 2);        // true
            eq1.CheckEquality(1, 10);       // false

            EqualityCheker<string> eq2 = new EqualityCheker<string>();
            eq2.CheckEquality("Hi", "Hi");          // true
        }
    }
//----------------------------------------------------------------------------


