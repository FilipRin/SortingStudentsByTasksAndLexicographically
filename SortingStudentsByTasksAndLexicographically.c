#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#define MAXx 30



typedef struct node
{
    int godina;
    int index;
    char ime[MAXx];
    int poeni;
    int brZadatka;
    char prezime[MAXx];
    struct node* next;
} Node;

char* readLine()
{
    char* old_word = NULL, * new_word, c=NULL;
    int i = 0;
    if (c == '\n')
    {
        return NULL;
    }
    printf("Insert like: indexNumber/yearNumber, name surrname, pointsNumber or if you inserted enough press enter for empty line to stop inserting\n");
    while ((c = getchar()) != '\n')
    {
        new_word = realloc(old_word, (i + 1) * sizeof(char));
        if (!new_word)
        {
            printf("Mem greska");
            break;
        }
        else
        {
            old_word = new_word;
        }
        old_word[i] = c;
        i++;
    }
    new_word = realloc(old_word, (i + 1) * sizeof(char));
    if (!new_word)
    {
        printf("Mem greska");
        i--;
    }
    else
        old_word = new_word;
    old_word[i] = '\0';
    c = '\0';
    return old_word;
}

Node* ReadLines(Node* head)
{
    char c, d, ** niz = NULL;
    char* line;
    int brrrr = 0;
    Node* last = NULL;
    while (1)
    {
        line = readLine();
        if (!strlen(line))
        {
            free(line);
            break;
        }
        niz = realloc(niz, (brrrr + 1) * sizeof(niz));
        niz[(brrrr)++] = line;
    }
    for (int b = brrrr - 1; b >= 0; b--)
    {
        Node* node = NULL;
        node = malloc(sizeof(Node));
        if (!node)
        {
            printf("Mem greska");
            break;
        }
        int i = 0;
        char pom[MAXx];
        c = niz[b][i];
        while (c != '/')
        {
            pom[i] = niz[b][i];
            i++;
            c = niz[b][i];
        }
        pom[i] = '\0';
        node->index = atoi(pom);
        int brpom = 0;
        int x = 0;
        i++;
        pom[brpom] = niz[b][i];
        i++;
        brpom++;
        pom[brpom] = niz[b][i];
        i++;
        brpom++;
        c = niz[b][i];
        pom[brpom] = niz[b][i];
        while (c != ',')
        {
            if (isdigit(c))
            {
                x = x * 10;
                x = x + c - 48;
            }
            i++;
            brpom++;
            c = niz[b][i];
            if (c != ',')
            {
                pom[brpom] = niz[b][i];
            }
        }
        pom[++brpom] = '\0';
        node->godina = atoi(pom);
        x = 0;
        i++;
        i++;
        brpom = 0;
        c = niz[b][i];
        while (c != ' ')
        {
            node->ime[brpom] = niz[b][i];
            brpom++;
            i++;
            c = niz[b][i];
        }
        node->ime[brpom] = '\0';
        brpom = 0;
        i++;
        c = niz[b][i];
        while (c != ',')
        {
            node->prezime[brpom] = niz[b][i];
            brpom++;
            i++;
            c = niz[b][i];
        }
        node->prezime[brpom] = '\0';
        brpom = 0;
        i++;
        i++;
        c = niz[b][i];
        while (c != '\0')
        {
            if (isdigit(c))
            {
                x = x * 10;
                x = x + c - 48;
            }
            i++;
            c = niz[b][i];
        }
        node->poeni = x;
        node->next = NULL;
        if (last == NULL)
            head = node;
        else
            last->next = node;
        last = node;
    }
    return head;
}

void printList(Node* head)
{
    printf("Printing all students with their info\n");
    for (Node* current = head; current != NULL; current = current->next)
    {
        if (current->index < 10)
        {
            printf("000%d", current->index);
        }
        else if (current->index < 100)
        {
            printf("00%d", current->index);
        }
        else if (current->index < 1000)
        {
            printf("0%d", current->index);
        }
        else printf("%d", current->index);
        printf("/%d, %s %s, %d\n", current->godina, current->ime, current->prezime, current->poeni);
    }
}

int Zadatak(Node* head, int modZadatak)
{
    int poslednjeDveCifre;
    for (Node* current = head; current != NULL; current = current->next)
    {
        poslednjeDveCifre = current->godina;
        while (poslednjeDveCifre > 1000)
        {
            poslednjeDveCifre = poslednjeDveCifre - 1000;
        }
        while (poslednjeDveCifre > 100)
        {
            poslednjeDveCifre = poslednjeDveCifre - 100;
        }
        current->brZadatka = (current->index + poslednjeDveCifre) % modZadatak;
    }
}

