#pragma once
#include "precomp.h"

namespace QuickSort {
    // Helper function for partitioning the tanks
    int partition(std::vector<Tank*>& tanks, int low, int high)
    {
        const Tank* pivot = tanks[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (tanks[j]->compare_health(*pivot) <= 0)
            {
                i++;
                std::swap(tanks[i], tanks[j]);
            }
        }

        std::swap(tanks[i + 1], tanks[high]);
        return i + 1;
    }

    // QuickSort algorithm implementation
    void quickSort(std::vector<Tank*>& tanks, int low, int high)
    {
        if (low < high)
        {
            int pivot = partition(tanks, low, high);
            quickSort(tanks, low, pivot - 1);
            quickSort(tanks, pivot + 1, high);
        }
    }

    void sortTanks(std::vector<Tank>& original, std::vector<Tank*>& sorted_tanks, int begin, int end)
    {
        const int NUM_TANKS = end - begin;
        sorted_tanks.reserve(NUM_TANKS);

        for (int i = begin; i < end; i++)
        {
            sorted_tanks.emplace_back(&original[i]);
        }

        quickSort(sorted_tanks, 0, NUM_TANKS - 1);
    }

    void heapify(std::vector<Tank*>& tanks, int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // If left child is larger than root
        if (left < n && tanks[left]->compare_health(*tanks[largest]) > 0)
            largest = left;

        // If right child is larger than current largest
        if (right < n && tanks[right]->compare_health(*tanks[largest]) > 0)
            largest = right;

        // If largest is not root
        if (largest != i) {
            std::swap(tanks[i], tanks[largest]);

            // Recursively heapify the affected sub-tree
            heapify(tanks, n, largest);
        }
    }

    void heapSort(std::vector<Tank*>& tanks)
    {
        int n = tanks.size();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(tanks, n, i);

        // One by one extract an element from heap
        for (int i = n - 1; i >= 0; i--) {
            // Move current root to end
            std::swap(tanks[0], tanks[i]);

            // call max heapify on the reduced heap
            heapify(tanks, i, 0);
        }
    }

    void heapSortTanks(std::vector<Tank>& original, std::vector<Tank*>& sorted_tanks, int begin, int end)
    {
        const int NUM_TANKS = end - begin;
        sorted_tanks.reserve(NUM_TANKS);

        for (int i = begin; i < end; i++)
        {
            sorted_tanks.emplace_back(&original[i]);
        }

        heapSort(sorted_tanks);
    }
}