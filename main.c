#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Define stack operations
void sa(int *stack, int size);
void pb(int **stack_a, int *size_a, int **stack_b, int *size_b);
void pa(int **stack_a, int *size_a, int **stack_b, int *size_b);
void ra(int *stack, int size);
void rra(int *stack, int size);
void rb(int *stack, int size);
void rrb(int *stack, int size);

// Utility functions
int *find_lis(int *arr, int size, int *lis_size);
void push_non_lis_to_b(int **stack_a, int *size_a, int **stack_b, int *size_b, int *lis, int lis_size);
void sort_and_push_back(int **stack_a, int *size_a, int **stack_b, int *size_b);
void final_rotate(int *stack_a, int size);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    int size_a = argc - 1;
    int *stack_a = malloc(size_a * sizeof(int));
    int *stack_b = NULL;
    int size_b = 0;

    // Initialize stack_a with input
    for (int i = 0; i < size_a; i++) {
        stack_a[i] = atoi(argv[i + 1]);
    }

    // Step 1: Find LIS
    int lis_size;
    int *lis = find_lis(stack_a, size_a, &lis_size);

    // Step 2: Push non-LIS elements to stack_b
    push_non_lis_to_b(&stack_a, &size_a, &stack_b, &size_b, lis, lis_size);
    free(lis);

    // Step 3: Sort stack_b and push back to stack_a
    sort_and_push_back(&stack_a, &size_a, &stack_b, &size_b);

    // Step 4: Final rotation of stack_a
    final_rotate(stack_a, size_a);

    // Output the sorted stack_a
    for (int i = 0; i < size_a; i++) {
        printf("%d ", stack_a[i]);
    }
    printf("\n");

    // Clean up
    free(stack_a);
    free(stack_b);
    return 0;
}

// Find LIS using dynamic programming
int *find_lis(int *arr, int size, int *lis_size) {
    int *dp = malloc(size * sizeof(int));
    int *prev = malloc(size * sizeof(int));
    int *lis = NULL;
    int max_len = 0, max_index = -1;

    for (int i = 0; i < size; i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_index = i;
        }
    }

    *lis_size = max_len;
    lis = malloc(max_len * sizeof(int));
    for (int i = max_len - 1; i >= 0; i--) {
        lis[i] = arr[max_index];
        max_index = prev[max_index];
    }

    free(dp);
    free(prev);
    return lis;
}

// Push non-LIS elements to stack_b
void push_non_lis_to_b(int **stack_a, int *size_a, int **stack_b, int *size_b, int *lis, int lis_size) {
    for (int i = 0; i < *size_a;) {
        int is_in_lis = 0;
        for (int j = 0; j < lis_size; j++) {
            if ((*stack_a)[0] == lis[j]) {
                is_in_lis = 1;
                break;
            }
        }
        if (!is_in_lis) {
            pb(stack_a, size_a, stack_b, size_b);
        } else {
            ra(*stack_a, *size_a);
            i++;
        }
    }
}

// Sort stack_b and push elements back to stack_a
void sort_and_push_back(int **stack_a, int *size_a, int **stack_b, int *size_b) {
    while (*size_b > 0) {
        int max_index = 0;
        for (int i = 1; i < *size_b; i++) {
            if ((*stack_b)[i] > (*stack_b)[max_index]) {
                max_index = i;
            }
        }

        // Rotate stack_b to bring max_index to top
        if (max_index < *size_b / 2) {
            while (max_index-- > 0) {
                rb(*stack_b, *size_b);
            }
        } else {
            while (max_index++ < *size_b) {
                rrb(*stack_b, *size_b);
            }
        }
        pa(stack_a, size_a, stack_b, size_b);
    }
}

// Final rotation to place the smallest element at the top
void final_rotate(int *stack_a, int size) {
    int min_index = 0;
    for (int i = 1; i < size; i++) {
        if (stack_a[i] < stack_a[min_index]) {
            min_index = i;
        }
    }

    if (min_index < size / 2) {
        while (min_index-- > 0) {
            ra(stack_a, size);
        }
    } else {
        while (min_index++ < size) {
            rra(stack_a, size);
        }
    }
}

// Stack operations
void sa(int *stack, int size) {
    if (size < 2) return;
    int tmp = stack[0];
    stack[0] = stack[1];
    stack[1] = tmp;
}

void pb(int **stack_a, int *size_a, int **stack_b, int *size_b) {
    if (*size_a == 0) return;
    *stack_b = realloc(*stack_b, (*size_b + 1) * sizeof(int));
    memmove(*stack_b + 1, *stack_b, *size_b * sizeof(int));
    (*stack_b)[0] = (*stack_a)[0];
    memmove(*stack_a, *stack_a + 1, (*size_a - 1) * sizeof(int));
    (*size_a)--;
    (*size_b)++;
}

void pa(int **stack_a, int *size_a, int **stack_b, int *size_b) {
    if (*size_b == 0) return;
    *stack_a = realloc(*stack_a, (*size_a + 1) * sizeof(int));
    memmove(*stack_a + 1, *stack_a, *size_a * sizeof(int));
    (*stack_a)[0] = (*stack_b)[0];
    memmove(*stack_b, *stack_b + 1, (*size_b - 1) * sizeof(int));
    (*size_b)--;
    (*size_a)++;
}

void ra(int *stack, int size) {
    if (size < 2) return;
    int tmp = stack[0];
    memmove(stack, stack + 1, (size - 1) * sizeof(int));
    stack[size - 1] = tmp;
}

void rra(int *stack, int size) {
    if (size < 2) return;
    int tmp = stack[size - 1];
    memmove(stack + 1, stack, (size - 1) * sizeof(int));
    stack[0] = tmp;
}

void rb(int *stack, int size) { ra(stack, size); }
void rrb(int *stack, int size) { rra(stack, size); }
