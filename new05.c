#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double stack[100]; int top = -1;char pass[10];
struct Acc{
    double amt;
    char name[20];
    char password[20];
    struct Acc *next;
};
struct Acc *head, *ptr, *newAcc, *temp, *p, *q;

void action(double amount){
    if(top == 99){
        printf("stack overflow");
    } else {
        top = top + 1;
        stack[top] = amount;   
    }
}

void createAcc(){
    struct Acc *newAcc;
    newAcc = (struct Acc*)malloc(sizeof(struct Acc));
    //checking if space exists in heap
    if(newAcc == NULL){
        printf("memory space");
        exit(0);
    }

    //accepting data
    printf("\nenter your name : ");
    scanf("%s", &newAcc -> name);
    printf("\nenter password : ");
    scanf("%s", newAcc -> password);
    printf("\namount to be deposited : ");
    scanf("%lf", & newAcc -> amt);
    action(newAcc -> amt);
    newAcc -> next = NULL;

    //checking if node already exists or not
    if(head == NULL){
        ptr = head = newAcc;
    } else {
        ptr = head;
    while(ptr -> next != NULL){
        ptr = ptr -> next;
    }
    ptr -> next = newAcc;
    ptr = newAcc;
    }
}

//delete account
void accDelete(){
    printf("\nEnter password : ");
    scanf("%s", pass);
    
    if (head == NULL) {
        printf("No accounts exist\n");
        return;
    }

    // Special case: deleting the first node
    if (strcmp(head->password, pass) == 0) {
        struct Acc *temp = head;
        head = head->next;
        free(temp);
        printf("Account deleted successfully\n");
        return;
    }

    // Find the node before the one to delete
    p = head;
    q = head->next;
    while (q != NULL && strcmp(q->password, pass) != 0) {
        p = q;
        q = q->next;
    }

    if (q == NULL) {
        printf("Account not found\n");
        return;
    }

    // Remove the node from the list
    p->next = q->next;
    free(q);
    printf("Account deleted successfully\n");
    
}

void withdraw(struct Acc *temp) {
  double amount;
  printf("Enter the amount to withdraw: ");
  scanf("%lf", &amount);
  if (temp -> amt < amount) {
    printf("\nInsufficient balance\n");
  } else {
    temp -> amt = temp -> amt - amount;
    action(temp -> amt);
    printf("\nWithdrawal Successful. New balance: %.2f\n", temp -> amt);
  }
}

void deposit(struct Acc *temp) {
  double amount;
  printf("Enter the amount to deposit: ");
  scanf("%lf", &amount);
  temp -> amt  += amount;
  action(temp -> amt);
  printf("\nDeposition Successful. New balance: %.2f\n", temp ->amt);
}

void check_balance(struct Acc *temp) {
  printf("\nCurrent balance: %.2f\n", temp -> amt);
}

void displayStack(){
    int i;
    if(top == -1){
        printf("stack empty");
    } else {
        printf("Transaction List : \n");
        for(i = top; i >= 0; i--){
            printf("%f \n", stack[i]);
        }
    }
}

void main(){
    int ch, c; // ch -> main switch case; c -> facility switch case
    char pass[10];
    while(1){
    printf("\n1. Create new Account\t2. Delete Account\t3. Avail Facilities\t4. Exit");
    printf("\nEnter your choice : ");
    scanf("%d", &ch);
    switch(ch){
        case 1:
        createAcc();
        break;
        case 2:
        accDelete();
        break;
        case 3:
        printf("\nEnter Account Password\n");
        scanf("%s", pass);
        ptr = head;
        while(ptr != NULL){
            if(strcmp(pass, ptr -> password) == 0){
                while(1){
                printf("\n1. Withdraw\t2. Deposit\t3. Check Balance \t4. Display Transaction\t5. show Main");
                printf("\nEnter your choice : ");
                scanf("%d", &c);
                switch(c){
                    case 1:
                    withdraw(ptr);
                    break;
                    case 2:
                    deposit(ptr);
                    break;
                    case 3:
                    check_balance(ptr);
                    break;
                    case 4:
                    displayStack(ptr);
                    break;
                    case 5:
                    break;
                    default:
                    printf("Invalid Choice\n");
                }
                if(c == 5)
                    break;
                }
            }ptr = ptr -> next; 
        }
        break;
        case 4:
        exit(0);
        break;
        default:
        printf("Invalid choice");        
    }
    }
}
