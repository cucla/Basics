/* 1. Call method in a separate thread in UnitTests
 * 2. Begin/End Async pattern in UnitTests
 */
 
// 1. Call method in a separate thread in Unit Tests-----------------------------------------
using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Diagnostics;

namespace UnitTestProject
{
    [TestClass]
    public class Test_Delegates
    {
        private void DoWork()
        {
            Debug.WriteLine("Hello World");
            Debug.WriteLine(System.Threading.Thread.CurrentThread.ManagedThreadId.ToString());
        }

        delegate void DoWorkDelegate();

        [TestMethod]
        public void Demo01()
        {
            Debug.WriteLine(System.Threading.Thread.CurrentThread.ManagedThreadId.ToString());           
            DoWorkDelegate m = DoWork;
            //m.Invoke();                                         // same thread
            
            IAsyncResult ar = m.BeginInvoke(null, null);          // different thread
            m.EndInvoke(ar);
        }
    }
}
//-------------------------------------------------------------------------------------------

// 2. Begin/End Async pattern in UnitTests---------------------------------------------------
using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Diagnostics;

namespace UnitTestProject
{
    [TestClass]
    public class Test_Delegates
    {
        private void DoWork()
        {
            Debug.WriteLine("Hello World");
            Debug.WriteLine(System.Threading.Thread.CurrentThread.ManagedThreadId.ToString());
        }

        delegate void DoWorkDelegate();

        [TestMethod]
        public void Demo01()
        { 
            // if you want to notify when .BeginInvoke() is done -> use callback

            Debug.WriteLine(System.Threading.Thread.CurrentThread.ManagedThreadId.ToString());
            DoWorkDelegate m = new DoWorkDelegate(DoWork);

            // 2. delegate is needed to pass TheCallback() into .BeginInvoke(callback, ...)
            AsyncCallback callback = new AsyncCallback(TheCallback);
            IAsyncResult ar = m.BeginInvoke(callback, m);
            // do more 

            ar.AsyncWaitHandle.WaitOne();  // only for unittest framework
        }

        // 1. TheCallback() is called when async method actually completes
        private static void TheCallback(IAsyncResult ar)
        {
            var m = ar.AsyncState as DoWorkDelegate;
            m.EndInvoke(ar); // this is where you use try/catch
        }
    }
}
//-------------------------------------------------------------------------------------------



