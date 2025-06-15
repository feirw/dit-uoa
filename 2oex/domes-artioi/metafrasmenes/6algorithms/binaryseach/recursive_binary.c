int BinarySearch (Key K, int L, int R){
/* To find the position of the search key K in the subarray
A[L:R]. Note: To search for K in A[0:n-1], the initial call
is BinarySearch(K, 0, n-1) */
    int Midpoint;
    Midpoint=(L+R)/2;
    if (L>R){
        return -1;
    } else if (K==A[Midpoint]){
        return Midpoint;
    } else if (K > A[Midpoint]){
        return BinarySearch(K, Midpoint+1, R);
    } else {
    return BinarySearch(K, L, Midpoint-1);
    }
}