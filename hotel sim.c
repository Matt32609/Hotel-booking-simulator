#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int ask_to_exit();
int menuselect();
int checkin();
int checkout();
int payment(const char *chosen_room, int room_price, const char *dateissue, int stay_duration);

struct Room
    {const char *name;
    int price;};

int ask_to_exit(void)
    {char exittask[20];
    int input;

    while (1)
        {printf("(1) Yes | (2) No\n");
        printf("Do you wish to continue? Enter either '1' or '2' to continue.\n");fgets(exittask, sizeof(exittask), stdin);
        if (exittask[0] == '\n')
            {printf("Invalid response.\n");
            continue;}
        if (sscanf(exittask, "%d", &input) != 1)
            {printf("Invalid response.\n");
            continue;}

        if (input == 1)
            {return 1;}
        else if (input == 2)
            {return 0;}
        else
            {printf("Invalid response.\n");
            continue;}}}

int menuselect(void)
    {while (1)
        {char ms[10];
        int input;
        printf("(1) Check-in | (2) Check-out | (3) Exit | (4) Reset simulator\n");
        printf("Hello. What would you like to do? Please enter a digit either 1, 2, 3 or 4 to continue.\n");fgets(ms, sizeof(ms), stdin);

        if (ms[0] == '\n')
            {printf("Invalid response.\n");
            return 1;}
        if (sscanf(ms,"%d", &input) != 1)
            {printf("Invalid response.\n");
            return 1;}

        if (input == 1)
            {checkin();}
        else if (input == 2)
            {checkout();}
        else if (input == 3)
            {return 0;}
        else if (input == 4)
            {FILE *f = fopen("bookings.txt", "w");

            if (f != NULL)
                {fclose(f);
                printf("All booking data has been successfully reset.\n");
                continue;}

            else
                {printf("Error resetting booking data.\n");
                continue;}}
        else
            {printf("Invalid response.\n");
            continue;}
            }
    }

