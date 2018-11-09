using System;


namespace AppForInterview
{
    public interface IAccount
    {
        void PrintData();
    }

    public class SavingAccount : IAccount
    {
        public void PrintData()
        {
            Console.WriteLine("Saving account data.");
        }
    }

    public class CurrentAccount : IAccount
    {
        public void PrintData()
        {
            Console.WriteLine("Current account data.");
        }
    }

    public class Account
    {
        // No need to be dependent on SavingAccount & CurrentAccount classes
        // Code below is tightly coupled:
        //
        // SavingAccount savingAccount = new SavingAccount();
        // CurrentAccount currentAccount = new CurrentAccount();

        // public void PrintAccounts()
        // {
        //    savingAccount.PrintData();
        //    currentAccount.PrintData();
        // }


        //----------------DI via constructor-------------------------------------
        // For loosely coupled code use Interface
        // so that no class objects are created in class
        private IAccount _account1, _account2;

        public Account(IAccount account1, IAccount account2)
        {
            this._account1 = account1;
            this._account2 = account2;
        }

        public void PrintAccounts()
        {
            _account1.PrintData();
            _account2.PrintData();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            IAccount savingAccount = new SavingAccount();
            IAccount currentAccount = new CurrentAccount();

            Account account = new Account(savingAccount, currentAccount);
            account.PrintAccounts();

            Console.Read();
        }
    }
}


....
    public class Account
    {

        //----------------DI via setter-------------------------------------
        public IAccount account1 { get; set; }
        public IAccount account2 { get; set; }

        public void PrintAccounts()
        {
            account1.PrintData();
            account2.PrintData();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Account account = new Account();
            account.account1 = new SavingAccount();
            account.account2 = new CurrentAccount();
            account.PrintAccounts();

            Console.Read();
        }
    }


....
    public class Account
    {
        //----------------DI via method------------------------------------

        public void PrintAccounts(IAccount account1, IAccount account2)
        {
            account1.PrintData();
            account2.PrintData();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Account account = new Account();
            account.PrintAccounts(new SavingAccount(), new CurrentAccount());

            Console.Read();
        }
    }
