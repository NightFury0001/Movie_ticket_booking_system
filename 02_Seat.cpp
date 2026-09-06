enum SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    string number;
    SeatType type;
public:
    Seat(string number, SeatType type) : number(number), type(type) {}
    string getNumber() const { return number; }
    SeatType getType() const { return type; }
    string getTypeName() const {
        if (type == SILVER) return "SILVER";
        if (type == GOLD) return "GOLD";
        return "PLATINUM";
    }
};
