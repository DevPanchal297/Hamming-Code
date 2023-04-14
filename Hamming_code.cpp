#include <bits/stdc++.h>
using namespace std;
string decode_msg(string msg)
{
    int n = msg.size();
    reverse(msg.begin(), msg.end());
    string org_msg = "";
    int j = 1;
    for (int i = 0; i < (n); i++)
    {
        if (i + 1 == j)
        {
            j *= 2;
            continue;
        }
        else
        {
            org_msg += msg[i];
        }
    }
    reverse(org_msg.begin(), org_msg.end());
    return org_msg;
}
int check_msg(string msg)
{
    int n = msg.size();
    int r = log2(n) + 1;
    reverse(msg.begin(), msg.end());
    vector<int> hamming_code(n, 0);
    int j = 1;
    int k = 0;
    for (int i = 0; i < (n); i++)
    {
        hamming_code[i] = msg[i] - '0';
    }
    vector<int> count(r, 0);
    for (int i = 1, k = 0; i <= (n); i *= 2, k++)
    {
        for (int j = 1; j <= (n); j++)
        {
            if ((j & i) == i)
            {
                if (hamming_code[j - 1] != -1)
                    count[k] += hamming_code[j - 1];
            }
        }
    }
    for (int i = 0; i < r; i++)
    {
        count[i] %= 2;
    }
    int error_bit = 0;
    for (int i = 1, j = 0; i <= (n); i *= 2, j++)
    {
        if (count[j])
            error_bit += i;
    }
    return error_bit;
}
string encode_msg(string msg)
{
    int n = msg.size();
    int r = 1;
    while (((int)pow(2, r)) < (n + r + 1))
    {
        r++;
    }
    reverse(msg.begin(), msg.end());
    vector<int> hamming_code(n + r, 0);
    int j = 1;
    int k = 0;
    for (int i = 0; i < (n + r); i++)
    {
        if (i + 1 == j)
        {
            j *= 2;
            continue;
        }
        else
        {
            hamming_code[i] = msg[k] - '0';
            k++;
        }
    }
    vector<int> count(r);
    for (int i = 1, k = 0; i <= (n + r); i *= 2, k++)
    {
        for (int j = 1; j <= (n + r); j++)
        {
            if ((j & i) == i)
            {
                if (hamming_code[j - 1] != -1)
                    count[k] += hamming_code[j - 1];
            }
        }
    }
    for (int i = 0; i < r; i++)
    {
        count[i] %= 2;
    }
    for (int i = 1, j = 0; i <= (n + r); i *= 2)
    {
        hamming_code[i - 1] = count[j];
        j++;
    }
    reverse(hamming_code.begin(), hamming_code.end());
    string encoded_msg = "";
    for (auto x : hamming_code)
    {
        encoded_msg += (char)(x + '0');
    }
    return encoded_msg;
}
void hammingCode()
{
    string msg;
    cout << "Enter the msg sent :- ";
    cin >> msg;
    string hamming_code = encode_msg(msg);
    cout << "msg encoded and sent :- " << hamming_code << "\n";
    cout << "Enter the msg received :- ";
    string msg_receive;
    cin >> msg_receive;
    int error_bit = check_msg(msg_receive);
    if (error_bit == 0)
    {
        cout << "System :- No data lost while data transmission.\n";
    }
    else
    {
        reverse(msg_receive.begin(), msg_receive.end());
        int terror_bit = msg_receive.size() - error_bit + 1;
 cout<<"System :- Data is modified while transmission. [ Error at bit position :- "<<terror_bit<<"]\n";
 cout<<"System :- Retrieving the data.\n";
 error_bit--;
 msg_receive[error_bit] = (msg_receive[error_bit] == '0' ? '1' : '0');
 reverse(msg_receive.begin(), msg_receive.end());
    }
    cout << "System :- Decoding the msg for the receiver.\n";
    string final_msg = decode_msg(msg_receive);
    cout << "org msg sent by sender :- " << final_msg << "\n";
}
int main()
{
    hammingCode();
    return 0;
}