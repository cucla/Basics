using System;
using System.Collections;

namespace AppForInterview
{
    // FACADE (wrapper) design pattern
    // creates type-safe collection, allowing only insertion of a Dog type into ArrayList

    public class Dog : IComparable
    {
        public Dog(string someName, string someBreed)
        {
            Name = someName;
            Breed = someBreed;
        }

        public string Name { get; set; }
        public string Breed { get; set; }
        public string BreedName { get { return Name + " -> " + Breed; } }

        public override string ToString() { return this.BreedName; }

        public int CompareTo(object obj)
        {
            if (obj is Dog)
                return this.Name.CompareTo(((Dog)obj).Name);
            else
                throw new ArgumentException("Object is not a Dog!");
        }
    }

    public class DogList: IEnumerable
    {
        const int INITIAL_SIZE = 25;

        public DogList() : this(INITIAL_SIZE) { }
        public DogList(int size) { _list = new ArrayList(size); }

        private ArrayList _list = null;

        public Dog this[int i]
        {
            get { return (Dog)_list[i]; }
            set { _list[i] = value; }
        }
        public void Add(Dog d) { _list.Add(d); }
        public int Count() { return _list.Count; }
        public void Sort() { _list.Sort(); }
        public void Reverse() { _list.Reverse(); }
        public void Remove(Dog d) { _list.Remove(d); }
        public IEnumerator GetEnumerator() { return _list.GetEnumerator(); }
    }

    class Program
    {
        static void Main(string[] args)
        {
            DogList dogs = new DogList();
            dogs.Add(new Dog("Bob", "spaniel"));
            dogs.Add(new Dog("Arden", "haski"));
            dogs.Add(new Dog("Boss", "shepherd"));

            for (int i = 0; i < dogs.Count(); i++)
            {
                Console.WriteLine(dogs[i]);
            }
            Console.WriteLine();

            dogs.Sort();
            foreach (Dog d in dogs) { Console.WriteLine(d); }
            Console.WriteLine();

            dogs.Reverse();
            foreach (Dog d in dogs) { Console.WriteLine(d); }
        }
    }
}
