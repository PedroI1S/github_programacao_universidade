#include <stdio.h>

int maxSubArraySum(int nums[], int n) {
    if (n == 0) return 0;
    int i = 0, j = 0;
    int mat[n][n];

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            mat[i][j] = 0;

    for (i = 0; i < n; i++) {
        mat[i][i] = nums[i];
    }

    j=0;
    for(i = 0; i < n; i++){
        j++;
        mat[i][j] = mat[i][j-1] + mat[i+1][j];
    }

    j=1;
    int controle = 1;

    for(i = 0; (i + controle) < (n - 1); i++){
        j++;
        
        mat[i][j] = (mat[i+1][j] + mat[i][j-2] > mat[i+2][j] + mat[i][j-1]) ? mat[i+1][j] + mat[i][j-2] : mat[i+2][j] + mat[i][j-1];

        if(j == (n-1)){
            printf("entrou %d, %d \n", i, j);
            i = -1;
            controle++;
            j = controle;
        }
    }
    
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%8d ", mat[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    
    int max_sum = maxSubArraySum(nums, n);
    
    //printf(" %d\n", max_sum);
    
    return 0;
}
