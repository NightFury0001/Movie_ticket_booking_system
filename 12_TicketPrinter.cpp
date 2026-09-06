class TicketPrinter {
public:
    void print(const Booking& booking) const {
        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : " << booking.getId() << "\n";
        cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        cout << "Screen     : Screen-" << booking.getShow()->getScreen()->getNumber()
             << " | " << booking.getShow()->getStartTime() << "\n";
        cout << "Seats      : ";
        for (const auto* seat : booking.getSeats()) cout << seat->getNumber() << " ";
        cout << "\nAmount     : Rs." << fixed << setprecision(2) << booking.getAmount()
             << "   Status: " << booking.getStatusText() << "\n";
        cout << "========================================\n";
    }
};
