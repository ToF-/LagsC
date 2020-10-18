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
void Suppression(struct Node **head_ref);
void deleteNode_withId(struct Node **head_ref, char *id);
void Liste(struct Node **head_ref);
void AjouterOrdre(struct Node **head_ref);
struct Node *selection(struct Node *node, ORDRE *order);
double CA(struct Node *node);
