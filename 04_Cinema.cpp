class Cinema {
private:
    string name;
    vector<Screen> screens; // OOP: Composition - Cinema owns Screens
public:
    Cinema(string name) : name(name) {}
    void addScreen(const Screen& screen) { screens.push_back(screen); }
    string getName() const { return name; }
    const vector<Screen>& getScreens() const { return screens; }
    Screen* findScreen(int number) {
        for (auto& screen : screens)
            if (screen.getNumber() == number) return &screen;
        return nullptr;
    }
};
