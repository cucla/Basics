// www.hackerearth.com
// Find if the graph is a tree or not

/*
 * Fact one: graph is a tree on n vertices, it has exactly n−1 edges
 * Fact two: [the degree or valency of a vertex is the number of edges that connect to it],
 * sum of all degrees is twice number of edges
 
SAMPLE INPUT:
3   (vertices)
1 2 1     (degree of each vertice)

 */
 
 #include <iostream>
 
int main()
{
    int v, a;
    std::cin >> v;
    
    int sum = 0;
    for (int i = 0; i < v; i++) {
        std::cin >> a;
        sum += a;
    }
    if ((v - 1) * 2 == sum)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
        
    return 0;
}
