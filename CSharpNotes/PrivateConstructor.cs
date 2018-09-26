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
 
 
