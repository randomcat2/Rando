#include <string.h>
    
    void printIPClassAndType(char ipAddress[]) {
        char firstOctet[4];
        int i = 0;
        while (ipAddress[i] != '.' && ipAddress[i] != '\0') {
            firstOctet[i] = ipAddress[i];
            i++;
        }
        firstOctet[i] = '\0';
    
        int firstOctetInt = atoi(firstOctet);
    
        char ipClass;
        if (firstOctetInt >= 1 && firstOctetInt <= 126)
            ipClass = 'A';
        else if (firstOctetInt >= 128 && firstOctetInt <= 191)
            ipClass = 'B';
        else if (firstOctetInt >= 192 && firstOctetInt <= 223)
            ipClass = 'C';
        else if (firstOctetInt >= 224 && firstOctetInt <= 239)
            ipClass = 'D';
        else if (firstOctetInt >= 240 && firstOctetInt <= 255)
            ipClass = 'E';
        else
            ipClass = 'U';
    
        printf("Class %c in binary: ", ipClass);
        for (int j = 7; j >= 0; j--) {
            printf("%d", (ipClass >> j) & 1);
        }
        printf("\n");
        
        char *token = strtok(ipAddress, ".");
        int secondOctetInt = atoi(strtok(NULL, "."));
        if (firstOctetInt == 10 || (firstOctetInt == 172 && secondOctetInt >= 16 && secondOctetInt <= 31) ||
            (firstOctetInt == 192 && secondOctetInt == 168)) {
            printf("Type: Private\n");
        } else {
            printf("Type: Public\n");
        }
    }
    
    int main() {
        char ipAddress[16];
        printf("Enter the IP address: ");
        scanf("%s", ipAddress);
        printIPClassAndType(ipAddress);
        return 0;
    }