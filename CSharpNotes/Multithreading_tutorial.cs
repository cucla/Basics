/* 1. Start second Thread twice
 */

// 1. Start second Thread twice-------------------------------------------------------------------
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("From Main() Id: {0}", Thread.CurrentThread.ManagedThreadId);

            var t1 = new Thread(new ThreadStart(DoWork));  // or Thread t1 = new Thread(DoWork);
            t1.Start();

            t1 = new Thread(DoMoreWork);
            t1.Start(44);
        }

        public static void DoWork()
        {
            Console.WriteLine("From DoWork() Id: {0}", Thread.CurrentThread.ManagedThreadId);
        }

        public static void DoMoreWork(object data)
        {
            Console.WriteLine("From DoMoreWork() Id: {0}", Thread.CurrentThread.ManagedThreadId);
            Console.WriteLine("From DoMoreWork() Data: '{0}'", data);
        }
    }
//------------------------------------------------------------------------------------------------

// 1. Start second Thread twice-------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

// 1. Start second Thread twice-------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

// 1. Start second Thread twice-------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
