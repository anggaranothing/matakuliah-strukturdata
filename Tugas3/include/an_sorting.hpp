#pragma once

#ifndef AN_SORTING_H
#define AN_SORTING_H

#include <string>

using std::string;
using std::swap;

enum sorttype_e
{
    SORT_TYPE_BUBBLE = 0,
    SORT_TYPE_SELECTION,
    SORT_TYPE_INSERTION
};

const string sorttype_name[] =
{
    "Bubble Sort",
    "Selection Sort",
    "Insertion Sort"
};

/*
* Bubble sorting.
* Implementasi berdasarkan pseudocode pada link sebagai berikut:
* https://en.wikipedia.org/wiki/Bubble_sort#Pseudocode_implementation
*/
template <typename T>
static void bubbleSort( T list[], int length, bool ascending = true )
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 1; i <= length-1; ++i)
        {
            /* if this pair is out of order */
            bool isSwappable = ( ascending ? list[i-1] > list[i] : list[i-1] < list[i] );
            if( isSwappable )
            {
                /* swap them and remember something changed */
                swap(list[i-1], list[i]);
                swapped = true;
            }
        }
    }
    while( swapped );
}

/*
* Selection sorting.
* Implementasi berdasarkan pseudocode pada link sebagai berikut:
* https://en.wikipedia.org/wiki/Selection_sort#Implementation
*/
template <typename T>
static void selectionSort( T list[], int length, bool ascending = true )
{
    /* advance the position through the entire array */
    /*   (could do j < n-1 because single element is also min element) */
    for (int j = 0; j < length-1; j++)
    {
        /* find the min element in the unsorted a[j .. n-1] */

        /* assume the min is the first element */
        int iMin = j;
        /* test against elements after j to find the smallest */
        for (int i = j+1; i < length; i++)
        {
            /* if this element is less, then it is the new minimum */
            bool isSmallest = ( ascending ? list[i] < list[iMin] : list[i] > list[iMin] );
            if (isSmallest)
            {
                /* found new minimum; remember its index */
                iMin = i;
            }
        }

        if (iMin != j) 
        {
            swap( list[j], list[iMin] );
        }
    }
}

/*
* Insertion sorting.
* Implementasi berdasarkan pseudocode pada link sebagai berikut:
* https://en.wikipedia.org/wiki/Insertion_sort#Algorithm
*/
template <typename T>
static void insertionSort( T list[], int length, bool ascending = true )
{
    int i = 1;
    while( i < length )
    {
        T temp = list[i];

        int j = i - 1;

        bool isSwappable = ( ascending ? list[j] > temp : list[j] < temp );
        while( j >= 0 && isSwappable )
        {
            list[j+1] = list[j];
            j = j - 1;

            // refresh lagi.
            isSwappable = ( ascending ? list[j] > temp : list[j] < temp );
        }

        list[j+1] = temp;
        i++;
    }
}

#endif

