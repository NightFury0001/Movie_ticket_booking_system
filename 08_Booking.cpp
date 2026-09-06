enum BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

class Booking {
private:
    static int nextBookingId; // OOP: Static member for unique IDs
    string bookingId;
    Show* show;
    Customer customer;
    vector<ShowSeat*> bookedSeats; // Aggregation: existing ShowSeats
    double bookingAmount; // OOP: Encapsulation
    BookingStatus status;
public:
    Booking(Show* show, const Customer& customer, const vector<ShowSeat*>& seats)
        : show(show), customer(customer), bookedSeats(seats),
          bookingAmount(0), status(PENDING) {
        bookingId = "BK" + to_string(nextBookingId++);
    }
    string getId() const { return bookingId; }
    Show* getShow() const { return show; }
    const Customer& getCustomer() const { return customer; }
    const vector<ShowSeat*>& getSeats() const { return bookedSeats; }
    double getAmount() const { return bookingAmount; }
    BookingStatus getStatus() const { return status; }
    string getStatusText() const {
        if (status == CONFIRMED) return "CONFIRMED";
        if (status == FAILED) return "FAILED";
        if (status == CANCELLED) return "CANCELLED";
        return "PENDING";
    }
    void setAmount(double amount) { bookingAmount = amount; }
    void confirm() { status = CONFIRMED; }
    void fail() { status = FAILED; }
    void cancel() { status = CANCELLED; }
};
int Booking::nextBookingId = 1001;
