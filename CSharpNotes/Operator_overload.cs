// class MyType is a wrapper around integer object
// class GenericType<T> constraints type parameter to objects of type MyType

using System;


namespace AppForInterview
{
    public class MyType
    {
        public MyType() : this(5) { }
        public MyType(int num)
        {
            _intfield = num;
        }

        private int _intfield;

        public int IntField
        {
            get { return _intfield; }
            set { _intfield = value; }
        }

        public static MyType operator +(MyType mt)  // unary plus
        {
            mt.IntField = (+mt.IntField);
            return mt;
        }

        public static MyType operator -(MyType mt)  // unary minus
        {
            mt.IntField = (-mt.IntField);
            return mt;
        }

        public static bool operator !(MyType mt)  
        {
            bool retVal = true;
            if (mt.IntField >= 0) retVal = false;
            return retVal;
        }

        public static bool operator true(MyType mt)
        {
            return !mt;
        }

        public static bool operator false(MyType mt)
        {
            return !mt;
        }

        public static MyType operator ++(MyType mt)
        {
            MyType result = new MyType(mt.IntField);
            ++result.IntField;
            return result;
        }

        public static MyType operator --(MyType mt)
        {
            MyType result = new MyType(mt.IntField);
            --result.IntField;
            return result;
        }

        public static MyType operator +(MyType lhs, MyType rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField += rhs.IntField;
            return result;
        }

        public static MyType operator -(MyType lhs, MyType rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField -= rhs.IntField;
            return result;
        }

        public static MyType operator +(MyType lhs, int rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField += rhs;
            return result;
        }

        public static MyType operator -(MyType lhs, int rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField -= rhs;
            return result;
        }

        public static MyType operator *(MyType lhs, MyType rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField *= rhs.IntField;
            return result;
        }

        public static MyType operator *(MyType lhs, int rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField *= rhs;
            return result;
        }

        public static MyType operator /(MyType lhs, MyType rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField /= rhs.IntField;
            return result;
        }

        public static MyType operator /(MyType lhs, int rhs)
        {
            MyType result = new MyType(lhs.IntField);
            result.IntField /= rhs;
            return result;
        }

        public static explicit operator int(MyType mt)
        {
            return mt.IntField;
        }

        public override string ToString()
        {
            return IntField.ToString();
        }
    }

    public class GenericType<T> where T : MyType
    {
        public void PrintSum(T arg1, T arg2)
        {
            Console.WriteLine(arg1 + " + " + arg2 + " = " + (arg1 + arg2));
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            GenericType<MyType> one = new GenericType<MyType>();
            one.PrintSum(new MyType(10), new MyType(100));
        }
    }
}
