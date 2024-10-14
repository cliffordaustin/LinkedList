#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char* name;
    char* subject;
    unsigned int age;
    char grade[2];
    struct Student* next;
} Student;

typedef struct studentData {
    char* name;
    char* subject;
    char grade[2];
    unsigned int age;
} studentData;

void printList(Student* student) {
    if (student == NULL) {
        printf("Empty student data");
    }

    Student* tmp = student;

    while (tmp->next != NULL) {
        printf("(%s, %s, %s, %d)->", tmp->name, tmp->subject, tmp->grade, tmp->age);
        tmp = tmp->next;
    }

    printf("(%s, %s, %s, %d)", tmp->name, tmp->subject, tmp->grade, tmp->age);
}

void inserNodeToHead(Student** head, Student* newNode) {
    if (newNode == NULL) return;

    newNode->next = *head;
    *head = newNode;
}

Student* createNode(char* name, char* subject, char grade[2], const int age) {
    Student* student = malloc(sizeof(*student));
    student->name = name;
    student->subject = subject;
    student->age = age;
    strncpy(student->grade, grade, 2);
    student->next = NULL;

    return student;
}

Student* getNode(Student* head, const char* name) {
    Student* tmp = head;

    while (tmp->name != name) {
        tmp = tmp->next;
    }
    return tmp;
}

void insertNode(Student* nodeToInsertAt, Student* newNode) {
    if (newNode == NULL) return;

    newNode->next = nodeToInsertAt->next;
    nodeToInsertAt->next = newNode;
}

void deleteNode(Student** head, const char* name) {
    Student* tmp = *head;
    Student* prev = NULL;

    while (tmp->next != NULL && tmp->name != name) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (prev != NULL) {
        prev->next = tmp->next;
    } else {
        // This means the node to delete is the head node
        *head = tmp->next;
    }
}

// what we want is for each loop, we move the current
// node by one position.
void reverseList(Student** head) {
    Student* tmp = *head;
    Student* curr = NULL;
    Student* prev = NULL;

    while (tmp != NULL) {
        curr = tmp;
        tmp = tmp->next;
        curr->next = prev;
        prev = curr;
    }

    *head = prev;
}

void cleanLinkedList(Student* head) {
    Student* tmp = head;

    while (tmp->next != NULL) {
        Student* next = tmp->next->next;
        free(tmp->next);

        tmp->next = next;
    }
}

int main(void) {
    studentData data[10] = {
        {"Mark", "Science", "B", 11},
        {"Jeff", "English", "C+", 12},
        {"Sam", "History", "A", 10},
        {"Clifford", "Maths", "A+", 10},
        {"Alex", "Geography", "B+", 11},
        {"James", "Maths", "D", 13},
        {"Tom", "Science", "C", 12},
        {"Peter", "English", "B", 11},
        {"John", "History", "A", 10},
        {"Steve", "Geography", "C+", 12}
    };

    Student* head = NULL;

    const int studentDataLen = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < studentDataLen; i++) {
        Student* newNode = createNode(data[i].name, data[i].subject, data[i].grade, data[i].age);
        inserNodeToHead(&head, newNode);
    }

    Student* nodeToInsertAt = getNode(head, "Clifford");

    Student* newNode = createNode("Cassie", "Science", "A+", 7);

    insertNode(nodeToInsertAt, newNode);

    deleteNode(&head, "James");

    reverseList(&head);

    printList(head);

    cleanLinkedList(head);

    free(head);

    return 0;
}
