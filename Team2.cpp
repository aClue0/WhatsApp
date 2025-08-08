#include <iostream> // check line 313
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User // FINISHED
{
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User()
    {
        // TODO: Implement default constructor
        username = "";
        password = "";
        phoneNumber = "";
    }

    User(string uname, string pwd, string phone) // User Hazem("0clue" , "1234" , "01205417173");
    {
        // TODO: Implement parameterized constructor
        username = uname;
        password = pwd;
        phoneNumber = phone;
    }

    string getUsername() const
    {
        // TODO: Implement getter
        return username;
    }

    string getPhoneNumber() const
    {
        // TODO: Implement getter
        return phoneNumber;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return status;
    }

    string getLastSeen() const
    {
        // TODO: Implement getter
        return lastSeen;
    }

    void setStatus(string newStatus) // habiba.setStatus(online);
    {
        // TODO: Implement setter
        status = newStatus;
    }

    void setPhoneNumber(string phone)
    {
        // TODO: Implement setter
        phoneNumber = phone;
    }

    void updateLastSeen()
    {
        // TODO: Implement last seen update
        time_t currentTime = time(0);
        lastSeen = ctime(&currentTime);
        if (!lastSeen.empty() && lastSeen.back() == '\n')
        {
            lastSeen.pop_back();
        }
    }

    bool checkPassword(string pwd) const
    {
        // TODO: Implement password check
        if (password == pwd)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void changePassword(string newPwd)
    {
        // TODO: Implement password change
        password = newPwd;
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message // FINISHED
{
private:
    string sender; //   users = {"hazem", "rahma" , "salma"}
    string content;
    string timestamp;
    string status;
    Message *replyTo;

public:
    Message()
    {
        // TODO: Implement default constructor
        sender = "";
        content = "";
        timestamp = "";
        status = "Sent";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt)
    {
        // TODO: Implement parameterized constructor
        sender = sndr;
        content = cntnt;
        updateTimestamp();
        status = "Sent";
    }

    string getContent() const
    {
        // TODO: Implement getter
        return content;
    }

    string getSender() const
    {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return status;
    }

    Message *getReplyTo() const
    {
        // TODO: Implement getter
        return replyTo;
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
        status = newStatus;
    }

    void setReplyTo(Message *msg)
    {
        // TODO: Implement setter
        replyTo = msg;
    }

    void updateTimestamp()
    {
        time_t now = time(0);
        timestamp = ctime(&now);
        if (!timestamp.empty() && timestamp.back() == '\n')
        {
            timestamp.pop_back();
        }
    }

    void display() const
    {
        // TODO: Implement message display
        if (replyTo != nullptr)
        {
            cout << sender << endl;
            cout << "replied to : " << replyTo->getSender() << endl
                 << " \" " << replyTo->getContent() << " \" " << endl;
            cout << endl
                 << content << endl
                 << timestamp << endl;
        }
        else
        {
            cout << sender << endl
                 << content << endl
                 << timestamp << endl;
        }
    }

    void addEmoji(string emojiCode)
    {
        // TODO: Implement emoji support
        if (emojiCode == "smile")
        {
            content += "😄";
        }
        else if (emojiCode == "shy")
        {
            content += "🤭";
        }
        else if (emojiCode == "angry")
        {
            content += "😡";
        }
        else if (emojiCode == "heart")
        {
            content += "❤";
        }
        else if (emojiCode == "cry")
        {
            content += "😭";
        }
        else
        {
            content += "Not defined";
        }
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat // FINISHED
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        // TODO: Implement default constructor
        participants = {};
        messages = {};
        chatName = {};
    }

    Chat(vector<string> users, string name)
    {
        // TODO: Implement parameterized constructor
        participants = users;
        chatName = name;
    }

    void addMessage(const Message &msg)
    {
        // TODO: Implement message addition
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string &username)
    {
        // TODO: Implement message deletion
        if ((index >= 0 && index < messages.size()) && messages[index].getSender() == username)
        {
            messages.erase(messages.begin() + index);
            cout << "Message deleted successfully" << endl;
            return true;
        }
        return false;
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
        cout << "Chat " << chatName << endl;
        for (int i = 0; i < messages.size(); i++)
        {
            messages[i].display();
        }
    }

    vector<Message> searchMessages(string keyword) const
    {
        // TODO: Implement message search
        vector<Message> result;
        bool found = false;
        for (int i = 0; i < messages.size(); i++)
        {

            if (messages[i].getContent().find(keyword) != string::npos)
            {
                result.push_back(messages[i]);
                found = true;
            }
        }
        if (!found)
        {
            cout << "No messages has the keyword : " << keyword << endl;
        }
        return result;
    }

    void exportToFile(const string &filename) const // FuzetekProjectT2.exportToFile(Fuzetek);
    {
        // TODO: Implement export to file
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to create file " << filename << endl;
            return;
        }

        file << "Chat: " << chatName << endl;

        for (int i = 0; i < participants.size(); i++) // printing the members of the group
        {
            file << "Members of the chat : " << participants[i];

            if (i != participants.size() - 1)
            {
                file << ", ";
            }
        }

        file << endl;
        file << "---------------------------------------------" << endl;

        for (int i = 0; i < messages.size(); i++)
        {
            file << messages[i].getSender() << ", " << messages[i].getContent() << endl;
        }
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat // Menna
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        // TODO: Implement constructor
        user1 = u1;
        user2 = u2;
    }

    void displayChat() const override
    {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string &username) const
    {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat // Salma
{
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin)
    {
        // TODO: Implement add admin
        admins.push_back(newAdmin); // Hazem did this
    }

    bool removeParticipant(const string &admin, const string &userToRemove)
    {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const
    {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const
    {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc)
    {
        // TODO: Implement set description
    }

    void displayChat() const override
    {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string &username)
    {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp // Habiba
{
private:
    vector<User> users;
    vector<Chat *> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        // TODO: Implement user search
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == username)
            {
                return currentUserIndex;
            }
        }
        return -1;
    }

    bool isLoggedIn() const
    {
        // TODO: Implement login check
        return false;
    }

    string getCurrentUsername() const
    {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        // TODO: Implement user registration
    }

    void login()
    {
        // TODO: Implement user login
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
    }

    void createGroup()
    {
        // TODO: Implement group creation
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
    }

    void logout()
    {
        // TODO: Implement logout
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}