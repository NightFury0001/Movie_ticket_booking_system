class Show {
private:
    Movie* movie;       // Aggregation: Movie exists independently
    Screen* screen;     // Association: Screen belongs to Cinema
    string startTime;
    vector<ShowSeat> showSeats; // OOP: Composition - Show owns show-specific seat states
public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) {
        for (const auto& seat : screen->getSeats())
            showSeats.emplace_back(&seat);
    }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    void displaySeats() const {
        cout << "\nScreen-" << screen->getNumber() << "  " << startTime
             << "  " << movie->getTitle() << "\n";
        for (const auto& showSeat : showSeats)
            cout << showSeat.getTypeName() << " " << showSeat.getNumber()
                 << " " << showSeat.getStatusText() << "\n";
        cout << "([ ] = available, [X] = booked)\n";
    }
    ShowSeat* findShowSeat(const string& number) {
        for (auto& showSeat : showSeats)
            if (showSeat.getNumber() == number) return &showSeat;
        return nullptr;
    }
};
