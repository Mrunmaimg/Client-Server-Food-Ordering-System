#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int sock;

void giveFeedback() {
    char feedback[1024];
    char client_name[1024];
    char name_msg[] = "Please enter your name: ";
    printf("%s", name_msg);
    scanf(" %[^\n]", client_name);  // R
    char msg[] = "Please give your feedback: ";
    printf("%s", msg);
    scanf(" %[^\n]", feedback);  // Read feedback including spaces
    send(sock, client_name, sizeof(client_name), 0);
    send(sock, feedback, sizeof(feedback), 0);
    

    printf("Thank you for your feedback!\n");
}

int main() {
    struct sockaddr_in serverAddr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    // Switch case for user options
    bool loop = true;
    while(1){
    int choice;
    printf("Customer Panel:\n");
    printf("1.Order Items\n");
    printf("2.Give Feedback\n");  // Added an option to order items
    printf("3.Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    send(sock, &choice, sizeof(choice), 0);

    switch (choice) {
        case 2:
            giveFeedback();
            break;
        case 1: {
            // Order items option
            printf("Requesting menu from the server...\n");
            char menu[1024];
            recv(sock, menu, sizeof(menu), 0);
            printf("Received menu from the server:\n%s\n", menu);

            // Request item selection and quantity
            int itemChoice, quantity;
            printf("Enter the item number you want to order (1-5) or 6 to exit: ");
            scanf("%d", &itemChoice);

            if (itemChoice >= 1 && itemChoice <= 5) {
                printf("Enter quantity: ");
                scanf("%d", &quantity);

                // Send item choice and quantity to the server
                send(sock, &itemChoice, sizeof(itemChoice), 0);
                send(sock, &quantity, sizeof(quantity), 0);

                // Receive and print the server's response
                char response[1024];
                recv(sock, response, sizeof(response), 0);
                printf("Server Response: %s\n", response);
            } else if (itemChoice == 6) {
                printf("Exiting the order menu.\n");
            } else {
                printf("Invalid item choice.\n");
            }
            break;
        }
        case 3:
            // Exit case
            char response[1024];
                recv(sock, response, sizeof(response), 0);
                printf("Server Response: %s\n", response);
            printf("Exiting the customer panel. Goodbye!\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
    }
    }

    close(sock);

    return 0;
}
//client  
