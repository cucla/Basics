// https://books.google.com.tw/books?id=K0ICo6r29W4C&pg=PA1&source=gbs_toc_r&cad=4#v=onepage&q&f=false
// https://books.google.com.tw/books?id=HCxxUaZHQF4C&pg=PA286&lpg=PA286&dq=C%23+sortablebindinglist.clear&source=bl&ots=Njy8YNJeaA&sig=bMnUhvDr3adTwVeYkpFvpyYBd-c&hl=en&sa=X&ved=2ahUKEwi4jMDv2sbdAhUJvbwKHfkfBEEQ6AEwD3oECAUQAQ#v=onepage&q=C%23%20sortablebindinglist.clear&f=false
// (117 page)

/* 1. Array Sum
 * 2. Matrix diagonals
 * 3. Anonymous delegate
 */
 
// 1. Array Sum-------------------------------------------------------------------------------
int[] myArr = { 1, 10, 100, 1000 };
myArr.Sum();

int sum = 0;
Array.ForEach(myArr, (a) => { sum += a; });

int sum2 = myArr.Aggregate((a, b) => a + b );
//--------------------------------------------------------------------------------------------

// 2. Matrix diagonals------------------------------------------------------------------------
public static IEnumerable<T> PrimaryDiagonal<T>(IEnumerable<T[]> values)
{
    return values.Select((x, i) => x[i]);
}

public static IEnumerable<T> SecondaryDiagonal<T>(IEnumerable<T[]> values)
{
    return values.Reverse().Select((x, i) => x[i]);
}

static void Main(string[] args)
{
    int[][] jaggedArr = new int[][]
    {
        new int[] { 11, 2, 4 },
        new int[] { 4, 5, 6 },
        new int[] { 10, 8, -12 }
    };

    var primarySum = PrimaryDiagonal(jaggedArr).Sum();
    var secondarySum = SecondaryDiagonal(jaggedArr).Sum();
}
//--------------------------------------------------------------------------------------------

// 3. Anonymous delegate----------------------------------------------------------------------
delegate int MyDelegate(int[] _scores, int _aScore);

static int[] climbingLeaderboard(int[] scores, int[] alice)
{
    int[] result = new int[alice.Count()];
    var distinctScores = scores.Distinct().ToArray();

    MyDelegate locateRanking = (scoresArr, aliceScore) => {
        var itr = Array.Find(scoresArr, el => el <= aliceScore);
        var idx = Array.FindIndex(scoresArr, score => score == itr);
        return idx == -1 ? distinctScores.Count() + 1 : idx + 1;
    };

    for (int i = 0; i < alice.Count(); i++)
    {
        result[i] = locateRanking(distinctScores, alice[i]);
    }
    return result;
}
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

// 1. Array Sum-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
