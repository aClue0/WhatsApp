#include <iostream>
#include <vector> // do reply to in send message and typing indicator
#include <string>
#include <ctime>
#include <fstream>
#include <sstream> // for stringstream
#include <filesystem>
using namespace std;

// ========================
//       USER CLASS   habiba
// ========================
class User // username,password,phone
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

    string getPassword() const
    {
        return password;
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
        // this gives a format  ex. 15:42 -salma
        time_t now = time(0);
        struct tm *time = localtime(&now); // tm pre defined struct in ctime , pointer as localtime returns a pointer
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", time->tm_hour, time->tm_min);
        timestamp = buffer;

        /* snprintf formats and write data to a string
        takes pointer of the arry, size to prevent overflow,
        string format, and what is going to be formated
        --"%02d:%02d" format so integer would be at least 2 digits, pad with zeros */
    }

    void display() const
    {
        // TODO: Implement message display
        if (replyTo != nullptr)
        {
            cout << sender << endl;
            cout << "replied to : " << replyTo->getSender() << ": "
                 << " \" " << replyTo->getContent() << " \" " << endl;

            cout << content
                 << "[" << timestamp << "]" << "\t[" << status << "]" << endl;
        }
        else
        {
            cout << sender << ": "
                 << content
                 << " [" << timestamp << "]" << "\t[" << status << "]" << endl;
        }
    }

    void addEmoji(string emojiCode)
    {
        // TODO: Implement emoji support
        if (emojiCode == "smile")
        {
            content += " :)";
        }
        else if (emojiCode == "shy")
        {
            content += " :\"";
        }
        else if (emojiCode == "angry")
        {
            content += " >:(";
        }
        else if (emojiCode == "heart")
        {
            content += " <3";
        }
        else if (emojiCode == "cry")
        {
            content += " ToT";
        }
        else if (emojiCode == "none")
        {
            content += "";
        }
        else
        {
            content += " Not defined";
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

    string toSmall(string message) const
    {
        string result;
        for (int i = 0; i < message.size(); i++)
        {
            result += tolower(message[i]);
        }
        return result;
    }

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
        else if ((index >= 0 && index < messages.size()))
        {
            cout << "Invalid Index!" << endl;
        }
        else if (messages[index].getSender() == username)
        {
            cout << "You didn't send this message!" << endl;
        }
        return false;
    }

    void showTypingIndicator(const string &username) const
    {
        // TODO: Implement typing indicator
        cout << username << " is typing..." << endl;
    }

    void editMessage(int idx, string cntnt, const string &username)
    {
        if (idx < 0 || idx >= messages.size())
        {
            cout << "No message with that index found!" << endl;
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
            string emoji;
            cout << "To add an emoji please choose from the following \n"
                 << "{smile,shy,angry,heart,cry,none}" << endl;
            cin >> emoji;
            messages[idx].addEmoji(emoji);
            cout << "Message edited successfully" << endl;
        }
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
        cout << "Chat " << chatName << endl;

        if (messages.empty())
        {
            cout << "No messages yet." << endl;
        }
        else
        {
            for (int i = 0; i < messages.size(); i++)
            {
                messages[i].display();
            }
        }
    }

    vector<Message> searchMessages(string keyword) const // add helper function and make fun case insensitive ?
    {
        // TODO: Implement message search
        vector<Message> result;
        bool found = false;
        string smallKeyword = toSmall(keyword);
        for (int i = 0; i < messages.size(); i++)
        {
            string smallContent = toSmall(messages[i].getContent());
            if (smallContent.find(smallKeyword) != string::npos)
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

    string getName()
    {
        return chatName;
    }

    void markMessagesRead(const string &username) // need to change tha status of the message - salma
    {
        for (auto &msg : messages)
        {
            if (msg.getSender() != username && msg.getStatus() != "Read")
            {
                msg.setStatus("Read");
            }
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
        participants = {u1, u2};
        chatName = u1 + " and " + u2;
    }

    void displayChat() const override
    {
        cout << "\n------------------ " << chatName << " ------------------" << endl;
        if (messages.empty())
        {
            cout << "No messages yet. Start the conversation!" << endl;
        }
        else
        {
            for (int i = 0; i < messages.size(); i++)
            {
                messages[i].display();
            }
        }
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
        else
        {
            cout << username << " already in group." << endl;
        }
    }

    vector<string> getAdmins()
    {
        return admins;
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

        if (currentUserIndex != -1)
        {
            return users[currentUserIndex].getUsername();
        }
        return "";
    }

    void saveToFile(const User &user)
    {
        ofstream file("users.txt", ios::app); // opens in append mode
        if (!file.is_open())
        {
            cout << "Error saving user to file.\n";
            return;
        }
        file << user.getUsername() << "," << user.getPassword() << "," << user.getPhoneNumber() << "\n";
        file.close();
    }

    void loadFromFile()
    {
        ifstream file("users.txt");
        if (!file.is_open())
        {
            return;
        }

        string line;
        while (getline(file, line)) // while will read the file line by line 
        {
            if (line.empty())
                continue;
// turn string into a stream to be read from 
// sstream is a string lib like cin/cout but instead of a terminal it read from and write to a string in memory.  
            stringstream ss(line); 
            string name, pass, phone;

            // spilt the string by ,
            getline(ss, name, ','); 
            getline(ss, pass, ',');
            getline(ss, phone, ',');

            if (!name.empty() && !pass.empty() && !phone.empty())
            {
                users.push_back(User(name, pass, phone));
            }
        }
        file.close();
    }

public:
    WhatsApp() : currentUserIndex(-1) {
        loadFromFile();
    }

    ~WhatsApp() // Destructor
    {
        for (int i = 0; i < chats.size(); i++)
        {
            delete chats[i];
        }
    }

    void signUp()
    {
        // TODO: Implement user registrat
        string username, phone, password;
        cin.ignore();
        cout << "Enter your Username : " << endl;
        getline(cin, username);
        if (findUserIndex(username) != -1)
        {
            cout << "Username Taken!" << endl;
            return;
        }
        cout << "Enter your Password : " << endl;
        getline(cin, password);
        cout << "Enter your Phonenumber : " << endl;
        getline(cin, phone);
        User thisUser(username, password, phone);
        users.push_back(thisUser);
        saveToFile(thisUser);
        cout << "\n------------------Signup successful! You can now log in ------------------" << endl;

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

        int userIndex = findUserIndex(username);

        if (userIndex != -1 && users[userIndex].checkPassword(password))
        {
            cout << "\n------------------ Login Successful! ------------------" << endl;
            currentUserIndex = userIndex;
            users[userIndex].setStatus("online");
            return;
        }
        cout << "Username or Password is not correct!" << endl;
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
        cin.ignore();
        string u1 = getCurrentUsername();
        string u2;
        cout << "\nWho do you want to chat with? ";
        getline(cin, u2);

        if (findUserIndex(u2) == -1)
        {
            cout << "There's no user with that username!" << endl;
            return;
        }

        // Try to find an existing private chat
        Chat *selectedChat = nullptr;
        for (int i = 0; i < chats.size(); i++)
        {
            if (chats[i]->getName() == u1 + " and " + u2 || chats[i]->getName() == u2 + " and " + u1)
            {
                selectedChat = chats[i];
                break;
            }
        }

        // If it doesn't exist, create it
        if (!selectedChat)
        {
            PrivateChat *thisChat = new PrivateChat(u1, u2);
            chats.push_back(thisChat);
            selectedChat = thisChat;
            cout << "\n------------------ Private chat created successfully! ------------------\n";
        }

        bool in_chat = true;
        while (in_chat)
        {
            selectedChat->markMessagesRead(getCurrentUsername());
            selectedChat->displayChat();
            cout << "\n1. Send Message\n2. Search Messages\n3. Edit Messages\n"
                 << "4. Delete Messages\n5. Back\nChoice: ";
            string input;
            cin >> input;
            cin.ignore();
            int choice = stoi(input);
            switch (choice)
            {
            case 1:
            {
                selectedChat->showTypingIndicator(u1);
                string content, emoji;
                cout << "Enter your message: ";
                getline(cin, content);
                Message msg(u1, content);
                cout << "To add an emoji please choose from the following \n"
                     << "{smile,shy,angry,heart,cry,none}" << endl;
                cin >> emoji;
                msg.addEmoji(emoji);
                selectedChat->addMessage(msg);

                break;
            }
            case 2:
            {
                string key;
                cout << "Entry Keyword: " << endl;
                getline(cin, key);
                vector<Message> resluts = selectedChat->searchMessages(key);
                for (const auto &msg : resluts)
                {
                    msg.display();
                }
                break;
            }

            case 3:
            {
                int index;
                string new_content;
                cout << "Enter Index of message to be Edited: " << endl;
                cin >> index;
                cin.ignore();

                cout << "Enter New Edited Message: " << endl;
                getline(cin, new_content);

                selectedChat->editMessage(index, new_content, u1);
                break;
            }
            case 4:
            {

                int index;
                string new_content;
                cout << "Enter Index of message to be deleted: " << endl;
                cin >> index;
                selectedChat->deleteMessage(index, u1);
                break;
            }
            case 5:
            {
                in_chat = false;
            }
            default:
                cout << "Enter a valid Choice!" << endl;
                break;
            }
        }
    }

    void createGroup() // i need to check if the other users have the created chat or not
    {
        // TODO: Implement group creation   changes made by -Hazem
        cin.ignore();
        int input;
        string u1 = users[currentUserIndex].getUsername();

        cout << "Who do you want to add to your group?" << endl;
        for (int i = 0; i < users.size(); i++) // displays the users you can add
        {
            cout << i << ") " << users[i].getUsername() << " ";
        }
        cout << "\nNOTE: To complete adding members to your Group Chat enter \"-1\"" << endl; // taking -1 as exit

        bool isAddingMember = true;
        vector<string> AddedMembers = {u1}; // creator is already part of the group
        while (isAddingMember)              // keeps registering their index and adding them in AddedMembers until you type -1
        {
            int input;
            cin >> input;
            if (input == -1) // if you exited
            {
                isAddingMember = false;
            }
            else
            {
                string thisUser = users[input].getUsername();
                bool exist = false; // need to check if I already added that member

                for (int i = 0; i < AddedMembers.size(); i++)
                {
                    string thisMember = AddedMembers[i];
                    if (thisUser == thisMember)
                    {
                        cout << "Member already exist!" << endl;
                        exist = true;
                        break;
                    }
                }

                if (input != -1 && (input > 0 && input < users.size()) & isAddingMember & !exist) // if your index is right
                {
                    AddedMembers.push_back(thisUser);
                    cout << thisUser << " added to group." << endl;
                }
            }
        }
        cin.ignore();
        cout << endl
             << "------------------ Name your Group Chat! ------------------" << endl;

        string groupName = "";   // ---------------------- i dont think that I need to check if there is a group chat with the same requirements or not because there may be but i want to create another one with another name or smt
        getline(cin, groupName); // enter your group name

        GroupChat *thisGroup = new GroupChat(AddedMembers, groupName, u1 /*Creator*/); // makes group chat
        thisGroup->addAdmin(u1);                                                       // adds creator in the admin rightaway
        chats.push_back(thisGroup);
        cout << "What is your group's description? ";
        string description = {};
        getline(cin, description);
        thisGroup->setDescription(description);
        cout << endl;

        bool in_groupchat = true;
        while (in_groupchat)
        {
            thisGroup->markMessagesRead(getCurrentUsername());

            thisGroup->displayChat();
            cout << "\n1. Send Message\n2. Search Messages\n3. Edit Messages\n"
                 << "4. Delete Messages\n";
            if (thisGroup->isAdmin(u1))
            {
                cout << "5. Add Admin\n6. Add Participants\n7. Remove Participants\n"; // this is the new part we need to implement this
            }
            cout << "8. Back\nChoice: ";
            string input;
            cin >> input;
            cin.ignore();
            int choice = stoi(input); // handles letter input NOTE: i need to do this in the top too in choosing the members, also i took most of the code from the private chat part

            switch (choice)
            {
            case 1:
            {
                thisGroup->showTypingIndicator(u1);
                string content, emoji;
                cout << "Enter your message: ";
                getline(cin, content);
                Message msg(u1, content);
                cout << "To add an emoji please choose from the following \n"
                     << "{smile,shy,angry,heart,cry,none}" << endl;
                cin >> emoji;
                msg.addEmoji(emoji);
                thisGroup->addMessage(msg);

                break;
            }
            case 2:
            {
                string key;
                cout << "Entry Keyword: " << endl;
                getline(cin, key);
                vector<Message> resluts = thisGroup->searchMessages(key);
                for (const auto &msg : resluts)
                {
                    msg.display();
                }
                break;
            }

            case 3:
            {
                int index;
                string new_content;
                cout << "Enter Index of message to be Edited: " << endl;
                cin >> index;
                cin.ignore();

                cout << "Enter New Edited Message: " << endl;
                getline(cin, new_content);

                thisGroup->editMessage(index, new_content, u1);
                break;
            }
            case 4:
            {

                int index;
                string new_content;
                cout << "Enter Index of message to be deleted: " << endl;
                cin >> index;
                thisGroup->deleteMessage(index, u1);
                break;
            }

            // ---------------------------------- TODO IMPLEMENT THE 5 6 7 CASES : ADD ADMIN, ADD PARTICIPANTS ,REMOVE PARTICIPANTS
            case 5:
            {
                cout << "Enter username to grant admin: ";
                string username;
                getline(cin, username);
                thisGroup->addAdmin(username);

                break;
            }
            case 6:
            {
                cout << "Enter username to add to group: ";
                string username;
                getline(cin, username);
                if (findUserIndex(username) == -1)
                {
                    cout << "User not found ." << endl;
                    break;
                }
                thisGroup->sendJoinRequest(username);
                break;
            }
            case 7:
            {
                cout << "Enter username to remove from group: ";
                string username;
                getline(cin, username);
                thisGroup->removeParticipant(u1, username);
                break;
            }
            case 8:
            {
                in_groupchat = false;
            }
            default:
                cout << "Enter a valid Choice!" << endl;
                break;
            }
        }
        /* Habiba's Code :
     if(! isLoggedIn()){
     cout<<"login"<<endl;
        return;
        }
         string groupname;
        cout<<"create group"<<endl;
        cout<<"inter group name"<<endl;
        cin.ignore();
        getline(cin,groupname);

          vector<string> members;
       string currentUser = getCurrentUsername();
       members.push_back(currentUser);

        int nummembers;
       cout<<"add nummembers"<<endl;
       cin >> nummembers;

        for( int i = 0 ; i< nummembers; i++){
        string memberName;
        cout<<"enter memberName"<< i+1<<":"<<endl;
        cin >>memberName;

        if (findUserIndex(memberName) != -1 && memberName != currentUser){
            members.push_back(memberName);
        }
        else{
            cout<<" member not found ";
           }
           GroupChat* newgroup = new
           GroupChat(members,groupname,currentUser );
           chats.push_back(newgroup);

           cout<<"group has been created"<< groupname <<endl;
*/
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
        if (chats.size() == 0)
        {
            cout << "No Chats yet, Try to Chat with someone!" << endl;
        }
        else
        {
            cout << "Chats: " << endl;
            for (int i = 0; i < chats.size(); i++)
            {
                cout << i << "- " << chats[i]->getName() << endl;
                ;
            }
        }
    }

    void logout()
    {
        // TODO: Implement logout
        users[currentUserIndex].setStatus("offline");
        users[currentUserIndex].updateLastSeen();
        return;
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