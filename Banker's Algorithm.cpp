#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_multiple(char value[], int multiple, char end_line[])
{
    for (int i = 0; i < multiple; i++)
    {
        printf("%s", value);
    }
    printf("%s", end_line);
}

int main()
{
    int allocate_size, resource_size;

    printf("Enter allocate size: ");
    scanf("%d", &allocate_size);
    printf("Enter resource size: ");
    scanf("%d", &resource_size);

    int *available = (int *)malloc(resource_size * sizeof(int));
    int *work = (int *)malloc(resource_size * sizeof(int));
    int **allocate = (int **)malloc(allocate_size * sizeof(int *));
    int **max = (int **)malloc(allocate_size * sizeof(int *));
    int **need = (int **)malloc(allocate_size * sizeof(int *));
    int *finish = (int *)calloc(allocate_size, sizeof(int));
    int *safe_sequence = (int *)malloc(allocate_size * sizeof(int));

    for (int i = 0; i < allocate_size; i++)
    {
        allocate[i] = (int *)malloc(resource_size * sizeof(int));
        max[i] = (int *)malloc(resource_size * sizeof(int));
        need[i] = (int *)malloc(resource_size * sizeof(int));
    }

    print_multiple("=", 60, "\n");
    printf("Enter total units of each resource:\n");
    for (int i = 0; i < resource_size; i++)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    print_multiple("=", 60, "\n");
    for (int i = 0; i < allocate_size; i++)
    {
        printf("Enter allocation of process %d:\n", i + 1);
        for (int j = 0; j < resource_size; j++)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocate[i][j]);
        }
    }

    print_multiple("=", 60, "\n");
    for (int i = 0; i < allocate_size; i++)
    {
        printf("Enter max of process %d:\n", i + 1);
        for (int j = 0; j < resource_size; j++)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocate[i][j];
        }
    }

    for (int i = 0; i < resource_size; i++)
    {
        for (int j = 0; j < allocate_size; j++)
        {
            available[i] -= allocate[j][i];
        }
    }

    memcpy(work, available, resource_size * sizeof(int));
    int count = 0;
    print_multiple("=", 60, "\n");
    printf("Process  Alloc      Max        Need       Avail      State\n");
    printf("        A  B  C     A  B  C    A  B  C    A  B  C\n");

    while (count < allocate_size)
    {
        int found = 0;
        for (int i = 0; i < allocate_size; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < resource_size; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == resource_size)
                {
                    printf("P%d     ", i + 1);
                    for (j = 0; j < resource_size; j++)
                        printf("%d  ", allocate[i][j]);
                    printf("    ");
                    for (j = 0; j < resource_size; j++)
                        printf("%d  ", max[i][j]);
                    printf("    ");
                    for (j = 0; j < resource_size; j++)
                        printf("%d  ", need[i][j]);
                    printf("    ");
                    for (j = 0; j < resource_size; j++)
                        printf("%d  ", work[j]);
                    printf("    SAFE\n");

                    for (int k = 0; k < resource_size; k++)
                        work[k] += allocate[i][k];
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("System is in an UNSAFE state. Deadlock detected!\n");
            break;
        }
    }

    if (count == allocate_size)
    {
        print_multiple("=", 60, "\n");
        printf("System is in a SAFE state. Safe sequence: ");
        for (int i = 0; i < allocate_size; i++)
            printf("P%d ", safe_sequence[i] + 1);
        printf("\n");
        print_multiple("=", 60, "\n");
    }

    for (int i = 0; i < allocate_size; i++)
    {
        free(allocate[i]);
        free(max[i]);
        free(need[i]);
    }
    free(allocate);
    free(max);
    free(need);
    free(available);
    free(work);
    free(finish);
    free(safe_sequence);

    return 0;
}

