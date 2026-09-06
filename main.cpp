#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <set>
using namespace std;

// Course rule: no header files. Each class is kept in its own .cpp file and included here.
#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "06_ShowSeat.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

vector<string> splitSeats(const string& input) {
    vector<string> result;
    string item;
    stringstream ss(input);
    while (getline(ss, item, ',')) {
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        if (!item.empty()) result.push_back(item);
    }
    return result;
}

int main() {
    Cinema cinema("Campus Cinema");
    cinema.addScreen(Screen(1));
    cinema.addScreen(Screen(2));

    Movie movie1("3 Idiots", "Hindi", 170);
    Movie movie2("Interstellar", "English", 169);

    Show show1(&movie1, cinema.findScreen(1), "06:00 PM");
    Show show2(&movie1, cinema.findScreen(2), "09:00 PM");
    Show show3(&movie2, cinema.findScreen(1), "08:30 PM");
    vector<Show*> shows = {&show1, &show2, &show3};

    BookingService bookingService;
    Customer customer("Guest", "N/A");

    int choice;
    do {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
        cout << "Choose: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid menu choice.\n";
            continue;
        }

        if (choice == 1) {
            cout << "\n[1] "; movie1.print();
            cout << "[2] "; movie2.print();
        }
        else if (choice == 2) {
            int movieChoice;
            cout << "\nChoose movie: 1. " << movie1.getTitle()
                 << "  2. " << movie2.getTitle() << "\nChoice: ";
            cin >> movieChoice;
            if (movieChoice < 1 || movieChoice > 2) { cout << "Invalid movie choice.\n"; continue; }

            vector<Show*> movieShows;
            for (auto* show : shows)
                if ((movieChoice == 1 && show->getMovie() == &movie1) ||
                    (movieChoice == 2 && show->getMovie() == &movie2))
                    movieShows.push_back(show);

            cout << "Available shows:\n";
            for (size_t i = 0; i < movieShows.size(); ++i)
                cout << i + 1 << ". Screen-" << movieShows[i]->getScreen()->getNumber()
                     << " " << movieShows[i]->getStartTime() << "\n";

            int showChoice;
            cout << "Choose show: "; cin >> showChoice;
            if (showChoice < 1 || showChoice > (int)movieShows.size()) { cout << "Invalid show choice.\n"; continue; }
            Show* selectedShow = movieShows[showChoice - 1];
            selectedShow->displaySeats();

            cout << "Enter customer name: ";
            cin.ignore();
            string name, phone, seatInput;
            getline(cin, name);
            cout << "Enter phone: "; getline(cin, phone);
            customer = Customer(name, phone);

            cout << "Seats (e.g. A1,B2): ";
            getline(cin, seatInput);
            vector<string> seats = splitSeats(seatInput);
            if (seats.empty()) { cout << "No seats entered.\n"; continue; }

            int paymentChoice, paymentResult = 1;
            cout << "Pay by: 1.UPI  2.Card  3.Cash\nChoice: ";
            cin >> paymentChoice;
            unique_ptr<Payment> payment;
            if (paymentChoice == 1 || paymentChoice == 2) {
                cout << "Simulate result: 1.Success  2.Fail\nChoice: ";
                cin >> paymentResult;
            }
            bool success = paymentResult == 1;
            if (paymentChoice == 1) payment = make_unique<UpiPayment>(success);
            else if (paymentChoice == 2) payment = make_unique<CardPayment>(success);
            else if (paymentChoice == 3) payment = make_unique<CashPayment>();
            else { cout << "Invalid payment choice.\n"; continue; }

            bookingService.createBooking(*selectedShow, customer, seats, *payment);
        }
        else if (choice == 3) {
            string id;
            cout << "Enter Booking ID: "; cin >> id;
            bookingService.cancelBooking(id);
        }
        else if (choice == 4) {
            bookingService.printCustomerBookings();
        }
        else if (choice != 0) {
            cout << "Invalid menu choice.\n";
        }
    } while (choice != 0);

    cout << "Thank you.\n";
    return 0;
}
