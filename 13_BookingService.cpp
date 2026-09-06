class BookingService {
private:
    vector<Booking> bookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    bool validateSeats(const vector<ShowSeat*>& seats) const {
        if (seats.empty()) return false;
        for (const auto* seat : seats)
            if (!seat || !seat->isAvailable()) return false;
        return true;
    }

    void releaseSeats(const vector<ShowSeat*>& seats) {
        for (auto* seat : seats) seat->cancelSeat();
    }

public:    Booking* createBooking(Show& show, const Customer& customer,
                           const vector<string>& seatNumbers, Payment& payment) {
        set<string> uniqueNumbers(seatNumbers.begin(), seatNumbers.end());
        if (uniqueNumbers.size() != seatNumbers.size()) {
            cout << "Duplicate seat number entered. Booking rejected.\n";
            return nullptr;
        }

        vector<ShowSeat*> selectedSeats;
        for (const string& number : seatNumbers) {
            ShowSeat* showSeat = show.findShowSeat(number);
            if (!showSeat) {
                cout << "Invalid seat number: " << number << "\n";
                return nullptr;
            }
            selectedSeats.push_back(showSeat);
        }

        if (!validateSeats(selectedSeats)) {
            cout << "One or more selected seats are already BOOKED. Nothing changed.\n";
            return nullptr;
        }

        Booking booking(&show, customer, selectedSeats); // «create» Booking
        double total = priceCalculator.calculate(selectedSeats);
        booking.setAmount(total);

        for (auto* seat : selectedSeats) seat->bookSeat();

        bool isPaid = payment.pay(total); // OOP: Runtime polymorphism through Payment&
        if (!isPaid) {
            releaseSeats(selectedSeats);
            booking.fail();
            bookings.push_back(booking);
            cout << "Payment FAILED. Seats released; booking not confirmed.\n";
            return &bookings.back();
        }

        booking.confirm();
        bookings.push_back(booking);
        cout << "Payment successful.\n";
        ticketPrinter.print(bookings.back());
        return &bookings.back();
    }

    bool cancelBooking(const string& bookingId) {
        for (auto& booking : bookings) {
            if (booking.getId() == bookingId && booking.getStatus() == CONFIRMED) {
                releaseSeats(booking.getSeats());
                booking.cancel();
                cout << "Booking cancelled. Seats are AVAILABLE again.\n";
                return true;
            }
        }
        cout << "Confirmed booking not found.\n";
        return false;
    }

    void printCustomerBookings() const {
        if (bookings.empty()) { cout << "No bookings yet.\n"; return; }
        for (const auto& booking : bookings) {
            cout << booking.getId() << " | "
                 << booking.getShow()->getMovie()->getTitle() << " | "
                 << booking.getStatusText() << "\n";
        }
    }
};