int checkin(void)
    {while (1)
        {char ci[10];
        int input;
        printf("(1) Standard Room(RM100/night) | (2) Superior Room(RM350/night) | (3) Deluxe Room(RM500/night)\n");
        printf("(4) Executive Room(RM800/night) | (5) Penthouse(RM1200/night) | (6) Return to Menu\n");
        printf("Please select the type of room that you'd like to stay by entering a digit either 1, 2, 3, 4, 5 or 6 to continue.\n");fgets(ci, sizeof(ci), stdin);

        if (ci[0] == '\n')
            {printf("Invalid response.\n");
            return 1;}
        if (sscanf(ci, "%d", &input) != 1)
            {printf("Invalid response.\n");
            return 1;}

        if (input == 6)
            {return 1;}
        
        struct Room selection_of_rooms[] = {{" ", 0}, {"Standard Room", 100}, {"Superior Room", 350}, {"Deluxe Room", 500}, {"Executive Room", 800}, {"Penthouse", 1200}};

        if ((input >= 1) && (input <= 5))
            {const char *chosen_room = selection_of_rooms[input].name;
            int room_price = selection_of_rooms[input].price;
            
            char rc[10];
            int input;
            
            while (1)
                {printf("(1) Yes | (2) No\n");
                printf("You have chosen %s\n", chosen_room);
                printf("Would you like to continue? Enter a digit either 1 or 2 to continue.\n");fgets(rc, sizeof(rc), stdin);

                if (rc[0] == '\n')
                    {printf("Invalid response.\n");
                    return 1;}
                if (sscanf(rc, "%d", &input) != 1)
                    {printf("Invalid response.\n");
                    return 1;}

                if (input == 1)
                    while (1)
                    {char dateissue[15];
                    int year, month, day;

                    printf("Please enter your check out date in the following format (YYYY-MM-DD):\n");fgets(dateissue, sizeof(dateissue), stdin);
                    dateissue[strcspn(dateissue, "\n")] = '\0';

                    if (dateissue[0] == '\0')
                        {printf("Invalid response.\n");
                        return 1;}
                    if (strlen(dateissue) != 10 || dateissue[4] != '-' || dateissue[7] != '-' || sscanf(dateissue, "%d-%d-%d", &year, &month, &day) != 3)
                        {printf("Invalid date format.\n");
                        continue;}

                    time_t now = time(NULL);
                    struct tm check_in_info = *localtime(&now);
                    struct tm check_out_info = check_in_info;

                    check_in_info.tm_hour = 12;
                    check_in_info.tm_min = 0;
                    check_in_info.tm_sec = 0;
                    check_in_info.tm_isdst = -1;

                    check_out_info.tm_hour = 12;
                    check_out_info.tm_min = 0;
                    check_out_info.tm_sec = 0;
                    check_out_info.tm_isdst = -1;

                    check_out_info.tm_year = year - 1900;
                    check_out_info.tm_mon = month - 1;
                    check_out_info.tm_mday = day;

                    time_t check_in_date = mktime(&check_in_info);
                    time_t check_out_date = mktime(&check_out_info);

                    if (check_in_date == (time_t)-1 || check_out_date == (time_t)-1 || check_out_info.tm_year != year - 1900 || check_out_info.tm_mon != month - 1 || check_out_info.tm_mday != day)
                        {printf("Invalid calendar date.\n");
                        continue;}

                    if (check_out_date <= check_in_date)
                        {printf("Sorry, you cannot pick a date in the past or today. Please try again.\n");
                        continue;}

                    int stay_duration = (int)(difftime(check_out_date, check_in_date) / 86400.0);

                    if (stay_duration < 1)
                        {stay_duration = 1;}

                    printf("--- YOUR BOOKING INFORMATION ---\n");
                    printf("Room chosen : %s\n", chosen_room);

                    printf("Check-in: %04d-%02d-%02d\n", check_in_info.tm_year + 1900, check_in_info.tm_mon + 1, check_in_info.tm_mday);

                    printf("Check-out: %s\n", dateissue);
                    printf("Stay duration: %d nights\n", stay_duration);
                    
                    char proceed[10];
                    int input;
                    while (1)
                        {printf("(1) Yes | (2) No\n");
                        printf("Would you like to continue? Enter a digit either 1 or 2 to continue.\n"); fgets(proceed, sizeof(proceed), stdin);

                        if (proceed[0] == '\n')
                            {printf("Invalid response.\n");
                            continue;}
                        
                        if (sscanf(proceed, "%d", &input) != 1)
                            {printf("Invalid response.\n");
                            continue;}
                        
                        if (input == 1)
                            {printf("You will be brought to the payment page.\n");
                            payment(chosen_room, room_price, dateissue, stay_duration);}
                        else if (input == 2)
                            {return 1;}
                        else
                            {printf("Invalid response.\n");
                            continue;}
                        }
                        }
                else if (input == 2)
                    {return 1;}
                else
                    {printf("Invalid response,\n");
                    return 1;}
                }
            }
        else if (input == 6)
            {return 1;}
        else
            {printf("Invalid response.");
            continue;}
    }
}

