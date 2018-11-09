using System;
using System.Diagnostics;

namespace AppForInterview
{
    class Program
    {
        delegate int myDelegate(int num1, int num2);

        static int Add(int num1, int num2) { return num1 + num2; }


        static void Main(string[] args)
        {
            int a = 10, b = 20;

            //--------measure time for delegate to invoke Add() method-------------
            Stopwatch time = new Stopwatch();
            time.Reset();
            time.Start();
            for (int i = 0; i < 500; i++)
            {
                myDelegate d = Add;
                d.Invoke(a, b);
            }
            time.Stop();
            Console.Write(time.ElapsedTicks.ToString());
            Console.WriteLine();

            //--------measure time for delegate to invoke Anonymous method----------
            time.Reset();
            time.Start();
            for (int i = 0; i < 500; i++)
            {
                myDelegate d = delegate (int num1, int num2) { return num1 + num2; };
                d.Invoke(a, b);
            }
            time.Stop();
            Console.Write(time.ElapsedTicks.ToString());

            Console.Read();
        }
    }
}
