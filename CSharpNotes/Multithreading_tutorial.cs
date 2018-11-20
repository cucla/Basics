/* 1. Start worker Thread twice
 * 2. Synchronization options
 */

// 1. Start second Thread twice-------------------------------------------------------------------
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("From Main() Id: {0}", Thread.CurrentThread.ManagedThreadId);

            var t1 = new Thread(new ThreadStart(DoWork));  
            //or Thread t1 = new Thread(DoWork);
            //or Thread t1 = new Thread ( () => Console.WriteLine ("Hello!") );   // using lambda
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

// 2. Synchronization options---------------------------------------------------------------------
using System;
using System.Runtime.Remoting.Contexts;
using System.Threading;

namespace AppForInterview
{
    // RACE CONDITION occurs if few threads access the same object, not synchronized
    // Solution 1: locks
    // Solution 2: use Monitor class
    // Solution 3: use Mutex class
    // Solution 3: use Semaphore class
    // Solution 5: use [Synchronization] Attribute

    public class Work
    {
        private static object _myLock = new object();
        private static Mutex mutex = new Mutex();
        static Semaphore SemaphoreObj = new Semaphore(2, 4);

        public void UseLock()
        {
            lock (_myLock)
            {
                //Some printing work-----------------------------------------------------
                Console.Write("Thread Id: {0} -> ", Thread.CurrentThread.ManagedThreadId);
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(500);
                    Console.Write("{0} ", i);
                }
                Console.WriteLine();
                //-----------------------------------------------------------------------
            }
        }

        public void UseMonitor()
        {
            try
            {
                Monitor.Enter(_myLock);

                //Some printing work-----------------------------------------------------
                Console.Write("Thread Id: {0} -> ", Thread.CurrentThread.ManagedThreadId);
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(500);
                    Console.Write("{0} ", i);
                }
                Console.WriteLine();
                //-----------------------------------------------------------------------
            }
            finally
            {
                Monitor.Exit(_myLock);
            }
        }

        // with Monitor class we can check if lock is present 
        // and return immediately instead of waiting if acquiring a lock wasn’t possible
        public void UseMonitor2()
        {
            var hasLock = false;

            try
            {
                Monitor.TryEnter(_myLock, ref hasLock);
                if (!hasLock)
                {
                    return;
                }

                //Some printing work-----------------------------------------------------
                Console.Write("Thread Id: {0} -> ", Thread.CurrentThread.ManagedThreadId);
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(500);
                    Console.Write("{0} ", i);
                }
                Console.WriteLine();
                //-----------------------------------------------------------------------
            }
            finally
            {
                if (hasLock)
                {
                    Monitor.Exit(_myLock);
                }
            }
        }

        public void UseMutex()
        {
            try
            {
                mutex.WaitOne();   // Wait until it is safe to enter.  

                //Some printing work-----------------------------------------------------
                Console.Write("Thread Id: {0} -> ", Thread.CurrentThread.ManagedThreadId);
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(500);
                    Console.Write("{0} ", i);
                }
                Console.WriteLine();
                //-----------------------------------------------------------------------
            }
            finally
            {
                mutex.ReleaseMutex();
            }
        }

        public void UseSemaphore() 
        {
            try
            {
                SemaphoreObj.WaitOne();   // 2 semaphores are immediately created and the others wait

                //Some printing work-----------------------------------------------------
                Console.Write("Thread Id: {0} -> ", Thread.CurrentThread.ManagedThreadId);
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(500);
                    Console.Write("{0} ", i);
                }
                Console.WriteLine();
                //-----------------------------------------------------------------------
            }
            finally
            {
                SemaphoreObj.Release();
            }
        }
    }

    [Synchronization]
    public class Work2 : ContextBoundObject
    {
        public void UseSynchronization()
        {
            //Some printing work-----------------------------------------------------
            Console.Write("Thread Id: {0} -> ", Thread.CurrentThread.ManagedThreadId);
            for (int i = 0; i < 10; i++)
            {
                Thread.Sleep(500);
                Console.Write("{0} ", i);
            }
            Console.WriteLine();
            //-----------------------------------------------------------------------
        }
    }
    

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("From Main() Id: {0}", Thread.CurrentThread.ManagedThreadId);

            Work w = new Work();   // access the same object
            Work2 w2 = new Work2();  

            Thread[] thArr = new Thread[5];
            for (int i = 0; i < 5; i++)
            {
                //thArr[i] = new Thread(new ThreadStart(w.UseLock));
                //thArr[i] = new Thread(new ThreadStart(w.UseMonitor));
                //thArr[i] = new Thread(new ThreadStart(w.UseMonitor2));
                //thArr[i] = new Thread(new ThreadStart(w.UseMutex));
                thArr[i] = new Thread(new ThreadStart(w.UseSemaphore));
                //thArr[i] = new Thread(new ThreadStart(w2.UseSynchronization));
            }

            foreach (Thread x in thArr)
            {
                x.Start();
            }


            Console.Read();
        }
    }
}
//------------------------------------------------------------------------------------------------

// 1. Start second Thread twice-------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

// 1. Start second Thread twice-------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
