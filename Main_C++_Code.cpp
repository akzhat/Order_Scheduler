// Name : Akshat Sharma
// Roll No. : 19EC10002
// Assignment No. 04

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


//utility functions to swap, merge sort, find min and max
void swap(int *a1, int *a2)
{
    int *temp = a1;
    a1 = a2;
    a2 = temp;
}
void merge(int *arr1, int *arr, int l, int m, int r)
{
    int i = l, j = m + 1;

    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2], L1[n1], R1[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
        L1[i] = arr1[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
        R1[j] = arr1[m + 1 + j];
    }
    i = 0, j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            arr[k] = L[i];
            arr1[k] = L1[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = R[j];
            arr1[k] = R1[j];
            j++;
            k++;
        }
    }

    while (i < n1)
    {
        arr[k] = L[i];
        arr1[k] = L1[i];
        k++;
        i++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        arr1[k] = R1[j];
        j++;
        k++;
    }
}
void merge_sort(int *arr1, int *arr, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        merge_sort(arr1, arr, l, m);
        merge_sort(arr1, arr, m + 1, r);
        merge(arr1, arr, l, m, r);
    }
}
int min_(int **arr, int k)
{
    int min, min_val = 100000000;
    for (int i = 0; i < k; i++)
    {
        if (min_val > arr[i][0])
        {
            min = i;
            min_val = arr[i][0];
        }
    }
    return min;
}
int max_(int **arr, int k)
{
    int max, max_val = 0;
    for (int i = 0; i < k; i++)
    {
        if (max_val < arr[i][0])
        {
            max = i;
            max_val = arr[i][0];
        }
    }
    return max_val;
}



//Function to calculate waiting time
void waiting(int *A, int **arr, int k)
{
    int wait = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 3; j < arr[i][1] + 2; j++)
        {
            int w = 0;
            for (int r = 2; r < j; r++)
            {
                w += A[arr[i][r]];
            }
            wait += w;
        }
    }
    cout << "Waiting time is:  " << wait << endl;
}

//Function to print schedule
void print_schedule(int *A, int **arr, int k)
{
    cout << "Order Schedule (waiting time in parenthesis)" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << "Counter " << i + 1 << ":   ";
        for (int j = 0; j < arr[i][1]; j++)
        {
            cout << arr[i][j + 2] + 1 << "(" << A[arr[i][j + 2]] << ")   ";
        }
        cout << endl;
    }
}

//Function to print scedule for PART B and C
void print_schedule_b_c(int *A1, int *A, int **arr, int k)
{
    cout << "Order Schedule (waiting time in parenthesis)" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << "Counter " << i + 1 << ":   ";
        for (int j = 0; j < arr[i][1]; j++)
        {
            cout << A1[arr[i][j + 2]] + 1 << "(" << A[arr[i][j + 2]] << ")   ";
        }
        cout << endl;
    }
}

int schedule_orders_a(int *A, int n, int k)
{
    //create 2D array of k rows and max n+2 columns, wait time, no. of orders and n max orders for  counter
    int **arr = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++)
        arr[i] = (int *)malloc((n + 2) * sizeof(int));

    //initializing the array
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + 2; j++)
        {
            arr[i][j] = 0;
        }
    }

    //adding orders
    for (int i = 0; i < n; i++)
    {
        int min = min_(arr, k);
        arr[min][0] += A[i];
        arr[min][arr[min][1] + 2] = i;
        arr[min][1]++;
    }
    print_schedule(A, arr, k);
    int max = max_(arr, k);
    cout << "Cafe closes at:  " << max << endl;
    waiting(A, arr, k);
    return max;
}

int schedule_orders_b(int *A1, int *A, int n, int k)
{
    for (int i = 0; i < n; i++)
    {
        A1[i] = i;
    }

    merge_sort(A1, A, 0, n - 1);

    //create 2D array of k rows and max n+2 columns, wait time, no. of orders and n max orders for  counter
    int **arr = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++)
        arr[i] = (int *)malloc((n + 2) * sizeof(int));

    //initializing the array
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + 2; j++)
        {
            arr[i][j] = 0;
        }
    }

    //adding orders
    for (int i = 0; i < n; i++)
    {
        int min = min_(arr, k);
        arr[min][0] += A[i];
        arr[min][arr[min][1] + 2] = i;
        arr[min][1]++;
    }
    print_schedule_b_c(A1, A, arr, k);
    int max = max_(arr, k);
    cout << "Cafe closes at:  " << max << endl;
    waiting(A, arr, k);
    return max;
}

int schedule_orders_c(int *A1, int *A, int n, int k)
{
    //create 2D array of k rows and max n+2 columns, wait time, no. of orders and n max orders for  counter
    int **arr = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++)
        arr[i] = (int *)malloc((n + 2) * sizeof(int));

    //initializing the array
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + 2; j++)
        {
            arr[i][j] = 0;
        }
    }

    //adding orders
    for (int i = 0; i < n; i++)
    {
        int min = min_(arr, k);
        arr[min][0] += A[i];
        arr[min][arr[min][1] + 2] = i;
        arr[min][1]++;
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 2; j < (arr[i][1]) / 2 + 2; j++)
        {
            swap(arr[i][j], arr[i][arr[i][1] + 3 - j]);
        }
    }
    print_schedule_b_c(A1, A, arr, k);
    int max = max_(arr, k);
    cout << "Cafe closes at:  " << max << endl;
    waiting(A, arr, k);
    return max;
}


// main driver function
int main()
{
    //Asking for apt inputs
    int n, k;
    cout << "Enter n:";
    cin >> n;
    cout << "Enter k:";
    cin >> k;

    int *A = (int *)malloc(n * sizeof(int));
    cout << "Enter order processing time" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    //Array A contains the waiting times for the orders
    //A1 is an array to keep track of order numbers
    int A1[n];

    //printing necessary output by callin gnecessary functions
    cout << endl
         << "Part A" << endl;
    int close_a = schedule_orders_a(A, n, k);
    cout << endl
         << "Part B" << endl;
    int close_b = schedule_orders_b(A1, A, n, k);
    cout << endl
         << "Part C" << endl;
    int close_c = schedule_orders_c(A1, A, n, k);
}