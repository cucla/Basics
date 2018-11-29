namespace AppForInterview
{ 
    class Demo
    {
        /* NOT ~    :   ~0 -> 1
         *              ~1 -> 0
         * AND &    :   1 & 1 -> 1  
         *              1 & 0 -> 0   
         *              0 & 0 -> 0 
         * OR |     :   1 | 1 -> 1
         *              1 | 0 -> 1
         *              0 | 0 -> 0   
         * XOR ^    :   1 ^ 1 -> 0
         *              0 ^ 0 -> 0
         *              1 ^ 0 -> 1     
         * << 1     :   adds 1 'zero' on the right  
         * >> 1     :   removes 1 bit on the right                                    
         */

        static void Main(string[] args)
        {   
            // NOT
            Console.WriteLine($"~5 [~{Convert.ToString(5, toBase: 2)}] : " +
                $"{Convert.ToString(~5 & 0x7, toBase: 2)}, {~5 & 0x7}");        // 111
            Console.WriteLine($"~11 [~{Convert.ToString(11, toBase: 2)}] : " +
                $"{Convert.ToString(~11 & 0xf, toBase: 2)}, {~11 & 0xf}");     // 1111
            Console.WriteLine($"~16 [~{Convert.ToString(16, toBase: 2)}] : " +
                $"{Convert.ToString(~16 & 0x1f, toBase: 2)}, {~16 & 0x1f}");   // 11111
            Console.WriteLine();

            // XOR
            Console.WriteLine($"10 ^ 11 [ {Convert.ToString(10, toBase: 2)} ^ " + 
                $"{Convert.ToString(11, toBase: 2)} ] : " +
                $"{Convert.ToString(10 ^ 11, toBase: 2)}, {10 ^ 11}");

            Console.WriteLine($"10 ^ 12 [ {Convert.ToString(10, toBase: 2)} ^ " +
                $"{Convert.ToString(12, toBase: 2)} ] : " +
                $"{Convert.ToString(10 ^ 12, toBase: 2)}, {10 ^ 12}");
            Console.WriteLine();

            // SHIFT
            Console.WriteLine($"11 << 1 [{Convert.ToString(11, toBase: 2)} << 1]  : " + 
                $"{Convert.ToString(11 << 1, toBase: 2)}, {11 << 1}");
            Console.WriteLine($"11 << 4 [{Convert.ToString(11, toBase: 2)} << 4]  : " +
                $"{Convert.ToString(11 << 4, toBase: 2)}, {11 << 4}");
            Console.WriteLine();
            Console.WriteLine($"1 << 1 : {Convert.ToString(1 << 1, toBase: 2)}");
            Console.WriteLine($"1 << 2 : {Convert.ToString(1 << 2, toBase: 2)}");
            Console.WriteLine($"1 << 4 : {Convert.ToString(1 << 4, toBase: 2)}");
            Console.WriteLine();
            Console.WriteLine($"11 >> 1 [{Convert.ToString(11, toBase: 2)} >> 1]  : " +
                $"{Convert.ToString(11 >> 1, toBase: 2)}, {11 >> 1}");
            Console.WriteLine($"11 >> 3 [{Convert.ToString(11, toBase: 2)} >> 3]  : " +
                $"{Convert.ToString(11 >> 3, toBase: 2)}, {11 >> 3}");
            Console.WriteLine($"11 >> 4 [{Convert.ToString(11, toBase: 2)} >> 4]  : " +
                $"{Convert.ToString(11 >> 4, toBase: 2)}, {11 >> 4}");
            Console.WriteLine($"11 >> 5 [{Convert.ToString(11, toBase: 2)} >> 5]  : " +
                $"{Convert.ToString(11 >> 5, toBase: 2)}, {11 >> 5}");
            Console.WriteLine();

            // PROPERTY No.1
            // (x-1) will have all the bits same as (x), except for the rightmost 1 in (x) 
            // and all the bits to the right of the rightmost 1
            Console.WriteLine($"22 : {Convert.ToString(22, toBase: 2)}");
            Console.WriteLine($"22 - 1 : {Convert.ToString(22 - 1, toBase: 2)}");
            Console.WriteLine($"21 : {Convert.ToString(21, toBase: 2)}");
            Console.WriteLine($"21 - 1 : {Convert.ToString(21 - 1, toBase: 2)}");
            Console.WriteLine();

            // PROPERTY No.2
            // Powers of 2 have only 1 bit set (only 1 'one' and rest 'zeros')
            // x & (x-1) should give 0000000...
            Console.WriteLine($"4 & 3 [{Convert.ToString(4, toBase: 2)} & {Convert.ToString(3, toBase: 2)}]  : " +
                $"{Convert.ToString(4 & 3, toBase: 2)}, {4 & 3}");
            Console.WriteLine();

            // count number of 1s:
            Console.WriteLine($"22 & 21 [{Convert.ToString(22, toBase: 2)} & {Convert.ToString(21, toBase: 2)}]  : " +
                $"{Convert.ToString(22 & 21, toBase: 2)}, {22 & 21}");
            Console.WriteLine($"20 & 19 [{Convert.ToString(20, toBase: 2)} & {Convert.ToString(19, toBase: 2)}]  : " +
                $"{Convert.ToString(20 & 19, toBase: 2)}, {20 & 19}");
            Console.WriteLine($"16 & 15 [{Convert.ToString(16, toBase: 2)} & {Convert.ToString(15, toBase: 2)}]  : " +
                $"{Convert.ToString(16 & 15, toBase: 2)}, {16 & 15}");
            Console.WriteLine();
            /*
               int count_one (int n)
               {
                    while( n )
                    {
                        n = n & (n-1);
                        count++;
                    }
                    return count;
               }
             */

            // check if nth bit is set ( 4 is 100) :
            Console.WriteLine($"22 & 4 [{Convert.ToString(22, toBase: 2)} & {Convert.ToString(4, toBase: 2)}]  : " +
                $"{Convert.ToString(22 & 4, toBase: 2)}, {22 & 4}");
            // if( N & (1 << i) ) return true;

        }
    }
}
