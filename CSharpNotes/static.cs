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
