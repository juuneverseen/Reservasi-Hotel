# Reservasi-Hotel
This program is a hotel reservation system that allows users to register, log in, top up their balance, and book hotel rooms. There are two types of users:

Admin: Can manage user accounts, add room types, view reservations, and check total earnings.
Regular Users: Can check available room types, top up their balance, book a room, and view their reservations.
The program stores user, room, and reservation data in files (users.dat, rooms.dat, reservations.dat) to maintain data persistence.

## Features in the Program
1. For Admin:
- View user accounts
- Add new room types
- View reservations (sorted by name or search by customer name)
- Check total earnings from reservations

2. For Users:
- Register and log in
- Check available room types (sorted by price)
- Check balance and top up
- Book a room (deducts balance based on room price and stay duration)
- View their own reservations

## How to Create the Program
1. Define structures (struct) for Users, Rooms, and Reservations
- The program defines three structures: User, Kamar (Room), and Reservasi (Reservation) to store data.
2. Implement data loading and saving functions
- Data is loaded from files when the program starts using LoadData().
- Data is saved after new user registration, room addition, or reservation.
3. Create functions for registration and login
- The Registrasi() function handles user sign-ups.
- The LoginAdmin() and LoginUser() functions allow admins and users to log in.
4. Implement user and admin menus
- MenuAdmin() provides options for admin tasks.
- MenuUser() offers features like checking room types, booking rooms, and managing balance.
5. Handle file operations
- The program uses binary files (.dat) to store user, room, and reservation data using fopen(), fwrite(), fread(), and fseek().
6. Sort and search reservations
Reservations can be sorted alphabetically or searched by name.
7. Implement the main menu (main())
Provides options for registration, login, and exit.

## Instruction
1. Run the program
2. Choose an option from the main menu:
- Press 1 to Register (if not registered).
- Press 2 to Log in as Admin or User.
- Press 3 to Exit the program.
3. For Admin Users:
- After logging in, choose from options like viewing users, adding rooms, checking reservations, and total earnings.
4. For Regular Users:
- After logging in, check room types, view balance, top up, or book a room.
- Booking a room deducts the price from the user’s balance.
- Users can view their reservations.
5. To Exit:
- Users and admins can log out and return to the main menu.
- Choose 3 from the main menu to quit the program.