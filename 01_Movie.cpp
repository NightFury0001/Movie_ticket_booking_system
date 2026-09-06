class Movie {
private:
    string title;
    string language;
    int duration;
public:
    Movie() : title(""), language(""), duration(0) {}
    Movie(string title, string language, int duration)
        : title(title), language(language), duration(duration) {} // this-like constructor initialization
    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return duration; }
    void print() const { cout << title << " | " << language << " | " << duration << " min\n"; }
};
