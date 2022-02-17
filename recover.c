#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //sprawdza czy uzytkownik podal jedna nazwe pliku
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // sprawdza, czy plik da sie otworzyc
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer [512];
    int image_count = 0;
    char title [8];
    FILE *jpeg = NULL;

    // odczytaj inptr i tymczasowo przechowuj dane w bufferze
    while (fread(buffer, 1, sizeof(buffer), inptr) == 512)
    {
        //jesli 4-bitowa sekwencja jest znaleziona
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && buffer[3] >> 4 == 0xe)
        {

            image_count++;

            //zamknij poprzedni plik jpg, jesli jakis jest
            if (image_count > 1)
            {
                fclose(jpeg);
            }

            sprintf(title, "%03d.jpg", image_count - 1);
            jpeg = fopen(title, "w");
        }
        //jesli zapisujemy, to z bufra do pliku img
        if (image_count > 0)
        {
            fwrite(&buffer, 512, 1, jpeg);
        }
    }
    // zamknij wszystkie pliki
    fclose(jpeg);
    fclose(inptr);

}
