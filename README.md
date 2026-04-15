# Hotel-booking-simulator
--------------------------------------
A command-line interface (CLI) application built in Python that simulates a professional hotel front-desk system. The project focuses on managing the guest lifecycle—from room selection and automated billing to persistent record-keeping.

This simulator was developed to enhance my understanding in the usage of dictionaries , JSON concepts to save user's data and the usage of functions . At the same time , this project also introduces me to random and datetime module to strengthen the realism of the simulator.

---------------------------------------
Key features of the code:
--------------------------------------
1. Dictionary-Driven Room Selection:
- I implemented a dictionary to map user inputs to specific room attributes (Room Name and Nightly Rate). This approach replaces long if-else chains with a cleaner, more scalable lookup system that manages everything from Standard rooms to the Penthouse.

2. Date-Time Arithmetic for Billing:
- Using Python’s datetime module, the program captures the current date and calculates the delta (difference) between check-in and check-out. This ensures the stay duration is calculated automatically, which then drives the total cost calculation without manual entry.

3. Logical Room Number Allocation:
- To mirror a real-world hotel floor plan, I used random.randint within specific ranges. I wrote logic to ensure room numbers are "tier-aware"—assigning lower numbers to Standard rooms and reserving the 900-series exclusively for Penthouses.

4. Persistent Data Storage via JSON:
- I implemented a JSON-based database system to ensure data persistence. By using json.load() and json.dump(), the simulator maintains guest records even after the program is closed, moving the project beyond a simple volatile script to a persistent application.

5. Robust Input Validation & Error Trapping:
- To prevent system crashes, I wrapped user inputs in try-except blocks. This handles ValueErrors gracefully—such as when a user enters a string instead of an integer—and includes logical validation to ensure check-out dates cannot be set in the past.
  
6. Recursive Navigation & State Control:
- The program is designed with a circular navigation flow. By utilizing recursive function calls, I ensured that users could backtrack to the main menu at any point in the transaction without losing their session or breaking the program's execution loop.

7. Dynamic Record Management:
- The check-out system performs a targeted search through a list of dictionaries. Once a match is found, the program modifies the data structure in real-time and updates the external JSON file, simulating a live database update.
---------------------------------------------
To run the simulator:
---------------------------------------------
- chmod +x hotel_booking_simulator.py (to gain permission to run this simulator)
- ./hotel_booking_simulator.py (to run the simulator)

(ALTERNATIVE)
- python3 hotel_booking_simulator.py | cat -e

--------------------------------------------
Image demonstration of the simulator:
<img width="562" height="338" alt="MINGW64__c_Users_Matthew Kam_Desktop_R 15_04_2026 13_55_59" src="https://github.com/user-attachments/assets/4757e443-f0b4-4bab-a44a-c3fd023443a2" />



