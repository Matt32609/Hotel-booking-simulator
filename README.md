# Hotel-booking-simulator (LAST BRIDGING PROJECT BETWEEN PYTHON AND C BEFORE THE COMMENCEMENT OF MY DATA SCIENCE DEGREE)
--------------------------------------
A command-line interface (CLI) application built in Python and C that simulates a professional hotel front-desk system. The project focuses on managing the guest lifecycle—from room selection and automated billing to persistent record-keeping.

This simulator was developed to enhance my understanding of dictionaries, JSON for persistent data storage, and the use of functions such as a length function. At the same time, the project introduced me to the "random" and "datetime" modules/features in C and Python, which helped make the simulator more realistic.

---------------------------------------
Key features of the code:
--------------------------------------
1. Dictionary-Driven Room Selection:
- I implemented a dictionary to map user inputs to specific room attributes, such as room name and nightly rate. (Python : selection_of_rooms = {1: ["Standard Room", 100], 2: ["Superior Room", 350], 3: ["Deluxe Room", 500], 4: ["Executive Room", 800], 5: ["Penthouse", 1200]} /  C : struct Room selection_of_rooms[] = {{" ", 0}, {"Standard Room", 100}, {"Superior Room", 350}, {"Deluxe Room", 500}, {"Executive Room", 800}, {"Penthouse", 1200}};) This approach replaces long "if-else" chains with a cleaner, more scalable lookup system that manages everything from Standard rooms to the Penthouse.

2. Date-Time Arithmetic for Billing:
- Using Python’s "datetime" module and C's <<time.h>> and struct feature for time such as (mktime) , the program captures the current date and calculates the delta (difference) between check-in and check-out. This ensures the stay duration is calculated automatically, which then drives the total cost calculation without manual entry.

3. Logical Room Number Allocation:
- To mirror a real-world hotel floor plan, I used "random.randint()" / "%(max - min + 1), min" within specific ranges. I wrote logic to ensure room numbers are tier-aware, assigning lower numbers to Standard rooms and reserving the 900-series exclusively for Penthouses.

4. Persistent Data Storage via JSON:
- I implemented a JSON-based database system to ensure data persistence. By using JSON, the simulator maintains guest records even after the program is closed, moving the project beyond a simple volatile script to a persistent application.

5. Dynamic Record Management:
- The check-out system performs a targeted search through a list of dictionaries. Once a match is found, the program modifies the data structure in real time and updates the external JSON file, simulating a live database update.

---------------------------------------------
To run the simulator:
---------------------------------------------
(PYTHON)
- chmod +x hotel_booking_simulator.py 
- ./hotel_booking_simulator.py 

(ALTERNATIVE)
- python3 hotel_booking_simulator.py | cat -e
--------------------------------------------
(C)
- gcc hotel_sim.c -o hotel_sim
- ./hotel_sim.exe
--------------------------------------------
Image demonstration of the simulator:
---------------------------------------------

<img width="562" height="338" alt="MINGW64__c_Users_Matthew Kam_Desktop_R 15_04_2026 17_13_08" src="https://github.com/user-attachments/assets/4c6eb73d-c162-4b39-817b-ac5a1a0280c4" />




