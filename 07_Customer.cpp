class Customer {
private:
    string name;
    string phone;
public:
    Customer() : name("Guest"), phone("N/A") {}
    Customer(string name, string phone) : name(name), phone(phone) {}
    string getName() const { return name; }
    string getPhone() const { return phone; }
};
