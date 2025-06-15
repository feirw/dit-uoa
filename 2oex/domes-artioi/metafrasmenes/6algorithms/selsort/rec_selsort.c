/* FindMin is an auxiliary function used by the Selection sort below */
int FindMin(InputArray A, int n){
    int i,j=n;
    for (i=0; i<n; ++i){
        if (A[i]<A[j]){
            j=i;
        }
        return j;
    } 
}
    void SelectionSort(InputArray A, int n){
        int MinPosition, temp;
        if (n>0){
            MinPosition=FindMin(A,n);
            temp=A[n]; A[n]=A[MinPosition]; A[MinPosition]=temp;
            SelectionSort(A, n-1)
        }
}

