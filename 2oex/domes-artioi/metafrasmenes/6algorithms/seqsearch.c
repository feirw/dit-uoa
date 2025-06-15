#define n 100
typedef int Key;
typedef Key SearchArray[n];

int SequentialSearch(Key K, SearchArray A){
    int i;
    for (i=0; i<n; ++i){
        if (K==A[i]){
            return i;
        } 
    }
    return(-1);
}