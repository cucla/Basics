class Singleton{
public:
    static Singleton * GetInstance() {
		if(NULL == s_instance)
			 s_instance=new Singleton();
		return s_instance;      
	}
    void display() { printf("Singleton class!!!\n"); }  
    ~Singleton() { }
private:
    Singleton(){} 
    Singleton(const Singleton & obj){}
   
    static Singleton * s_instance;    
};

Singleton * Singleton::s_instance = 0;


int main()
{
    // both objects have the same address
    Singleton * s_obj1 = Singleton::GetInstance();
    s_obj1->display();
    cout<<"Address of object is:"<<s_obj1<<"\n"; 
 
    Singleton * s_obj2 = Singleton::GetInstance(); 
    s_obj2->display();	
    cout<<"Address of object is:"<<s_obj2<<"\n";
}
