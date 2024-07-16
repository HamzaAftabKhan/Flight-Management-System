# Flight-Management-System
This project is an Airline Management System built using Object-Oriented Programming principles. It allows users to book flights, manage complaints, and perform administrative tasks through a user-friendly menu interface.

**Features**
1)View Flight Routes: Displays available international and local flight routes.
2)User Login: Supports passenger and admin logins with validation.
3)Flight Booking: Allows users to book flights and select meal preferences.
4)Complaint Management: Users can register and manage complaints.
5)Admin Panel: Admins can view and resolve complaints.

**Prerequisites**
C++ compiler (e.g., g++, Visual Studio)
Basic understanding of C++ and Object-Oriented Programming concepts.
**Installation**
Clone the repository:
git clone https://github.com/HamzaAftabKhan/Flight-Management-System.git
Navigate to the project directory:
cd Flight-Management-System
Usage
Compile the program:
g++ main.cpp -o Flight-Management-System
Run the program:
./Flight-Management-System
Follow the on-screen instructions to navigate through the menu.
**Class Structure**
Main Classes
Login: Base class for user and admin management.
User: Handles user registration and login validation.
Admin: Manages administrative tasks, including complaints.
HomePage: Interface for user actions after logging in.
Passenger: Abstract class for passenger details and functionalities.
Booking: Derived class that manages booking operations.
Routes: Displays flight routes and availability.
Complaint: Manages user complaints.
**Contributing**
Contributions are welcome! Please create a pull request or open an issue for suggestions and improvements.
