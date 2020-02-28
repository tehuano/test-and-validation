#include <stdio.h>
#include <malloc.h>

#define MAX_INT_VALUE 10000000

/*
denom: array having the coin denominations. Should have atleast 1 element
num_denom: number of denominations
final_amount: amount for which change has to be obtained
Return value: Minimum number of coins needed to represent final_amount
*/

int find_min_coins(int denom[], int num_denom, int final_amount);

// Driver program to test above function 
int main() {
    int i, j; 
    int arr[] = {1, 2, 3}; 
    int final_amount = 15;

    int m = sizeof(arr)/sizeof(arr[0]);
    find_min_coins(arr, m, final_amount);
    
    getchar(); 
    return 0; 
}
 
int find_min_coins(int denom[], int num_denom, int final_amount) {
    /*Array for storing the minimum number of coins for an amount*/
    int *min_num_coins = (int*) malloc( (final_amount+1) * sizeof(int));
     
    /*Array for storing the coin denomination chosen for an amount*/
    int *chosen_denom = (int*) malloc( (final_amount+1) * sizeof(int));
    int i, cur_amt, smaller_amt, result;
    int ex[] = {100,100,2};
 
    min_num_coins[0] = 0;
    for (cur_amt = 1; cur_amt <= final_amount; cur_amt++) {
        min_num_coins[cur_amt] = MAX_INT_VALUE;
        for (i = 0; i < num_denom; ++i) {
            if (ex[i] > 0 && (denom[i] <= cur_amt)) {
         
                smaller_amt = cur_amt - denom[i];
 
                if ((1 + min_num_coins[smaller_amt]) < min_num_coins[cur_amt]) {
                    min_num_coins[cur_amt] = 1 + min_num_coins[smaller_amt];
                    chosen_denom[cur_amt] = denom[i];
                    ex[i]--;
                }
            }
        }
    }
     
    result = min_num_coins[final_amount];
    printf("Minimum number of coins = %d\n", result);
 
    /*print the chosen denominations to get the final amount*/
    cur_amt = final_amount;
    int counter = 0;
    while (cur_amt > 0 && counter < (final_amount + 1)) {
        printf("%d ", chosen_denom[cur_amt]);
        cur_amt = cur_amt - chosen_denom[cur_amt];
        counter++;
    }
    printf(" = %d\n", final_amount);
    free(min_num_coins);
    free(chosen_denom);
    return result;
}