int payment(const char *chosen_room, int room_price, const char *dateissue, int stay_duration)
    {struct Booking
        {int room_number; char type[30]; char date[11]; int price;};

    struct Booking all_bookings[881];
    int taken_rooms[881];
    int booking_count = 0;
    int current_bookings = 0;

    printf("--- PAYMENT PAGE ---\n");

    int total_cost = room_price * stay_duration;

    FILE *f = fopen("bookings.txt", "r");

    if (f != NULL)
        {while (booking_count < 881)
            {int check = fscanf(f, " %d|%29[^|]|%10[^|]|%d",
                &all_bookings[booking_count].room_number,
                all_bookings[booking_count].type,
                all_bookings[booking_count].date,
                &all_bookings[booking_count].price);

            if (check == EOF)
                {break;}

            if (check != 4)
                {printf("Error reading booking data.\n");
                fclose(f);
                return 1;}

            booking_count = booking_count + 1;}

        fclose(f);}

    for (int i = 0; i < booking_count; i = i + 1)
        {taken_rooms[i] = all_bookings[i].room_number;

        if (strcmp(all_bookings[i].type, chosen_room) == 0)
            {current_bookings = current_bookings + 1;}}

    if (strcmp(chosen_room, "Standard Room") == 0 && current_bookings >= 200)
        {printf("Sorry, %s is sold out!\n", chosen_room);
        return 1;}

    else if (strcmp(chosen_room, "Superior Room") == 0 && current_bookings >= 200)
        {printf("Sorry, %s is sold out!\n", chosen_room);
        return 1;}

    else if (strcmp(chosen_room, "Deluxe Room") == 0 && current_bookings >= 200)
        {printf("Sorry, %s is sold out!\n", chosen_room);
        return 1;}

    else if (strcmp(chosen_room, "Executive Room") == 0 && current_bookings >= 200)
        {printf("Sorry, %s is sold out!\n", chosen_room);
        return 1;}

    else if (strcmp(chosen_room, "Penthouse") == 0 && current_bookings >= 81)
        {printf("Sorry, %s is sold out!\n", chosen_room);
        return 1;}

    if (booking_count >= 881)
        {printf("Sorry, the hotel is fully booked.\n");
        return 1;}

    int room_number;

    /*% (max - min + 1) + min*/ 
    while (1)
        {if (strcmp(chosen_room, "Standard Room") == 0)
            {room_number = rand() % 200 + 100;}

        else if (strcmp(chosen_room, "Superior Room") == 0)
            {room_number = rand() % 200 + 300;}

        else if (strcmp(chosen_room, "Deluxe Room") == 0)
            {room_number = rand() % 200 + 500;}

        else if (strcmp(chosen_room, "Executive Room") == 0)
            {room_number = rand() % 200 + 700;}

        else if (strcmp(chosen_room, "Penthouse") == 0)
            {room_number = rand() % 81 + 900;}

        else
            {room_number = rand() % 881 + 100;}

        int room_taken = 0;

        for (int i = 0; i < booking_count; i = i + 1)
            {if (room_number == taken_rooms[i])
                {room_taken = 1;
                break;}}

        if (room_taken == 0)
            {break;}
        }

    printf("Room: %s\n", chosen_room);
    printf("Night(s): %d\n", stay_duration);
    printf("Total Amount: RM%d\n", total_cost);

    char pf[20];
    int payment_final;

    while (1)
        {printf("(1) Yes | (2) No\n");
        printf("Would you like to proceed with this transaction? Please enter a digit either 1 or 2 to continue.\n");fgets(pf, sizeof(pf), stdin);

        if (pf[0] == '\n')
            {printf("Invalid response.\n");
            continue;}

        char extra;

        if (sscanf(pf, " %d %c", &payment_final, &extra) != 1)
            {printf("Sorry, this was an invalid response. Please enter again.\n");
            continue;}

        if (payment_final == 1)
            {struct Booking new_entry; new_entry.room_number = room_number; strcpy(new_entry.type, chosen_room); strcpy(new_entry.date, dateissue); new_entry.price = room_price;

            all_bookings[booking_count] = new_entry;
            booking_count = booking_count + 1;

            FILE *f = fopen("bookings.txt", "w");

            if (f == NULL)
                {printf("Error saving booking data.\n");
                return 1;}

            int save_ok = 1;

            for (int i = 0; i < booking_count; i = i + 1)
                {if (fprintf(f, "%d|%s|%s|%d\n",
                    all_bookings[i].room_number,
                    all_bookings[i].type,
                    all_bookings[i].date,
                    all_bookings[i].price) < 0)
                    {save_ok = 0;
                    break;}}

            if (fclose(f) != 0)
                {save_ok = 0;}

            if (save_ok == 0)
                {printf("Error saving booking data.\n");
                return 1;}

            printf("Thank you for your payment! Your room number throughout the stay is %d. Enjoy your stay!\n", room_number);
            exit(0);
            }

        else if (payment_final == 2)
            {return 1;}

        else
            {printf("Invalid response.\n");
            continue;}
        }
    }

