
int BinarySearch(Key K){
    int L, R, Midpoint;
    /* Initializations */
    L=0;
    R=n-1;
    /* While the interval L:R is non-empty, test key K against the middle key */
    while (L<=R){
        Midpoint=(L+R)/2;
        if (K==A[Midpoint]){
            return Midpoint;
        } else if (K > Midpoint) {
            L=Midpoint+1;
        } else {
            R=Midpoint-1;
        }
    }
    /* If the search interval became empty, key K was not found */
    return -1;
}