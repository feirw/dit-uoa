void MoveTowers(int n, int start, int finish, int spare){
    if (n==1){
        printf("Move a disk from peg %ld to peg %ld\n", start,finish);
    } else {
    MoveTowers(n-1, start, spare, finish);
    printf("Move a disk from peg %ld to peg %ld\n", start,finish);
    MoveTowers(n-1, spare, finish, start);
    }
}