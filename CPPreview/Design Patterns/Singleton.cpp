class Singleton{
public:
    static Singleton* GetInstance(){
		if(NULL == s_instance)
		{
			 s_instance=new Singleton();
		}
 
		return s_instance;      
	}
    void display(){		
		printf("Singleton class!!!\n");
	}
  
	~Singleton(){ 
		//delete s_instance;
	}
private:
	// Make the constructor private so, user can 
	//create object directly but with GetInstance() method.
	Singleton(){} 
	// copy constructor private
	Singleton(const Singleton & obj){}
   
    static Singleton* s_instance;
    
};
// initialize static singleton pointer
Singleton *Singleton::s_instance = 0;


int main(){
    //Singleton pattern
    Singleton* s_obj1 = Singleton::GetInstance();
    s_obj1->display();
	
	cout<<"Address of object is:"<<s_obj1<<"\n"; 
Singleton* s_obj2 = Singleton::GetInstance(); 
s_obj2->display();	
	
	cout<<"Address of object is:"<<s_obj2<<"\n";
 
	//Note that address of both object s_obj1 & s_obj2 must be same.	
	
 
    return 0;
}