int checkout(void)
    {char ri[20];
    int room_input;
    char extra;

    printf("Please enter your room number (Enter an invalid response to return to the main menu):\n");fgets(ri, sizeof(ri), stdin);

    if (sscanf(ri, " %d %c", &room_input, &extra) != 1)
        {printf("Invalid response. Returning to menu.\n");
        return 1;}

    struct Booking
        {int room_number; char type[30]; char date[11]; int price;};

    struct Booking all_bookings[881];
    int booking_count = 0;

    FILE *f = fopen("bookings.txt", "r");

    if (f != NULL)
        {while (booking_count < 881)
            {int check = fscanf(f, " %d|%29[^|]|%10[^|]|%d",
                &all_bookings[booking_count].room_number,
                all_bookings[booking_count].type,
                all_bookings[booking_count].date,
                &all_bookings[booking_count].price);

            if (check == EOF)
                {break;}

            if (check != 4)
                {printf("Error reading booking data.\n");
                fclose(f);
                return 1;}

            booking_count = booking_count + 1;}

        if (ferror(f))
            {printf("Error reading booking data.\n");
            fclose(f);
            return 1;}

        fclose(f);}

    int found_guest = -1;

    for (int i = 0; i < booking_count; i = i + 1)
        {if (all_bookings[i].room_number == room_input)
            {found_guest = i;
            break;}}

    if (found_guest != -1)
        {printf("Booking Found: %s\n", all_bookings[found_guest].type);

        time_t now = time(NULL);
        struct tm *current = localtime(&now);

        if (current == NULL)
            {printf("Invalid current date.\n");
            return 1;}

        struct tm today_info = *current;
        struct tm scheduled_info = today_info;

        int year, month, day;

        if (sscanf(all_bookings[found_guest].date, "%d-%d-%d", &year, &month, &day) != 3)
            {printf("Invalid saved date.\n");
            return 1;}

        today_info.tm_hour = 12;
        today_info.tm_min = 0;
        today_info.tm_sec = 0;
        today_info.tm_isdst = -1;

        scheduled_info.tm_hour = 12;
        scheduled_info.tm_min = 0;
        scheduled_info.tm_sec = 0;
        scheduled_info.tm_isdst = -1;

        scheduled_info.tm_year = year - 1900;
        scheduled_info.tm_mon = month - 1;
        scheduled_info.tm_mday = day;

        time_t today = mktime(&today_info);
        time_t scheduled_date = mktime(&scheduled_info);

        if (today == (time_t)-1 || scheduled_date == (time_t)-1 || scheduled_info.tm_year != year - 1900 || scheduled_info.tm_mon != month - 1 || scheduled_info.tm_mday != day)
            {printf("Invalid saved date.\n");
            return 1;}

        int overstay_days = (int)(difftime(today, scheduled_date) / 86400.0);

        if (overstay_days > 0)
            {int extra_charge = overstay_days * all_bookings[found_guest].price;

            printf("NOTICE: You have overstayed by %d day(s).\n", overstay_days);
            printf("Extra charges incurred: RM%d\n", extra_charge);}

        char co[20];
        int input;

        while (1)
            {printf("(1) Yes | (2) No\n");
            printf("Would you like to check out?\n");fgets(co, sizeof(co), stdin);

            if (co[0] == '\n')
                {printf("Invalid response.\n");
                continue;}

            if (sscanf(co, " %d %c", &input, &extra) != 1)
                {printf("Invalid response.\n");
                continue;}

            if (input == 1)
                {for (int i = found_guest; i < booking_count - 1; i = i + 1)
                    {all_bookings[i] = all_bookings[i + 1];}

                booking_count = booking_count - 1;

                FILE *f = fopen("bookings.txt", "w");

                if (f != NULL)
                    {int save_ok = 1;

                    for (int i = 0; i < booking_count; i = i + 1)
                        {if (fprintf(f, "%d|%s|%s|%d\n",
                            all_bookings[i].room_number,
                            all_bookings[i].type,
                            all_bookings[i].date,
                            all_bookings[i].price) < 0)
                            {save_ok = 0;
                            break;}}

                    if (fclose(f) != 0)
                        {save_ok = 0;}

                    if (save_ok == 0)
                        {printf("Error saving booking data.\n");
                        return 1;}}

                else
                    {printf("Error saving booking data.\n");
                    return 1;}

                printf("We hope you enjoyed your stay! You are more than welcome to stay with us again.\n");
                exit(0);}

            else if (input == 2)
                {printf("Check-out process cancelled.\n");
                return 1;}

            else
                {printf("Invalid response.\n");
                continue;}
            }
        }

    else
        {printf("Room number not found. Please try again.\n");
        return 1;}
    }

int main(void)
    {menuselect();
    return 0;}
        



