#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void out_vec(vector<int> vec_1)
{
    int n = vec_1.size();
    for(int i = 0; i < n; i++)
    {
        cout << vec_1[i];
    }
    cout << endl;
}

/*Funkce pro kontrolu jestli vstupní string je opravdu číslo*/
bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while(it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/*Funkce pro převedení obou vektorů na stejnou délku aby se s nima dalo pěkně pracovat*/
vector<int> simv(vector<int> vec_1, vector<int> vec_2)
{
    int s1, s2;
    s1 = vec_1.size();
    s2 = vec_2.size();
    if(s1 > s2)
    {
        vector<int>::iterator it;
        for(int i = s2; i < s1; i++)
        {
            it = vec_2.begin(); // nevím jestli je tohle nejlepší řešení ale funguje
            vec_2.insert(it, 0);
        }
        return vec_2;
    }
    else if(s2 > s1)
    {
        vector<int>::iterator it;
        for(int i = s1; i < s2; i++)
        {
            it = vec_1.begin();
            vec_1.insert(it, 0);
        }
        return vec_1;
    }
}

/*Funkce pro sčítání "pod sebou"*/
vector<int> addv(vector<int> vec_1, vector<int> vec_2)
{
    int ast1 = 0, ast2 = 0, ast3 = 0, carry = 0;
    int n = vec_1.size();
    vector<int> res;
    for(int i = n; i > 0; i--)
    {
        ast1 = vec_1[i-1];
        ast2 = vec_2[i-1];
        ast3 = ast1 + ast2 + carry;
        if(ast3 >= 10)
        {
            carry = 1;
            ast3 -= 10;
        }else carry = 0;
        res.push_back(ast3);
    }
    if(carry>0) res.push_back(carry);
    return res;
}

/*Funkce pro odčítání "pod sebou"*/
vector<int> subv(vector<int> vec_1, vector<int> vec_2)
{
    int ast1 = 0, ast2 = 0, ast3 = 0, carry = 0;
    int n = vec_1.size();
    vector<int> res;
    for(int i = n; i > 0; i--)
    {
        ast1 = vec_1[i-1];
        ast2 = vec_2[i-1];
        if(ast2 > ast1)
        {
            ast1 += 10;
            ast3 = ast1 - (ast2 + carry);
            carry = 1;
        }else
        {
            ast3 = ast1 - (ast2 + carry);
            carry = 0;
        }
        res.push_back(ast3);
    }
    return res;
}

int main()
{
    string in_1, in_2;
    vector<int> addvec, subvec, multvec;

    cout << "Zadejte prvni cislo: ";
    cin >> in_1;

    cout << "Zadejte druhe cislo: ";
    cin >> in_2;

    if(is_number(in_1) == false || (is_number(in_2) == false))
    {
        cout << "CHYBA VE VSTUPU: Zadany vstup neni cislo." << endl;
        return 1;
    }

    vector<char> vec__1(in_1.begin(), in_1.end());
    vector<char> vec__2(in_2.begin(), in_2.end());

    vector<int> vec_1(vec__1.begin(), vec__1.end());
    vector<int> vec_2(vec__2.begin(), vec__2.end());

    for(auto& i: vec_1) i -= '0';
    for(auto& i: vec_2) i -= '0';

    /*Pokus o vymazání vektorů z paměťi*/
    vec__1.clear();
    vec__2.clear();
    vec__1.shrink_to_fit();
    vec__2.shrink_to_fit();

    out_vec(vec_1);
    out_vec(vec_2); //Vypíšu oba vektory

    if(vec_2.size() < vec_1.size())
    {
        vec_2 = simv(vec_1, vec_2);
    }
    else if(vec_1.size() < vec_2.size()) vec_1 = simv(vec_1, vec_2);

    cout << "------\n";
    addvec = addv(vec_1, vec_2); //Sečtu je
    out_vec(addvec);

    cout << "------\n";
    subvec = subv(vec_1, vec_2); //Odečtu je
    out_vec(subvec);
    //POZNÁMKA: Odčítání nefunguje správně když se odečítá větší číslo od menšího

    return 0;
}
