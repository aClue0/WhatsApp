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
        status = "Offline";
    }

    User(string uname, string pwd, string phone) // User Hazem("0clue" , "1234" , "01205417173");
    {
        // TODO: Implement parameterized constructor
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = "Offline"; // offline untill user login -salma
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
        if (newStatus == "Offline")
        { // makes sure to update the lastseen when user goes offline
            updateLastSeen();
        }
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
        updateTimestamp();
    }

    Message(string sndr, string cntnt)
    {
        // TODO: Implement parameterized constructor
        sender = sndr;
        content = cntnt;
        status = "Sent";
        replyTo = nullptr;
        updateTimestamp();
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

    void setContent(string cntnt)
    {
        content = cntnt;
        updateTimestamp(); // need to Update timestamp when message is edited -salma
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

    void updateTimestamp() // choose a format
    {
        /*
        this give the time in the format ex. Sun Aug 10 15:42:33 2025
         time_t now = time(0);
         timestamp = ctime(&now);
         if (!timestamp.empty() && timestamp.back() == '\n')
         {
             timestamp.pop_back();
         }*/

        // this gives a format  ex. 15:42 -salma
        time_t now = time(0);
        struct tm *time = localtime(&now); // tm pre defined struct in ctime , pointer as localtime returns a pointer
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", time->tm_hour, time->tm_min);
        timestamp = buffer;

        /*snprintf formats and write data to a string
        takes pointer of the arry, size to prevent overflow,
        string format, and what is going to be formated
        --"%02d:%02d" format so integer would be at least 2 digits, pad with zeros*/
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
                 << "[" << timestamp << "]" << endl;
        }
        else
        {
            cout << sender << endl
                 << content << endl
                 << "[" << timestamp << "]" << endl;
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
        chatName = "";
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
        messages.back().setStatus("Delivered"); // update status as msg is now in sys -salma
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

    void editMessage(int idx, string cntnt, const string &username)
    {
        if (idx < 0 || idx >= messages.size())
        {
            cout << "No index with that number found!" << endl;
            return;
        }
        else if (messages[idx].getSender() != username)
        {
            cout << "You didn't send this message!" << endl;
            return;
        }
        else
        {
            messages[idx].setContent(cntnt);
            cout << "Message edited successfully" << endl;
        }
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
        cout << "Chat " << chatName << endl;

        /*if (messages.empty()) {
            cout << "No messages yet." << endl;*/

        for (int i = 0; i < messages.size(); i++)
        {
            messages[i].display();
        }
    }

    vector<Message> searchMessages(string keyword) const // add helper function and make fun case insensitive ?
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
        file << "Members of the chat : " << endl;
        for (int i = 0; i < participants.size(); i++) // printing the members of the group
        {
            file << participants[i];

            if (i != participants.size() - 1)
            {
                file << ", ";
            }
        }

        file << endl;
        file << "---------------------------------------------" << endl;

        for (int i = 0; i < messages.size(); i++)
        {
            file << messages[i].getSender() << ", " << messages[i].getContent() << endl; // add timestamp?
        }

        file.close();
        cout << "Chat exported to " << filename << endl;
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat // Menna , This needs alot of work I tried to make it better -Hazem
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
        // participants = {u1, u2};
        // chatName = u1 + " and " + u2;
    }

    void sendMessage()
    {
        cout << user1 << "enter your message: " << endl;
        string content;
        getline(cin, content);
        Message msg(user1, content);
        addMessage(msg);
    }

    void displayChat() const override
    {
        cout << "Private Chat between " << user1 << " and " << user2 << endl
             << endl;

        /* if (messages.empty()) {
            cout << "No messages yet. Start the conversation!" << endl;*/

        for (int i = 0; i < messages.size(); i++)
        {
            messages[i].display();
        }
    }

    void showTypingIndicator(const string &username) const
    { // added again - howa kan ra7 feen ?? -salma
        // TODO: Implement typing indicator
        cout << username << " is typing..." << endl;
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
        participants = users;
        chatName = name;
        admins.push_back(creator);
        description = "";
    }

    void addAdmin(string newAdmin)
    {
        // TODO: Implement add admin
        bool already_admin = isAdmin(newAdmin);
        bool is_participant = isParticipant(newAdmin);

        if (already_admin)
        {
            cout << newAdmin << " is already an admin" << endl;
        }
        else if (is_participant)
        {
            admins.push_back(newAdmin);
            cout << newAdmin << " is now an admin of " << chatName << endl;
        }
        else
        {
            cout << newAdmin << " is not a participant of the group" << endl;
        }
    }

    /* function checks if the adimn is in the vector
    if he is acutally an admin then it search for the participant to remove */

    bool removeParticipant(const string &admin, const string &userToRemove)
    {
        // TODO: Implement remove participant
        bool is_admin = isAdmin(admin);
        bool is_participant = isParticipant(userToRemove);
        bool was_admin = isAdmin(userToRemove);

        if (!is_admin)
        {
            cout << admin << " is not an admin of this group" << endl;
            return false;
        }
        else if (admin == userToRemove)
        {
            cout << "Admins can't remove themselves" << endl;
            return false;
        }

        if (!is_participant)
        {
            cout << userToRemove << " is not in the group chat" << endl;
            return false;
        }

        for (int i = 0; i < participants.size(); i++)
        {
            if (userToRemove == participants[i])
            {
                participants.erase(participants.begin() + i);
                break;
            }
        }

        if (was_admin)
        {
            for (int j = 0; j < admins.size(); j++)
            {
                if (userToRemove == admins[j])
                {
                    admins.erase(admins.begin() + j);
                    break;
                }
            }
        }

        cout << admin << " Has Removed " << userToRemove << " From The Group" << endl;

        return true;
    }

    bool isAdmin(string username) const
    {
        // TODO: Implement admin check
        for (const auto &ad : admins)
        {
            if (ad == username)
            {
                return true;
            }
        }
        return false;
    }

    bool isParticipant(string username) const
    {
        // TODO: Implement participant check
        for (const auto &p : participants)
        {
            if (p == username)
            {
                return true;
            }
        }
        return false;
    }

    void setDescription(string desc)
    {
        // TODO: Implement set description
        description = desc;
    }

    void displayChat() const override
    {
        // TODO: Implement group chat display
        cout << "Group Chat: " << chatName << endl;
        cout << "Description: " << description << endl;
        cout << "-------------------------------------" << endl;
        if (messages.empty())
        {
            cout << "No messages yet." << endl;
        }
        else
        {
            for (const auto &msg : messages)
            {
                msg.display();
            }
        }
    }

    void sendJoinRequest(const string &username)
    {
        // TODO: Implement join request
        if (!isParticipant(username))
        {
            participants.push_back(username);
            cout << username << " has joined " << chatName << endl;
        }
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
                return i;
            }
        }
        return -1;
    }

    bool isLoggedIn() const
    {
        // TODO: Implement login check
        if (currentUserIndex != -1 && users[currentUserIndex].getStatus() == "online")
        {
            return true;
        }
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
        // TODO: Implement user registrat
        string username, phone, password;
        cin.ignore();
        cout << "Enter your Username : " << endl;
        getline(cin, username);
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == username)
            {
                cout << "Username Taken!" << endl;
                return;
            }
        }
        cout << "Enter your Password : " << endl;
        getline(cin, password);
        cout << "Enter your Phonenumber : " << endl;
        getline(cin, phone);
        User thisUser(username, password, phone);
        users.push_back(thisUser);
    }

    void login()
    {
        // TODO: Implement user login
        string username, password;
        cin.ignore();
        cout << "Enter your username : " << endl;
        getline(cin, username);
        cout << "Enter your password : " << endl;
        getline(cin, password);
        for (int i = 0; i < users.size(); i++)
        {
            if ((users[i].getUsername() == username) && users[i].checkPassword(password))
            {
                cout << "Login Successful!" << endl;
                currentUserIndex = i;
                users[i].setStatus("online");
                return;
            }
        }
        cout << "Username or Password is not correct!" << endl;
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
        cin.ignore();
        string u1 = users[currentUserIndex].getUsername();
        string u2;
        cout << "Who do you want to chat with? " << endl;
        getline(cin, u2);
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == u2)
            {
                break;
            }
            else if (i == users.size() - 1)
            {
                cout << "There's no user with that username!" << endl;
                return;
            }
        }
        PrivateChat(u1, u2);
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