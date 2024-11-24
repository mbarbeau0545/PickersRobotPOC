#include <stdio.h>
#include "./LIBQueue.h"

#define BUFFER_SIZE 3

typedef struct 
{
    t_uint32 essai_3;
    t_uint8 essai_1;
    t_uint8 essai_2;
} t_sEssais;

int main() {
    t_sEssais tryMax_as[BUFFER_SIZE];
    for (t_uint8 LLI_u8 = 0 ; LLI_u8 < BUFFER_SIZE ; LLI_u8++)
    {
        tryMax_as[LLI_u8].essai_1 = 0;
        tryMax_as[LLI_u8].essai_2 = 0;
        tryMax_as[LLI_u8].essai_3 = 0;
    }
    t_sLIBQUEUE_QueueCore queue;

    t_sLIBQUEUE_QueueCfg queue_cfg = {
        .bufferHead_pv = tryMax_as,
        .bufferSize_u8 = BUFFER_SIZE,
        .elementSize_u8 = sizeof(t_sEssais),
        .enableOverwrite_b = False,
    };

    if (LIBQUEUE_Create(&queue,queue_cfg) != 0) {
        printf("Erreur d'initialisation\n");
        return -1;
    }

    t_sEssais try1 = {
        .essai_1 = 9,
        .essai_2 = 10,
        .essai_3 = 78900,
    };
    t_sEssais try2 = {
        .essai_1 = 5,
        .essai_2 = 6,
        .essai_3 = 98900,
    };
    t_sEssais try3 = {
        .essai_1 = 7,
        .essai_2 = 8,
        .essai_3 = 632900,
    };
    if (LIBQUEUE_WriteElement(&queue, &try1) == 0) {
        printf("Valeur ajoutee 1");
    }
    if (LIBQUEUE_WriteElement(&queue, &try2) == 0) {
        printf("Valeur ajoutee 2");
    }
    if (LIBQUEUE_WriteElement(&queue, &try3) == 0) {
        printf("Valeur ajoutee 2");
    }
    if (LIBQUEUE_WriteElement(&queue, &try1) == 0) {
        printf("Valeur ajoutee 2");
    }

    t_sEssais TryRecup1;
    t_sEssais TryRecup2;

    LIBQUEUE_ReadElement(&queue, &TryRecup1);

    if (LIBQUEUE_WriteElement(&queue, &try1) == 0) {
        printf("Valeur ajoutee 1");
    }
    LIBQUEUE_ReadElement(&queue, &TryRecup2);

    printf("Get from queue %d, %d, %d\n", TryRecup1.essai_1, TryRecup1.essai_2, (int)TryRecup1.essai_3 );
    printf("Get from queue %d, %d, %d\n", TryRecup2.essai_1, TryRecup2.essai_2, (int)TryRecup2.essai_3 );

    return 0;
}
