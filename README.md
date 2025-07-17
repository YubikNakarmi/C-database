
# Database with C

This is a simple CRUD system written in C. It has basic capabilities like creating a database and adding, updating and removing elements from the database. All data is stored in a .txt file.

This CRUD system stores medicinal details, and has to levels of access 
+ Admin
+ User



## Acknowledgements

 - This CRUD system was tested both in Linux and Windows, so it should run properly in both operating systems.
 - Original project by [gabrielwitor](https://github.com/gabrielwitor/CRUD-C)
 - This project is under the [MIT license](https://opensource.org/license/mit/).



## How to use

Clone the repository

```bash
git clone https://github.com/YubikNakarmi/C-database
```

Open the repository folder

```bash
cd C-database
```

Compile the `main.c` file.

```bash
gcc main.c -o main
```

Execute the `main` file.

```bash
.\main
```

## Features
### ✅ General User Mode
- **Create**: Add new medicine entries to the database.
- **Read**: View details of available medicines.
- **Update**: Edit existing medicine records.
- **Delete**: Remove expired or invalid medicine entries.
- **Leave**: Exit the program.
- **Admin Login**: Securely access the admin dashboard.

### 🔐 Admin Mode
- **Add User**: Register new system users.
- **View Users**: Display all registered users.
- **Edit User**: Update user information.
- **Delete User**: Remove inactive or unauthorized users.
- **View Logs**: Audit actions performed on the system.
- **Back**: Return to main menu.



You should be prompted with the following screen:





