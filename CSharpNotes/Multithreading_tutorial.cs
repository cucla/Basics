/* 1. Call method in a separate thread in UnitTests
 * 2. Begin/End Async pattern in UnitTests
 * 3. Begin/End Async Networking example in UnitTests
 * 4. Begin/End Async Database example in UnitTests
 * 5. Use IsCompleted property of the IAsyncResult
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

//3. Begin/End Async Networking example in UnitTests-----------------------------------------
namespace Networking
{
    [TestClass]
    public class Test_Download
    {
        string url = "http://deelay.me/5000/http://www.delsink.com";

        [TestMethod]
        public void Test_Download_DelsinkCOM()
        {
            var httpRequestInfo = HttpWebRequest.CreateHttp(url);
            var callback = new AsyncCallback(HttpResponseAvailable);
            var ar = httpRequestInfo.BeginGetResponse(callback, httpRequestInfo);

            ar.AsyncWaitHandle.WaitOne();
        }
        private static void HttpResponseAvailable(IAsyncResult ar)
        {
            var httpRequestInfo = ar.AsyncState as HttpWebRequest;
            var httpResponseInfo = httpRequestInfo.EndGetResponse(ar) as HttpWebResponse;

            var responseStream = httpResponseInfo.GetResponseStream(); // downloading the page contents
            using (var sr = new StreamReader(responseStream))
            {
                var webPage = sr.ReadToEnd();
            }
        }
    }
}
//-------------------------------------------------------------------------------------------

// 4. Begin/End Async Database example in UnitTests------------------------------------------
namespace Databases
{
    [TestClass]
    public class Test_Databases
    {
        [TestMethod]
        public void Test_DB_Async()
        {
            string connectionString;
            #region Assign connectionString
            connectionString = "";
            #endregion

            string sqlSelect = "SELECT @@VERSION";

            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();

                var sqlCommand = new SqlCommand(sqlSelect, sqlConnection);
                var callback = new AsyncCallback(DataAvailable);
                var ar = sqlCommand.BeginExecuteReader(callback, sqlCommand);

                ar.AsyncWaitHandle.WaitOne();
            }
        }
        private static void DataAvailable(IAsyncResult ar)
        {
            var sqlCommand = ar.AsyncState as SqlCommand;
            using (var reader = sqlCommand.EndExecuteReader(ar))
            {
                while (reader.Read())
                {
                    var data = reader[0].ToString();
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------

// 5. Use IsCompleted property of the IAsyncResult-------------------------------------------
    class Program
    {
        public delegate int BinaryOp(int x, int y);

        static void Main(string[] args)
        {
            Console.WriteLine("Main() invoked on thread {0}", Thread.CurrentThread.ManagedThreadId);

            BinaryOp b = Add;
            IAsyncResult ar = b.BeginInvoke(5, 5, null, null);
            while (!ar.IsCompleted)
            {
                //Do some other work on priamry thread..
                Console.WriteLine("Doing some work in Main()!");
                Thread.Sleep(100);
            }

            int result = b.EndInvoke(ar);
            Console.WriteLine("5 + 5 is {0}", result);
        }

        public static int Add(int a, int b)
        {
            Console.WriteLine("On thread {0}", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(500);
            return (a + b);
        }
    }
//-------------------------------------------------------------------------------------------

