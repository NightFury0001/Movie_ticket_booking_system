class Payment {
public:
    virtual bool pay(double amount) = 0; // OOP: Abstraction
    virtual string methodName() const = 0;
    virtual ~Payment() {}
};
