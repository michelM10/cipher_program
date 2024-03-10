// file:CS112_A2_T2_SECTION 15&16_20231181_20230436_20230159.cpp
// route cipher: mohrael mourad lotfy demian
//Polybius Square Cipher: michelle magdy faried ibrahim
//rail_fence cipher: zyad mohamed ahmed abdelzaher





#include <bits\stdc++.h>
using namespace std;
const vector <vector<char>> letters = {{'A','B','C','D','E'},{'F','G','H','I','K'},{'L','M','N','O','P'},{'Q','R','S','T','U'},{'V','W','X','Y','Z'}};

void Rail_fence_cipher(string word)
{
    string new_word; //word without spaces and with characters in lower case
    for (char i : word)
    {
        if (isspace(i))
            continue;
        if (isupper(i))
            i = tolower(i);
        new_word += i;
    }
    vector<char> row1, row2, row3;
    for (int i = 0; i < new_word.length(); i++)
    {
        // Distribute characters into rows based on their position in the word.
        if (i % 4 == 0)
        {
            row1.push_back(new_word[i]);
        }
        else if (i % 2 != 0)
        {
            row2.push_back(new_word[i]);
        }
        else
        {
            row3.push_back(new_word[i]);
        }
    }
    // Append characters from each row to the result string.

    string result;
    for (char i : row1) result += i;
    for (char j : row2) result += j;
    for (char k : row3) result += k;
    cout << result;
}

void Rail_fence_decipher(string word)
{
    // Initialize vectors to represent each row in the Rail Fence Cipher
    vector <char> row1,row2,row3;
    int nrow1 = ceil(word.length()/4.f);
    int nrow2 = word.length()/2;
    // Loop through each character in the input word.
    for (int i = 0 ; i < word.length() ; i++)
    {
        // Distribute characters into rows based on the calculated counts.
        if (nrow1 > 0)
        {
            row1.push_back(word[i]);
            nrow1 -= 1;
        }
        else if (nrow2 > 0)
        {
            row2.push_back(word[i]);
            nrow2 -= 1;
        }
        else
            row3.push_back(word[i]);
    }
    // Initialize a string to store the result of deciphering the Rail Fence Cipher.
    string result;
    // Reconstruct the original word by appending characters from each row in the correct order.
    for (int i = 0; i < word.length(); i++)
    {
        // Append characters from each row according to the original Rail Fence pattern.
        if (i % 4 == 0)
        {
            result += row1.at(0);
            row1.erase(row1.begin());
        }
        else if (i % 2 != 0)
        {
            result += row2.at(0);
            row2.erase(row2.begin());
        }
        else
        {
            result += row3.at(0);
            row3.erase(row3.begin());
        }
    }
    // Print the resulting string, which is the deciphered word.
    cout << result;
}

// Function to get an integer from user input, handling invalid inputs
int get_int(){
    while (true) {
        int num;
        cin >> num;
        if (cin.fail()) {
            cin.clear();// Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// Discard input buffer
            cerr << "Invalid input! Please enter an integer." << endl;// Display error message
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// Discard remaining input
            return num;// Return the valid integer
        }
    }
}
// Function to check for repeated elements in a vector
bool check_repeated(vector<int>& v){
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size() ; ++j) {
            if(i==j)continue;// Skip comparison with itself
            else{
                if(v[i]==v[j])// If a repeated element is found
                    return true;// Return true indicating repetition
            }
        }
    }
    return false;// No repetition found, return false
}
void Polybius_Square_cipher(string& txt){
    vector<int> enc;
    bool flag=true;
    cout<<"enter the Key:"<<endl;
    // Loop until a valid non-repeated encryption key is entered.
    while(flag){
        for (int i = 0; i < 5; ++i) {
            int x=get_int();
            // Validate the input to be between 1 and 5.
            while(x<=0 || x >5){
                cerr<<"Invalid input please enter a number between 1 and 5"<<endl;
                x=get_int();
            }
            enc.push_back(x);// Add the validated integer to the encryption key.
        }
        flag= check_repeated(enc);// Check if the encryption key contains repeated integers.
        if(flag){
            cerr<<"invalid input! start again and enter non repeated integers in the cipher \n";
            enc.clear();// Clear the encryption key vector if it contains repeated integers.
        }
    }
    // Preprocess the input text.
    string res;
    for (int i = 0; i < txt.length(); ++i) {
        if(txt[i]=='J')txt[i]='I';// Replace 'J' with 'I'
        else if(txt[i]==' ')txt[i]=' ';// Leave spaces unchanged.
        else if(!isalpha(txt[i]))continue;// Ignore non-alphabetic characters.
        else{
            txt[i]= toupper(txt[i]);// Convert characters to uppercase.
        }
    }
    // Encrypt the text using the Polybius Square cipher.
    for (int k = 0; k < txt.length(); ++k) {
        bool flag=false;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if(txt[k]==letters[i][j]){// Match characters with their corresponding position in the Polybius Square.
                    res+= to_string(enc[i])+to_string(enc[j]);
                    flag= true;// Set flag to true to break out of loops.
                    break;
                }
                else if(txt[k] == ' '){
                    res += ' ';// Append space if the character is a space.
                    flag = true;// Set flag to true to break out of loops.
                    break;
                }
                else if(!isalpha(txt[k])){
                    flag= true;
                    break;
                }
            }
            if(flag)break;
        }
    }
    // Check if the result contains only spaces.
    if(all_of(res.begin(),res.end(),::isspace)){
        cout<<"we cipher only text."<<endl;// If the result contains only spaces, print a message indicating that only text is ciphered.
    }
    cout<<res<<endl;// Print the encrypted result.
}

