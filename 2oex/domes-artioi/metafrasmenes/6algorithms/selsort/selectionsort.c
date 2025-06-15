
void SelectionSort(InputArray A) {
    int MinPosition, temp, i, j;
    for (i=n-1; i>0; --i){
        MinPosition=i;
        for (j=0; j<i; ++i){
            if (A[j] < A[MinPosition]){
                MinPosition=j;
            }
        }
        temp=A[i];
        A[i]=A[MinPosition];
        A[MinPosition]=temp;
    }
}