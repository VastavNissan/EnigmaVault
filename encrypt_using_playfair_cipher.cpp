/*
 * C++ Program to Encode a Message Using Playfair Cipher
 */
#include <iostream>
#include <vector>
using namespace std;

void get_pos(char, int &, int &);
void same_row(int, vector<char> &, int, int);
void same_column(int, vector<char> &, int, int);
void diff_col_row(int, int, vector<char> &, int, int);
void encode(vector<char>, int);
void get_input(vector<char> &);
void convert_string(vector<char> &, vector<char> &);

const char encoder[5][5] = {{'A', 'B', 'C', 'D', 'E'},
                            {'F', 'G', 'H', 'I', 'K'},
                            {'L', 'M', 'N', 'O', 'P'},
                            {'Q', 'R', 'S', 'T', 'U'},
                            {'V', 'W', 'X', 'Y', 'Z'}};

void get_pos(char p, int &r, int &c)
{
    if (p < 'J')
    {
        r = (p - 65) / 5;
        c = (p - 65) % 5;
    }
    else if (p > 'J')
    {
        r = (p - 66) / 5;
        c = (p - 66) % 5;
    }
    return;
}

void same_row(int r, vector<char> &code, int c1, int c2)
{
    code.push_back(encoder[r][(c1 + 1) % 5]);
    code.push_back(encoder[r][(c2 + 1) % 5]);
    return;
}

void same_column(int c, vector<char> &code, int r1, int r2)
{
    code.push_back(encoder[(r1 + 1) % 5][c]);
    code.push_back(encoder[(r2 + 1) % 5][c]);
    return;
}

void diff_col_row(int r1, int c1, vector<char> &code, int r2, int c2)
{
    code.push_back(encoder[r1][c2]);
    code.push_back(encoder[r2][c1]);
    return;
}

void encode(vector<char> msgx, int len)
{
    vector<char> code;
    int i = 0, j = 0;
    int r1, c1, r2, c2;
    while (i < len)
    {
        get_pos(msgx[i], r1, c1);
        i++;
        get_pos(msgx[i], r2, c2);
        if (r1 == r2)
        {
            same_row(r1, code, c1, c2);
        }
        else if (c1 == c2)
        {
            same_column(c1, code, r1, r2);
        }
        else
        {
            diff_col_row(r1, c1, code, r2, c2);
        }
        i++;
    }
    cout << "\nCODE: ";
    for (j = 0; j < code.size(); j++)
    {
        cout << code[j];
    }
    return;
}

void get_input(vector<char> &a)
{
    char c;
    while (1)
    {
        c = getchar();
        if (c >= 97 && c <= 122)
            c -= 32;
        if (c == '\n')
            break;
        else if (c == ' ')
            continue;
        else if (c == 'J')
            a.push_back('I');
        a.push_back(c);
    }
    return;
}

void convert_string(vector<char> &msg, vector<char> &msgx)
{
    int i, j;
    i = j = 0;
    while (i < msg.size())
    {
        msgx.push_back(msg[i]);
        i++;
        if (i == msg.size())
        {
            msgx.push_back('X');
            break;
        }
        if (msg[i] == msgx[j])
        {
            msgx.push_back('X');
            j++;
        }
        else if (msg[i] != msgx[j])
        {
            j++;
            msgx.push_back(msg[i]);
            i += 1;
        }
        j++;
    }
}

int main()
{
    vector<char> msg;
    vector<char> msgx;
    int i, j;
    cout << "Enter Message to Encrypt:";
    get_input(msg);
    convert_string(msg, msgx);
    int len = msgx.size();
    /*
    cout<<"\n\n";
    for (i = 0;i < len;i++)
    cout<<msgx[i];
    */
    // this is the string after making pairs of 2
    encode(msgx, len);

    return 0;
}