void SortPoZadatku(Node* head)
{
    for (Node* i = head; i != NULL; i = i->next)
    {
        for (Node* j = i->next; j != NULL; j = j->next)
        {
            if (i->brZadatka >= j->brZadatka)
            {
                int tmp = i->brZadatka;
                i->brZadatka = j->brZadatka;
                j->brZadatka = tmp;

                tmp = i->poeni;
                i->poeni = j->poeni;
                j->poeni = tmp;

                tmp = i->godina;
                i->godina = j->godina;
                j->godina = tmp;

                tmp = i->index;
                i->index = j->index;
                j->index = tmp;

                char temp[MAXx];
                strcpy(temp, i->ime);
                strcpy(i->ime, j->ime);
                strcpy(j->ime, temp);

                strcpy(temp, i->prezime);
                strcpy(i->prezime, j->prezime);
                strcpy(j->prezime, temp);
            }
        }
    }
}

void SortPoLeksikografskom(Node* head)
{
    for (Node* i = head; i != NULL; i = i->next)
    {
        for (Node* j = i->next; j != NULL; j = j->next)
        {
            if (i->brZadatka == j->brZadatka)
            {

                if ((strcmp(i->ime, j->ime)) > 0)
                {
                    int tmp = i->brZadatka;
                    i->brZadatka = j->brZadatka;
                    j->brZadatka = tmp;

                    tmp = i->poeni;
                    i->poeni = j->poeni;
                    j->poeni = tmp;

                    tmp = i->godina;
                    i->godina = j->godina;
                    j->godina = tmp;

                    tmp = i->index;
                    i->index = j->index;
                    j->index = tmp;

                    char temp[MAXx];
                    strcpy(temp, i->ime);
                    strcpy(i->ime, j->ime);
                    strcpy(j->ime, temp);

                    strcpy(temp, i->prezime);
                    strcpy(i->prezime, j->prezime);
                    strcpy(j->prezime, temp);
                }
                else if ((strcmp(i->ime, j->ime)) == 0)
                {
                    if ((strcmp(i->prezime, j->prezime)) > 0)
                    {
                        int tmp = i->brZadatka;
                        i->brZadatka = j->brZadatka;
                        j->brZadatka = tmp;

                        tmp = i->poeni;
                        i->poeni = j->poeni;
                        j->poeni = tmp;

                        tmp = i->godina;
                        i->godina = j->godina;
                        j->godina = tmp;

                        tmp = i->index;
                        i->index = j->index;
                        j->index = tmp;

                        char temp[MAXx];
                        strcpy(temp, i->ime);
                        strcpy(i->ime, j->ime);
                        strcpy(j->ime, temp);

                        strcpy(temp, i->prezime);
                        strcpy(i->prezime, j->prezime);
                        strcpy(j->prezime, temp);
                    }
                }
            }
        }
    }
}

void printListZaZadatak(Node* head)
{
    printf("Printing all students with their info sorted by tasks and lexicographically, with number of their assigned task\n");
    for (Node* current = head; current != NULL; current = current->next)
    {
        printf("%d, ", current->brZadatka);
        if (current->index < 10)
        {
            printf("000%d", current->index);
        }
        else if (current->index < 100)
        {
            printf("00%d", current->index);
        }
        else if (current->index < 1000)
        {
            printf("0%d", current->index);
        }
        else printf("%d", current->index);
        printf("/%d, %s %s, %d\n", current->godina, current->ime, current->prezime, current->poeni);
    }
}

void RacunajProsecnuVrednost(Node* head)
{
    int i = 0;
    float ProsecnaVrednost = 0;
    for (Node* current = head; current != NULL; current = current->next)
    {
        ProsecnaVrednost = current->poeni + ProsecnaVrednost;
        i++;
    }
    ProsecnaVrednost = ProsecnaVrednost / i;
    printf("Average number of points on all tasks is: %0.2f", ProsecnaVrednost);
}

void OslobodiMemoriju(Node* head)
{
    Node* current = head;
    while (current != NULL)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    Node* glava = NULL;
    int modZadatak;
    glava = ReadLines(glava);
    scanf("%d", &modZadatak);
    printList(glava);
    Zadatak(glava, modZadatak);
    SortPoZadatku(glava);
    SortPoLeksikografskom(glava);
    printListZaZadatak(glava);
    RacunajProsecnuVrednost(glava);
    OslobodiMemoriju(glava);
    //_getch();
    return 0;
}