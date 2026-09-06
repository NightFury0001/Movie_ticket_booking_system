class PriceCalculator {
private:
    static constexpr double SILVER_PRICE = 150;
    static constexpr double GOLD_PRICE = 250;
    static constexpr double PLATINUM_PRICE = 400;
public:
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0;
        for (const auto* seat : seats) total += getSeatPrice(seat->getType());
        return total;
    }
    double getSeatPrice(SeatType type) const {
        if (type == SILVER) return SILVER_PRICE;
        if (type == GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }
};
