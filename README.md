***

# Student Management System (SRMS)

A simple and efficient Student Management System built using C.
The project uses file handling to store, manage, and analyze student records so that data persists even after the program exits.

## Features

### Core Functionality
- Add new student records  
- View all student records  
- Search for a student by ID or name  
- Update existing student information  
- Delete a student record  
- Export student records to a CSV file  
- Generate student reports and summaries

### Analytics and Reporting
- Display top-performing students  
- Count the total number of students  
- Categorize students by department  
- Sort students by marks, name, or ID

### Security and Login
- Admin login system using credentials stored in a file  
- Track login history with timestamps  
- Credentials stored in a dedicated text file  
- Planned support for encrypted credential storage and role-based login

### Additional Usability Features
- Simple file-based “database” using plain text files  
- Auto-save after every operation  
- Error handling for invalid inputs  
- Prevention of duplicate student IDs  
- Clean and modular C code structure for easier maintenance

## Project Structure

- `src/`  
  Contains all C source files (main logic, menu handling, file operations, utilities).
- `include/`  
  Header files defining structures, function prototypes, and constants.
- `data/`  
  - `students.txt` – Raw student data storage  
  - `exported_students.csv` – Exported student report in CSV format  
  - `credentials.txt` – Admin login credentials  
  - `login_history.txt` – Timestamped login records
- `output/`  
  - `report.txt` – Generated report file  
  - `top_students.txt` – List of top performers  
  - Additional backups or generated outputs (if enabled)

## How It Works

1. The admin logs in using a username and password stored in `credentials.txt`.  
2. Each login attempt is appended to `login_history.txt` with a timestamp and status.  
3. Student records are stored in `students.txt` using a predefined, consistent format.  
4. Exporting generates `exported_students.csv` for use in Excel or other tools.  
5. Updates and deletions are handled via temporary files to safely rewrite `students.txt`.

## How to Run

1. Install a C compiler (GCC recommended).
2. Compile the program from the `src` folder (adjust source filenames if needed):
   ```bash
   gcc main.c -o sms
   ```
3. Run the executable:
   ```bash
   ./sms
   ```


## File Formats

- **Credentials (`credentials.txt`)**  
  - Line 1: username  
  - Line 2: password[1]

- **Login History (`login_history.txt`)**  
  - Each line: `<timestamp> – <status>`  
  - Example: `2025-01-11 14:32:22 – Login successful`

- **Exported CSV (`exported_students.csv`)**  
  - Columns: `student_id, name, department, marks, age`

## Future Enhancements

- Graphical User Interface (GUI)  
- Online database integration (e.g., MySQL/PostgreSQL)  
- Role-based login system (admin, staff, viewer)  
- Encrypted credential storage  
- Attendance and fee management modules

## Author

**TALLURI REVANTH SAI** – SRM University  
Email: revanthsai_talluri@srmap.edu.in  
Passionate about C programming, data management, and automation.

***
