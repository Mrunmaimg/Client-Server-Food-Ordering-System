# Client-Server Food Ordering System

This repository contains a basic client-server application built in C, where a client can interact with a food ordering system hosted on a server. The client can:
- Order items from a menu
- Provide feedback
- Exit the system

The server handles requests, processes orders, stores feedback, and sends appropriate responses back to the client.

## Features
- **Menu Ordering**: The client can order food items, specify quantity, and receive the total bill from the server.
- **Feedback**: The client can send feedback to the server, which is stored in a file.
- **Exit Option**: The client can exit the system, and the total bill will be displayed before termination.

## TCP/IP Socket Communication
This system leverages **TCP/IP sockets** to establish a reliable connection between the client and server. Here's how the TCP/IP communication works:
- **Socket Creation**: Both the client and server create a socket using the `socket()` function, specifying `SOCK_STREAM` to use the TCP protocol.
- **Server Binding and Listening**: The server binds to a specific IP address and port (in this case, `127.0.0.1:8080`) using `bind()` and listens for incoming client connections with `listen()`.
- **Client-Server Communication**: Once a client connects using the `connect()` function, the server accepts the connection using `accept()`. Data is exchanged between the client and server using `send()` and `recv()`, ensuring reliable message delivery due to TCP’s nature.
- **Multiple Requests**: The server can handle multiple client requests, such as ordering items, providing feedback, and exiting, using the same established TCP connection.

## Prerequisites
To run this project, you need:
- A Unix-based system (Linux).
- GCC (GNU Compiler Collection) to compile the C programs.

## How to Run

### 1. Clone the repository
```bash
git clone https://github.com/Mrunmaimg/Client-Server-Food-Ordering-System.git
cd Client-Server-Food-Ordering-System
cd restaurant management system
```


### 2. Compile the server and client

#### Compile the Server:
```bash
gcc server.c -o server
```

#### Compile the Client:
```bash
gcc client.c -o client
```

### 3. Run the Server
Open a terminal and run the server:
```bash
./server
```
The server will begin listening on port `8080`.

### 4. Run the Client
Open another terminal and run the client:
```bash
./client
```
The client will establish a connection with the server and display a menu with options to order items, provide feedback, or exit.

### 5. Interaction
- **Ordering**: Select option 1 from the client menu to view the menu, place an order, and receive the total bill.
- **Feedback**: Select option 2 to provide feedback, which is saved on the server in `Feedback_data.txt`.
- **Exit**: Select option 3 to exit and view the total bill.

## Files
- **server.c**: The server-side code, responsible for receiving client requests, processing orders, storing feedback, and managing the total bill.
- **client.c**: The client-side code, where the user can interact with the server by sending orders or feedback.
- **Feedback_data.txt**: This file stores feedback from clients.
- **Order_data.txt**: This file logs orders placed by clients.

## Sample Interaction

### Client Panel
```bash
Customer Panel:
1. Order Items
2. Give Feedback
3. Exit
Enter your choice: 1
```

### Server Logs
```bash
Order Received:
Order Quantity: 2  
Food Item: Pizza.  
Total Price: $40.00
File Appended
```

## Notes
- Ensure that both the server and client are running on the same machine or network. For network-based setups, replace the IP address in `client.c` with the server’s IP address.
- Feedback and order information are stored in `Feedback_data.txt` and `Order_data.txt`, respectively, on the server side.

--- 
