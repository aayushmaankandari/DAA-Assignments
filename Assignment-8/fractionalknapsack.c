#include <stdio.h>
#include <stdlib.h>

// Structure for items
typedef struct {
    double value;
    double weight;
    double rate;   // deterioration rate
    double ratio;  // effective value/weight
} Item;

// Comparator for sorting
int cmp(const void *a, const void *b) {
    Item *i1 = (Item *)a;
    Item *i2 = (Item *)b;
    return (i2->ratio > i1->ratio) ? 1 : -1;
}

double fractionalKnapsack(Item items[], int n, double capacity, double time) {
    // Update effective value based on deterioration
    for (int i = 0; i < n; i++) {
        double effective_value = items[i].value - items[i].rate * time;
        if (effective_value < 0) effective_value = 0; // can't go negative
        items[i].ratio = effective_value / items[i].weight;
    }

    // Sort items by ratio
    qsort(items, n, sizeof(Item), cmp);

    double totalValue = 0.0;
    double remaining = capacity;

    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].weight <= remaining) {
            totalValue += items[i].ratio * items[i].weight;
            remaining -= items[i].weight;
        } else {
            totalValue += items[i].ratio * remaining;
            remaining = 0;
        }
    }

    return totalValue;
}

int main() {
    int n = 3;
    double capacity = 50;
    double time = 5; // deterioration applied at time=5

    Item items[] = {
        {100, 20, 2, 0}, // value, weight, rate
        {60, 10, 1, 0},
        {120, 30, 3, 0}
    };

    double maxValue = fractionalKnapsack(items, n, capacity, time);
    printf("Maximum value with deterioration: %.2f\n", maxValue);

    return 0;
}
