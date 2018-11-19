/* 1. Call method in a separate thread in Unit Tests
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


