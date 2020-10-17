struct Node {
    ORDRE *ordre;
    struct Node* next;
};
void printOrdres(struct Node* n);
void writeOrdres(struct Node **head_ref, char *fileName);
void getFichierOrder(struct Node **head_ref, char *fileName);
void append(struct Node** head_ref, ORDRE* new_data);
void freeOrders(struct Node **head_ref);
void deleteList(struct Node **head_ref);
