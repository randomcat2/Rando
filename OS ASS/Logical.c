#include <stdio.h>

// Define structures for segments and pages
struct Segment {
    int base;
    int limit;
};

struct Page {
    int frame;
    // Add more fields if needed
};

// Define functions for translation
int translateSegmentation(int logicalAddress, struct Segment segments[], int numSegments) {
    for (int i = 0; i < numSegments; i++) {
        if (logicalAddress >= segments[i].base && logicalAddress < segments[i].base + segments[i].limit) {
            // Calculate physical address using segment base
            return segments[i].base + (logicalAddress - segments[i].base);
        }
    }
    return -1; // Segment not found
}

int translatePaging(int logicalAddress, struct Page pageTable[], int numPages, int pageSize) {
    // Divide logical address into page number and offset
    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= 0 && pageNumber < numPages) {
        // Look up page number in page table to get frame number
        int frameNumber = pageTable[pageNumber].frame;
        // Calculate physical address using frame number and offset
        return frameNumber * pageSize + offset;
    } else {
        return -1; // Page not found
    }
}

int main() {
    // Initialize segments and page table
    struct Segment segments[] = {{0, 1000}, {2000, 500}, {4000, 800}};
    struct Page pageTable[] = {{2}, {0}, {1}}; // Page table mapping page number to frame number
    int numSegments = sizeof(segments) / sizeof(segments[0]);
    int numPages = sizeof(pageTable) / sizeof(pageTable[0]);
    int pageSize = 200; // Size of each page

    // Accept user input for logical address
    int logicalAddress;
    printf("Enter logical address: ");
    scanf("%d", &logicalAddress);

    // Translate logical address using segmentation
    int physicalAddressSegmentation = translateSegmentation(logicalAddress, segments, numSegments);
    if (physicalAddressSegmentation != -1) {
        // If needed, translate resulting physical address using paging
        int physicalAddress;
        physicalAddress = translatePaging(physicalAddressSegmentation, pageTable, numPages, pageSize);

        // Display the physical address
        if (physicalAddress != -1) {
            printf("Physical address: %d\n", physicalAddress);
        } else {
            printf("Page not found.\n");
        }
    } else {
        printf("Segment not found.\n");
    }

    return 0;
}
