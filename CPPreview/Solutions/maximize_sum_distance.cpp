/* Given array [-8, 4, 0, 5, -3, 6] find max sum of 2 elements including their distance
 * Here, 4 (A[1]) + 6 (A[5]) + 4 (distance) = 14
 */
 
  int sumP = Integer.MIN_VALUE;
  int sumQ = Integer.MIN_VALUE;
  for(int i = 0; i < A.length; i++){
      sumP = Math.max(A[i] - i, sumP);
      sumQ = Math.max(A[i] + i, sumQ);
  }
  return sumP + sumQ;
  
