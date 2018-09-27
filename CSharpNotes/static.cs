// Use the 'static' modifier

/* 1. Static field and method in a non-static class, which do not belong to 
 * any instance, instead they belong to the class
 */
public class Employee
{
    public string id;
    public string name;

    public Employee() { }
    public Employee(string name, string id)
    {
        this.name = name;
        this.id = id;
    }

    public static int employeeCounter;
    public static int AddEmployee() { return ++employeeCounter; }
}
class MainClass
{
    static void Main()
    {
        Employee4 e = new Employee4("Ben", "054321");
        Employee.employeeCounter = 1;
        Employee4.AddEmployee();       //2
    }
}

/* 2. STATIC CONSTRUCTOR
 * useful for initializing any static fields, 
 * in particular for reading required configuration data into readonly fields
 * >> does not take access modifiers or have parameters
 * >> is called automatically before the first instance is created or any static members are referenced
 * >> cannot be called directly
 *
 * 2.1. In a non-static class A (static constructor is called only once):
 */
 public class Program 
 { 
     public static void Main(string[] args) 
     { 
         A myClass1WithStaticConstructor = new A();
         A myClass2WithStaticConstructor = new A();
     } 
 } 
 public class A 
 { 
     static string firstPart= "http://www.example.com/";
     static string fullUrl;
     static string urlFragment = "foo/bar";
     
     public A() { Console.WriteLine("default constructor"); }
     static A() { 
         fullUrl = firstPart + urlFragment;     // no matter fields order
         Console.WriteLine("static constructor"); 
     } 
 } 

/* 2.2. In a static class A (static constructor is called only once):
 */
public class Program
{
	public static void Main(string[] args)
	{
		Console.WriteLine(A.fullUrl);
	}
}
public static class A
{
	public static string firstPart = "http://www.example.com/";
	public static string fullUrl;
	public static string urlFragment = "foo/bar";

	static A()
	{
		fullUrl = firstPart + urlFragment;     // no matter fields order
		Console.WriteLine("static constructor");
	}
}

 
