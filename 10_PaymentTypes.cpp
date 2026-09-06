class UpiPayment : public Payment { // OOP: Inheritance
private:
    bool shouldSucceed;
public:
    UpiPayment(bool shouldSucceed = true) : shouldSucceed(shouldSucceed) {}
    bool pay(double amount) override {
        cout << "UPI payment of Rs." << fixed << setprecision(2) << amount << " processing...\n";
        return shouldSucceed;
    }
    string methodName() const override { return "UPI"; }
};

class CardPayment : public Payment {
private:
    bool shouldSucceed;
public:
    CardPayment(bool shouldSucceed = true) : shouldSucceed(shouldSucceed) {}
    bool pay(double amount) override {
        cout << "Card payment of Rs." << fixed << setprecision(2) << amount << " processing...\n";
        return shouldSucceed;
    }
    string methodName() const override { return "Card"; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment of Rs." << fixed << setprecision(2) << amount << " accepted.\n";
        return true;
    }
    string methodName() const override { return "Cash"; }
};
