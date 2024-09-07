#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
double totalBill = 0.0;

int main() {
    int serverSock, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char feedback[1024];
    char client_name[1024];
    char menu[] = "Menu:\n1. Momos - $10.00\n2. Mojito - $15.00\n3. Pizza - $20.00\n4. Biriyani - $30.00\n5. Chicken Tandoori - $25.00\n6. Exit";
    char items_from_menu[50][50]={"Momos","Mojito","Pizza","Biriyani","Chicken_Tandoori"};
    double itemPrices[] = {10.00, 15.00, 20.00, 30.00, 25.00};

    if ((serverSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSock, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    addrSize = sizeof(newAddr);
    newSocket = accept(serverSock, (struct sockaddr *)&newAddr, &addrSize);  // Accept connection

    // Receive choice from client
    int Momos=0,Mojito=0,Pizza=0,Biriyani=0,Chicken_Tandoori=0;
    float One_day_total_bill=0.0;
    while(1){
    int choice;
    recv(newSocket, &choice, sizeof(choice), 0);

    switch (choice) {
        case 2: {
            // Feedback case
            recv(newSocket, client_name, sizeof(client_name), 0);
            recv(newSocket, feedback, sizeof(feedback), 0);
            printf("Client Name: %s\n", client_name);
            printf("Feedback received: %s\n", feedback);
            FILE *file = fopen("Feedback_data.txt","a");
    	    if(file == NULL){
    	    perror("Error opening file");
            return 1;
    	    }

    fwrite(client_name, sizeof(char), strlen(client_name), file);
    fprintf(file,"\n");
    fwrite(feedback, sizeof(char), strlen(feedback), file);
    fprintf(file,"\n\n");
    fclose(file);

    printf("Feedback appended\n");

            // Calculate total bill (in this example, we assume a fixed menu)
            
            //printf("Total Bill: $%.2f\n", totalBill);

            break;
        }
        case 1: {
            // Order items case
            printf("Sending menu to the client...\n");
            send(newSocket, menu, sizeof(menu), 0);

            int itemChoice, quantity;
            recv(newSocket, &itemChoice, sizeof(itemChoice), 0);
            recv(newSocket, &quantity, sizeof(quantity), 0);

            if (itemChoice >= 1 && itemChoice <= 5) {
                // Calculate total price
                double totalPrice = quantity * itemPrices[itemChoice - 1];
                totalBill += totalPrice;

                // Display the order with quantity
                char orderResponse[1024];
                sprintf(orderResponse, "\n\nOrder Quantity: %d  \nFood Item: %s. \nTotal Price: $%.2f\n\n", quantity, items_from_menu[itemChoice-1], totalPrice);
                printf("Order Received: %s\n", orderResponse);
                FILE *file = fopen("Order_data.txt","a");
    	    if(file == NULL){
    	    perror("Error opening file");
            return 1;
    	    }
    	    fprintf(file, "%s (%dx): %.2f\n", items_from_menu[itemChoice - 1],quantity,totalPrice);

    	    fclose(file);

    	    printf("File Appended\n");
    	    //One_day_total_bill += totalBill;
    	    
    	    

                // You can send an order confirmation back to the client if needed
                send(newSocket, orderResponse, sizeof(orderResponse), 0);
            } else if (itemChoice == 6) {
                printf("Exiting the order menu.\n");
            } else {
                printf("Invalid item choice.\n");
            }

            break;
        }
        case 3:
            // Exit case
            // Display the order with quantity
                char orderResponse[1024];
                sprintf(orderResponse, "Total Bill: $%.2f\n", totalBill);
                printf("%s\n", orderResponse);
                /*FILE *file = fopen("Order_data.txt","a");
    	    if(file == NULL){
    	    perror("Error opening file");
            return 1;
    	    }
    	    fprintf(file,"Today's Total Bill : ");
                fprintf(file,"One day total bill is %.2f",One_day_total_bill);
                fprintf(file,"\n\nDay end\n\n");
                fclose(file);
                printf("One day bill saved");*/
                

                // You can send an order confirmation back to the client if needed
                send(newSocket, orderResponse, sizeof(orderResponse), 0);
            //printf("Total Bill: $%.2f\n", totalBill);
            printf("Exiting the server.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice received from the client.\n");
    }
    }

    close(newSocket);
    close(serverSock);

    return 0;
}
//server 
