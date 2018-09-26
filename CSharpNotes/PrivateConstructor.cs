// When do we need a private constructor?

/* 1. Base Constructor
 * Can be used to create "base" constructors that are called from other
 * more accessible constructors
 */ 
public class MyClass
{
    private MyClass(object data1, string data2) { }   
    public MyClass(object data1) : this(data1, null) { }
    public MyClass(string data2) : this(null, data2) { }
    public MyClass() : this(null, null) { }
}

/* 2. Pseudo-Sealed with Nested Children
 * Any nested classes that inherit from the outer class can access the 
 * private constructor
 */ 
public abstract class BaseClass
{
    private BaseClass() { }
    public class SubClass1 : BaseClass
    {
        public SubClass1() : base() { }
    }

    public class SubClass2 : BaseClass
    {
        public SubClass2() : base() { }
    }
}
 
