#!/usr/bin/env python3

import datetime
import json
import random

def load_from_json():
    try:
        with open("bookings.json", "r") as f:
            return json.load(f)
    except (FileNotFoundError, json.JSONDecodeError):
        return [] 

def save_to_json(data_list):
    with open("bookings.json", "w") as f:
        json.dump(data_list, f, indent=4)

def menu_selection():
    try:
        print("(1) Check-in | (2) Check-out | (3) Exit | (4) Reset simulator ")
        select = int(input("Hello. What would you like to do? Please enter a digit either 1, 2, 3 or 4 to continue,"))
        if select == 1:
            check_in()
        elif select == 2:
            check_out()
        elif select == 3:
            exit()
        elif select == 4:
            save_to_json([]) 
            print("Simulator fully reset")
            return True
    except ValueError:
        print("Sorry , this was an invalid response . Please enter again.")
        return True
    
def check_in():
    try:
        print("(1) Standard Room(RM100/night) | (2) Superior Room(RM350/night) | (3) Deluxe Room(RM500/night)")
        print("(4) Executive Room(RM800/night) | (5) Penthouse(RM1200/night) | (6) Return to Menu")
        selection = int(input("Please select the type of room that you'd like to stay by entering a digit either 1, 2, 3, 4, 5 or 6 to continue. "))
        if selection == 6:
                return menu_selection()
        selection_of_rooms = {1: ["Standard Room", 100], 2: ["Superior Room", 350], 3: ["Deluxe Room", 500], 4: ["Executive Room", 800], 5: ["Penthouse", 1200]}
        if selection in selection_of_rooms:
            chosen_room = selection_of_rooms[selection][0]
            room_price = selection_of_rooms[selection][1]
            print("(1) Yes | (2) No")
            confirmation = int(input(f"You have chosen {chosen_room}. Would you like to continue? Enter a digit either 1 or 2 to continue."))
            if confirmation == 1:
                date_str = input("Please enter your check-out date (YYYY-MM-DD): ")
                check_in_date = datetime.datetime.now()
                check_out_date = datetime.datetime.strptime(date_str, "%Y-%m-%d")  
                
                if check_out_date <= check_in_date:
                    print("Sorry, you cannot pick a date in the past or today. Please try again.")
                    return check_in() 
                    
                stay_duration = (check_out_date.date() - check_in_date.date()).days
                if stay_duration < 1:
                    stay_duration = 1 
                print(f"--- YOUR BOOKING INFORMATION ---")
                print(f"Room: {chosen_room}")
                print(f"Check-in:  {check_in_date.strftime('%Y-%m-%d')}")
                print(f"Check-out: {check_out_date.strftime('%Y-%m-%d')}")
                jdjd = int(input(f"Would you like to continue? Enter a digit either 1 or 2 to continue."))
                print("(1) Yes | (2) No")
                if jdjd == 1:
                    print("You will be bought to the payment page.")
                    payment(chosen_room, room_price, date_str, stay_duration)
                elif jdjd == 2:
                    menu_selection()
            elif confirmation == 2:
                menu_selection()
    except ValueError:
        print("Sorry , this was an invalid response . Please enter again.")
        return True

def payment(chosen_room, room_price, date_str, stay_duration):
    try:
        print(f"--- PAYMENT PAGE ---")
        total_cost = room_price * stay_duration
        if chosen_room == "Standard Room":
            room_number = random.randint(100, 299) 
        elif chosen_room == "Superior Room":
            room_number = random.randint(300, 499)  
        elif chosen_room == "Deluxe Room":
            room_number = random.randint(500, 699)  
        elif chosen_room == "Executive Room":
            room_number = random.randint(700, 899) 
        elif chosen_room == "Penthouse":
            room_number = random.randint(900, 980)  
        else:
            room_number = random.randint(100, 980)  
        print(f"Room: {chosen_room}")
        print(f"Nights: {stay_duration}")
        print(f"Total Amount: RM{total_cost}")
        print("(1) Yes | (2) No")
        payment_final = int(input("Would you like to proceed with this transaction? Please enter a digit either 1 or 2 to continue."))
        if payment_final == 1:
            all_bookings = load_from_json()
            new_entry = {"room_number": room_number, "type": chosen_room, "date": date_str}
            all_bookings.append(new_entry)
            
            save_to_json(all_bookings)
            
            print(f"Thank you for your payment! Your room number throughout the stay is {room_number}. Enjoy your stay!")
            menu_selection()
        elif payment_final == 2:
            menu_selection()
    except ValueError:
        print("Sorry , this was an invalid response . Please enter again.")
        return True

def check_out():
    try:
        room_input = int(input("Please enter your room number:"))
        all_bookings = load_from_json()
        
        found_guest = None
        for guest in all_bookings:
            if guest["room_number"] == room_input:
                found_guest = guest
                break
        
        if found_guest:
            print(f"Booking Found: {found_guest['type']}")
            print("(1) Yes | (2) No")
            if int(input("Would you like to complete check-out? ")) == 1:
                all_bookings.remove(found_guest)
                save_to_json(all_bookings)
                print("We hope you enjoyed your stay! You are more than welcome to stay with us again.")
            else:
                print("Check-out process cancelled.")
                menu_selection()
        else:
            print("Room number not found. Please try again.")
            menu_selection()
    except ValueError:
        print("Sorry , this was an invalid response . Please enter again.")
        return True

while True:
    menu_selection()







        

    