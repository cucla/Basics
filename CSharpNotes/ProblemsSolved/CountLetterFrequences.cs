public class Histogram
    {
        public static int[] CountFrequences(string inputStr = null)
        {
            int[] letterFrequences = new int[26];
            const int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7, I = 8,
                J = 9, K = 10, L = 11, M = 12, N = 13, O = 14, P = 15, Q = 16, R = 17,
                S = 18, T = 19, U = 20, V = 21, W = 22, X = 23, Y = 24, Z = 25;

            if(inputStr != null)
            {
                for(int i = 0; i < inputStr.Length; i++)
                {
                    switch(inputStr[i])
                    {
                        case 'A':
                            ++letterFrequences[A];
                            break;
                        case 'B':
                            ++letterFrequences[B];
                            break;
                        case 'C':
                            ++letterFrequences[C];
                            break;
                        case 'D':
                            ++letterFrequences[D];
                            break;
                        case 'E':
                            ++letterFrequences[E];
                            break;
                        case 'F':
                            ++letterFrequences[F];
                            break;
                        case 'G':
                            ++letterFrequences[G];
                            break;
                        case 'H':
                            ++letterFrequences[H];
                            break;
                        case 'I':
                            ++letterFrequences[I];
                            break;
                        case 'J':
                            ++letterFrequences[J];
                            break;
                        case 'K':
                            ++letterFrequences[K];
                            break;
                        case 'L':
                            ++letterFrequences[L];
                            break;
                        case 'M':
                            ++letterFrequences[M];
                            break;
                        case 'N':
                            ++letterFrequences[N];
                            break;
                        case 'O':
                            ++letterFrequences[O];
                            break;
                        case 'P':
                            ++letterFrequences[P];
                            break;
                        case 'Q':
                            ++letterFrequences[Q];
                            break;
                        case 'R':
                            ++letterFrequences[R];
                            break;
                        case 'S':
                            ++letterFrequences[S];
                            break;
                        case 'T':
                            ++letterFrequences[T];
                            break;
                        case 'U':
                            ++letterFrequences[U];
                            break;
                        case 'V':
                            ++letterFrequences[V];
                            break;
                        case 'W':
                            ++letterFrequences[W];
                            break;
                        case 'X':
                            ++letterFrequences[X];
                            break;
                        case 'Y':
                            ++letterFrequences[Y];
                            break;
                        case 'Z':
                            ++letterFrequences[Z];
                            break;
                        default: break;
                    }
                }
            }
            return letterFrequences;
        } 
        
        public static void PrettyPrint(int[] letterFrequences)
        {
            for(int i = 0; i < letterFrequences.Length; ++i)
            {
                Console.Write((char)(i + 65) + ": ");  // transform 0 -> 'A'
                for (int j = 0; j < letterFrequences[i]; ++i)
                    Console.Write("*");
                Console.WriteLine();
            }
        }     
    }
    
    static void Main(string[] args)
    {
        Histogram.PrettyPrint(Histogram.CountFrequences("LITERAL IN UPPER CASE"));
    }
