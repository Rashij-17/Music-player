#include <iostream>
#include <string>

using namespace std;

class Song {
public:
    string name;
    Song *next;
    Song *prev;

    Song(string x) : name(x), next(nullptr), prev(nullptr) {}
};

class Songlist {
private:
    Song *start;
    Song *current;

public:
    Songlist() : start(nullptr), current(nullptr) {}

    // Destructor to clean up memory
    ~Songlist() {
        Song* temp = start;
        while (temp) {
            Song* nextSong = temp->next;
            delete temp;
            temp = nextSong;
        }
    }

    void insert(string name) {
        Song *newsong = new Song(name);
        if (start == nullptr) {
            start = newsong;
            current = start;
        } else {
            Song *temp = start;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newsong;
            newsong->prev = temp;
        }
        cout << "\n> Added '" << name << "' to playlist." << endl;
    }

    void playNext() {
        if (current && current->next) {
            current = current->next;
            cout << "\n>>> Switched to: " << current->name << endl;
        } else {
            cout << "\n[!] No more songs ahead." << endl;
        }
    }

    void playPrev() {
        if (current && current->prev) {
            current = current->prev;
            cout << "\n<<< Switched back to: " << current->name << endl;
        } else {
            cout << "\n[!] This is the first song." << endl;
        }
    }

    void display() {
        if (!start) {
            cout << "\nPlaylist is empty! Add some music." << endl;
            return;
        }
        cout << "\n---------- CURRENT PLAYLIST ----------" << endl;
        Song *temp = start;
        while (temp) {
            if (temp == current) cout << " -> [PLAYING] " << temp->name << endl;
            else cout << "    " << temp->name << endl;
            temp = temp->next;
        }
        cout << "--------------------------------------" << endl;
    }
};

int main() {
    Songlist myPlaylist;
    int choice;
    string songName;

    cout << "=== DSA MUSIC PLAYER CONSOLE ===" << endl;

    do {
        cout << "\n1. Add Song\n2. Next Song\n3. Previous Song\n4. View Playlist\n5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from buffer

        switch (choice) {
            case 1:
                cout << "Enter song name: ";
                getline(cin, songName);
                myPlaylist.insert(songName);
                break;
            case 2:
                myPlaylist.playNext();
                break;
            case 3:
                myPlaylist.playPrev();
                break;
            case 4:
                myPlaylist.display();
                break;
            case 5:
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
