// id_table.h : Creates table of ids used in the program to compile
#include <string.h>

#define MAX_ID_TABLE_SIZE 100

struct Id* id_table[MAX_ID_TABLE_SIZE];
int id_table_size = 0;

int add_id(char* name){
    int i;
    for (i = 0; i < id_table_size; i++) {
        if (strcmp(id_table[i]->name, name) == 0)
            return id_table[i]->id;
    }
    struct Id* item = (struct Id*)malloc(sizeof(struct Id));
    item->id = id_table_size;
    item->name = name;
    item->type = INTEGER;
    id_table[id_table_size] = item;
    return id_table_size++; 
}

struct Id* get_id(int id) {
    return id_table[id];
}

void set_id(int id, int val) {
    id_table[id]->val = val;
}

void print_ids() {
    int i;
    for(i = 0; i<id_table_size; i++) {
        printf("%s: \tid: %d\ttype: %d\tval: %d\n", id_table[i]->name, id_table[i]->id, id_table[i]->type, id_table[i]->val);
        printf("------------------------------\n");
    }
}