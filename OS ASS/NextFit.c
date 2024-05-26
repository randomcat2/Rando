#include <stdio.h>

void implementNextFit(int blockSize[], int blocks, int processSize[], int processes)
{
    // This will store the block id of the allocated block to a process
    int allocation[processes];
    int occupied[blocks];
    
    // initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for(int i = 0; i < processes; i++){
        allocation[i] = -1;
    }
    
    for(int i = 0; i < blocks; i++){
        occupied[i] = 0;
    }
 
    // Next Fit starts searching for available memory 
    // starting from the last allocated block's index
    int lastIndexAllocated = 0;
    for (int i=0; i < processes; i++)
    {
        // Start searching for available memory from the last allocated block
        int indexPlaced = -1;
        for(int j = lastIndexAllocated; j < blocks; j++)
        {
            // if not occupied and block size is large enough
            if(blockSize[j] >= processSize[i] && !occupied[j])
            {
                indexPlaced = j;
                break; // Found suitable block, break the loop
            }
        }
        
        // If no suitable block is found starting from lastIndexAllocated, start from the beginning
        if (indexPlaced == -1)
        {
            for(int j = 0; j < lastIndexAllocated; j++)
            {
                // if not occupied and block size is large enough
                if(blockSize[j] >= processSize[i] && !occupied[j])
                {
                    indexPlaced = j;
                    break; // Found suitable block, break the loop
                }
            }
        }
 
        // If we were successfully able to find block for the process
        if (indexPlaced != -1)
        {
            // allocate this block j to process p[i]
            allocation[i] = indexPlaced;
            
            // make the status of the block as occupied
            occupied[indexPlaced] = 1;
 
            // Reduce available memory for the block
            blockSize[indexPlaced] -= processSize[i];

            // Update the lastIndexAllocated to the index of the block where the process was allocated
            lastIndexAllocated = indexPlaced + 1;
        }
    }
 
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
 
// Driver code
int main()
{
    int blockSize[] = {100, 50, 30, 120, 35};
    int processSize[] = {40, 10, 30, 60};
    int blocks = sizeof(blockSize)/sizeof(blockSize[0]);
    int processes = sizeof(processSize)/sizeof(processSize[0]);
 
    implementNextFit(blockSize, blocks, processSize, processes);
 
    return 0;
}
