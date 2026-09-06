class Screen {
private:
    int screenNumber;
    vector<Seat> seats; // OOP: Composition - Screen owns its Seat objects
public:
    Screen(int screenNumber) : screenNumber(screenNumber) {
        seats.emplace_back("A1", SILVER);
        seats.emplace_back("A2", SILVER);
        seats.emplace_back("A3", SILVER);
        seats.emplace_back("B1", GOLD);
        seats.emplace_back("B2", GOLD);
        seats.emplace_back("B3", GOLD);
        seats.emplace_back("C1", PLATINUM);
        seats.emplace_back("C2", PLATINUM);
    }
    int getNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }
};