bool check_cipher(string& txt) {
    string valid = "12345 ";// Define valid characters for the encryption key.
    bool flag ;
    for (int i = 0; i < txt.size(); ++i) {
        flag = false;
        for (int j = 0; j < valid.size(); ++j) {
            if (txt[i] == valid[j])flag = true;// Check if each character in the encryption key is valid.
        }
        if(!flag)return false;// If any character is invalid, return false.
    }
    return true;// If all characters are valid, return true.
}


void Polybius_Square_decipher(string& txt){
    vector<int> enc;
    bool flag1=true;
    cout<<"enter the Key:"<<endl;
    // Loop until a valid non-repeated decryption key is entered.
    while(flag1){
        for (int i = 0; i < 5; ++i) {
            int x=get_int();// Get an integer input from the user.
            // Validate the input to be between 1 and 5.
            while(x<=0 || x >5){
                cerr<<"Invalid input please enter a number between 1 and 5"<<endl;
                x=get_int();
            }
            enc.push_back(x);// Add the validated integer to the decryption key.
        }
        flag1= check_repeated(enc);// Check if the decryption key contains repeated
        if(flag1){
            cerr<<"invalid input! start again and enter non repeated integers in the cipher \n";
            enc.clear();// Clear the decryption key vector if it contains repeated integers.
        }
    }
    string res;// String to store the decrypted result.
    bool flag;
    flag= check_cipher(txt);
    while (!flag || txt.empty()){
        cerr<<"invalid input please enter a full integer cipher!\n";
        getline(cin,txt);// Prompt user to enter a valid cipher.
        flag= check_cipher(txt);// Check if the entered text is a valid cipher.
    }
    // Decrypt the text using the Polybius Square cipher decryption algorithm.
    for (int i = 0; i < txt.length()-1; ) {
        int a,b;
        if(txt[i]==' '){
            res+=' ';// Append space if the character is a space.
            i++;// Move to the next character in the input text.
            continue;
        }
        // Match the encryption key indices with the corresponding characters in the Polybius Square.
        for (int j = 0; j < 5; ++j) {
            if(enc[j]==txt[i]-'0')
                a=j;
            if(enc[j]==txt[i+1]-'0')
                b=j;
        }
        res+= letters[a][b];// Append the decrypted character to the result string.
        i+=2;// Move to the next pair of characters in the input text.
    }
    cout<<res<<endl; // Print the decrypted result.
}


class Matrix {
public:
    // Function to generate a route matrix from a given string.
    vector<vector<char>> route_get_matrix(string temp, int rows,int key) {
        // Initialize a matrix with dimensions specified by rows and key, filled with placeholder character 'X'.
        vector<vector<char>> route_matrix(rows, vector<char>(key, 'X'));
        int cnt = 0;
        // Fill the matrix row by row with characters from the given string.
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < key; ++j) {
                if (cnt < temp.length()) {
                    route_matrix[i][j] = temp[cnt];
                    cnt++;// Move to the next character in the string.
                }
            }
        }
        return route_matrix;// Return the generated route matrix.
    }
};

void route_ciphering(vector<vector<char>> route_matrix,int rows,int cols){
    int up=0,bottom=rows-1,right=cols-1,left=0;// Initialize boundary variables.
    string ciphered;// String to store the ciphered text.
    // Traverse the matrix in a clockwise spiral order and append characters to the ciphered string.
    while(left<=right && up<=bottom) {
        if(right==left){// If only one column remains.
            for (int i = up; i <=bottom ; ++i) {
                ciphered += route_matrix[i][right];
            }
            break;
        }
        if(bottom==up){// If only one row remains.
            for (int i = right; i >=left ; --i) {
                ciphered += route_matrix[bottom][i];
            }
            break;
        }

        //add right col
        for (int i = up; i <= bottom; ++i) {
            ciphered += route_matrix[i][right];
        }
        if(right>left)
            right--;
        //add bottom row
        for (int i = right; i >=left ; --i) {
            ciphered += route_matrix[bottom][i];
        }
        if(bottom>up)
            bottom--;
        //add left col
        for (int i = bottom; i >= up ; --i) {
            ciphered += route_matrix[i][left];
        }
        left++;
        //add upper row
        for (int i = left; i <= right; ++i) {
            ciphered += route_matrix[up][i];
        }
        up++;
    }
    cout<<ciphered<<endl;
}

