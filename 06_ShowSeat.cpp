enum SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    const Seat* seat;
    SeatStatus seatStatus; // OOP: Encapsulation - status changed only by validated methods
public:
    ShowSeat(const Seat* seat) : seat(seat), seatStatus(AVAILABLE) {}
    string getNumber() const { return seat->getNumber(); }
    SeatType getType() const { return seat->getType(); }
    string getTypeName() const { return seat->getTypeName(); }
    bool isAvailable() const { return seatStatus == AVAILABLE; }
    bool bookSeat() {
        if (!isAvailable()) return false;
        seatStatus = BOOKED;
        return true;
    }
    void cancelSeat() { seatStatus = AVAILABLE; }
    string getStatusText() const { return isAvailable() ? "[ ]" : "[X]"; }
};