void route_deciphering(string ciphered,int rows,int cols){
    vector<vector<char>> route_matrix(rows,vector<char>(cols));
    int up=0,bottom=rows-1,right=cols-1,left=0;
    int c=0;// Initialize counter for accessing characters in the ciphered string.
    // Traverse the matrix in the same route order as ciphering and fill it with characters from the ciphered string.
    while(left<=right && up<=bottom) {
        if(right==left){
            for (int i = up; i <=bottom ; ++i) {
                route_matrix[i][right]=ciphered[c];
                c++;
            }
            break;
        }
        if(bottom==up){
            for (int i = right; i >=left ; --i) {
                route_matrix[bottom][i]=ciphered[c];
                c++;
            }
            break;
        }

        //add right col
        for (int i = up; i <= bottom; ++i) {
            route_matrix[i][right]=ciphered[c];
            c++;
        }
        if(right>left)
            right--;
        //add bottom row
        for (int i = right; i >=left ; --i) {
            route_matrix[bottom][i]=ciphered[c];
            c++;
        }
        if(bottom>up)
            bottom--;
        //add left col
        for (int i = bottom; i >= up ; --i) {
            route_matrix[i][left]=ciphered[c];
            c++;
        }
        left++;
        //add upper row
        for (int i = left; i <= right; ++i) {
            route_matrix[up][i]=ciphered[c];
            c++;
        }
        up++;
    }
    string deciphered;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            deciphered+=route_matrix[i][j];
        }
    }
    cout<<deciphered<<endl;
}


void route_cipher(string msg,int choice) {
    Matrix m;// Create an instance of the Matrix class.
    cout<<"enter the key\n";
    int key;
    while(!(cin>>key)||key<2 || key>msg.length()/2){
        cout<<"invalid input! please enter an integer greater than two\n and less than the length of the text divided two\n";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');// Clear the input buffer.
        cin.clear();// Clear the failbit from the input stream.
    }
    string original=msg,temp;
    // Convert all alphabetic characters in the original message to uppercase and store them in the temp string.
    for (char c:original) {
        if(isalpha(c)){
            if(islower(c)){
                temp+= toupper(c);
            }
            else{
                temp+=c;
            }
        }
    }
    // Calculate the number of rows needed based on the length of the temp string and the key.
    int row = (temp.length() % key == 0) ? temp.length() / key : temp.length() / key + 1;
    // Get the route matrix based on the temp string, number of rows, and the key.
    vector<vector<char>> matrix = m.route_get_matrix(temp, row,key);
    // Based on user choice, either perform route ciphering or route deciphering.
    if (choice == 1)
		route_ciphering(matrix,row,key);
	else
    	route_deciphering(temp,row,key);
}

int main() {
    cout<<"Welcome to our program!\n----------------------------\n";
    while(true)
    {
        int choice;
        string message;
        cout << "choose what do you want to do today!" << endl;
        cout << "1- Cipher" << endl;
        cout << "2- Decipher" << endl;
        cout << "3- Exit" << endl;
        cout << "-----------------------------" << endl;
        while (!(cin >> choice) or choice < 1 or choice > 3)
        {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Invalid choise" << endl;
        }
        if (choice == 1)
        {
            cout << "Please enter the massage you want to cipher:\n";
            cin.ignore();
            getline(cin,message);
            while(all_of(message.begin(), message.end(), ::isspace))
            {
                cout<<"Invalid input."<<endl;
                getline(cin,message);
            }
            cout << "Which Cipher do you like to choose?\n";
            cout << "1- Rail fence cipher" << endl;
            cout << "2- Polybius Square cipher" << endl;
            cout << "3- Route cipher" << endl;
            while (!(cin >> choice) or choice < 1 or choice > 3)
            {
                cin.clear();
                cin.ignore(999,'\n');
                cout<<"Invalid value."<<endl;
            }
            if (choice == 1)
            {
                Rail_fence_cipher(message);
                cout<<"\n----------------\n";
            }
            else if (choice == 2)
            {
                Polybius_Square_cipher(message);
            }
            else if (choice == 3)
            {
                route_cipher(message,1);
            }
        }
        else if (choice == 2)
        {
            cout << "Please enter the massage you want to decipher:\n";
            cin.ignore();
            getline(cin,message);
            while(all_of(message.begin(), message.end(), ::isspace))
            {
                cout<<"Invalid input."<<endl;
                getline(cin,message);
            }
            cout << "Which decipher do you like to choose?\n";
            cout << "1- Rail_fence cipher" << endl;
            cout << "2- Polybius Square cipher" << endl;
            cout << "3- Route cipher" << endl;
            while (!(cin >> choice or choice < 1 or choice > 3))
            {
                cin.clear();
                cin.ignore(999,'\n');
                cout<<"Invalid value."<<endl;
            }
            if (choice == 1)
            {
                Rail_fence_decipher(message);
                cout<<"\n----------------\n";
            }
            else if (choice == 2)
            {
                Polybius_Square_decipher(message);
                cout<<"\n----------------\n";
            }
            else if (choice == 3)
            {
                route_cipher(message,2);
            }
        }
        else if (choice == 3)
        {
            cout<<"Thanks for using our program.";
            break;
        }
    }
}